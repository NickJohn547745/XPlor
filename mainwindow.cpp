#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    mTypeMap = QMap<ASSET_TYPE, int>();
    mTypeOrder = QStringList();
    mRawFileMap = QMap<QString, QString>();
    mTreeMap = QMap<QString, QTreeWidgetItem*>();
    mStrTableMap = QMap<QString, QVector<QPair<QString, QString>>>();
    mBSPVersion = 0;
    mDiskLumpCount = 0;
    mDiskLumpOrder = QVector<quint32>();
    mLumps = QMap<quint32, Lump>();
    mRecentFiles = QQueue<QString>();
    mSettingsValid = false;
    mRecentFileActions = QVector<QAction*>();

    const QString appSettingsPath = QDir::currentPath() + "/appSettings.ini";
    QSettings appSettings(appSettingsPath, QSettings::IniFormat);
    if (appSettings.contains("mRecentFiles")) {
        mSettingsValid = true;

        QStringList recentFiles = appSettings.value("mRecentFiles").toStringList();
        foreach (QString recentFile, recentFiles) {
            mRecentFiles.enqueue(recentFile);
        }
    }

    connect(ui->treeWidget_Scripts, &QTreeWidget::itemSelectionChanged, this, &MainWindow::ScriptSelected);
    connect(ui->comboBox_StringTable, &QComboBox::currentTextChanged, this, &MainWindow::StrTableSelected);

    // Initialize Asset Index Table
    ui->tableWidget_Index->setColumnCount(2);
    ui->tableWidget_Index->setHorizontalHeaderLabels({"Asset Name", "Asset Count"});
    ui->tableWidget_Index->verticalHeader()->setVisible(false);
    ui->tableWidget_Index->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_Index->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_Index->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_Index->setShowGrid(false);
    ui->tableWidget_Index->setStyleSheet("QTableView {selection-background-color: red;}");

    // Initialize Asset Order Table
    ui->tableWidget_Order->setColumnCount(2);
    ui->tableWidget_Order->setHorizontalHeaderLabels({"Asset Name", "Asset Count"});
    ui->tableWidget_Order->verticalHeader()->setVisible(false);
    ui->tableWidget_Order->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_Order->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_Order->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_Order->setShowGrid(false);
    ui->tableWidget_Order->setStyleSheet("QTableView {selection-background-color: red;}");

    // Initialize Menu table
    ui->treeWidget_Menus->setHeaderLabels({"Components", "Description"});
    ui->treeWidget_Menus->setColumnWidth(0, width() / 4 * 3); // Name column

    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

    QWidget *container = QWidget::createWindowContainer(view);
    QSize screenSize = view->screen()->size();
    container->setMinimumSize(QSize(200, 100));
    container->setMaximumSize(screenSize);

    QHBoxLayout *hLayout = new QHBoxLayout(ui->frame_Scene);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignTop);
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);

    // Root entity
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

    // Camera
    Qt3DRender::QCamera *cameraEntity = view->camera();

    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(0, 0, 50.0f)); // Move farther along Z-axis
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);

    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    lightEntity->addComponent(lightTransform);

    // For camera controls
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
    camController->setCamera(cameraEntity);

    // Set root object of the scene
    view->setRootEntity(rootEntity);

    // Load custom 3D model
    Qt3DRender::QMesh *customMesh = new Qt3DRender::QMesh();
    customMesh->setSource(QUrl::fromLocalFile(":/obj/data/obj/defaultactor_LOD0.obj"));

    // Adjust the model transformation
    Qt3DCore::QTransform *customTransform = new Qt3DCore::QTransform();
    customTransform->setRotationX(-90);
    customTransform->setRotationY(-90);

    // Keep translation if necessary
    customTransform->setTranslation(QVector3D(0.0f, -100.0f, -200.0f));

    Qt3DExtras::QNormalDiffuseMapMaterial *customMaterial = new Qt3DExtras::QNormalDiffuseMapMaterial();

    Qt3DRender::QTextureLoader *normalMap = new Qt3DRender::QTextureLoader();
    normalMap->setSource(QUrl::fromLocalFile(":/obj/data/obj/normalmap.png"));
    customMaterial->setNormal(normalMap);

    Qt3DRender::QTextureLoader *diffuseMap = new Qt3DRender::QTextureLoader();
    diffuseMap->setSource(QUrl::fromLocalFile(":/obj/data/obj/diffusemap.png"));
    customMaterial->setDiffuse(diffuseMap);

    Qt3DCore::QEntity *m_torusEntity = new Qt3DCore::QEntity(rootEntity);
    m_torusEntity->addComponent(customMesh);
    m_torusEntity->addComponent(customMaterial);
    m_torusEntity->addComponent(customTransform);

    LoadFile_D3DBSP(":/d3dbsp/data/d3dbsp/barebones.d3dbsp");

    Reset();
}

MainWindow::~MainWindow() {
    const QString appSettingsPath = QDir::currentPath() + "/appSettings.ini";
    QSettings appSettings(appSettingsPath, QSettings::IniFormat);
    appSettings.setValue("mRecentFiles", mRecentFiles.toList());

    delete ui;
}

void MainWindow::Reset() {
    // Reset tabwidget to 'General' tab
    ui->tabWidget->setCurrentIndex(0);

    // Reset 'General' tab fields
    ui->lineEdit_FastFile->clear();
    ui->comboBox_Company->setCurrentIndex(0);
    ui->comboBox_FileType->setCurrentIndex(0);
    ui->checkBox_Signed->setChecked(false);
    ui->lineEdit_Magic->clear();
    ui->spinBox_Magic->clear();
    ui->spinBox_TagCount->clear();
    ui->spinBox_FileSize->clear();
    ui->spinBox_RecordCount->clear();

    // Reset 'Unknowns' tab fields
    ui->lineEdit_U1->clear();
    ui->spinBox_U1->clear();
    ui->lineEdit_U2->clear();
    ui->spinBox_U2->clear();
    ui->lineEdit_U3->clear();
    ui->spinBox_U3->clear();
    ui->lineEdit_U4->clear();
    ui->spinBox_U4->clear();
    ui->lineEdit_U5->clear();
    ui->spinBox_U5->clear();
    ui->lineEdit_U6->clear();
    ui->spinBox_U6->clear();
    ui->lineEdit_U7->clear();
    ui->spinBox_U7->clear();
    ui->lineEdit_U8->clear();
    ui->spinBox_U8->clear();
    ui->lineEdit_U9->clear();
    ui->spinBox_U9->clear();
    ui->lineEdit_U10->clear();
    ui->spinBox_U10->clear();
    ui->lineEdit_U11->clear();
    ui->spinBox_U11->clear();

    // Reset 'Tags' tab fields
    ui->listWidget_Tags->clear();

    // Reset 'Localized Strings' tab fields
    ui->listWidget_LocalString->clear();

    // Reset 'Asset Index/Order' tab fields
    ui->tableWidget_Index->clear();
    ui->tableWidget_Order->clear();

    // Reset 'Raw Files' tab fields
    ui->treeWidget_Scripts->clear();
    ui->plainTextEdit_Scripts->clear();

    // Reset 'Tech Sets' tab fields
    ui->listWidget_TechSets->clear();

    // Reset 'Zone Dump' tab fields
    ui->spinBox_DumpIndex->clear();
    ui->comboBox_DumpAsset->setCurrentIndex(0);
    ui->plainTextEdit_ZoneDump->clear();

    // Reset 'String Tables' tab fields
    ui->comboBox_StringTable->setCurrentIndex(0);
    ui->tableWidget_StringTable->clear();

    // Reset '3D Scene' tab fields
    ui->treeWidget_Models->clear();

    // Reset class vars
    mTypeMap.clear();
    mTypeOrder.clear();
    mTagCount = 0;
    mRecordCount = 0;
    mRawFileMap.clear();
    mTreeMap.clear();
    mStrTableMap.clear();

    // Refresh recent files
    RefreshRecentFileMenu();
}

