#include "xtreewidget.h"
#include "qheaderview.h"
#include "qmenu.h"
#include "utils.h"

XTreeWidget::XTreeWidget(QWidget *parent)
    : QTreeWidget(parent) {
    mFastFiles = QMap<QString, std::shared_ptr<FastFile>>();
    mZoneFiles = QMap<QString, std::shared_ptr<ZoneFile>>();
    mDDSFiles = QMap<QString, std::shared_ptr<DDSFile>>();
    mIWIFiles = QMap<QString, std::shared_ptr<IWIFile>>();

    setContextMenuPolicy(Qt::CustomContextMenu);
    setSelectionMode(QTreeWidget::SingleSelection);
    setColumnCount(3);
    setColumnWidth(0, 275);
    setColumnWidth(1, 50);
    setColumnWidth(2, 50);
    header()->hide();
    setMinimumWidth(350);

    connect(this, &QTreeWidget::itemSelectionChanged, this, &XTreeWidget::ItemSelectionChanged);
    connect(this, &XTreeWidget::customContextMenuRequested, this, &XTreeWidget::PrepareContextMenu);
}

XTreeWidget::~XTreeWidget() {

}

void XTreeWidget::AddFastFile(std::shared_ptr<FastFile> aFastFile) {
    QTreeWidgetItem *fastFileItem = new QTreeWidgetItem(this);
    fastFileItem->setText(0, aFastFile->GetFileStem());
    fastFileItem->setIcon(0, QIcon(":/icons/icons/Icon_FastFile.png"));
    if (aFastFile->GetPlatform() == "PC") {
        fastFileItem->setIcon(1, QIcon(":/icons/icons/Icon_PC.png"));
    } else if (aFastFile->GetPlatform() == "360") {
        fastFileItem->setIcon(1, QIcon(":/icons/icons/Icon_Xbox.png"));
    }
    if (aFastFile->GetGame() == "COD4") {
        fastFileItem->setIcon(2, QIcon(":/icons/icons/Icon_COD4.png"));
    } else if (aFastFile->GetGame() == "COD5") {
        fastFileItem->setIcon(2, QIcon(":/icons/icons/Icon_COD5.png"));
    } else if (aFastFile->GetGame() == "COD6") {
        fastFileItem->setIcon(2, QIcon(":/icons/icons/Icon_COD6.png"));
    } else if (aFastFile->GetGame() == "COD7") {
        fastFileItem->setIcon(2, QIcon(":/icons/icons/Icon_COD7.png"));
    } else if (aFastFile->GetGame() == "COD8") {
        fastFileItem->setIcon(2, QIcon(":/icons/icons/Icon_COD8.png"));
    } else if (aFastFile->GetGame() == "COD9") {
        fastFileItem->setIcon(2, QIcon(":/icons/icons/Icon_COD9.png"));
    }

    AddZoneFile(std::make_shared<ZoneFile>(aFastFile->GetZoneFile()), fastFileItem);

    mFastFiles[aFastFile->GetFileStem().section(".", 0, 0)] = aFastFile;

    resizeColumnToContents(1);
}

