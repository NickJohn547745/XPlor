#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    mTypeMap = QMap<QString, int>();
    mTypeOrder = QStringList();
    mRawFileMap = QMap<QString, QString>();
    mTreeMap = QMap<QString, QTreeWidgetItem*>();
    mStrTableMap = QMap<QString, QVector<QPair<QString, QString>>>();
    mBSPVersion = 0;
    mDiskLumpCount = 0;
    mDiskLumpOrder = QVector<quint32>();
    mLumps = QMap<quint32, Lump>();

    connect(ui->treeWidget_Scripts, &QTreeWidget::itemSelectionChanged, this, &MainWindow::ScriptSelected);
    connect(ui->comboBox_StringTable, &QComboBox::currentTextChanged, this, &MainWindow::StrTableSelected);

    // Initialize Asset Index Table
    ui->tableWidget_Index->setColumnCount(3);
    ui->tableWidget_Index->setHorizontalHeaderLabels({"Asset Type", "Asset Name", "Asset Count"});
    ui->tableWidget_Index->verticalHeader()->setVisible(false);
    ui->tableWidget_Index->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_Index->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_Index->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_Index->setShowGrid(false);
    ui->tableWidget_Index->setStyleSheet("QTableView {selection-background-color: red;}");

    // Initialize Asset Order Table
    ui->tableWidget_Order->setColumnCount(3);
    ui->tableWidget_Order->setHorizontalHeaderLabels({"Asset Type", "Asset Name", "Asset Count"});
    ui->tableWidget_Order->verticalHeader()->setVisible(false);
    ui->tableWidget_Order->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_Order->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_Order->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_Order->setShowGrid(false);
    ui->tableWidget_Order->setStyleSheet("QTableView {selection-background-color: red;}");

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
}

