#include "mainwindow.h"
#include "qheaderview.h"
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
    mTreeWidget = new QTreeWidget();
    mRootItem = mTreeWidget->invisibleRootItem();
    mScriptEditor = new QPlainTextEdit();
    mModelViewer = new ModelViewer();

    // Connect Help > About dialog
    connect(ui->actionAbout, &QAction::triggered, this, [this](bool checked) {
        Q_UNUSED(checked);

        AboutDialog *aboutDialog = new AboutDialog(this);
        aboutDialog->exec();

        delete aboutDialog;
    });

    connect(ui->actionOpen_Fast_File, &QAction::triggered, this, [this](bool checked) {
        Q_UNUSED(checked);
        OpenFastFile();
    });
    connect(ui->actionOpen_Zone_File, &QAction::triggered, this, [this](bool checked) {
        Q_UNUSED(checked);
        OpenZoneFile();
    });


    QDockWidget *treeDockWidget = new QDockWidget(this);
    mTreeWidget->header()->hide();
    treeDockWidget->setWidget(mTreeWidget);
    addDockWidget(Qt::LeftDockWidgetArea, treeDockWidget);

    setCentralWidget(mScriptEditor);

    LoadFile_D3DBSP(":/d3dbsp/data/d3dbsp/barebones.d3dbsp");

    Reset();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::Reset() {
    // Clear data tree
    mTreeWidget->clear();

    // Reset class vars
    mTypeMap.clear();
    mTypeOrder.clear();
    mTagCount = 0;
    mRecordCount = 0;
    mRawFileMap.clear();
    mTreeMap.clear();
    mStrTableMap.clear();
}

/*
    OpenFastFile()

    Opens a file dialog in the steam folder,
    and opens the selected file.
*/
bool MainWindow::OpenFastFile(const QString aFastFilePath) {
    if (aFastFilePath.isEmpty()) { return false; }

    // Reset dialog before opening new file
    Reset();

    // Add fast file as tree widget root
    const QString fastFileStem = aFastFilePath.split('/').last();
    QTreeWidgetItem *fastFileItem = new QTreeWidgetItem(mRootItem);
    fastFileItem->setText(0, fastFileStem);
    mRootItem = fastFileItem;

    // Check fastfile can be read
    QFile *fastFileObj = new QFile(aFastFilePath);
    if (!fastFileObj->open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Warning!", QString("Failed to open FastFile: %1!")
                                                   .arg(aFastFilePath));
        return false;
    }

    // Decompress fastfile and close
    const QByteArray fastFileData = fastFileObj->readAll();
    const QByteArray decompressedData = Compressor::DecompressZLIB(fastFileData);

    // Open zone file as little endian stream
    QDataStream fastFileStream(fastFileData);
    fastFileStream.setByteOrder(QDataStream::LittleEndian);

    // Parse data from fast file header
    FastFile fastFile = FastFileParser::ParseFFHeader(&fastFileStream);

    QTreeWidgetItem *metaDataItem = new QTreeWidgetItem(mRootItem);
    metaDataItem->setText(0, "Metadata");

    QTreeWidgetItem *companyItem = new QTreeWidgetItem(metaDataItem);
    companyItem->setText(0, "Company: " + Utils::CompanyEnumToStr(fastFile.company));
    QTreeWidgetItem *fileTypeItem = new QTreeWidgetItem(metaDataItem);
    fileTypeItem->setText(0, "File Type: " + Utils::FileTypeEnumToStr(fastFile.fileType));
    QTreeWidgetItem *signageItem = new QTreeWidgetItem(metaDataItem);
    signageItem->setText(0, "Signage: " + Utils::SignageEnumToStr(fastFile.signage));
    QTreeWidgetItem *magicItem = new QTreeWidgetItem(metaDataItem);
    magicItem->setText(0, "Magic: " + fastFile.magic);
    QTreeWidgetItem *versionItem = new QTreeWidgetItem(metaDataItem);
    versionItem->setText(0, "Version: " + QString::number(fastFile.version));

    const QString zoneFilePath = fastFileObj->fileName().replace(".ff", ".zone");
    fastFileObj->close();

    // Check zone file is writeable
    QFile *zoneFile = new QFile(zoneFilePath);
    if (!zoneFile->open(QIODevice::ReadWrite)) {
        qDebug() << QString("Zone file could not be written to: '%1'").arg(zoneFilePath);
        return false;
    }

    // Write zone data
    zoneFile->write(decompressedData);
    zoneFile->close();

    // Open zone file after decompressing ff and writing
    return OpenZoneFile(zoneFilePath);
}

/*
    OpenFastFile()

    Opens a file dialog in the steam folder,
    and opens the selected file.
*/
bool MainWindow::OpenFastFile() {
    const QString fastFileName = Utils::GetOpenFastFileName();
    if (!OpenFastFile(fastFileName)) {
        qDebug() << "Failed to open Fast file!";
        return false;
    }
    return true;
}