void XTreeWidget::AddZoneFile(std::shared_ptr<ZoneFile> aZoneFile, QTreeWidgetItem *aParentItem) {
    QTreeWidgetItem *zoneItem;
    if (aParentItem != nullptr) {
        zoneItem = new QTreeWidgetItem(aParentItem);
    } else {
        zoneItem = new QTreeWidgetItem(this);
    }
    zoneItem->setIcon(0, QIcon(":/icons/icons/Icon_ZoneFile.png"));
    zoneItem->setText(0, aZoneFile->GetFileStem());

    auto assetMap = aZoneFile->GetAssetMap();

    if (!assetMap.localStrings.isEmpty()) {
        QTreeWidgetItem *localStrRoot = new QTreeWidgetItem(zoneItem);
        localStrRoot->setText(0, "String Files");
        localStrRoot->setIcon(0, QIcon(":/icons/icons/Icon_StringFile.png"));

        QTreeWidgetItem *localStrItem = new QTreeWidgetItem(localStrRoot);
        localStrItem->setText(0, aZoneFile->GetFileStem().section('.', 0, 0) + ".str");
        localStrItem->setIcon(0, QIcon(":/icons/icons/Icon_StringFile.png"));
    }

    if (!assetMap.techSets.isEmpty()) {
        QTreeWidgetItem *techSetRoot = new QTreeWidgetItem(zoneItem);
        techSetRoot->setText(0, "Tech Sets");
        techSetRoot->setIcon(0, QIcon(":/icons/icons/Icon_TechSetFile.png"));

        for (TechSet techSet : assetMap.techSets) {
            QTreeWidgetItem *techSetItem = new QTreeWidgetItem(techSetRoot);
            techSetItem->setText(0, techSet.name);
            techSetItem->setIcon(0, QIcon(":/icons/icons/Icon_TechSetFile.png"));
        }
    }

    if (!assetMap.rawFiles.isEmpty()) {
        QTreeWidgetItem *rawFileRoot = new QTreeWidgetItem(zoneItem);
        rawFileRoot->setText(0, "Raw Files");
        rawFileRoot->setIcon(0, QIcon(":/icons/icons/Icon_GSCFile.png"));
        for (RawFile rawFile : assetMap.rawFiles) {
            if (!rawFile.length) { continue; }

            QTreeWidgetItem *tempItem = rawFileRoot;
            for (const QString &pathPart : rawFile.path.split('/')) {
                bool childFound = false;
                for (int i = 0; i < tempItem->childCount(); i++) {
                    QTreeWidgetItem *childItem = tempItem->child(i);
                    //qDebug() << "Child text: " << childItem->text(0);
                    if (childItem->text(0) == pathPart) {
                        tempItem = childItem;

                        childFound = true;
                        break;
                    }
                }

                if (pathPart.contains(".gsc")) {
                    QTreeWidgetItem *rawFileItem = new QTreeWidgetItem(tempItem);
                    rawFileItem->setText(0, pathPart);

                    tempItem = rawFileItem;
                } else if (!childFound) {
                    tempItem = new QTreeWidgetItem(tempItem);
                    tempItem->setText(0, pathPart);
                }

            }
            tempItem->setIcon(0, QIcon(":/icons/icons/Icon_GSCFile.png"));
        }
    }

    if (!assetMap.menuFiles.isEmpty()) {
        QTreeWidgetItem *menuRoot = new QTreeWidgetItem(zoneItem);
        menuRoot->setText(0, "Menu Files");
        menuRoot->setIcon(0, QIcon(":/icons/icons/Icon_MenuFile.png"));

        int menuIndex = 1;
        for (MenuFile menuFile : assetMap.menuFiles) {
            QTreeWidgetItem *menuFileRoot = new QTreeWidgetItem(menuRoot);
            menuFileRoot->setText(0, QString("Menu %1").arg(menuIndex));
            for (Menu menu : menuFile.menuDefs) {
                QTreeWidgetItem *menuItem = new QTreeWidgetItem(menuFileRoot);
                menuItem->setText(0, menu.name);
                menuItem->setIcon(0, QIcon(":/icons/icons/Icon_MenuFile.png"));
            }
            menuIndex++;
        }
    }

    if (!assetMap.images.isEmpty()) {
        QTreeWidgetItem *imageRoot = new QTreeWidgetItem(zoneItem);
        imageRoot->setText(0, "Images");
        imageRoot->setIcon(0, QIcon(":/icons/icons/Icon_Image.png"));

        for (Image image : assetMap.images) {
            QTreeWidgetItem *imageItem = new QTreeWidgetItem(imageRoot);
            imageItem->setText(0, image.materialName);
            imageItem->setIcon(0, QIcon(":/icons/icons/Icon_Image.png"));
        }
    }

    mZoneFiles[aZoneFile->GetFileStem().section(".", 0, 0)] = aZoneFile;
}