void MainWindow::StrTableSelected(QString aStrTableName) {
    ui->tableWidget_StringTable->clear();

    ui->tableWidget_StringTable->setColumnCount(2);
    int entryIndex = 0;
    for (auto strTableEntry : mStrTableMap[aStrTableName]) {
        ui->tableWidget_StringTable->insertRow(ui->tableWidget_StringTable->rowCount() + 1);
        ui->tableWidget_StringTable->setItem(entryIndex, 0, new QTableWidgetItem(strTableEntry.first));
        ui->tableWidget_StringTable->setItem(entryIndex, 1, new QTableWidgetItem(Utils::AssetTypeToString(strTableEntry.second)));

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
    OpenFastFile()

    Opens a file dialog in the steam folder,
    and opens the selected file.
*/
QFile* MainWindow::OpenFastFile() {
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

    // Check fastfile can be read
    QFile *fastFile = new QFile(fastFilePath);
    if (!fastFile->open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Warning!", QString("%1 could not be read!.").arg(fastFilePath));
        return nullptr;
    }
    return fastFile;
}

/*
    OpenZoneFile()

    Opens a file dialog in the steam folder,
    and opens the selected file.
*/
QFile* MainWindow::OpenZoneFile() {
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

    // Check fastfile can be read
    QFile *zoneFile = new QFile(zoneFilePath);
    if (!zoneFile->open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Warning!", QString("%1 could not be read!.").arg(zoneFilePath));
        return nullptr;
    }
    return zoneFile;
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

void MainWindow::ParseFFHeader(QFile *aFastFilePtr) {
    // Open stream to fastfile
    QDataStream afastFileStream(aFastFilePtr);
    afastFileStream.setByteOrder(QDataStream::LittleEndian);

    ParseFFCompany(&afastFileStream);
    ParseFFFileType(&afastFileStream);
    ParseFFSignage(&afastFileStream);
    ParseFFMagic(&afastFileStream);
    ParseFFVersion(&afastFileStream);
}

void MainWindow::ParseZoneHeader(QDataStream *aZoneFileStream) {
    ParseZoneSize(aZoneFileStream);
    ParseZoneUnknownsA(aZoneFileStream);

    ParseZoneTagCount(aZoneFileStream);
    ParseZoneUnknownsB(aZoneFileStream);

    ParseZoneRecordCount(aZoneFileStream);

    if (mTagCount) {
        ParseZoneUnknownsC(aZoneFileStream);
        ParseZoneTags(aZoneFileStream);
    } else {
        aZoneFileStream->skipRawData(4);
    }
}

void MainWindow::ParseZoneSize(QDataStream *aZoneFileStream) {
    // Byte 0-3: (unsigned int?) correlates to the fastfile's
    //           size after decompression minus 36 bytes (24h)
    quint32 zoneFileSize;
    *aZoneFileStream >> zoneFileSize;
    if (zoneFileSize <= 0) {
        qDebug() << "Tried to open empty zone file!";
        exit(-1);
    }
    zoneFileSize += 36;
    ui->spinBox_FileSize->setValue(zoneFileSize);

    qDebug() << QString("Zone file size: '%1'").arg(zoneFileSize);
}

/*
    ParseZoneUnknownsA()

    Parses the 1st section of unknowns as hex vals and uint32s
*/
void MainWindow::ParseZoneUnknownsA(QDataStream *aZoneFileStream) {
    // Byte 4-7, 8-11, 12-15: unknown
    QByteArray unknown1(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown1.data(), 4);
    ui->lineEdit_U1->setText(unknown1.toHex());
    ui->spinBox_U1->setValue(unknown1.toUInt());

    QByteArray unknown2(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown2.data(), 4);
    ui->lineEdit_U2->setText(unknown2.toHex());
    ui->spinBox_U2->setValue(unknown2.toUInt());

    QByteArray unknown3(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown3.data(), 4);
    ui->lineEdit_U3->setText(unknown3.toHex());
    ui->spinBox_U3->setValue(unknown3.toUInt());

    // Byte 16-19, 20-23: empty/unknown
    QByteArray unknown4(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown4.data(), 4);
    ui->lineEdit_U4->setText(unknown4.toHex());
    ui->spinBox_U4->setValue(unknown4.toUInt());

    QByteArray unknown5(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown5.data(), 4);
    ui->lineEdit_U5->setText(unknown5.toHex());
    ui->spinBox_U5->setValue(unknown5.toUInt());

    // Byte 24-27: somehow related to the filesize, but smaller value
    QByteArray unknown6(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown6.data(), 4);
    ui->lineEdit_U6->setText(unknown6.toHex());
    ui->spinBox_U6->setValue(unknown6.toUInt());

    // Byte 28-31, 32-35: unknown
    QByteArray unknown7(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown7.data(), 4);
    ui->lineEdit_U7->setText(unknown7.toHex());
    ui->spinBox_U7->setValue(unknown7.toUInt());

    QByteArray unknown8(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown8.data(), 4);
    ui->lineEdit_U8->setText(unknown8.toHex());
    ui->spinBox_U8->setValue(unknown8.toUInt());

    qDebug() << QString("Unknowns A: '%1''%2''%3''%4''%5''%6''%7''%8'")
                    .arg(unknown1.toHex())
                    .arg(unknown2.toHex())
                    .arg(unknown3.toHex())
                    .arg(unknown4.toHex())
                    .arg(unknown5.toHex())
                    .arg(unknown6.toHex())
                    .arg(unknown7.toHex())
                    .arg(unknown8.toHex());
}

/*
    ParseZoneTagCount()

    Parses the number of string tags in the zone index
*/
void MainWindow::ParseZoneTagCount(QDataStream *aZoneFileStream) {
    // Byte 36-39: might indicate where the index record starts,
    //             calculation unknown
    *aZoneFileStream >> mTagCount;
    ui->spinBox_TagCount->setValue(mTagCount);
    qDebug() << QString("Tag count: '%1'").arg(mTagCount);
}

/*
    ParseZoneRecordCount()

    Parses the number of records in the zone index
*/
void MainWindow::ParseZoneRecordCount(QDataStream *aZoneFileStream) {
    // Byte 44-47: (unsigned int) number of records
    *aZoneFileStream >> mRecordCount;
    ui->spinBox_RecordCount->setValue(mRecordCount);
    qDebug() << QString("Record count: '%1'").arg(mRecordCount);
}

/*
    ParseZoneUnknownsB()

    Parses the 2nd section of unknowns as hex vals and uint32s
*/
void MainWindow::ParseZoneUnknownsB(QDataStream *aZoneFileStream) {
    // Byte 44-47: Unknown/empty?
    QByteArray unknown9(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown9.data(), 4);
    ui->lineEdit_U9->setText(unknown9.toHex());
    ui->spinBox_U9->setValue(unknown9.toUInt());

    qDebug() << QString("Unknowns B: \n\t'%1'")
                    .arg(unknown9.toHex());
}

/*
    ParseZoneUnknownsC()

    Parses the 3rd section of unknowns as hex vals and uint32s
*/
void MainWindow::ParseZoneUnknownsC(QDataStream *aZoneFileStream) {
    // Byte 40-43: Unknown/empty?
    QByteArray unknown10(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown10.data(), 4);
    ui->lineEdit_U10->setText(unknown10.toHex());
    ui->spinBox_U10->setValue(unknown10.toUInt());

    // Byte 44-47: Unknown/empty?
    QByteArray unknown11(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown11.data(), 4);
    ui->lineEdit_U11->setText(unknown11.toHex());
    ui->spinBox_U11->setValue(unknown11.toUInt());

    qDebug() << QString("Unknowns C: \n\t'%1'\n\t'%2'")
                    .arg(unknown10.toHex())
                    .arg(unknown11.toHex());
}

/*
    ParseZoneTags()

    Parses the string tags ate the start of zone file
*/
void MainWindow::ParseZoneTags(QDataStream *aZoneFileStream) {
    // Byte 48-51: Repeated separators? ÿÿÿÿ x i
    aZoneFileStream->skipRawData(4 * (mTagCount - 1));

    // Parse tags/strings before index
    QString zoneTag;
    char zoneTagChar;
    for (quint32 i = 0; i < mTagCount - 1; i++) {
        *aZoneFileStream >> zoneTagChar;
        while (zoneTagChar != 0) {
            zoneTag += zoneTagChar;
            *aZoneFileStream >> zoneTagChar;
        }
        ui->listWidget_Tags->addItem(zoneTag);
        // qDebug() << "Tag: " << zoneTag;
        zoneTag.clear();
    }
}

/*
    ParseZoneIndex()

    Parse the binary zone index data and populate table
*/
void MainWindow::ParseZoneIndex(QDataStream *aZoneFileStream) {
    // Don't parse if no records
    if (!mRecordCount) { return; }

    // Track past assets and counts
    int consecutiveIndex = 0;
    int consecutiveCount = 0;
    QString lastAssetType = "";

    // Parse index & map found asset types
    for (quint32 i = 0; i < mRecordCount; i++) {
        // Skip record start
        QByteArray rawAssetType(4, Qt::Uninitialized);
        aZoneFileStream->readRawData(rawAssetType.data(), 4);
        if (!mTypeMap.contains(rawAssetType.toHex())) {
            mTypeMap[rawAssetType.toHex()] = 0;
        }
        mTypeMap[rawAssetType.toHex()]++;
        mTypeOrder << rawAssetType.toHex();

        // Skip separator
        aZoneFileStream->skipRawData(4);

        // Get asset description from type
        const QString assetType = rawAssetType.toHex();

        // Set lastAsset as current if first run
        if (lastAssetType.isEmpty()) {
            lastAssetType = assetType;
        }

        // Track counts or populate asset order table
        if (lastAssetType == assetType) {
            // Count consecutive assets
            consecutiveCount++;
        } else {
            // Insert row and populate for the previous asset type
            ui->tableWidget_Order->insertRow(consecutiveIndex);
            ui->tableWidget_Order->setItem(consecutiveIndex, 0, new QTableWidgetItem(lastAssetType));
            ui->tableWidget_Order->setItem(consecutiveIndex, 1, new QTableWidgetItem(Utils::AssetTypeToString(lastAssetType)));
            ui->tableWidget_Order->setItem(consecutiveIndex, 2, new QTableWidgetItem(QString::number(consecutiveCount)));

            // Update counts and asset type
            consecutiveCount = 1;
            consecutiveIndex++;
            lastAssetType = assetType;
        }
    }
}

void MainWindow::ParseAsset_LocalString(QDataStream *aZoneFileStream) {
    // Skip separator
    qint32 langStrPtr, referenceStrPtr;
    *aZoneFileStream >> langStrPtr >> referenceStrPtr;

    // Parse language-specific string if present
    QString langStr;
    if (langStrPtr == -1) {
        char langStrChar;
        *aZoneFileStream >> langStrChar;
        while (langStrChar != 0) {
            langStr += langStrChar;
            *aZoneFileStream >> langStrChar;
        }
    } else {
        langStr = "MEMORY_REFERENCE";
    }

    // Parse reference str ig present
    QString referenceStr;
    if (referenceStrPtr == -1) {
        char referenceStrChar;
        *aZoneFileStream >> referenceStrChar;
        while (referenceStrChar != 0) {
            referenceStr += referenceStrChar;
            *aZoneFileStream >> referenceStrChar;
        }
    } else {
        referenceStr = "MEMORY_REFERENCE";
    }

    const int localStrIndex = ui->listWidget_LocalString->count() + 1;
    ui->listWidget_LocalString->addItem(QString("[%1] %2 = %3").arg(localStrIndex).arg(referenceStr).arg(langStr));
}

void MainWindow::ParseAsset_RawFile(QDataStream *aZoneFileStream) {
    // Skip start separator FF FF FF FF (pointer?)
    aZoneFileStream->skipRawData(4);

    quint32 rawFileLength;
    *aZoneFileStream >> rawFileLength;

    // Skip unknown 4 byte data
    aZoneFileStream->skipRawData(4);

    bool isBik = false;

    // Parse rawfile path
    QString rawFilePath;
    char rawFilePathChar;
    *aZoneFileStream >> rawFilePathChar;
    while (rawFilePathChar != 0) {
        rawFilePath += rawFilePathChar;
        *aZoneFileStream >> rawFilePathChar;
    }
    rawFilePath.replace(",", "");
    if (rawFilePath.contains(".bik")) {
        isBik = true;
    } else {
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
    }

    if (false && isBik) {
        qDebug() << "rawFileLength: " << rawFileLength;
        QByteArray bikData(rawFileLength, Qt::Uninitialized);
        aZoneFileStream->readRawData(bikData.data(), rawFileLength);

        //QFile bikFile(QDir::currentPath() + "/" + rawFilePath.split('/').last());
        //qDebug() << bikFile.fileName();
        //if (!bikFile.open(QIODevice::WriteOnly)) {
        //    qWarning() << "Failed to open .bik file for writing!";
        //    return;
        //}
        //qDebug() << QString("%1: %2").arg(rawFilePath).arg(bikFile.fileName());
        //bikFile.write(bikData);
    } else {
        // Parse gsc contents
        QString rawFileContents;
        char rawFileContentsChar;
        *aZoneFileStream >> rawFileContentsChar;
        while (rawFileContentsChar != 0 && rawFileContentsChar != -1) {
            rawFileContents += rawFileContentsChar;
            *aZoneFileStream >> rawFileContentsChar;
        }
        mRawFileMap[rawFilePath] = (rawFileContents.isEmpty()) ? ("EMPTY") : (rawFileContents);
        qDebug() << QString("%1: %2").arg(rawFilePath).arg(rawFileContents);
    }
}

void MainWindow::ParseAsset_PhysPreset(QDataStream *aZoneFileStream) {

}

void MainWindow::ParseAsset_XModel(QDataStream *aZoneFileStream) {

}

void MainWindow::ParseAsset_Material(QDataStream *aZoneFileStream) {
    aZoneFileStream->skipRawData(27 * 4);

    qint32 materialNamePtr;
    *aZoneFileStream >> materialNamePtr;
    qDebug() << "materialNamePtr: " << materialNamePtr;
    if (materialNamePtr == -1) {
        QString materialName;
        char materialNameChar;
        *aZoneFileStream >> materialNameChar;
        while (materialNameChar != 0) {
            materialName += materialNameChar;
            *aZoneFileStream >> materialNameChar;
        }
        qDebug() << "Parsing Material: " << materialName;
    }

    aZoneFileStream->skipRawData(3 * 4);

    qint32 compressionPtr, compression, unknownSectionPtr;
    *aZoneFileStream >> compressionPtr;
    qDebug() << "compressionPtr: " << compressionPtr;
    if (compressionPtr == -1) {
        *aZoneFileStream >> compression;
        qDebug() << QString("Found material with DXT%1 compression!").arg(compression);

        *aZoneFileStream >> unknownSectionPtr;
        qDebug() << "unknownSectionPtr: " << unknownSectionPtr;
        if (unknownSectionPtr == -2) {
            aZoneFileStream->skipRawData(6 * 4);
        }
    }

    qint32 imageNamePtr;
    *aZoneFileStream >> imageNamePtr;
    qDebug() << "imageNamePtr: " << imageNamePtr;
    if (imageNamePtr == -1) {
        QString imageName;
        char imageNameChar;
        *aZoneFileStream >> imageNameChar;
        while (imageNameChar != 0) {
            imageName += imageNameChar;
            *aZoneFileStream >> imageNameChar;
        }
        qDebug() << "- Embeded image: " << imageName;
    }

    QByteArray compressionData(4, Qt::Uninitialized);
    QString compressionStr;
    if (compressionPtr == -1) {
        aZoneFileStream->skipRawData(2 * 4);
        aZoneFileStream->readRawData(compressionData.data(), 4);
        aZoneFileStream->skipRawData(4);
        compressionStr = QString::fromUtf8(compressionData);
        aZoneFileStream->skipRawData(4);
    }
    aZoneFileStream->skipRawData(4);
}

void MainWindow::ParseAsset_PixelShader(QDataStream *aZoneFileStream) {

}

void MainWindow::ParseAsset_BikFile(QDataStream *aZoneFileStream) {
    QByteArray testData(32, Qt::Uninitialized);
    aZoneFileStream->readRawData(testData.data(), 32);
    qDebug() << "Test Data: " << testData;

    //aZoneFileStream->skipRawData(4);

    quint32 fileSize;
    //*aZoneFileStream >> fileSize;
    //qDebug() << ".bik file size:" << fileSize;

    // // Parse rawfile path
    // QString filePath;
    // char filePathChar;
    // *aZoneFileStream >> filePathChar;
    // while (filePathChar != 0) {
    //     filePath += filePathChar;
    //     *aZoneFileStream >> filePathChar;
    // }

    // QByteArray bikData(fileSize, Qt::Uninitialized);
    // aZoneFileStream->readRawData(bikData.data(), fileSize);
    // qDebug() << filePath;

    // QFile bikFile(QDir::currentPath() + "/" + filePath.split('/').last());
    // qDebug() << bikFile.fileName();
    // if (!bikFile.open(QIODevice::WriteOnly)) {
    //     qWarning() << "Failed to open .bik file for writing!";
    //     return;
    // }
    // bikFile.write(bikData);
}

void MainWindow::ParseAsset_Image(QDataStream *aZoneFileStream) {

}

void MainWindow::ParseAsset_LoadedSound(QDataStream *aZoneFileStream) {

}

void MainWindow::ParseAsset_ColMapMP(QDataStream *aZoneFileStream) {

}

void MainWindow::ParseAsset_GameMapSP(QDataStream *aZoneFileStream) {

}

void MainWindow::ParseAsset_GameMapMP(QDataStream *aZoneFileStream) {

}

void MainWindow::ParseAsset_LightDef(QDataStream *aZoneFileStream) {

}

void MainWindow::ParseAsset_UIMap(QDataStream *aZoneFileStream) {

}

void MainWindow::ParseAsset_SNDDriverGlobals(QDataStream *aZoneFileStream) {

}

void MainWindow::ParseAsset_AIType(QDataStream *aZoneFileStream) {

}

void MainWindow::ParseAsset_FX(QDataStream *aZoneFileStream) {

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
}

void MainWindow::ParseAsset_Weapon(QDataStream *aZoneFileStream) {
    //WEAPON_FILE
}

void MainWindow::ParseAsset_D3DBSP(QDataStream *aZoneFileStream) {
    //D3DBSP_DUMP
}

void MainWindow::ParseAsset_TechSet(QDataStream *aZoneFileStream)
{
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
    qDebug() << "Tech Set: " << techSetName;
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
    // Try to prompt user to open fastfile
    QFile *fastFile;
    if (!(fastFile = OpenFastFile())) {
        QMessageBox::warning(this, "Warning!", QString("Failed to open FastFile!."));
        return;
    }

    // Parse data from fast file header
    ParseFFHeader(fastFile);

    // Decompress fastfile and close
    const QByteArray fastFileData = fastFile->readAll();
    const QByteArray decompressedData = DecompressZLIB(fastFileData);
    // ui->plainTextEdit_ZoneDump->setPlainText(decompressedData.toHex());

    const QString zoneFilePath = fastFile->fileName().replace(".ff", ".zone");
    fastFile->close();

    // Check zone file is writeable
    QFile *zoneFile = new QFile(zoneFilePath);
    if (!zoneFile->open(QIODevice::ReadWrite)) {
        qDebug() << QString("Zone file could not be written to: '%1'").arg(zoneFilePath);
        return;
    }
    // Write zone data
    zoneFile->write(decompressedData);
    zoneFile->close();

    // Open zone file as little endian stream
    QDataStream zoneFileStream(decompressedData);
    zoneFileStream.setByteOrder(QDataStream::LittleEndian);

    // Parse data from zone file header
    ParseZoneHeader(&zoneFileStream);
    ParseZoneIndex(&zoneFileStream);

    // Track current and consecutive assets
    int assetIndex = 0;

    // Iterate asset types found in index
    for (auto [assetType, assetCount] : mTypeMap.asKeyValueRange()) {
        // Get asset description from type
        QString assetStr = Utils::AssetTypeToString(assetType);

        // Insert row and populate
        ui->tableWidget_Index->insertRow(assetIndex);
        ui->tableWidget_Index->setItem(assetIndex, 0, new QTableWidgetItem(assetType));
        ui->tableWidget_Index->setItem(assetIndex, 1, new QTableWidgetItem(assetStr));
        ui->tableWidget_Index->setItem(assetIndex, 2, new QTableWidgetItem(QString::number(assetCount)));

        // Update count
        assetIndex++;
    }

    for (int i = 0; i < mTypeOrder.size(); i++) {
        const QString typeHex = mTypeOrder[i];
        const QString typeStr = Utils::AssetTypeToString(typeHex);

        // qDebug() << "Parsing Asset of Type: " << typeHex;
        if (typeStr == "LOCAL STRING") { // localized string asset
            ParseAsset_LocalString(&zoneFileStream);
        } else if (typeStr == "RAW FILE") { // gsc
            ParseAsset_RawFile(&zoneFileStream);
        } else if (typeStr == "PHYS PRESET") { // physpreset
            ParseAsset_PhysPreset(&zoneFileStream);
        } else if (typeStr == "MODEL") { // xmodel
            ParseAsset_XModel(&zoneFileStream);
        } else if (typeStr == "MATERIAL") { // material
            ParseAsset_Material(&zoneFileStream);
        } else if (typeStr == "SHADER") { // pixelshader
            ParseAsset_PixelShader(&zoneFileStream);
        } else if (typeStr == "BIK FILE") { // bik file?
            ParseAsset_BikFile(&zoneFileStream);
        } else if (typeStr == "IMAGE") { // image
            ParseAsset_Image(&zoneFileStream);
        } else if (typeStr == "SOUND") { // loaded_sound
            ParseAsset_LoadedSound(&zoneFileStream);
        } else if (typeStr == "COLLISION MAP") { // col_map_mp
            ParseAsset_ColMapMP(&zoneFileStream);
        } else if (typeStr == "MP MAP") { // game_map_sp
            ParseAsset_GameMapSP(&zoneFileStream);
        } else if (typeStr == "SP MAP") { // game_map_mp
            ParseAsset_GameMapMP(&zoneFileStream);
        } else if (typeStr == "LIGHT DEF") { // lightdef
            ParseAsset_LightDef(&zoneFileStream);
        } else if (typeStr == "UI MAP") { // ui_map
            ParseAsset_UIMap(&zoneFileStream);
        } else if (typeStr == "SND DRIVER GLOBALS") { // snddriverglobals
            ParseAsset_SNDDriverGlobals(&zoneFileStream);
        } else if (typeStr == "AI TYPE") { // aitype
            ParseAsset_AIType(&zoneFileStream);
        } else if (typeStr == "EFFECT") { // aitype
            ParseAsset_FX(&zoneFileStream);
        } else if (typeStr == "ANIMATION") { // aitype
            ParseAsset_XAnim(&zoneFileStream);
        } else if (typeStr == "STRING TABLE") { // string_table
            ParseAsset_StringTable(&zoneFileStream);
        } else if (typeStr == "MENU") { // string_table
            ParseAsset_MenuFile(&zoneFileStream);
        } else if (typeStr == "WEAPON") { // string_table
            ParseAsset_Weapon(&zoneFileStream);
        } else if (typeStr == "D3DBSP DUMP") { // string_table
            ParseAsset_D3DBSP(&zoneFileStream);
        } else if (typeStr == "TECH SET") { // string_table
            ParseAsset_TechSet(&zoneFileStream);
        } else if (typeStr != "UNKNOWN") {
            qDebug() << "Found bad asset type!" << typeStr;
        }
    }

    // Close zone file
    zoneFile->close();

    // Clean up
    delete zoneFile;
    delete fastFile;
}

void MainWindow::on_pushButton_FastFile_2_clicked() {
    // Check zone file is writeable
    QFile *zoneFile;
    if (!(zoneFile = OpenZoneFile())) {
        QMessageBox::warning(this, "Warning!", QString("Failed to open FastFile!."));
        return;
    }
    const QByteArray decompressedData = zoneFile->readAll();

    // Open zone file as little endian stream
    QDataStream zoneFileStream(decompressedData);
    zoneFileStream.setByteOrder(QDataStream::LittleEndian);

    // Parse data from zone file header
    ParseZoneHeader(&zoneFileStream);
    ParseZoneIndex(&zoneFileStream);

    // Track current and consecutive assets
    int assetIndex = 0;

    // Iterate asset types found in index
    for (auto [assetType, assetCount] : mTypeMap.asKeyValueRange()) {
        // Get asset description from type
        QString assetStr = Utils::AssetTypeToString(assetType);

        // Insert row and populate
        ui->tableWidget_Index->insertRow(assetIndex);
        ui->tableWidget_Index->setItem(assetIndex, 0, new QTableWidgetItem(assetType));
        ui->tableWidget_Index->setItem(assetIndex, 1, new QTableWidgetItem(assetStr));
        ui->tableWidget_Index->setItem(assetIndex, 2, new QTableWidgetItem(QString::number(assetCount)));

        // Update count
        assetIndex++;
    }

    for (int i = 0; i < mTypeOrder.size(); i++) {
        const QString typeHex = mTypeOrder[i];
        const QString typeStr = Utils::AssetTypeToString(typeHex);

        // qDebug() << "Parsing Asset of Type: " << typeHex;
        if (typeStr == "LOCAL STRING") { // localized string asset
            ParseAsset_LocalString(&zoneFileStream);
        } else if (typeStr == "RAW FILE") { // gsc
            ParseAsset_RawFile(&zoneFileStream);
        } else if (typeStr == "PHYS PRESET") { // physpreset
            ParseAsset_PhysPreset(&zoneFileStream);
        } else if (typeStr == "MODEL") { // xmodel
            ParseAsset_XModel(&zoneFileStream);
        } else if (typeStr == "MATERIAL") { // material
            ParseAsset_Material(&zoneFileStream);
        } else if (typeStr == "SHADER") { // pixelshader
            ParseAsset_PixelShader(&zoneFileStream);
        } else if (typeStr == "BIK FILE") { // .bik file
            ParseAsset_BikFile(&zoneFileStream);
        } else if (typeStr == "IMAGE") { // image
            ParseAsset_Image(&zoneFileStream);
        } else if (typeStr == "SOUND") { // loaded_sound
            ParseAsset_LoadedSound(&zoneFileStream);
        } else if (typeStr == "COLLISION MAP") { // col_map_mp
            ParseAsset_ColMapMP(&zoneFileStream);
        } else if (typeStr == "MP MAP") { // game_map_sp
            ParseAsset_GameMapSP(&zoneFileStream);
        } else if (typeStr == "SP MAP") { // game_map_mp
            ParseAsset_GameMapMP(&zoneFileStream);
        } else if (typeStr == "LIGHT DEF") { // lightdef
            ParseAsset_LightDef(&zoneFileStream);
        } else if (typeStr == "UI MAP") { // ui_map
            ParseAsset_UIMap(&zoneFileStream);
        } else if (typeStr == "SND DRIVER GLOBALS") { // snddriverglobals
            ParseAsset_SNDDriverGlobals(&zoneFileStream);
        } else if (typeStr == "AI TYPE") { // aitype
            ParseAsset_AIType(&zoneFileStream);
        } else if (typeStr == "EFFECT") { // aitype
            ParseAsset_FX(&zoneFileStream);
        } else if (typeStr == "ANIMATION") { // aitype
            ParseAsset_XAnim(&zoneFileStream);
        } else if (typeStr == "STRING TABLE") { // string_table
            ParseAsset_StringTable(&zoneFileStream);
        } else if (typeStr == "MENU") { // string_table
            ParseAsset_MenuFile(&zoneFileStream);
        } else if (typeStr == "WEAPON") { // string_table
            ParseAsset_Weapon(&zoneFileStream);
        } else if (typeStr == "D3DBSP DUMP") { // string_table
            ParseAsset_D3DBSP(&zoneFileStream);
        } else if (typeStr == "TECH SET") { // string_table
            ParseAsset_TechSet(&zoneFileStream);
        } else {
            qDebug() << "Found bad asset type!" << typeStr;
        }
    }

    // Close zone file
    zoneFile->close();

    // Clean up
    delete zoneFile;
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