void MainWindow::StrTableSelected(QString aStrTableName) {
    ui->tableWidget_StringTable->clear();

    ui->tableWidget_StringTable->setColumnCount(2);
    int entryIndex = 0;
    for (auto strTableEntry : mStrTableMap[aStrTableName]) {
        ui->tableWidget_StringTable->insertRow(ui->tableWidget_StringTable->rowCount() + 1);
        ui->tableWidget_StringTable->setItem(entryIndex, 0, new QTableWidgetItem(strTableEntry.first));
        ui->tableWidget_StringTable->setItem(entryIndex, 1, new QTableWidgetItem(strTableEntry.second));

        entryIndex++;
    }
}

void MainWindow::ScriptSelected() {
    QTreeWidgetItem *selectedItem = ui->treeWidget_Scripts->selectedItems()[0];
    if (!selectedItem) {
        qDebug() << "Attempted to load invalid tree item!";
        return;
    }

    const QString itemName = selectedItem->text(0);
    const QStringList scriptExts = {"gsc", "csc", "atr", "shock", "vision", "rmb"};
    if (!scriptExts.contains(itemName.split('.').last())) {
        qDebug() << QString("Attempted to parse invalid raw file: %1!").arg(itemName);
        return;
    }

    ui->plainTextEdit_Scripts->clear();
    for (auto [scriptName, scriptContents] : mRawFileMap.asKeyValueRange()) {
        if (scriptName.contains(itemName)) {
            ui->plainTextEdit_Scripts->setPlainText(scriptContents);
            return;
        }
    }
}

QByteArray MainWindow::DecompressZLIB(QByteArray compressedData) {
    QByteArray decompressedData;
    uLongf decompressedSize = compressedData.size() * 4;
    decompressedData.resize(static_cast<int>(decompressedSize));

    Bytef *destination = reinterpret_cast<Bytef*>(decompressedData.data());
    uLongf *destLen = &decompressedSize;
    const Bytef *source = reinterpret_cast<const Bytef*>(compressedData.data());
    uLong sourceLen = compressedData.size();

    int result = uncompress(destination, destLen, source, sourceLen);

    if (result == Z_OK) {
        decompressedData.resize(static_cast<int>(decompressedSize));
    } else {
        decompressedData.clear();
        qDebug() << QString("In DecompressZLIB: %1").arg(Utils::ZLibErrorToString(result)).toLatin1();
    }
    return decompressedData;
}

/*
    GetFastFilePath()

    Opens a file dialog in the steam folder,
    and opens the selected file.
*/
QString MainWindow::GetFastFilePath() {
    // Reset dialog before opening new file
    Reset();

    // Open file dialog to steam apps
    const QString steamPath = "C:/Program Files (x86)/Steam/steamapps/common/Call of Duty World at War/zone/english/";
    const QString fastFilePath = QFileDialog::getOpenFileName(this, "Open FastFile", steamPath, "FastFile (*.ff);;All Files (*.*)");
    if (!QFile::exists(fastFilePath)) {
        QMessageBox::warning(this, "Warning!", QString("%1 does not exist!.").arg(fastFilePath));
        return nullptr;
    }
    ui->lineEdit_FastFile->setText(fastFilePath);

    const QString fastFileStem = fastFilePath.split('/').last();
    setWindowTitle(QString("FastFile Wizard - %1").arg(fastFileStem));

    return fastFilePath;
}

/*
    GetZoneFilePath()

    Opens a file dialog in the steam folder,
    and opens the selected file.
*/
QString MainWindow::GetZoneFilePath() {
    // Reset dialog before opening new file
    Reset();

    // Open file dialog to steam apps
    const QString steamPath = "C:/Program Files (x86)/Steam/steamapps/common/Call of Duty World at War/zone/english/";
    const QString zoneFilePath = QFileDialog::getOpenFileName(this, "Open ZoneFile", steamPath, "ZoneFile (*.zone);;All Files (*.*)");
    if (!QFile::exists(zoneFilePath)) {
        QMessageBox::warning(this, "Warning!", QString("%1 does not exist!.").arg(zoneFilePath));
        return nullptr;
    }
    ui->lineEdit_ZoneFile->setText(zoneFilePath);

    const QString zoneFileStem = zoneFilePath.split('/').last();
    setWindowTitle(QString("FastFile Wizard - %1").arg(zoneFileStem));

    return zoneFilePath;
}

QByteArray MainWindow::OpenFastFile(QString aFastFilePath)
{
    Reset();

    // Check fastfile can be read
    QFile *fastFile = new QFile(aFastFilePath);
    qDebug() << aFastFilePath;
    if (!fastFile->open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Warning!", QString("FastFile '%1' could not be read!.").arg(fastFile->fileName()));
        return QByteArray();
    }
    LogOpenedFile(fastFile->fileName());
    ui->lineEdit_FastFile->setText(fastFile->fileName());

    // Decompress fastfile and close
    const QByteArray fastFileData = fastFile->readAll();

    // Parse data from fast file header
    ParseFFHeader(fastFileData.mid(0, 12));

    fastFile->close();

    // Decompress fastfile and close
    const QByteArray decompressedData = DecompressZLIB(fastFileData.mid(12));
    // ui->plainTextEdit_ZoneDump->setPlainText(decompressedData.toHex());

    const QString zoneFilePath = aFastFilePath.replace(".ff", ".zone");
    ui->lineEdit_ZoneFile->setText(zoneFilePath);

    // Open zone file
    OpenZoneFile(zoneFilePath);

    // Clean up & return
    delete fastFile;
    return fastFileData;
}

QByteArray MainWindow::OpenZoneFile(QString aZoneFilePath)
{
    Reset();

    // Check zone file is writeable
    QFile *zoneFile = new QFile(aZoneFilePath);
    if (!zoneFile->open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Warning!", QString("ZoneFile '%1' could not be read!.").arg(zoneFile->fileName()));
        return QByteArray();
    }
    LogOpenedFile(zoneFile->fileName());
    ui->lineEdit_ZoneFile->setText(zoneFile->fileName());

    // Parse & close zone file
    QByteArray zoneFileData = zoneFile->readAll();
    ParseZoneFile(zoneFileData);
    zoneFile->close();

    // Check if corresponding zone file exists
    const QString fastFilePath = zoneFile->fileName().replace(".zone", ".ff");
    if (QFile::exists(fastFilePath)) {
        ui->lineEdit_FastFile->setText(fastFilePath);
        LogOpenedFile(fastFilePath);
    }

    // Clean up & return
    delete zoneFile;
    return zoneFileData;
}

void MainWindow::ParseFFCompany(QDataStream *afastFileStream) {
    // Check for null datastream ptr
    if (!afastFileStream) { return; }
    // Parse company
    QByteArray companyData(2, Qt::Uninitialized);
    afastFileStream->readRawData(companyData.data(), 2);
    if (companyData == "IW") {
        qDebug() << "Company found: 'INFINITY_WARD'";
        ui->comboBox_Company->setCurrentIndex(1);
    } else if (companyData == "TA") {
        qDebug() << "Company found: 'TREYARCH'";
        ui->comboBox_Company->setCurrentIndex(2);
    } else if (companyData == "Sl") {
        qDebug() << "Company found: 'SLEDGEHAMMER'";
        ui->comboBox_Company->setCurrentIndex(3);
    } else if (companyData == "NX") {
        qDebug() << "Company found: 'NEVERSOFT'";
        ui->comboBox_Company->setCurrentIndex(4);
    } else {
        qDebug() << QString("Failed to find company, found '%1'!").arg(companyData);
        return;
    }
}