void XTreeWidget::PrepareContextMenu(const QPoint &pos) {
    auto activeItem = itemAt(pos);
    if (!activeItem) { return; }
    if (activeItem->text(0).isEmpty()) { return; }

    QString activeText = activeItem->text(0);
    QMenu *contextMenu = new QMenu(this);

    if (activeText.contains(".dds")) {
        const QString fileStem = activeText.replace(".dds", "");
        if (!mDDSFiles.contains(fileStem)) {
            qDebug() << "Error: Could not find " << fileStem << " in DDS map!";
            return;
        }

        QAction *closeAction = new QAction("Close File");
        contextMenu->addAction(closeAction);
        connect(closeAction, &QAction::triggered, this, [this, &fileStem, &activeItem](bool checked) {
            Q_UNUSED(checked);

            mDDSFiles.remove(fileStem);
            invisibleRootItem()->removeChild(activeItem);
        });

        QMenu *exportSubmenu = new QMenu("Export...", this);
        contextMenu->addMenu(exportSubmenu);

        std::shared_ptr<DDSFile> ddsFile = mDDSFiles[fileStem];

        QAction *exportIWIAction = new QAction("Export as IWI");
        exportSubmenu->addAction(exportIWIAction);
        connect(exportIWIAction, &QAction::triggered, this, [ddsFile](bool checked) {
            Q_UNUSED(checked);

            ddsFile->SaveIWI();
        });

        QAction *exportPNGAction = new QAction("Export as PNG");
        exportSubmenu->addAction(exportPNGAction);
        connect(exportPNGAction, &QAction::triggered, this, [ddsFile](bool checked) {
            Q_UNUSED(checked);

            ddsFile->SavePNG();
        });

        QAction *exportJPGAction = new QAction("Export as JPG");
        exportSubmenu->addAction(exportJPGAction);
        connect(exportJPGAction, &QAction::triggered, this, [ddsFile](bool checked) {
            Q_UNUSED(checked);

            ddsFile->SaveJPG();
        });
    } else if (activeText.contains(".iwi")) {
        const QString fileStem = activeText.replace(".iwi", "");
        if (!mIWIFiles.contains(fileStem)) {
            qDebug() << "Error: Could not find " << fileStem << " in IWI map!";
            return;
        }

        QAction *closeAction = new QAction("Close File");
        contextMenu->addAction(closeAction);
        connect(closeAction, &QAction::triggered, this, [this, &fileStem, &activeItem](bool checked) {
            Q_UNUSED(checked);

            mIWIFiles.remove(fileStem);
            invisibleRootItem()->removeChild(activeItem);
        });

        QMenu *exportSubmenu = new QMenu("Export...", this);
        contextMenu->addMenu(exportSubmenu);

        std::shared_ptr<IWIFile> iwiFile = mIWIFiles[fileStem];

        QAction *exportDDSAction = new QAction("Export as DDS");
        exportSubmenu->addAction(exportDDSAction);
        connect(exportDDSAction, &QAction::triggered, this, [iwiFile](bool checked) {
            Q_UNUSED(checked);

            iwiFile->SaveDDS();
        });

        QAction *exportPNGAction = new QAction("Export as PNG");
        exportSubmenu->addAction(exportPNGAction);
        connect(exportPNGAction, &QAction::triggered, this, [iwiFile](bool checked) {
            Q_UNUSED(checked);

            iwiFile->SavePNG();
        });

        QAction *exportJPGAction = new QAction("Export as JPG");
        exportSubmenu->addAction(exportJPGAction);
        connect(exportJPGAction, &QAction::triggered, this, [iwiFile](bool checked) {
            Q_UNUSED(checked);

            iwiFile->SaveJPG();
        });
    } else if (activeText.contains(".ff")) {
        QMenu *closeMultipleAction = new QMenu("Close Multiple Tabs");

        QAction *closeAllAction = new QAction("Close All");
        closeMultipleAction->addAction(closeAllAction);
        connect(closeAllAction, &QAction::triggered, this, [this](bool checked) {
            Q_UNUSED(checked);

            clear();
        });

        QAction *closeAllButAction = new QAction("Close All BUT This");
        closeMultipleAction->addAction(closeAllButAction);
        connect(closeAllButAction, &QAction::triggered, this, [this, &activeItem](bool checked) {
            Q_UNUSED(checked);

            for (int i = 0; i < invisibleRootItem()->childCount(); i++) {
                auto childItem = invisibleRootItem()->child(i);
                if (childItem == activeItem) { continue; }
                invisibleRootItem()->removeChild(childItem);
                i--;
            }
        });

        QAction *closeAboveAction = new QAction("Close All Above");
        closeMultipleAction->addAction(closeAboveAction);
        connect(closeAboveAction, &QAction::triggered, this, [this, &activeItem](bool checked) {
            Q_UNUSED(checked);

            for (int i = 0; i < invisibleRootItem()->childCount(); i++) {
                auto childItem = invisibleRootItem()->child(i);
                if (childItem == activeItem) { return; }
                invisibleRootItem()->removeChild(childItem);
                i--;
            }
        });

        QAction *closeBelowAction = new QAction("Close All Below");
        closeMultipleAction->addAction(closeBelowAction);
        connect(closeBelowAction, &QAction::triggered, this, [this, &activeItem](bool checked) {
            Q_UNUSED(checked);

            bool ready = false;
            for (int i = 0; i < invisibleRootItem()->childCount(); i++) {
                auto childItem = invisibleRootItem()->child(i);
                if (!ready && (childItem != activeItem)) { continue; }
                if (childItem == activeItem) {
                    ready = true;
                    continue;
                }
                invisibleRootItem()->removeChild(childItem);
                i--;
            }
        });

        contextMenu->addMenu(closeMultipleAction);
        const QString fileStem = activeText.replace(".ff", "");
        if (!mFastFiles.contains(fileStem)) {
            qDebug() << "Error: Could not find " << fileStem << " in Fast File map!";
            return;
        }

        QAction *closeAction = new QAction("Close File");
        contextMenu->addAction(closeAction);
        connect(closeAction, &QAction::triggered, this, [this, &fileStem, &activeItem](bool checked) {
            Q_UNUSED(checked);

            mFastFiles.remove(fileStem);
            invisibleRootItem()->removeChild(activeItem);
        });

        QMenu *exportSubmenu = new QMenu("Export...", this);
        contextMenu->addMenu(exportSubmenu);

        std::shared_ptr<FastFile> fastFile = mFastFiles[fileStem];

        QAction *exportDDSAction = new QAction("Export as Zone File");
        exportSubmenu->addAction(exportDDSAction);
        connect(exportDDSAction, &QAction::triggered, this, [fastFile](bool checked) {
            Q_UNUSED(checked);

            //fastFile->SaveZone();
        });
    } else if (activeText.contains(".zone")) {
        const QString fileStem = activeText.replace(".zone", "");
        if (!mZoneFiles.contains(fileStem)) {
            qDebug() << "Error: Could not find " << fileStem << " in Zone File map!";
            return;
        }

        QMenu *exportSubmenu = new QMenu("Export...", this);
        contextMenu->addMenu(exportSubmenu);

        std::shared_ptr<ZoneFile> zoneFile = mZoneFiles[fileStem];

        QAction *exportDDSAction = new QAction("Export as Fast File");
        exportSubmenu->addAction(exportDDSAction);
        connect(exportDDSAction, &QAction::triggered, this, [zoneFile](bool checked) {
            Q_UNUSED(checked);

            //zoneFile->SaveFastFile();
        });
    }

    QPoint pt(pos);
    contextMenu->exec(mapToGlobal(pt));

    delete contextMenu;
}

