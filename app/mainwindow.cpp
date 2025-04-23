#include "mainwindow.h"
#include "aboutdialog.h"
#include "fastfile.h"
#include "materialviewer.h"
#include "preferenceeditor.h"
#include "soundviewer.h"
#include "stringtableviewer.h"
#include "techsetviewer.h"
#include "ui_mainwindow.h"
#include "compression.h"
#include "iwifile.h"
#include "ddsfile.h"
#include "statusbarmanager.h"
#include "ddsviewer.h"
#include "fastfileviewer.h"
#include "ipak_structs.h"
#include "iwiviewer.h"
#include "localstringviewer.h"
#include "imagewidget.h"
#include "xtreewidget.h"
#include "zonefileviewer.h"
#include "techsetviewer.h"
#include "logmanager.h"

#include <qmath.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setAcceptDrops(true);

    mTypeMap = QMap<QString, int>();
    mTypeOrder = QStringList();
    mRawFileMap = QMap<QString, QString>();
    mImageMap = QMap<QString, Image>();
    mTreeMap = QMap<QString, QTreeWidgetItem *>();
    mStrTableMap = QMap<QString, QVector<QPair<QString, QString>>>();
    mBSPVersion = 0;
    mDiskLumpCount = 0;
    mDiskLumpOrder = QVector<quint32>();
    mLumps = QMap<quint32, Lump>();
    mTreeWidget = new XTreeWidget(this);
    mLogWidget = new QPlainTextEdit(this);

    //ModelViewer *mModelViewer = new ModelViewer(container);
    //mModelViewer->setAcceptDrops(false);

    mProgressBar = new QProgressBar(this);
    mProgressBar->setMaximum(100);  // Default max value
    mProgressBar->setVisible(false); // Initially hidden

    connect(&StatusBarManager::instance(), &StatusBarManager::statusUpdated,
            this, &MainWindow::HandleStatusUpdate);

    connect(&StatusBarManager::instance(), &StatusBarManager::progressUpdated,
            this, &MainWindow::HandleProgressUpdate);

    connect(&LogManager::instance(), &LogManager::entryAdded,
            this, &MainWindow::HandleLogEntry);

    statusBar()->addPermanentWidget(mProgressBar);

    connect(ui->actionPreferences, &QAction::triggered, this, [this](bool checked) {
        Q_UNUSED(checked);

        PreferenceEditor *prefEditor = new PreferenceEditor(this);
        prefEditor->exec();
    });

    ui->tabWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tabWidget, &QTabWidget::customContextMenuRequested, this, [this](const QPoint &pos) {
        if (pos.isNull())
            return;

        int tabIndex = ui->tabWidget->tabBar()->tabAt(pos);
        QMenu *contextMenu = new QMenu(this);

        QAction *closeAction = new QAction("Close");
        contextMenu->addAction(closeAction);
        connect(closeAction, &QAction::triggered, this, [this, &tabIndex](bool checked) {
            Q_UNUSED(checked);

            ui->tabWidget->removeTab(tabIndex);
        });

        QMenu *closeMultipleAction = new QMenu("Close Multiple Tabs");

        QAction *closeAllAction = new QAction("Close All");
        closeMultipleAction->addAction(closeAllAction);
        connect(closeAllAction, &QAction::triggered, this, [this](bool checked) {
            Q_UNUSED(checked);

            ui->tabWidget->clear();
        });

        QAction *closeAllButAction = new QAction("Close All BUT This");
        closeMultipleAction->addAction(closeAllButAction);
        connect(closeAllButAction, &QAction::triggered, this, [this, &tabIndex](bool checked) {
            Q_UNUSED(checked);

            for (int i = 0; i < ui->tabWidget->count(); i++) {
                if (i != tabIndex) {
                    ui->tabWidget->removeTab(i);
                }
            }
        });

        QAction *closeLeftAction = new QAction("Close All to the Left");
        closeMultipleAction->addAction(closeLeftAction);
        connect(closeLeftAction, &QAction::triggered, this, [this, &tabIndex](bool checked) {
            Q_UNUSED(checked);

            for (int i = 0; i < tabIndex; i++) {
                ui->tabWidget->removeTab(i);
            }
        });

        QAction *closeRightAction = new QAction("Close All to the Right");
        closeMultipleAction->addAction(closeRightAction);
        connect(closeRightAction, &QAction::triggered, this, [this, &tabIndex](bool checked) {
            Q_UNUSED(checked);

            for (int i = tabIndex + 1; i < ui->tabWidget->count(); i++) {
                ui->tabWidget->removeTab(i);
            }
        });

        contextMenu->addMenu(closeMultipleAction);

        QPoint pt(pos);
        contextMenu->exec(ui->tabWidget->mapToGlobal(pt));

        delete contextMenu;
    });

    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, [this](int index) {
        ui->tabWidget->removeTab(index);
    });

    connect(mTreeWidget, &XTreeWidget::Cleared, this, [this]() {
        ui->tabWidget->clear();
    });

    connect(mTreeWidget, &XTreeWidget::RawFileSelected, this, [this](std::shared_ptr<RawFile> rawFile, const QString aParentName) {
        QPlainTextEdit *scriptEditor = new QPlainTextEdit(this);
        scriptEditor->setAcceptDrops(false);
        scriptEditor->setProperty("PARENT_NAME", QVariant::fromValue(aParentName));

        if (rawFile->contents.isEmpty()) {
            scriptEditor->setPlainText("EMPTY");
        } else {
            scriptEditor->setPlainText(rawFile->contents);
        }

        QString fileStem = rawFile->path.split('/').last();
        for (int i = 0; i < ui->tabWidget->count(); i++) {
            if (ui->tabWidget->tabText(i) == fileStem) {
                return;
            }
        }

        QScrollArea *scrollArea = new QScrollArea(ui->tabWidget);
        scrollArea->layout()->addWidget(scriptEditor);

        ui->tabWidget->addTab(scrollArea, fileStem);
        ui->tabWidget->setTabIcon(ui->tabWidget->count() - 1, QIcon(":/icons/icons/Icon_GSCFile.png"));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    });

    connect(mTreeWidget, &XTreeWidget::ImageSelected, this, [this](std::shared_ptr<Image> image, const QString aParentName) {
        ImageWidget *mImageWidget = new ImageWidget(this);
        mImageWidget->setAcceptDrops(false);
        mImageWidget->SetImage(image);
        mImageWidget->setProperty("PARENT_NAME", QVariant::fromValue(aParentName));

        QString fileStem = image->materialName;
        for (int i = 0; i < ui->tabWidget->count(); i++) {
            if (ui->tabWidget->tabText(i) == fileStem) {
                return;
            }
        }

        ui->tabWidget->addTab(mImageWidget, fileStem);
        ui->tabWidget->setTabIcon(ui->tabWidget->count() - 1, QIcon(":/icons/icons/Icon_Image.png"));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    });

    connect(mTreeWidget, &XTreeWidget::MenuSelected, this, [](std::shared_ptr<Menu> menu, const QString aParentName) {
        Q_UNUSED(menu);
    });

    connect(mTreeWidget, &XTreeWidget::DDSFileSelected, this, [this](std::shared_ptr<DDSFile> ddsFile, const QString aParentName) {
        DDSViewer *ddsViewer = new DDSViewer(this);
        ddsViewer->setAcceptDrops(false);
        ddsViewer->SetDDSFile(ddsFile);
        ddsViewer->setProperty("PARENT_NAME", QVariant::fromValue(aParentName));

        QString fileStem = ddsFile->fileStem + ".dds";
        for (int i = 0; i < ui->tabWidget->count(); i++) {
            if (ui->tabWidget->tabText(i) == fileStem) {
                return;
            }
        }

        ui->tabWidget->addTab(ddsViewer, fileStem);
        ui->tabWidget->setTabIcon(ui->tabWidget->count() - 1, QIcon(":/icons/icons/Icon_DDSFile.png"));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    });

    connect(mTreeWidget, &XTreeWidget::MaterialSelected, this, [this](std::shared_ptr<Material> material, const QString aParentName) {
        MaterialViewer *matViewer = new MaterialViewer(this);
        matViewer->setAcceptDrops(false);
        matViewer->SetMaterial(material);
        matViewer->setProperty("PARENT_NAME", QVariant::fromValue(aParentName));

        QString fileStem = material->name;
        for (int i = 0; i < ui->tabWidget->count(); i++) {
            if (ui->tabWidget->tabText(i) == fileStem) {
                return;
            }
        }

        ui->tabWidget->addTab(matViewer, fileStem);
        ui->tabWidget->setTabIcon(ui->tabWidget->count() - 1, QIcon(":/icons/icons/Icon_Material.png"));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    });

    connect(mTreeWidget, &XTreeWidget::DDSFileSelected, this, [this](std::shared_ptr<DDSFile> ddsFile, const QString aParentName) {
        DDSViewer *ddsViewer = new DDSViewer(this);
        ddsViewer->setAcceptDrops(false);
        ddsViewer->SetDDSFile(ddsFile);
        ddsViewer->setProperty("PARENT_NAME", QVariant::fromValue(aParentName));

        QString fileStem = ddsFile->fileStem + ".dds";
        for (int i = 0; i < ui->tabWidget->count(); i++) {
            if (ui->tabWidget->tabText(i) == fileStem) {
                return;
            }
        }

        ui->tabWidget->addTab(ddsViewer, fileStem);
        ui->tabWidget->setTabIcon(ui->tabWidget->count() - 1, QIcon(":/icons/icons/Icon_DDSFile.png"));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    });

    connect(mTreeWidget, &XTreeWidget::IWIFileSelected, this, [this](std::shared_ptr<IWIFile> iwiFile, const QString aParentName) {
        IWIViewer *iwiViewer = new IWIViewer(this);
        iwiViewer->setAcceptDrops(false);
        iwiViewer->SetIWIFile(iwiFile);
        iwiViewer->setProperty("PARENT_NAME", QVariant::fromValue(aParentName));

        QString fileStem = iwiFile->fileStem + ".iwi";
        for (int i = 0; i < ui->tabWidget->count(); i++) {
            if (ui->tabWidget->tabText(i) == fileStem) {
                return;
            }
        }

        ui->tabWidget->addTab(iwiViewer, fileStem);
        ui->tabWidget->setTabIcon(ui->tabWidget->count() - 1, QIcon(":/icons/icons/Icon_IWIFile.png"));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    });

    connect(mTreeWidget, &XTreeWidget::FastFileSelected, this, [this](std::shared_ptr<FastFile> aFastFile, const QString aParentName) {
        FastFileViewer *fastFileViewer = new FastFileViewer(this);
        fastFileViewer->setAcceptDrops(false);
        fastFileViewer->SetFastFile(aFastFile);
        fastFileViewer->setProperty("PARENT_NAME", QVariant::fromValue(aParentName));

        QString fileStem = aFastFile->GetStem() + ".ff";
        for (int i = 0; i < ui->tabWidget->count(); i++) {
            if (ui->tabWidget->tabText(i) == fileStem) {
                return;
            }
        }

        ui->tabWidget->addTab(fastFileViewer, fileStem);
        ui->tabWidget->setTabIcon(ui->tabWidget->count() - 1, QIcon(":/icons/icons/Icon_FastFile.png"));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    });

    connect(mTreeWidget, &XTreeWidget::ZoneFileSelected, this, [this](std::shared_ptr<ZoneFile> aZoneFile, const QString aParentName) {
        ZoneFileViewer *zoneFileViewer = new ZoneFileViewer(this);
        zoneFileViewer->setAcceptDrops(false);
        zoneFileViewer->SetZoneFile(aZoneFile);
        zoneFileViewer->setProperty("PARENT_NAME", QVariant::fromValue(aParentName));

        QString fileStem = aZoneFile->GetStem() + ".zone";
        for (int i = 0; i < ui->tabWidget->count(); i++) {
            if (ui->tabWidget->tabText(i) == fileStem) {
                return;
            }
        }

        QWidget *containerWidget = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(containerWidget);
        layout->addWidget(zoneFileViewer);
        containerWidget->setLayout(layout);

        // Create a scroll area and set its properties
        QScrollArea *scrollArea = new QScrollArea(ui->tabWidget);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true); // Important to allow resizing
        scrollArea->setWidget(containerWidget);

        ui->tabWidget->addTab(scrollArea, fileStem);
        ui->tabWidget->setTabIcon(ui->tabWidget->count() - 1, QIcon(":/icons/icons/Icon_ZoneFile.png"));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    });

    connect(mTreeWidget, &XTreeWidget::LocalStringSelected, this, [this](std::shared_ptr<ZoneFile> aZoneFile, const QString aParentName) {
        LocalStringViewer *localStrViewer = new LocalStringViewer(this);
        localStrViewer->setAcceptDrops(false);
        localStrViewer->SetZoneFile(aZoneFile);
        localStrViewer->setProperty("PARENT_NAME", QVariant::fromValue(aParentName));

        QString fileStem = aZoneFile->GetStem() + ".str";
        for (int i = 0; i < ui->tabWidget->count(); i++) {
            if (ui->tabWidget->tabText(i) == fileStem) {
                return;
            }
        }

        ui->tabWidget->addTab(localStrViewer, fileStem);
        ui->tabWidget->setTabIcon(ui->tabWidget->count() - 1, QIcon(":/icons/icons/Icon_String.png"));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    });

    connect(mTreeWidget, &XTreeWidget::TechSetSelected, this, [this](std::shared_ptr<TechSet> aTechSet, const QString aParentName) {
        TechSetViewer *techSetViewer = new TechSetViewer(this);
        techSetViewer->setAcceptDrops(false);
        techSetViewer->SetTechSet(aTechSet);
        techSetViewer->setProperty("PARENT_NAME", QVariant::fromValue(aParentName));

        QString fileStem = aTechSet->name;
        for (int i = 0; i < ui->tabWidget->count(); i++) {
            if (ui->tabWidget->tabText(i) == fileStem) {
                return;
            }
        }

        ui->tabWidget->addTab(techSetViewer, aTechSet->name);
        ui->tabWidget->setTabIcon(ui->tabWidget->count() - 1, QIcon(":/icons/icons/Icon_TechSetFile.png"));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    });

    connect(mTreeWidget, &XTreeWidget::StrTableSelected, this, [this](std::shared_ptr<StringTable> aStrTable, const QString aParentName) {
        StringTableViewer *strTableViewer = new StringTableViewer(this);
        strTableViewer->setAcceptDrops(false);
        strTableViewer->SetStringTable(aStrTable);
        strTableViewer->setProperty("PARENT_NAME", QVariant::fromValue(aParentName));

        QString fileStem = aStrTable->name;
        for (int i = 0; i < ui->tabWidget->count(); i++) {
            if (ui->tabWidget->tabText(i) == fileStem) {
                return;
            }
        }

        ui->tabWidget->addTab(strTableViewer, fileStem);
        ui->tabWidget->setTabIcon(ui->tabWidget->count() - 1, QIcon(":/icons/icons/Icon_StringTable.png"));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    });

    connect(mTreeWidget, &XTreeWidget::SoundSelected, this, [this](std::shared_ptr<Sound> aSound, const QString aParentName) {
        SoundViewer *soundViewer = new SoundViewer(this);
        soundViewer->setAcceptDrops(false);
        soundViewer->SetSound(aSound);
        soundViewer->setProperty("PARENT_NAME", QVariant::fromValue(aParentName));

        QString fileStem = aSound->path.split('/').last();
        for (int i = 0; i < ui->tabWidget->count(); i++) {
            if (ui->tabWidget->tabText(i) == fileStem) {
                return;
            }
        }

        ui->tabWidget->addTab(soundViewer, fileStem);
        ui->tabWidget->setTabIcon(ui->tabWidget->count() - 1, QIcon(":/icons/icons/Icon_Sound.png"));
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    });

    connect(mTreeWidget, &XTreeWidget::ItemSelected, this, [this](const QString itemText) {
        for (int i = 0; i < ui->tabWidget->count(); i++) {
            if (ui->tabWidget->tabText(i) == itemText) {
                ui->tabWidget->setCurrentIndex(i);
                break;
            }
        }
    });

    connect(mTreeWidget, &XTreeWidget::ItemClosed, this, [this](const QString itemText) {
        for (int i = 0; i < ui->tabWidget->count(); i++) {
            const QString parentName = ui->tabWidget->widget(i)->property("PARENT_NAME").toString();
            if (parentName == itemText) {
                ui->tabWidget->removeTab(i);
                break;
            }
        }
    });

    // Connect Help > About dialog
    connect(ui->actionAbout, &QAction::triggered, this, [this](bool checked) {
        Q_UNUSED(checked);

        AboutDialog *aboutDialog = new AboutDialog(this);
        aboutDialog->exec();

        delete aboutDialog;
    });

    connect(ui->actionOpen_Fast_File, &QAction::triggered, this,
            [this](bool checked) {
                Q_UNUSED(checked);
                OpenFastFile();
            });
    connect(ui->actionOpen_Zone_File, &QAction::triggered, this,
            [this](bool checked) {
                Q_UNUSED(checked);
                OpenZoneFile();
            });

    QDockWidget *treeDockWidget = new QDockWidget(this);
    treeDockWidget->setWidget(mTreeWidget);
    treeDockWidget->setWindowTitle("Tree Browser");
    addDockWidget(Qt::LeftDockWidgetArea, treeDockWidget);

    QDockWidget *logDockWidget = new QDockWidget(this);
    logDockWidget->setWidget(mLogWidget);
    logDockWidget->setWindowTitle("Logs");
    addDockWidget(Qt::RightDockWidgetArea, logDockWidget);

    ui->toolBar->addAction(ui->actionNew_Fast_File);
    ui->toolBar->addAction(ui->actionNew_Zone_File);
    ui->toolBar->addAction(ui->actionOpen_Fast_File);
    ui->toolBar->addAction(ui->actionOpen_Zone_File);
    ui->toolBar->addAction(ui->actionOpen_Folder);
    ui->toolBar->addAction(ui->actionSave);
    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actionCut);
    ui->toolBar->addAction(ui->actionCopy);
    ui->toolBar->addAction(ui->actionPaste);
    ui->toolBar->addSeparator();

    ui->toolBar->addSeparator();

    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->actionFind_2);

    Reset();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::Reset() {
    // Clear data tree
    // mTreeWidget->clear();

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
    const QString fastFileStem = aFastFilePath.section("/", -1, -1).section('.', 0, 0);
    if (mTreeWidget->HasFastFile(fastFileStem)) {
        LogManager::instance().addError("Can't add duplicate file!");
        return false;
    }

    std::shared_ptr<FastFile> fastFile = FastFile::Open(aFastFilePath);
    fastFile->SetStem(fastFileStem);
    mTreeWidget->AddFastFile(fastFile);

    // Open zone file after decompressing ff and writing
    return true;
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
bool MainWindow::OpenZoneFile(const QString aZoneFilePath, bool fromFF) {
    Q_UNUSED(aZoneFilePath);
    Q_UNUSED(fromFF);

    //ZoneFile zoneFile;
    //if (!zoneFile.Load(aZoneFilePath)) {
    //    qDebug() << "Error: Failed to load zone file!";
    //    return false;
    //}
    //mTreeWidget->AddZoneFile(std::make_shared<ZoneFile>(zoneFile));

    return true;
}

bool MainWindow::OpenZoneFile() {
    const QString zoneFileName = Utils::GetOpenZoneFileName();
    if (!OpenZoneFile(zoneFileName)) {
        qDebug() << "Failed to open Zone file!";
        return false;
    }
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
    quint32 lumpOffset =
        sizeof(quint32) * 3 + sizeof(LumpIndexEntry) * mDiskLumpCount;

    for (quint32 i = 0; i < mDiskLumpCount; i++) {
        LumpIndexEntry indexEntry;
        stream >> indexEntry.type >> indexEntry.length;

        mDiskLumpOrder[i] = indexEntry.type;

        Lump &lump = mLumps[indexEntry.type];
        lump.size = indexEntry.length;
        lump.content.resize(indexEntry.length);
        lump.isEmpty = false;

        qDebug() << "Lump Type:"
                 << Utils::LumpTypeToString((LUMP_TYPE)indexEntry.type)
                 << "Lump Size:" << indexEntry.length;

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

struct Command {
    quint32 size = 0;
    bool compressed = false;
};
quint32 DXT1 = 0x31545844;  // 'DXT1'
quint32 DXT3 = 0x33545844;  // 'DXT3'
quint32 DXT5 = 0x35545844;  // 'DXT5'

int MainWindow::LoadFile_IWI(const QString aFilePath) {
    mTreeWidget->AddIWIFile(std::make_shared<IWIFile>(aFilePath));

    return 0;
}

int MainWindow::LoadFile_DDSFiles(const QStringList aFilePaths) {
    for (const QString &filePath : aFilePaths) {
        if (!filePath.endsWith(".dds", Qt::CaseInsensitive)) {
            qDebug() << "Error: Invalid filename " << filePath;
            return -1;
        }
        mTreeWidget->AddDDSFile(std::make_shared<DDSFile>(filePath));
    }
    return 0;
}

void MainWindow::HandleLogEntry(const QString &entry) {
    QString logContents = mLogWidget->toPlainText() + "\n" + entry;
    if (mLogWidget->toPlainText().isEmpty()) {
        logContents = entry;
    }
    mLogWidget->setPlainText(logContents);
}

void MainWindow::HandleStatusUpdate(const QString &message, int timeout) {
    statusBar()->showMessage(message, timeout);
    mProgressBar->setVisible(false); // Hide progress bar if just a message
}

void MainWindow::HandleProgressUpdate(const QString &message, int progress, int max) {
    mProgressBar->setMaximum(max);
    mProgressBar->setValue(progress);
    mProgressBar->setVisible(true);

    QString progressText = QString("%1 (%2/%3)").arg(message).arg(progress).arg(max);
    statusBar()->showMessage(progressText);
}

int MainWindow::LoadFile_DDS(const QString aFilePath) {
    if (!aFilePath.endsWith(".dds", Qt::CaseInsensitive)) {
        qDebug() << "Error: Invalid filename " << aFilePath;
        return -1;
    }
    mTreeWidget->AddDDSFile(std::make_shared<DDSFile>(aFilePath));
    return 0;
}

int MainWindow::LoadFile_XSUB(const QString aFilePath) {
    QFile file(aFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error: Unable to open file" << aFilePath;
        return 1; // ERR_FILE_NOT_FOUND
    }

    QDataStream stream(&file);
    stream.setByteOrder(QDataStream::LittleEndian);

    QByteArray magic(4, Qt::Uninitialized);
    stream.readRawData(magic.data(), 4);
    if (magic != "KAPI") {
        qDebug() << "Wrong magic, invalid XSUB file!";
        return -1;
    }
    qDebug() << "Magic: " << magic;

    stream.skipRawData(5 * 4);

    quint32 fileSize;
    stream >> fileSize;
    qDebug() << "File Size: " << fileSize;

    return 0; // Success
}

int MainWindow::LoadFile_IPAK(const QString aFilePath) {
    QFile file(aFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error: Unable to open file" << aFilePath;
        return 1; // ERR_FILE_NOT_FOUND
    }

    QDataStream stream(&file);
    stream.setByteOrder(QDataStream::BigEndian);

    IPAKHeader header;
    stream >> header;

    if (header.version == "50000") {
        if (header.magic == "KAPI") {
            stream.setByteOrder(QDataStream::LittleEndian);
        } else if (header.magic == "IPAK") {
            stream.setByteOrder(QDataStream::BigEndian);
        } else {
            qDebug() << "Invalid IPAK file!";
            return -1;
        }
    } else {
        qDebug() << "Invalid IPAK file version!";
        return -1;
    }

    qDebug() << "IPAK File " << "\n"
             << "- Platform: " << header.platform << "\n"
             << "- Magic: " << header.magic << "\n"
             << "- Size: " << header.size << "\n"
             << "- Version: " << header.version << "\n"
             << "- Sections: " << header.sectionCount;

    QDir outputFolder = QDir(QDir::currentPath() + "/output");
    outputFolder.remove(QDir::currentPath() + "/output");
    outputFolder.mkdir(QDir::currentPath() + "/output");

    QVector<IPAKDataChunkMetaData> metas = QVector<IPAKDataChunkMetaData>();

    QVector<IPAKIndexEntry> entries = QVector<IPAKIndexEntry>();
    QVector<IPAKSection> sections = QVector<IPAKSection>(header.sectionCount);
    for (uint i = 0; i < header.sectionCount; i++) {
        IPAKSection currentSection;
        stream >> currentSection;
        sections << currentSection;

        qDebug() << "   - IPAK Section " << i + 1 << "\n"
                 << "    - Type: " << currentSection.type << " -> " << currentSection.typeInt << "\n"
                 << "    - Offset: " << currentSection.offset << "\n"
                 << "    - Item (IWI) Count: " << currentSection.itemCount << "\n"
                 << "    - Size: " << currentSection.size;

        qint64 sectionPos = stream.device()->pos();
        stream.device()->seek(currentSection.offset);

        QString sectionType = currentSection.type;
        if (sectionType == "Data") {
            IPAKDataChunkHeader chunkHeader;
            stream >> chunkHeader;
            qDebug() << "     - Chunk Header\n"
                     << "      - Count: " << chunkHeader.count << "\n"
                     << "      - Offset: " << chunkHeader.offset;

            for (uint j = 0; j < 31; j++) {
                IPAKDataChunkCommand command;
                stream >> command;
                if (!command.size) { continue; }
                chunkHeader.commands << command;
                qDebug() << "         - Command\n"
                         << "          - Size: " << command.size << "\n"
                         << "          - Compressed: " << command.compressed;

            }
            for (uint j = 0; j < chunkHeader.count; j++) {
                auto command = chunkHeader.commands[j];

                qDebug() << "Reading from " << stream.device()->pos();
                QByteArray data = stream.device()->read(command.size);
                qDebug() << " to " << stream.device()->pos();

                QString outputFilePath = outputFolder.filePath(QString("%1.iwi").arg(j));
                if (command.compressed) {
                    //data = Compression::DecompressLZO(data);
                }
                QFile outputFile(outputFilePath);
                if (!outputFile.open(QIODevice::WriteOnly)) {
                    qDebug() << "Failed to extract IPAK file.";
                }
                qDebug() << "           - File Name: " << outputFile.fileName();
                outputFile.write(data);
                outputFile.close();
            }


            qDebug() << stream.device()->pos();
            stream.skipRawData(sizeof(quint32) * (31 - chunkHeader.count));
            qDebug() << stream.device()->pos();
        } else if (sectionType == "Index") {
            for (uint j = 0; j < currentSection.itemCount; j++) {
                IPAKIndexEntry entry;
                stream >> entry;

                if (entry.size == 0) { continue; }

                entries << entry;

                quint64 entryPos = stream.device()->pos();
                qDebug() << "     - Index Entry " << j + 1 << "\n"
                         << "      - Name Hash: " << entry.nameHash << "\n"
                         << "      - Data Hash: " << entry.dataHash << "\n"
                         << "      - Offset: " << entry.offset << "\n"
                         << "      - Size: " << entry.size;

                stream.device()->seek(entry.offset);

                QByteArray sectionData(entry.size, Qt::Uninitialized);
                stream.readRawData(sectionData.data(), entry.size);

                const QString entryKey = QString::number(entry.nameHash);
                QFile outputFile(outputFolder.filePath(QString("%1.dds").arg(entryKey)));
                if (!outputFile.open(QIODevice::WriteOnly)) {
                    qDebug() << "Failed to extract IPAK file.";
                }
                qDebug() << "      - File Name: " << outputFile.fileName();
                outputFile.write(sectionData);
                outputFile.close();

                stream.device()->seek(entryPos);
            }
        }
        stream.device()->seek(sectionPos);
        qDebug() << stream.device()->pos();
    }

    return 0; // Success
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    const QMimeData *mimeData = event->mimeData();
    bool goodDrag = true;
    if (mimeData->hasUrls()) {
        foreach (const QUrl url, mimeData->urls()) {
            if (!url.toString().contains(".ff") &&
                !url.toString().contains(".zone") &&
                !url.toString().contains(".ipak") &&
                !url.toString().contains(".d3dbsp") &&
                !url.toString().contains(".lzoin") &&
                !url.toString().contains(".xsub") &&
                !url.toString().contains(".iwi") &&
                !url.toString().contains(".dds")) {
                goodDrag = false;
            }
        }
    } else {
        goodDrag = false;
    }
    if (goodDrag) {
        event->acceptProposedAction();
    }
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event) {
    Q_UNUSED(event);
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent *event) {
    Q_UNUSED(event);
}

void MainWindow::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        QStringList ddsPaths = QStringList();
        foreach (const QUrl url, mimeData->urls()) {
            const QString urlStr = url.toLocalFile();
            if (urlStr.contains(".zone")) {
                qDebug() << "OpenZoneFile Returned: " << OpenZoneFile(urlStr);
            } else if (urlStr.contains(".ff")) {
                qDebug() << "OpenFastFile Returned: " << OpenFastFile(urlStr);
            } else if (urlStr.contains(".ipak")) {
                qDebug() << "LoadFile_IPAK Returned: " << LoadFile_IPAK(urlStr);
            } else if (urlStr.contains(".xsub")) {
                qDebug() << "LoadFile_XSUB Returned: " << LoadFile_XSUB(urlStr);
            } else if (urlStr.contains(".iwi")) {
                qDebug() << "LoadFile_IWI Returned: " << LoadFile_IWI(urlStr);
            } else if (urlStr.contains(".dds")) {
                if (mimeData->urls().size() == 1) {
                    qDebug() << "LoadFile_DDS Returned: " << LoadFile_DDS(urlStr);
                } else {
                    ddsPaths << urlStr;
                }
            } else if (urlStr.contains(".d3dbsp")) {
                LoadFile_D3DBSP(urlStr);
            } else if (urlStr.contains(".lzoin")) {
                QFile lzoFile(urlStr);
                if (!lzoFile.open(QIODevice::ReadOnly)) {
                    qDebug() << "LZO: Failed to read file!";
                    continue;
                }
                QByteArray data;// = Compression::DecompressLZO(lzoFile.readAll());
                lzoFile.close();

                if (data.isEmpty()) {
                    qDebug() << "LZO: Decompression gave empty result!";
                    continue;
                }

                QFile outputFile(url.toLocalFile().replace("lzoin", "lzoout"));
                if (!outputFile.open(QIODevice::WriteOnly)) {
                    qDebug() << "LZO: Failed to write file!";
                    continue;
                }
                outputFile.write(data);
                outputFile.close();
            } else {
                const QString ext = urlStr.split('.').last();
                ui->statusBar->showMessage(
                    QString("Can't display dropped file! .%1").arg(ext));
            }
        }
        if (ddsPaths.size() > 1) {
            qDebug() << "LoadFile_DDSFiles Returned: " << LoadFile_DDSFiles(ddsPaths);
        }
    } else {
        ui->statusBar->showMessage("Can't display dropped data!");
    }
}