void MainWindow::ParseFFFileType(QDataStream *afastFileStream) {
    // Parse filetype
    QByteArray fileTypeData(2, Qt::Uninitialized);
    afastFileStream->readRawData(fileTypeData.data(), 2);
    if (fileTypeData == "ff") {
        qDebug() << "File type found: 'FAST_FILE'";
        ui->comboBox_FileType->setCurrentIndex(1);
    } else {
        qDebug() << "Failed to find file type!";
        return;
    }
}

void MainWindow::ParseFFSignage(QDataStream *afastFileStream) {
    // Parse filetype
    QByteArray signedData(1, Qt::Uninitialized);
    afastFileStream->readRawData(signedData.data(), 1);
    if (signedData == "u") {
        qDebug() << "Found valid signage: Unsigned";
        ui->checkBox_Signed->setChecked(false);
    } else if (signedData == "0") {
        qDebug() << "Found valid signage: Signed";
        ui->checkBox_Signed->setChecked(true);
    } else {
        qDebug() << "Failed to determine signage of fastfile!";
        return;
    }
}

void MainWindow::ParseFFMagic(QDataStream *afastFileStream) {
    // Parse magic
    QByteArray magicData(3, Qt::Uninitialized);
    afastFileStream->readRawData(magicData.data(), 3);
    if (magicData == "100") {
        qDebug() << QString("Found valid magic: '%1'").arg(magicData);
        ui->lineEdit_Magic->setText(magicData.toHex());
        ui->spinBox_Magic->setValue(magicData.toInt());
    } else {
        qDebug() << "Magic invalid!";
        return;
    }
}

void MainWindow::ParseFFVersion(QDataStream *afastFileStream) {
    // Parse version
    quint32 version;
    *afastFileStream >> version;
    qDebug() << "Version:" << version;
    if (version == 387) {
        qDebug() << QString("Found valid version: '%1'").arg(version);
        ui->spinBox_Version->setValue(version);
    } else {
        qDebug() << "Version invalid!";
        return;
    }
}

void MainWindow::ParseFFHeader(QByteArray aFastFileData) {
    // Open stream to fastfile
    QDataStream afastFileStream(aFastFileData);
    afastFileStream.setByteOrder(QDataStream::LittleEndian);

    ParseFFCompany(&afastFileStream);
    ParseFFFileType(&afastFileStream);
    ParseFFSignage(&afastFileStream);
    ParseFFMagic(&afastFileStream);
    ParseFFVersion(&afastFileStream);
}

void MainWindow::ParseAsset_Localize(QDataStream *aZoneFileStream) {
    Localize localize;
    *aZoneFileStream >> localize;

    ui->listWidget_LocalString->addItem(QString("%1 = %2").arg(localize.referenceStr).arg(localize.localizedStr));
}

void MainWindow::ParseAsset_RawFile(QDataStream *aZoneFileStream) {
    RawFile rawFile;
    *aZoneFileStream >> rawFile;

    QString rawFilePath = rawFile.rawFilePath;
    rawFilePath.replace(",", "");
    const QStringList pathParts = rawFilePath.split('/');
    if (pathParts.size() == 0) {
        qDebug() << "Failed to parse ff path! " << rawFilePath;
        exit(-1);
    } else if (pathParts.size() == 1) {
        const QString path = pathParts[0];
        QTreeWidgetItem *newRootItem = new QTreeWidgetItem(ui->treeWidget_Scripts);
        newRootItem->setText(0, path);
    } else {
        const QString path = pathParts[0];
        QTreeWidgetItem *newRootItem;
        if (mTreeMap.contains(path)) {
            newRootItem = mTreeMap[path];
        } else {
            newRootItem = new QTreeWidgetItem(ui->treeWidget_Scripts);
            newRootItem->setText(0, path);
            mTreeMap[path] = newRootItem;
        }

        QTreeWidgetItem *parentItem = newRootItem;
        for (int i = 1; i < pathParts.size(); i++) {
            const QString path = pathParts[i];
            QTreeWidgetItem *newChildItem;
            if (mTreeMap.contains(path)) {
                newChildItem = mTreeMap[path];
            } else {
                newChildItem = new QTreeWidgetItem();
                newChildItem->setText(0, path);
                mTreeMap[path] = newChildItem;
            }
            parentItem->addChild(newChildItem);
            parentItem = newChildItem;
        }
    }
    mRawFileMap[rawFilePath] = (rawFile.rawFileContents.isEmpty()) ? ("EMPTY") : (rawFile.rawFileContents);
}

void MainWindow::ParseAsset_XModel(QDataStream *aZoneFileStream) {

}

void MainWindow::ParseAsset_Material(QDataStream *aZoneFileStream) {

}

void MainWindow::ParseAsset_PixelShader(QDataStream *aZoneFileStream) {

}

void MainWindow::ParseAsset_TechSet(QDataStream *aZoneFileStream) {
    aZoneFileStream->skipRawData(4);
    // Parse techset name
    QString techSetName;
    char techSetNameChar;
    *aZoneFileStream >> techSetNameChar;
    while (techSetNameChar == 0) {
        *aZoneFileStream >> techSetNameChar;
    }
    while (techSetNameChar != 0) {
        techSetName += techSetNameChar;
        *aZoneFileStream >> techSetNameChar;
    }
    techSetName.replace(",", "");
    ui->listWidget_TechSets->addItem(techSetName);
    //qDebug() << "Tech Set: " << techSetName;
}

void MainWindow::ParseAsset_LoadedSound(QDataStream *aZoneFileStream) {

}

void MainWindow::ParseAsset_ColMapMP(QDataStream *aZoneFileStream) {

}

void MainWindow::ParseAsset_FX(QDataStream *aZoneFileStream) {

}

void MainWindow::ParseAsset_Font(QDataStream *aZoneFileStream) {

}