void XTreeWidget::ItemSelectionChanged() {
    if (selectedItems().isEmpty()) { return; }

    QTreeWidgetItem *selectedItem = selectedItems().first();
    if (!selectedItem) { return; }
    if (selectedItem->text(0).isEmpty()) { return; }
    QString selectedText = selectedItem->text(0);
    const QString fileStem = selectedText.section(".", 0, 0);

    QTreeWidgetItem *parentItem = selectedItem->parent();

    if (selectedText.contains(".dds")) {
        if (!mDDSFiles.contains(fileStem)) {
            qDebug() << "Error: Could not find " << fileStem << " in DDS map!";
            return;
        }
        std::shared_ptr<DDSFile> ddsFile = mDDSFiles[fileStem];
        emit DDSFileSelected(ddsFile);
    } else if (selectedText.contains(".iwi")) {
        if (!mIWIFiles.contains(fileStem)) {
            qDebug() << "Error: Could not find " << fileStem << " in IWI map!";
            return;
        }
        emit IWIFileSelected(mIWIFiles[fileStem]);
    } else if (selectedText.contains(".ff")) {
        if (!mFastFiles.contains(fileStem)) {
            qDebug() << "Error: Could not find " << fileStem << " in Fast File map!";
            return;
        }
        emit FastFileSelected(mFastFiles[fileStem]);
    } else if (selectedText.contains(".zone")) {
        if (!mZoneFiles.contains(fileStem)) {
            qDebug() << "Error: Could not find " << fileStem << " in Zone File map!";
            return;
        }
        emit ZoneFileSelected(mZoneFiles[fileStem]);
    } else if (selectedText.contains(".str")) {
        if (!mZoneFiles.contains(fileStem)) {
            qDebug() << "Error: Could not find " << fileStem << " in Zone File map!";
            return;
        }
        emit LocalStringSelected(mZoneFiles[fileStem]);
    } else if (selectedText.contains(".gsc")) {
        QTreeWidgetItem *zoneRoot = selectedItem;
        if (!zoneRoot) { return; }

        while (!zoneRoot->text(0).contains(".zone")) {
            zoneRoot = zoneRoot->parent();
            if (!zoneRoot) { return; }
        }

        const QString fileStem = zoneRoot->text(0).section('.', 0, 0);
        if (!mZoneFiles.contains(fileStem)) {
            qDebug() << "Error: Could not find " << fileStem << " in Zone File map!";
            return;
        }

        QVector<RawFile> rawFiles = mZoneFiles[fileStem]->GetAssetMap().rawFiles;
        for (RawFile rawFile : rawFiles) {
            if (rawFile.path.contains(selectedText)) {
                emit RawFileSelected(std::make_shared<RawFile>(rawFile));
                return;
            }
        }
    } else if (parentItem && (parentItem->text(0) == "Images")) {
        QTreeWidgetItem *grandpaItem = parentItem->parent();
        if (grandpaItem && grandpaItem->text(0).contains(".zone")) {
            const QString fileStem = grandpaItem->text(0).section('.', 0, 0);
            QVector<Image> images = mZoneFiles[fileStem]->GetAssetMap().images;
            for (Image image : images) {
                if (image.materialName == selectedText) {
                    emit ImageSelected(std::make_shared<Image>(image));
                    break;
                }
            }
        }
    } else if (parentItem && (parentItem->text(0) == "Tech Sets")) {
        QTreeWidgetItem *grandpaItem = parentItem->parent();
        if (grandpaItem && grandpaItem->text(0).contains(".zone")) {
            const QString fileStem = grandpaItem->text(0).section('.', 0, 0);
            auto techsets = mZoneFiles[fileStem]->GetAssetMap().techSets;
            for (auto techset : techsets) {
                if (techset.name == selectedText) {
                    emit TechSetSelected(std::make_shared<TechSet>(techset));
                    break;
                }
            }
        }
    }
}