/*
    OpenZoneFile()

    Opens a file dialog in the steam folder,
    and opens the selected file.
*/
bool MainWindow::OpenZoneFile(const QString aZoneFilePath) {
    if (aZoneFilePath.isEmpty()) { return false; }

    // Reset dialog before opening new file
    //Reset();

    //ui->lineEdit_ZoneFile->setText(zoneFilePath);

    const QString zoneFileStem = aZoneFilePath.split('/').last();
    QTreeWidgetItem *zoneItem = new QTreeWidgetItem(mRootItem);
    zoneItem->setText(0, zoneFileStem);
    mRootItem = zoneItem;

    //setWindowTitle(QString("FastFile Wizard - %1").arg(zoneFileStem));

    // Check zone file can be read
    QFile *zoneFileObj = new QFile(aZoneFilePath);
    if (!zoneFileObj->open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Warning!", QString("%1 could not be read!.").arg(aZoneFilePath));
        return false;
    }
    const QByteArray decompressedData = zoneFileObj->readAll();

    // Open zone file as little endian stream
    QDataStream zoneFileStream(decompressedData);
    zoneFileStream.setByteOrder(QDataStream::LittleEndian);

    // Parse data from zone file header
    ZoneFile zoneFile = ZoneFileParser::ParseZoneHeader(&zoneFileStream);

    if (zoneFile.tagCount) {
        QTreeWidgetItem *tagsItem = new QTreeWidgetItem(mRootItem);
        tagsItem->setText(0, QString("Tags [%1]")
                                 .arg(zoneFile.tags.length()));
        foreach (const QString tag, zoneFile.tags) {
            QTreeWidgetItem *tagItem = new QTreeWidgetItem(tagsItem);
            tagItem->setText(0, tag);
        }
    }

    QTreeWidgetItem *indexRecordsItem = new QTreeWidgetItem(mRootItem);
    QTreeWidgetItem *assetsItem = new QTreeWidgetItem(mRootItem);

    mRootItem = indexRecordsItem;

    int consecutiveCount = 1;
    QString lastRecord = "";
    zoneFile.records = ZoneFileParser::ParseZoneIndex(&zoneFileStream, zoneFile.recordCount);
    indexRecordsItem->setText(0, QString("Index Records [%1]")
                                     .arg(zoneFile.records.length()));

    foreach (const QString record, zoneFile.records) {
        if (lastRecord.isEmpty()) {
            lastRecord = record;
            continue;
        } else if (lastRecord == record) {
            consecutiveCount++;
            continue;
        }
        QTreeWidgetItem *recordItem = new QTreeWidgetItem(mRootItem);
        recordItem->setText(0, QString("%1 [%2]")
                                   .arg(Utils::AssetTypeToString(lastRecord))
                                   .arg(consecutiveCount));
        lastRecord = record;
        consecutiveCount = 1;
    }

    mRootItem = assetsItem;

    // Parse current and consecutive assets
    AssetMap assetMap = ZoneFileParser::ParseAssets(&zoneFileStream, zoneFile.records);
    assetsItem->setText(0, QString("Assets"));

    if (!assetMap.rawFiles.isEmpty()) {
        QTreeWidgetItem *rawFilesItem = new QTreeWidgetItem(mRootItem);
        foreach (const RawFile rawFile, assetMap.rawFiles) {
            QTreeWidgetItem *rawFileItem = new QTreeWidgetItem(rawFilesItem);
            rawFileItem->setText(0, rawFile.path);
        }
        rawFilesItem->setText(0, QString("Raw Files [%1]")
                                     .arg(assetMap.rawFiles.length()));
    }

    if (!assetMap.localStrings.isEmpty()) {
        QTreeWidgetItem *localStrsItem = new QTreeWidgetItem(mRootItem);
        foreach (const LocalString localString, assetMap.localStrings) {
            QTreeWidgetItem *localStrItem = new QTreeWidgetItem(localStrsItem);
            localStrItem->setText(0, localString.string);
        }
        localStrsItem->setText(0, QString("Local Strings [%1]")
                                     .arg(assetMap.localStrings.length()));
    }

    if (!assetMap.stringTables.isEmpty()) {
        QTreeWidgetItem *strTablesItem = new QTreeWidgetItem(mRootItem);
        foreach (const StringTable stringTable, assetMap.stringTables) {
            QTreeWidgetItem *strTableItem = new QTreeWidgetItem(strTablesItem);
            strTableItem->setText(0, stringTable.name);
        }
        strTablesItem->setText(0, QString("String Tables [%1]")
                                      .arg(assetMap.stringTables.length()));
    }

    if (!assetMap.techSets.isEmpty()) {
        QTreeWidgetItem *techSetsItem = new QTreeWidgetItem(mRootItem);
        foreach (const TechSet techSet, assetMap.techSets) {
            QTreeWidgetItem *techSetItem = new QTreeWidgetItem(techSetsItem);
            techSetItem->setText(0, techSet.name);
        }
        techSetsItem->setText(0, QString("Tech Sets [%1]")
                                      .arg(assetMap.techSets.length()));
    }

    if (!assetMap.animations.isEmpty()) {
        QTreeWidgetItem *animationsItem = new QTreeWidgetItem(mRootItem);
        animationsItem->setText(0, "Animations");
        foreach (const Animation animation, assetMap.animations) {
            QTreeWidgetItem *animationItem = new QTreeWidgetItem(animationsItem);
            animationItem->setText(0, animation.name);
        }
        animationsItem->setText(0, QString("Animations [%1]")
                                     .arg(assetMap.animations.length()));
    }

    // Clean up zone file
    zoneFileObj->close();
    delete zoneFileObj;

    return true;
}

bool MainWindow::OpenZoneFile() {
    const QString zoneFileName = Utils::GetOpenZoneFileName();
    if (!OpenZoneFile(zoneFileName)) {
        qDebug() << "Failed to open Zone file!";
        return false;
    }
    mRootItem = mTreeWidget->invisibleRootItem();
    return true;
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