void MainWindow::ParseAsset_XAnim(QDataStream *aZoneFileStream) {
    // Read in pointer to x_anim name
    QByteArray namePtr(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(namePtr.data(), 4);

    // Read in counts
    quint16 dataByteCount, dataShortCount,
        dataIntCount, randomDataByteCount,
        randomDataIntCount, numframes;
    *aZoneFileStream >> dataByteCount >> dataShortCount >>
        dataIntCount >> randomDataByteCount >>
        randomDataIntCount >> numframes;

    // Read bool flags
    bool isLooped, isDelta;
    *aZoneFileStream >> isLooped >> isDelta;

    // Read in more counts
    quint8 noneRotatedBoneCount,
        twoDRotatedBoneCount, normalRotatedBoneCount,
        twoDStaticRotatedBoneCount, normalStaticRotatedBoneCount,
        normalTranslatedBoneCount, preciseTranslatedBoneCount,
        staticTranslatedBoneCount, noneTranslatedBoneCount,
        totalBoneCount, otherBoneCount1, otherBoneCount2;
    *aZoneFileStream >> noneRotatedBoneCount >>
        twoDRotatedBoneCount >> normalRotatedBoneCount >>
        twoDStaticRotatedBoneCount >> normalStaticRotatedBoneCount >>
        normalTranslatedBoneCount >> preciseTranslatedBoneCount >>
        staticTranslatedBoneCount >> noneTranslatedBoneCount >>
        totalBoneCount >> otherBoneCount1 >> otherBoneCount2;

    // Yet more counts
    quint8 notifyCount, assetType;
    *aZoneFileStream >> notifyCount >> assetType;

    // Read more bool flags
    bool pad;
    *aZoneFileStream >> pad;

    // Yet more more counts
    unsigned int randomDataShortCount, indexCount;
    *aZoneFileStream >> randomDataShortCount >> indexCount;

    // Read in floats
    float frameRate, frequency;
    *aZoneFileStream >> frameRate >> frequency;

    // Read in pointers
    quint32 boneIDsPtr, dataBytePtr, dataShortPtr, dataIntPtr,
        randomDataShortPtr, randomDataBytePtr, randomDataIntPtr,
        longIndiciesPtr, notificationsPtr, deltaPartsPtr;
    *aZoneFileStream >> boneIDsPtr >> dataBytePtr >> dataShortPtr
        >> dataIntPtr >> randomDataShortPtr >> randomDataBytePtr
        >> randomDataIntPtr >> longIndiciesPtr >> notificationsPtr
        >> deltaPartsPtr;

    // Read in x_anim file name
    QString xAnimName;
    char xAnimNameChar;
    *aZoneFileStream >> xAnimNameChar;
    while (xAnimNameChar != 0) {
        xAnimName += xAnimNameChar;
        *aZoneFileStream >> xAnimNameChar;
    }

    // Parse x_anim index header
    QVector<quint8> sectionLengths;
    for (int i = 0; i < numframes; i++) {
        quint8 sectionlength;
        *aZoneFileStream >> sectionlength;
        sectionLengths.push_back(sectionlength);
        // Skip padding
        aZoneFileStream->skipRawData(1);
    }
    // Skip unknown section
    aZoneFileStream->skipRawData(2 * 8);
}

void MainWindow::ParseAsset_MenuFile(QDataStream *aZoneFileStream) {
    //MENU_FILE
    aZoneFileStream->skipRawData(4); // Separator

    // Parse menu def count
    quint32 menuDefCount;
    *aZoneFileStream >> menuDefCount;

    if (menuDefCount > 1000) { return; }
    for (int i = 0; i < menuDefCount; i++) {
        aZoneFileStream->skipRawData(4); // Separator

        // Read in x_anim file name
        QString menuFilepath;
        char menuFilepathChar;
        *aZoneFileStream >> menuFilepathChar;
        while (menuFilepathChar != 0) {
            menuFilepath += menuFilepathChar;
            *aZoneFileStream >> menuFilepathChar;
        }
        qDebug() << "Parsing " << menuFilepath;

        QTreeWidgetItem *menuFilePathNode = new QTreeWidgetItem(ui->treeWidget_Menus);

        aZoneFileStream->skipRawData(4); // Separator

        QByteArray menuNamePtr(4, Qt::Uninitialized);
        aZoneFileStream->readRawData(menuNamePtr.data(), 4);
        QTreeWidgetItem *menuNamePtrNode = new QTreeWidgetItem(menuFilePathNode);
        menuNamePtrNode->setText(0, QString("Menu name ptr: %1").arg(menuNamePtr.toHex().toUpper()));

        QTreeWidgetItem *menuRectNode = new QTreeWidgetItem(menuFilePathNode);
        menuRectNode->setText(0, "Menu Rect");

        float menuRectX, menuRectY, menuRectWidth, menuRectHeight;
        *aZoneFileStream >> menuRectX >> menuRectY >> menuRectWidth >> menuRectHeight;
        QTreeWidgetItem *menuRectXNode = new QTreeWidgetItem(menuRectNode);
        menuRectXNode->setText(0, QString("X: %1").arg(menuRectX));
        QTreeWidgetItem *menuRectYNode = new QTreeWidgetItem(menuRectNode);
        menuRectYNode->setText(0, QString("Y: %1").arg(menuRectY));
        QTreeWidgetItem *menuRectWidthNode = new QTreeWidgetItem(menuRectNode);
        menuRectWidthNode->setText(0, QString("Width: %1").arg(menuRectWidth));
        QTreeWidgetItem *menuRectHeightNode = new QTreeWidgetItem(menuRectNode);
        menuRectHeightNode->setText(0, QString("Height: %1").arg(menuRectHeight));

        MENU_H_ALIGNMENT hAlign;
        *aZoneFileStream >> hAlign;
        QTreeWidgetItem *hAlignNode = new QTreeWidgetItem(menuRectNode);
        QString hAlignStr = Utils::MenuHAlignToStr(hAlign);
        hAlignNode->setText(0, QString("Horiz. Align: %1").arg(hAlignStr));

        MENU_V_ALIGNMENT vAlign;
        *aZoneFileStream >> vAlign;
        QTreeWidgetItem *vAlignNode = new QTreeWidgetItem(menuRectNode);
        QString vAlignStr = Utils::MenuVAlignToStr(vAlign);
        vAlignNode->setText(0, QString("Vert. Align: %1").arg(vAlignStr));

        float rectClientX, rectClientY, rectClientWidth, rectClientHeight;
        *aZoneFileStream >> rectClientX >> rectClientY >> rectClientWidth >> rectClientHeight;
        QTreeWidgetItem *menuRectClientNode = new QTreeWidgetItem(menuFilePathNode);
        menuRectClientNode->setText(0, "Menu Client Rect");
        QTreeWidgetItem *menuRectClientXNode = new QTreeWidgetItem(menuRectClientNode);
        menuRectClientXNode->setText(0, QString("X: %1").arg(rectClientX));
        QTreeWidgetItem *menuRectClientYNode = new QTreeWidgetItem(menuRectClientNode);
        menuRectClientYNode->setText(0, QString("Y: %1").arg(rectClientY));
        QTreeWidgetItem *menuRectClientWidthNode = new QTreeWidgetItem(menuRectClientNode);
        menuRectClientWidthNode->setText(0, QString("Width: %1").arg(rectClientWidth));
        QTreeWidgetItem *menuRectClientHeightNode = new QTreeWidgetItem(menuRectClientNode);
        menuRectClientHeightNode->setText(0, QString("Height: %1").arg(rectClientHeight));

        // Client horizontal alignment
        MENU_H_ALIGNMENT hClientAlign;
        *aZoneFileStream >> hClientAlign;
        QTreeWidgetItem *hClientAlignNode = new QTreeWidgetItem(menuRectClientNode);
        QString hClientAlignStr = Utils::MenuHAlignToStr(hAlign);
        hClientAlignNode->setText(0, QString("Horiz. Align: %1").arg(hClientAlignStr));

        // Client vertical alignment
        MENU_V_ALIGNMENT vClientAlign;
        *aZoneFileStream >> vClientAlign;
        QTreeWidgetItem *vClientAlignNode = new QTreeWidgetItem(menuRectClientNode);
        QString vClientAlignStr = Utils::MenuVAlignToStr(vAlign);
        vClientAlignNode->setText(0, QString("Vert. Align: %1").arg(vClientAlignStr));

        quint32 groupPtr; // Should be const char *
        *aZoneFileStream >> groupPtr;

        MENU_WINDOW_STYLE style;
        *aZoneFileStream >> style;

        MENU_WINDOW_BORDER border;
        *aZoneFileStream >> border;

        quint32 ownerDraw, ownerDrawFlags;
        *aZoneFileStream >> ownerDraw >> ownerDrawFlags;

        float borderSize;
        *aZoneFileStream >> borderSize;

        int staticFlags, dynamicFlags, nextTime;
        *aZoneFileStream >> staticFlags >> dynamicFlags >> nextTime;

        QTreeWidgetItem *colorsNode = new QTreeWidgetItem(menuFilePathNode);
        colorsNode->setText(0, "Menu Colors");

        float foregroundColorR, foregroundColorG, foregroundColorB, foregroundColorA,
            backgroundColorR, backgroundColorG, backgroundColorB, backgroundColorA,
            borderColorR, borderColorG, borderColorB, borderColorA,
            outlineColorR, outlineColorG, outlineColorB, outlineColorA;
        *aZoneFileStream >> foregroundColorR >> foregroundColorG >> foregroundColorB >> foregroundColorA
            >> backgroundColorR >> backgroundColorG >> backgroundColorB >> backgroundColorA
            >> borderColorR >> borderColorG >> borderColorB >> borderColorA
            >> outlineColorR >> outlineColorG >> outlineColorB >> outlineColorA;

        QTreeWidgetItem *foregroundColorNode = new QTreeWidgetItem(colorsNode);
        foregroundColorNode->setText(0, QString("Foreground Color: RGBA(%1, %2, %3, %4)")
                                            .arg(foregroundColorR).arg(foregroundColorG).arg(foregroundColorB).arg(foregroundColorA));
        foregroundColorNode->setBackground(1, Utils::ColorFromNormalized(foregroundColorR, foregroundColorG, foregroundColorB, foregroundColorA));
        QTreeWidgetItem *backgroundColorNode = new QTreeWidgetItem(colorsNode);
        backgroundColorNode->setText(0, QString("Background Color: RGBA(%1, %2, %3, %4)")
                                            .arg(backgroundColorR).arg(backgroundColorG).arg(backgroundColorB).arg(backgroundColorA));
        backgroundColorNode->setBackground(1, Utils::ColorFromNormalized(backgroundColorR, backgroundColorG, backgroundColorB, backgroundColorA));
        QTreeWidgetItem *borderColorNode = new QTreeWidgetItem(colorsNode);
        borderColorNode->setText(0, QString("Borer Color: RGBA(%1, %2, %3, %4)")
                                        .arg(borderColorR).arg(borderColorG).arg(borderColorB).arg(borderColorA));
        borderColorNode->setBackground(1, Utils::ColorFromNormalized(borderColorR, borderColorG, borderColorB, borderColorA));
        QTreeWidgetItem *outlineColorNode = new QTreeWidgetItem(colorsNode);
        outlineColorNode->setText(0, QString("Outline Color: RGBA(%1, %2, %3, %4)")
                                         .arg(outlineColorR).arg(outlineColorG).arg(outlineColorB).arg(outlineColorA));
        outlineColorNode->setBackground(1, Utils::ColorFromNormalized(outlineColorR, outlineColorG, outlineColorB, outlineColorA));

        quint32 materialPtr; // Should be Material *
        *aZoneFileStream >> materialPtr;

        quint32 fontPtr, fullScreen, itemCount, fontIndex;
        *aZoneFileStream >> fontPtr >> fullScreen >> itemCount >> fontIndex;

        quint32 cursorItem, fadeCycle;
        *aZoneFileStream >> cursorItem >> fadeCycle;

        float fadeClamp, fadeAmount, fadeInAmount, blurRadius;
        *aZoneFileStream >> fadeClamp >> fadeAmount >> fadeInAmount >> blurRadius;

        quint32 onOpenPtr, onFocusPtr, onClosePtr, onESCPtr; // Should be const char *
        *aZoneFileStream >> onOpenPtr >> onFocusPtr >> onClosePtr >> onESCPtr;

        quint32 onKeyPtr; // Should be ItemKeyHandler *
        *aZoneFileStream >> onKeyPtr;

        quint32 visibleExpCount, expEntryPtr; // components of statement_s
        *aZoneFileStream >> visibleExpCount >> expEntryPtr;

        quint32 allowedBindingPtr, soundNamePtr; // Should be const char *
        *aZoneFileStream >> allowedBindingPtr >> soundNamePtr;

        quint32 imageTrack;
        *aZoneFileStream >> imageTrack;

        float focusColorR, focusColorG, focusColorB, focusColorA;
        *aZoneFileStream >> focusColorR >> focusColorG >> focusColorB >> focusColorA;
        QTreeWidgetItem *focusColorNode = new QTreeWidgetItem(colorsNode);
        focusColorNode->setText(0, QString("Focus Color: RGBA(%1, %2, %3, %4)")
                                         .arg(focusColorR).arg(focusColorG).arg(focusColorB).arg(focusColorA));
        focusColorNode->setBackground(1, Utils::ColorFromNormalized(focusColorR, focusColorG, focusColorB, focusColorA));

        //QTreeWidgetItem *menuDefChildNode = new QTreeWidgetItem(menuDefNode);
        //menuDefChildNode->setText(0, menuDefName);

        float disabledColorR, disabledColorG, disabledColorB, disabledColorA;
        *aZoneFileStream >> disabledColorR >> disabledColorG >> disabledColorB >> disabledColorA;
        QTreeWidgetItem *disabledColorNode = new QTreeWidgetItem(colorsNode);
        disabledColorNode->setText(0, QString("Disabled Color: RGBA(%1, %2, %3, %4)")
                                         .arg(disabledColorR).arg(disabledColorG).arg(disabledColorB).arg(disabledColorA));
        disabledColorNode->setBackground(1, Utils::ColorFromNormalized(disabledColorR, disabledColorG, disabledColorB, disabledColorA));

        quint32 rectXExpCount, rectXExpPtr; // components of statement_s
        *aZoneFileStream >> rectXExpCount >> rectXExpPtr;

        quint32 rectYExpCount, rectYExpPtr; // components of statement_s
        *aZoneFileStream >> rectYExpCount >> rectYExpPtr;

        aZoneFileStream->skipRawData(4); // Separator

        QString menuDefName;
        char menuDefNameChar;
        int menuDefNameLen = 0;
        *aZoneFileStream >> menuDefNameChar;
        while (menuDefNameChar != 0 && menuDefNameLen < 30) {
            menuDefNameLen++;
            menuDefName += menuDefNameChar;
            *aZoneFileStream >> menuDefNameChar;
        }

        menuFilePathNode->setText(0, QString("%1 - %2").arg(menuDefName).arg(menuFilepath));

        QString defString;
        char defStringChar;
        int defStringLen = 0;
        *aZoneFileStream >> defStringChar;
        while (defStringChar != 0 && defStringLen < 30) {
            defStringLen++;
            defString += defStringChar;
            *aZoneFileStream >> defStringChar;
        }
        aZoneFileStream->skipRawData(4 * 10);


        QTreeWidgetItem *itemsNode = new QTreeWidgetItem(menuFilePathNode);
        itemsNode->setText(0, "Item Definitions");

        quint32 itemWindowDefNamePtr;
        *aZoneFileStream >> itemWindowDefNamePtr;

        QTreeWidgetItem *itemRectNode = new QTreeWidgetItem(itemsNode);
        itemRectNode->setText(0, "Item Text Rect");

        float itemRectX, itemRectY, itemRectWidth, itemRectHeight;
        *aZoneFileStream >> itemRectX >> itemRectY >> itemRectWidth >> itemRectHeight;
        QTreeWidgetItem *itemRectXNode = new QTreeWidgetItem(itemRectNode);
        itemRectXNode->setText(0, QString("X: %1").arg(itemRectX));
        QTreeWidgetItem *itemRectYNode = new QTreeWidgetItem(itemRectNode);
        itemRectYNode->setText(0, QString("Y: %1").arg(itemRectY));
        QTreeWidgetItem *itemRectWidthNode = new QTreeWidgetItem(itemRectNode);
        itemRectWidthNode->setText(0, QString("Width: %1").arg(itemRectWidth));
        QTreeWidgetItem *itemRectHeightNode = new QTreeWidgetItem(itemRectNode);
        itemRectHeightNode->setText(0, QString("Height: %1").arg(itemRectHeight));

        MENU_H_ALIGNMENT itemHAlignment;
        *aZoneFileStream >> itemHAlignment;
        QTreeWidgetItem *hTextAlignNode = new QTreeWidgetItem(itemRectNode);
        QString hTextAlignStr = Utils::MenuHAlignToStr(itemHAlignment);
        hTextAlignNode->setText(0, QString("Horiz. Align: %1").arg(hTextAlignStr));

        MENU_V_ALIGNMENT itemVAlignment;
        *aZoneFileStream >> itemVAlignment;
        QTreeWidgetItem *vTextAlignNode = new QTreeWidgetItem(itemRectNode);
        QString vTextAlignStr = Utils::MenuVAlignToStr(itemVAlignment);
        vTextAlignNode->setText(0, QString("Vert. Align: %1").arg(vTextAlignStr));

        quint32 itemGroupPtr; // Should be const char*
        *aZoneFileStream >> itemGroupPtr;

        MENU_WINDOW_STYLE itemWindowStyle;
        *aZoneFileStream >> itemWindowStyle;

        MENU_WINDOW_BORDER itemWindowBorder;
        *aZoneFileStream >> itemWindowBorder;

        quint32 itemOwnerDraw, itemOwnerDrawFlags;
        *aZoneFileStream >> itemOwnerDraw >> itemOwnerDrawFlags;

        float itemBorderSize;
        *aZoneFileStream >> itemBorderSize;

        int itemStaticFlags, itemDynamicFlags, itemNextTime;
        *aZoneFileStream >> itemStaticFlags >> itemDynamicFlags >> itemNextTime;

        float itemForegroundColorR, itemForegroundColorG, itemForegroundColorB, itemForegroundColorA,
            itemBackgroundColorR, itemBackgroundColorG, itemBackgroundColorB, itemBackgroundColorA,
            itemBorderColorR, itemBorderColorG, itemBorderColorB, itemBorderColorA,
            itemOutlineColorR, itemOutlineColorG, itemOutlineColorB, itemOutlineColorA;
        *aZoneFileStream >> itemForegroundColorR >> itemForegroundColorG >> itemForegroundColorB >> itemForegroundColorA
            >> itemBackgroundColorR >> itemBackgroundColorG >> itemBackgroundColorB >> itemBackgroundColorA
            >> itemBorderColorR >> itemBorderColorG >> itemBorderColorB >> itemBorderColorA
            >> itemOutlineColorR >> itemOutlineColorG >> itemOutlineColorB >> itemOutlineColorA;

        quint32 itemMaterialPtr; // Should be Material *
        *aZoneFileStream >> itemMaterialPtr;

        QTreeWidgetItem *itemTextRectNode = new QTreeWidgetItem(itemsNode);
        itemTextRectNode->setText(0, "Item Text Rect");

        float itemTextRectX, itemTextRectY, itemTextRectWidth, itemTextRectHeight;
        *aZoneFileStream >> itemTextRectX >> itemTextRectY >> itemTextRectWidth >> itemTextRectHeight;
        QTreeWidgetItem *itemTextRectXNode = new QTreeWidgetItem(itemTextRectNode);
        itemTextRectXNode->setText(0, QString("X: %1").arg(itemTextRectX));
        QTreeWidgetItem *itemTextRectYNode = new QTreeWidgetItem(itemTextRectNode);
        itemTextRectYNode->setText(0, QString("Y: %1").arg(itemTextRectY));
        QTreeWidgetItem *itemTextRectWidthNode = new QTreeWidgetItem(itemTextRectNode);
        itemTextRectWidthNode->setText(0, QString("Width: %1").arg(itemTextRectWidth));
        QTreeWidgetItem *itemTextRectHeightNode = new QTreeWidgetItem(itemTextRectNode);
        itemTextRectHeightNode->setText(0, QString("Height: %1").arg(itemTextRectHeight));

        MENU_H_ALIGNMENT itemText_hAlign;
        *aZoneFileStream >> itemText_hAlign;
        QTreeWidgetItem *hItemTextAlignNode = new QTreeWidgetItem(itemTextRectNode);
        QString hItemTextAlignStr = Utils::MenuHAlignToStr(itemText_hAlign);
        hItemTextAlignNode->setText(0, QString("Horiz. Align: %1").arg(hItemTextAlignStr));

        MENU_V_ALIGNMENT itemText_vAlign;
        *aZoneFileStream >> itemText_vAlign;
        QTreeWidgetItem *vItemTextAlignNode = new QTreeWidgetItem(itemTextRectNode);
        QString vItemTextAlignStr = Utils::MenuVAlignToStr(itemText_vAlign);
        vItemTextAlignNode->setText(0, QString("Vert. Align: %1").arg(vItemTextAlignStr));


        MENU_ITEM_TYPE itemType;
        *aZoneFileStream >> itemType;

        quint32 dataType, alignment;
        *aZoneFileStream >> dataType >> alignment;

        MENU_FONT_TYPE fontEnum;
        *aZoneFileStream >> fontEnum;

        quint32 textAlignMode;
        *aZoneFileStream >> textAlignMode;

        float textalignx, textaligny, textscale;
        *aZoneFileStream >> textalignx >> textaligny >> textscale;

        MENU_ITEM_TEXTSTYLE textStyle;
        *aZoneFileStream >> textStyle;

        int gameMsgWindowIndex, gameMsgWindowMode;
        *aZoneFileStream >> gameMsgWindowIndex >> gameMsgWindowMode;

        quint32 testPtr; // const char *
        *aZoneFileStream >> testPtr;

        quint32 textSavegameInfo;
        *aZoneFileStream >> textSavegameInfo;

        quint32 parentPtr; // menuDef_t *
        *aZoneFileStream >> parentPtr;

        quint32 mouseEnterText, mouseExitText, mouseEnter, mouseExit,
            action, onAccept, onFocus, leaveFocus, dvar, dvarTest; // const char *
        *aZoneFileStream >> mouseEnterText >> mouseExitText >> mouseEnter >> mouseExit
            >> action >> onAccept >> onFocus >> leaveFocus >> dvar >> dvarTest;

        quint32 keyHandlerPtr; // ItemKeyHandler *
        *aZoneFileStream >> keyHandlerPtr;

        quint32 enableDvarPtr; // const char *
        *aZoneFileStream >> enableDvarPtr;

        quint32 dvarFlags;
        *aZoneFileStream >> dvarFlags;

        quint32 focusSoundPtr; // snd_alias_list_t *;
        *aZoneFileStream >> focusSoundPtr;

        float special;
        *aZoneFileStream >> special;

        quint32 cursorPos;
        *aZoneFileStream >> cursorPos;

        // itemDefData_t typeData;

        // listBoxDef_s *listBox;

        quint32 startPos, endPos, drawPadding;
        *aZoneFileStream >> startPos >> endPos >> drawPadding;

        float elementWidth, elementHeight;
        *aZoneFileStream >> elementWidth >> elementHeight;

        quint32 elementStyle, numColumns;
        *aZoneFileStream >> elementStyle >> numColumns;

        //columnInfo_s columnInfo[16];

        quint32 doubleClickPtr; // const char *
        *aZoneFileStream >> doubleClickPtr;


        int notselectable, noScrollBars, usePaging;
        *aZoneFileStream >> notselectable >> noScrollBars >> usePaging;

        float itemSelectBorderColorR, itemSelectBorderColorG, itemSelectBorderColorB, itemSelectBorderColorA,
            itemDisableColorR, itemDisableColorG, itemDisableColorB, itemDisableColorA,
            itemFocusColor2R, itemFocusColor2G, itemFocusColor2B, itemFocusColor2A;
        *aZoneFileStream >> itemSelectBorderColorR >> itemSelectBorderColorG >> itemSelectBorderColorB >> itemSelectBorderColorA
            >> itemDisableColorR >> itemDisableColorG >> itemDisableColorB >> itemDisableColorA
            >> itemFocusColor2R >> itemFocusColor2G >> itemFocusColor2B >> itemFocusColor2A;

        quint32 selectIconPtr, backgroundItemListboxPtr, highlightTexturePtr; // Material *
        *aZoneFileStream >> selectIconPtr >> backgroundItemListboxPtr >> highlightTexturePtr;

        // editFieldDef_s *editField;

        float minVal, maxVal, defVal, range;
        *aZoneFileStream >> minVal >> maxVal >> defVal >> range;

        int maxChars, maxCharsGotoNext, maxPaintChars, paintOffset;
        *aZoneFileStream >> maxChars >> maxCharsGotoNext >> maxPaintChars >> paintOffset;

        // multiDef_s *multi;

        QVector<quint32> dvarListPtrs = QVector<quint32>(32);
        for (int i = 0; i < 32; i++) {
            quint32 dvarList;
            *aZoneFileStream >> dvarList;
            dvarListPtrs.push_back(dvarList);
        }

        QVector<quint32> dvarStrPtrs = QVector<quint32>(32);
        for (int i = 0; i < 32; i++) {
            quint32 dvarStr;
            *aZoneFileStream >> dvarStr;
            dvarStrPtrs.push_back(dvarStr);
        }

        QVector<float> dvarValues = QVector<float>(32);
        for (int i = 0; i < 32; i++) {
            float dvarValue;
            *aZoneFileStream >> dvarValue;
            dvarValues.push_back(dvarValue);
        }

        quint32 count, strDef;
        *aZoneFileStream >> count >> strDef;

        quint32 enumDvarNamePtr; // const char *
        *aZoneFileStream >> enumDvarNamePtr;

        quint32 dataPtr; // void *
        *aZoneFileStream >> dataPtr;

        quint32 itemImageTrack;
        *aZoneFileStream >> itemImageTrack;

        //statement_s visibleExp;
        //statement_s textExp;
        //statement_s materialExp;
        //statement_s rectXExp;
        //statement_s rectYExp;
        //statement_s rectWExp;
        //statement_s rectHExp;
        //statement_s foreColorAExp;
    }
}

void MainWindow::ParseAsset_Weapon(QDataStream *aZoneFileStream) {
    //WEAPON_FILE
}

void MainWindow::ParseAsset_D3DBSP(QDataStream *aZoneFileStream) {
    //D3DBSP_DUMP
}

void MainWindow::ParseAsset_StringTable(QDataStream *aZoneFileStream) {
    aZoneFileStream->skipRawData(4);

    quint32 columnCount, rowCount;
    *aZoneFileStream >> columnCount >> rowCount;
    columnCount = 0;
    rowCount = 0;

    aZoneFileStream->skipRawData(4);

    QString stringTableName;
    char stringTableNameChar;
    *aZoneFileStream >> stringTableNameChar;
    while (stringTableNameChar != 0) {
        stringTableName += stringTableNameChar;
        *aZoneFileStream >> stringTableNameChar;
    }
    ui->comboBox_StringTable->addItem(stringTableName);

    QVector<QString> tablePointers = QVector<QString>();
    for (quint32 i = 0; i < rowCount; i++) {
        QByteArray pointerData(4, Qt::Uninitialized);
        aZoneFileStream->readRawData(pointerData.data(), 4);
        tablePointers.push_back(pointerData.toHex());

        aZoneFileStream->skipRawData(4);
    }

    for (const QString &pointerAddr : tablePointers) {
        QString leadingContent = "";
        if (pointerAddr == "FFFFFFFF") {
            char leadingContentChar;
            *aZoneFileStream >> leadingContentChar;
            while (leadingContentChar != 0) {
                leadingContent += leadingContentChar;
                *aZoneFileStream >> leadingContentChar;
            }
        } else {
            leadingContent = pointerAddr;
        }

        QString content;
        char contentChar;
        *aZoneFileStream >> contentChar;
        while (contentChar != 0) {
            content += contentChar;
            *aZoneFileStream >> contentChar;
        }
        QPair<QString, QString> tableEntry = QPair<QString, QString>();
        tableEntry.first = leadingContent;
        tableEntry.second = content;
        if (!mStrTableMap.contains(stringTableName)) {
            mStrTableMap[stringTableName] = QVector<QPair<QString, QString>>();
        }
        mStrTableMap[stringTableName].push_back(tableEntry);
    }
}

void MainWindow::on_pushButton_FastFile_clicked() {
    // Open fast file
    QString fastFilePath = GetFastFilePath();
    OpenFastFile(fastFilePath);
}

void MainWindow::on_pushButton_ZoneFile_clicked() {
    const QString zoneFilePath = GetZoneFilePath();
    OpenZoneFile(zoneFilePath);
}

void MainWindow::LogOpenedFile(QString aFileName)
{
    mRecentFiles.enqueue(aFileName);
    mRecentFiles.removeDuplicates();

    RefreshRecentFileMenu();
}

void MainWindow::RefreshRecentFileMenu()
{
    foreach (QAction* action, mRecentFileActions) {
        ui->menuRecent_Fast_Files->removeAction(action);
        ui->menuRecent_Zone_Files->removeAction(action);

        action->deleteLater();
    }
    mRecentFileActions.clear();

    foreach (QString recentFileText, mRecentFiles) {
        if (recentFileText.contains(".ff")) {
            QAction *recentFastFileAction = new QAction(ui->menuRecent_Fast_Files);
            recentFastFileAction->setText(recentFileText);
            mRecentFileActions << recentFastFileAction;
            ui->menuRecent_Fast_Files->addAction(recentFastFileAction);

            connect(recentFastFileAction, &QAction::triggered, this, [&, this, recentFileText](bool checked = false) {
                OpenFastFile(recentFileText);
            });
        } else if (recentFileText.contains(".zone")) {
            QAction *recentZoneFileAction = new QAction(ui->menuRecent_Zone_Files);
            recentZoneFileAction->setText(recentFileText);
            mRecentFileActions << recentZoneFileAction;
            ui->menuRecent_Zone_Files->addAction(recentZoneFileAction);

            connect(recentZoneFileAction, &QAction::triggered, this, [&, this, recentFileText](bool checked = false) {
                OpenZoneFile(recentFileText);
            });
        }
    }
}

void MainWindow::ParseZoneFile(QByteArray aDecompressedData) {
    // Open zone file as little endian stream
    QDataStream zoneFileStream(aDecompressedData);
    zoneFileStream.setByteOrder(QDataStream::LittleEndian);
    zoneFileStream.setFloatingPointPrecision(QDataStream::SinglePrecision);

    // Parse data from zone file header
    Zone zone;
    zoneFileStream >> zone;

    // Add header data to ui
    ui->spinBox_FileSize->setValue(zone.zoneFileSize);
    ui->spinBox_TagCount->setValue(zone.tagCount);
    ui->spinBox_RecordCount->setValue(zone.recordCount);
    // Add unknowns to ui
    ui->lineEdit_U1->setText(QString::number(zone.unknown1, 16).toUpper());
    ui->spinBox_U1->setValue(zone.unknown1);
    ui->lineEdit_U2->setText(QString::number(zone.unknown2, 16).toUpper());
    ui->spinBox_U2->setValue(zone.unknown2);
    ui->lineEdit_U3->setText(QString::number(zone.unknown3, 16).toUpper());
    ui->spinBox_U3->setValue(zone.unknown3);
    ui->lineEdit_U4->setText(QString::number(zone.unknown4, 16).toUpper());
    ui->spinBox_U4->setValue(zone.unknown4);
    ui->lineEdit_U5->setText(QString::number(zone.unknown5, 16).toUpper());
    ui->spinBox_U5->setValue(zone.unknown5);
    ui->lineEdit_U6->setText(QString::number(zone.unknown6, 16).toUpper());
    ui->spinBox_U6->setValue(zone.unknown6);
    ui->lineEdit_U7->setText(QString::number(zone.unknown7, 16).toUpper());
    ui->spinBox_U7->setValue(zone.unknown7);
    ui->lineEdit_U8->setText(QString::number(zone.unknown8, 16).toUpper());
    ui->spinBox_U8->setValue(zone.unknown8);
    ui->lineEdit_U9->setText(QString::number(zone.unknown9, 16).toUpper());
    ui->spinBox_U9->setValue(zone.unknown9);
    ui->lineEdit_U10->setText(QString::number(zone.unknown10, 16).toUpper());
    ui->spinBox_U10->setValue(zone.unknown10);
    ui->lineEdit_U11->setText(QString::number(zone.unknown11, 16).toUpper());
    ui->spinBox_U11->setValue(zone.unknown11);
    // Add tags to ui list
    foreach (const QString tag, zone.tags) {
        ui->listWidget_Tags->addItem(tag);
    }

    // Track past assets and counts
    int consecutiveIndex = 0;
    int consecutiveCount = 0;
    ASSET_TYPE lastAssetType = ASSET_UNKNOWN;
    foreach (ASSET_TYPE assetType, zone.assetTypes) {
        const QString typeStr = Utils::AssetTypeToString(assetType);

        if (!mTypeMap.contains(assetType)) {
            mTypeMap[assetType] = 0;
        }
        mTypeMap[assetType]++;

        // Set lastAsset as current if first run
        if (lastAssetType == ASSET_UNKNOWN) {
            lastAssetType = assetType;
        }

        // Track counts or populate asset order table
        if (lastAssetType == assetType) {
            // Count consecutive assets
            consecutiveCount++;
        } else {
            // Insert row and populate for the previous asset type
            ui->tableWidget_Order->insertRow(consecutiveIndex);
            ui->tableWidget_Order->setItem(consecutiveIndex, 0, new QTableWidgetItem(Utils::AssetTypeToString(lastAssetType)));
            ui->tableWidget_Order->setItem(consecutiveIndex, 1, new QTableWidgetItem(QString::number(consecutiveCount)));

            // Update counts and asset type
            consecutiveCount = 1;
            consecutiveIndex++;
            lastAssetType = assetType;
        }

        // qDebug() << "Parsing Asset of Type: " << typeHex;
        if (typeStr == "ANIMATION") { // aitype
            ParseAsset_XAnim(&zoneFileStream);
        } else if (typeStr == "MODEL") { // xmodel
            ParseAsset_XModel(&zoneFileStream);
        } else if (typeStr == "MATERIAL") { // material
            ParseAsset_Material(&zoneFileStream);
        } else if (typeStr == "TECH SET") { // techset include
            ParseAsset_TechSet(&zoneFileStream);
        } else if (typeStr == "SOUND") { // loaded_sound
            ParseAsset_LoadedSound(&zoneFileStream);
        } else if (typeStr == "COLLISION MAP") { // col_map_mp
            ParseAsset_ColMapMP(&zoneFileStream);
        } else if (typeStr == "SHADER") { // pixelshader
            ParseAsset_PixelShader(&zoneFileStream);
        } else if (typeStr == "D3DBSP DUMP") { // string_table
            ParseAsset_D3DBSP(&zoneFileStream);
        } else if (typeStr == "FONT") { // font
            ParseAsset_Font(&zoneFileStream);
        } else if (typeStr == "MENU") { // string_table
            ParseAsset_MenuFile(&zoneFileStream);
        } else if (typeStr == "LOCAL STRING") { // localized string asset
            ParseAsset_Localize(&zoneFileStream);
        } else if (typeStr == "WEAPON") { // string_table
            ParseAsset_Weapon(&zoneFileStream);
        } else if (typeStr == "EFFECT") { // aitype
            ParseAsset_FX(&zoneFileStream);
        } else if (typeStr == "RAW FILE") { // gsc
            // ParseAsset_RawFile(&zoneFileStream);
            RawFile rawFile = RawFile();
            zoneFileStream >> rawFile;
            mRawFilesVec >> rawFile;
        } else if (typeStr == "STRING TABLE") { // string_table
            ParseAsset_StringTable(&zoneFileStream);
        } else {
            qDebug() << "Found bad asset type!" << typeStr;
        }
    }

    // Track current and consecutive assets
    int assetIndex = 0;

    // Iterate asset types found in index
    for (auto [assetType, assetCount] : mTypeMap.asKeyValueRange()) {
        const QString typeStr = Utils::AssetTypeToString(assetType);
        // Insert row and populate
        ui->tableWidget_Index->insertRow(assetIndex);
        ui->tableWidget_Index->setItem(assetIndex, 0, new QTableWidgetItem(typeStr));
        ui->tableWidget_Index->setItem(assetIndex, 1, new QTableWidgetItem(QString::number(assetCount)));

        // Update count
        assetIndex++;
    }
}

int MainWindow::LoadFile_D3DBSP(const QString aFilePath) {
    QFile file(aFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error: Unable to open file" << aFilePath;
        return 1; // ERR_FILE_NOT_FOUND
    }

    QDataStream stream(&file);
    stream.setByteOrder(QDataStream::LittleEndian);

    // Read Magic Value
    quint32 magicValue;
    stream >> magicValue;
    if (magicValue != 'PSBI') {
        qDebug() << "Error: Not a valid D3DBSP file";
        return 2; // ERR_NOT_A_D3DBSP_FILE
    }

    // Read BSP Version and Lump Count
    stream >> mBSPVersion;
    stream >> mDiskLumpCount;

    // Assign diskLumpOrderSize
    mDiskLumpOrder.resize(mDiskLumpCount);

    qDebug() << "BSP Version:" << mBSPVersion;
    qDebug() << "Lump Count:" << mDiskLumpCount;

    // Read Lump Index Entries
    quint32 lumpOffset = sizeof(quint32) * 3 + sizeof(LumpIndexEntry) * mDiskLumpCount;

    for (quint32 i = 0; i < mDiskLumpCount; i++) {
        LumpIndexEntry indexEntry;
        stream >> indexEntry.type >> indexEntry.length;

        mDiskLumpOrder[i] = indexEntry.type;

        Lump &lump = mLumps[indexEntry.type];
        lump.size = indexEntry.length;
        lump.content.resize(indexEntry.length);
        lump.isEmpty = false;

        qDebug() << "Lump Type:" << Utils::LumpTypeToString((LUMP_TYPE)indexEntry.type) << "Lump Size:" << indexEntry.length;

        // Handle offsets and padding
        qint64 currentPos = file.pos();
        file.seek(lumpOffset);
        file.read(lump.content.data(), lump.size);
        file.seek(currentPos);
        lumpOffset += Utils::PadInt4(indexEntry.length);
    }

    file.close();
    return 0; // Success
}