ZoneFile XTreeWidget::pFindZoneFile(const QString aFilePart) {
    foreach (auto zoneFile, mZoneFiles) {
        if (zoneFile->GetFileStem() == aFilePart) {
            return *zoneFile.get();
        }
    }
    return ZoneFile();
}

FastFile XTreeWidget::pFindFastFile(const QString aFilePart) {
    foreach (auto fastFile, mFastFiles) {
        if (fastFile->GetFileStem() == aFilePart) {
            return *fastFile.get();
        }
    }
    return FastFile();
}

void XTreeWidget::AddIWIFile(std::shared_ptr<IWIFile> aIWIFile) {
    const QString iwiFileName = QString(aIWIFile->fileStem + ".iwi");

    for (int i = 0; i < invisibleRootItem()->childCount(); i++) {
        auto iwiFileItem = invisibleRootItem()->child(i);
        if (iwiFileItem->text(0) == iwiFileName) {
            delete iwiFileItem;
        }
    }

    QTreeWidgetItem *iwiItem = new QTreeWidgetItem(this);
    iwiItem->setIcon(0, QIcon(":/icons/icons/Icon_IWIFile.png"));
    iwiItem->setText(0, iwiFileName);
    mIWIFiles[aIWIFile->fileStem.section(".", 0, 0)] = aIWIFile;
}

void XTreeWidget::AddDDSFile(std::shared_ptr<DDSFile> aDDSFile) {
    const QString ddsFileName = QString(aDDSFile->fileStem + ".dds");

    for (int i = 0; i < invisibleRootItem()->childCount(); i++) {
        auto ddsFileItem = invisibleRootItem()->child(i);
        if (ddsFileItem->text(0) == ddsFileName) {
            delete ddsFileItem;
        }
    }

    QTreeWidgetItem *ddsItem = new QTreeWidgetItem(this);
    ddsItem->setIcon(0, QIcon(":/icons/icons/Icon_DDSFile.png"));
    ddsItem->setText(0, ddsFileName);
    mDDSFiles[aDDSFile->fileStem.section(".", 0, 0)] = aDDSFile;
}
