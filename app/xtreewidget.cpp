#include "xtreewidget.h"
#include "qheaderview.h"
#include "qmenu.h"
#include "logmanager.h"

XTreeWidget::XTreeWidget(QWidget *parent)
    : QTreeWidget(parent) {
    mFastFiles = QMap<QString, std::shared_ptr<FastFile>>();
    mZoneFiles = QMap<QString, std::shared_ptr<ZoneFile>>();
    mDDSFiles = QMap<QString, std::shared_ptr<DDSFile>>();
    mIWIFiles = QMap<QString, std::shared_ptr<IWIFile>>();

    setContextMenuPolicy(Qt::CustomContextMenu);
    setSelectionMode(QTreeWidget::SingleSelection);
    setColumnCount(3);
    header()->hide();
    setMinimumWidth(350);
    setSortingEnabled(true);

    header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    // Set the last two columns to a fixed width
    //header()->setSectionResizeMode(1, QHeaderView::Fixed);
    //header()->setSectionResizeMode(2, QHeaderView::Fixed);

    // Adjust the fixed widths to suit your icon size (e.g., 32 pixels)
    //header()->resizeSection(0, 275);
    //header()->resizeSection(1, 32);
    //header()->resizeSection(2, 32);

    connect(this, &XTreeWidget::itemSelectionChanged, this, &XTreeWidget::ItemSelectionChanged);
    connect(this, &XTreeWidget::customContextMenuRequested, this, &XTreeWidget::PrepareContextMenu);
}

XTreeWidget::~XTreeWidget() {

}

void XTreeWidget::AddFastFile(std::shared_ptr<FastFile> aFastFile) {
    XTreeWidgetItem *fastFileItem = new XTreeWidgetItem(this);
    fastFileItem->setText(0, aFastFile->GetStem() + ".ff");
    fastFileItem->setIcon(0, QIcon(":/icons/icons/Icon_FastFile.png"));
    if (aFastFile->GetPlatform() == "PC") {
        fastFileItem->setIcon(1, QIcon(":/icons/icons/Icon_PC.png"));
    } else if (aFastFile->GetPlatform() == "360") {
        fastFileItem->setIcon(1, QIcon(":/icons/icons/Icon_Xbox.png"));
    } else if (aFastFile->GetPlatform() == "Wii") {
        fastFileItem->setIcon(1, QIcon(":/icons/icons/Icon_Wii.png"));
    } else if (aFastFile->GetPlatform() == "WiiU") {
        fastFileItem->setIcon(1, QIcon(":/icons/icons/Icon_WiiU.png"));
    }
    if (aFastFile->GetGame() == "COD2") {
        fastFileItem->setIcon(2, QIcon(":/icons/icons/Icon_COD2.png"));
    } if (aFastFile->GetGame() == "COD4") {
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

    AddZoneFile(aFastFile->GetZoneFile(), fastFileItem);

    mFastFiles[aFastFile->GetStem().section(".", 0, 0)] = aFastFile;

    resizeColumnToContents(1);
    setSortingEnabled(true);
    sortByColumn(0, Qt::AscendingOrder);
}

void XTreeWidget::AddZoneFile(std::shared_ptr<ZoneFile> aZoneFile, XTreeWidgetItem *aParentItem) {
    XTreeWidgetItem *zoneItem;
    if (aParentItem != nullptr) {
        zoneItem = new XTreeWidgetItem(aParentItem);
    } else {
        zoneItem = new XTreeWidgetItem(this);
    }
    zoneItem->setIcon(0, QIcon(":/icons/icons/Icon_ZoneFile.png"));
    zoneItem->setText(0, aZoneFile->GetStem() + ".zone");

    auto assetMap = aZoneFile->GetAssetMap();

    if (!assetMap.localStrings.isEmpty()) {
        XTreeWidgetItem *localStrRoot = new XTreeWidgetItem(zoneItem);
        localStrRoot->setText(0, "String Files");
        localStrRoot->setIcon(0, QIcon(":/icons/icons/Icon_StringFile.png"));

        XTreeWidgetItem *localStrItem = new XTreeWidgetItem(localStrRoot);
        localStrItem->setText(0, aZoneFile->GetStem().section('.', 0, 0) + ".str");
        localStrItem->setIcon(0, QIcon(":/icons/icons/Icon_StringFile.png"));
    }

    if (!assetMap.techSets.isEmpty()) {
        XTreeWidgetItem *techSetRoot = new XTreeWidgetItem(zoneItem);
        techSetRoot->setText(0, "Tech Sets");
        techSetRoot->setIcon(0, QIcon(":/icons/icons/Icon_TechSetFile.png"));

        for (TechSet techSet : assetMap.techSets) {
            XTreeWidgetItem *techSetItem = new XTreeWidgetItem(techSetRoot);
            techSetItem->setText(0, techSet.name);
            techSetItem->setIcon(0, QIcon(":/icons/icons/Icon_TechSetFile.png"));
        }
    }

    if (!assetMap.rawFiles.isEmpty()) {
        XTreeWidgetItem *rawFileRoot = new XTreeWidgetItem(zoneItem);
        rawFileRoot->setText(0, "Raw Files");
        rawFileRoot->setIcon(0, QIcon(":/icons/icons/Icon_GSCFile.png"));
        for (RawFile rawFile : assetMap.rawFiles) {
            if (!rawFile.length) { continue; }

            XTreeWidgetItem *tempItem = rawFileRoot;
            for (const QString &pathPart : rawFile.path.split('/')) {
                bool childFound = false;
                for (int i = 0; i < tempItem->childCount(); i++) {
                    QTreeWidgetItem *rawChildItem = tempItem->child(i);
                    XTreeWidgetItem *childItem = dynamic_cast<XTreeWidgetItem*>(rawChildItem);
                    if (childItem->text(0) == pathPart) {
                        tempItem = childItem;

                        childFound = true;
                        break;
                    }
                }

                if (pathPart.contains(".gsc")) {
                    XTreeWidgetItem *rawFileItem = new XTreeWidgetItem(tempItem);
                    rawFileItem->setText(0, pathPart);

                    tempItem = rawFileItem;
                } else if (!childFound) {
                    tempItem = new XTreeWidgetItem(tempItem);
                    tempItem->setText(0, pathPart);
                }

            }
            tempItem->setIcon(0, QIcon(":/icons/icons/Icon_GSCFile.png"));
        }
    }

    if (!assetMap.menuFiles.isEmpty()) {
        XTreeWidgetItem *menuRoot = new XTreeWidgetItem(zoneItem);
        menuRoot->setText(0, "Menu Files");
        menuRoot->setIcon(0, QIcon(":/icons/icons/Icon_MenuFile.png"));

        int menuIndex = 1;
        for (MenuFile menuFile : assetMap.menuFiles) {
            XTreeWidgetItem *menuFileRoot = new XTreeWidgetItem(menuRoot);
            menuFileRoot->setText(0, QString("Menu %1").arg(menuIndex));
            for (Menu menu : menuFile.menuDefs) {
                XTreeWidgetItem *menuItem = new XTreeWidgetItem(menuFileRoot);
                menuItem->setText(0, menu.name);
                menuItem->setIcon(0, QIcon(":/icons/icons/Icon_MenuFile.png"));
            }
            menuIndex++;
        }
    }

    if (!assetMap.images.isEmpty()) {
        XTreeWidgetItem *imageRoot = new XTreeWidgetItem(zoneItem);
        imageRoot->setText(0, "Images");
        imageRoot->setIcon(0, QIcon(":/icons/icons/Icon_Image.png"));

        for (Image image : assetMap.images) {
            XTreeWidgetItem *imageItem = new XTreeWidgetItem(imageRoot);
            imageItem->setText(0, image.materialName);
            imageItem->setIcon(0, QIcon(":/icons/icons/Icon_Image.png"));
        }
    }

    if (!assetMap.models.isEmpty()) {
        XTreeWidgetItem *modelsRoot = new XTreeWidgetItem(zoneItem);
        modelsRoot->setText(0, "Models");
        modelsRoot->setIcon(0, QIcon(":/icons/icons/Icon_Model.png"));

        for (Model model: assetMap.models) {
            XTreeWidgetItem *modelItem = new XTreeWidgetItem(modelsRoot);
            modelItem->setText(0, model.modelName);
            modelItem->setIcon(0, QIcon(":/icons/icons/Icon_Model.png"));
        }
    }

    if (!assetMap.materials.isEmpty()) {
        XTreeWidgetItem *materialsRoot = new XTreeWidgetItem(zoneItem);
        materialsRoot->setText(0, "Materials");
        materialsRoot->setIcon(0, QIcon(":/icons/icons/Icon_Material.png"));

        for (Material material: assetMap.materials) {
            XTreeWidgetItem *materialItem = new XTreeWidgetItem(materialsRoot);
            materialItem->setText(0, material.name);
            materialItem->setIcon(0, QIcon(":/icons/icons/Icon_Material.png"));
        }
    }

    if (!assetMap.stringTables.isEmpty()) {
        XTreeWidgetItem *strTableRoot = new XTreeWidgetItem(zoneItem);
        strTableRoot->setText(0, "String Tables");
        strTableRoot->setIcon(0, QIcon(":/icons/icons/Icon_StringTable.png"));

        for (StringTable strTable: assetMap.stringTables) {
            XTreeWidgetItem *modelItem = new XTreeWidgetItem(strTableRoot);
            modelItem->setText(0, strTable.name);
            modelItem->setIcon(0, QIcon(":/icons/icons/Icon_StringTable.png"));
        }
    }

    if (!assetMap.sounds.isEmpty()) {
        XTreeWidgetItem *soundsRoot = new XTreeWidgetItem(zoneItem);
        soundsRoot->setText(0, "Sounds");
        soundsRoot->setIcon(0, QIcon(":/icons/icons/Icon_Sound.png"));
        for (SoundAsset soundAsset : assetMap.sounds) {
            for (Sound sound : soundAsset.sounds) {
                XTreeWidgetItem *tempItem = soundsRoot;

                if (!sound.dataLength) { continue; }

                for (const QString &pathPart : sound.path.split('/')) {
                    if (pathPart.isEmpty()) { continue; }

                    bool childFound = false;
                    for (int i = 0; i < tempItem->childCount(); i++) {
                        XTreeWidgetItem *childItem = dynamic_cast<XTreeWidgetItem*>(tempItem->child(i));
                        if (childItem->text(0) == pathPart) {
                            tempItem = childItem;

                            childFound = true;
                            break;
                        }
                    }

                    if (pathPart.contains(".wav")) {
                        XTreeWidgetItem *soundItem = new XTreeWidgetItem(tempItem);
                        soundItem->setText(0, pathPart);

                        tempItem = soundItem;
                    } else if (!childFound) {
                        tempItem = new XTreeWidgetItem(tempItem);
                        tempItem->setText(0, pathPart);
                    }

                }
                tempItem->setIcon(0, QIcon(":/icons/icons/Icon_Sound.png"));
            }
        }
    }

    mZoneFiles[aZoneFile->GetStem().section(".", 0, 0)] = aZoneFile;
}

void XTreeWidget::CloseFastFile(const QString aFFName) {
    const QString fileStem = aFFName.section(".", 0, 0);
    emit ItemClosed(fileStem);
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
        const QString fileStem = activeText.replace(".zone", "");

        QMenu *closeMultipleAction = new QMenu("Close Multiple Tabs");

        QAction *closeAllAction = new QAction("Close All");
        closeMultipleAction->addAction(closeAllAction);
        connect(closeAllAction, &QAction::triggered, this, [this](bool checked) {
            Q_UNUSED(checked);

            mFastFiles.clear();
            clear();

            emit Cleared();
        });

        QAction *closeAllButAction = new QAction("Close All BUT This");
        closeMultipleAction->addAction(closeAllButAction);
        connect(closeAllButAction, &QAction::triggered, this, [this, &activeItem](bool checked) {
            Q_UNUSED(checked);

            for (int i = 0; i < invisibleRootItem()->childCount(); i++) {
                auto childItem = invisibleRootItem()->child(i);
                if (childItem == activeItem) { continue; }

                const QString fileStem = childItem->text(0).replace(".ff", "");
                if (!mFastFiles.contains(fileStem)) {
                    qDebug() << "Error: Could not find " << fileStem << " in Fast File map!";
                    return;
                }

                mFastFiles.remove(fileStem);
                CloseFastFile(fileStem);
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

                const QString fileStem = childItem->text(0).replace(".ff", "");
                if (!mFastFiles.contains(fileStem)) {
                    qDebug() << "Error: Could not find " << fileStem << " in Fast File map!";
                    return;
                }

                mFastFiles.remove(fileStem);
                CloseFastFile(fileStem);
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

                const QString fileStem = childItem->text(0).replace(".ff", "");
                if (!mFastFiles.contains(fileStem)) {
                    qDebug() << "Error: Could not find " << fileStem << " in Fast File map!";
                    return;
                }

                mFastFiles.remove(fileStem);
                CloseFastFile(fileStem);
                invisibleRootItem()->removeChild(childItem);
                i--;
            }
        });

        contextMenu->addMenu(closeMultipleAction);

        QAction *closeAction = new QAction("Close File");
        contextMenu->addAction(closeAction);
        connect(closeAction, &QAction::triggered, this, [this, &activeItem, &activeText](bool checked) {
            Q_UNUSED(checked);

            const QString fileStem = activeItem->text(0).replace(".ff", "");

            mFastFiles.remove(fileStem);
            CloseFastFile(activeText);
            invisibleRootItem()->removeChild(activeItem);
        });

        QMenu *exportSubmenu = new QMenu("Export...", this);
        contextMenu->addMenu(exportSubmenu);

        std::shared_ptr<FastFile> fastFile = mFastFiles[fileStem];

        QAction *exportFastFileAction = new QAction("Export Fast File");
        exportSubmenu->addAction(exportFastFileAction);
        connect(exportFastFileAction, &QAction::triggered, this, [fastFile](bool checked) {
            Q_UNUSED(checked);

            const QString fastFilePath = QFileDialog::getSaveFileName(
                nullptr, "Export Fast File...", QDir::currentPath(),
                "Fast File (*.ff);;All Files(*.*)");

            fastFile->ExportFastFile(fastFilePath);
        });
        QAction *exportZoneFileAction = new QAction("Export Zone File");
        exportSubmenu->addAction(exportZoneFileAction);
        connect(exportZoneFileAction, &QAction::triggered, this, [fastFile](bool checked) {
            Q_UNUSED(checked);

            const QString zoneFilePath = QFileDialog::getSaveFileName(
                nullptr, "Export Zone File...", QDir::currentPath(),
                "Zone File (*.zone);;All Files(*.*)");
            fastFile->GetZoneFile()->SaveZoneFile(zoneFilePath);
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

        QAction *exportZoneFileAction = new QAction("Export Zone File");
        exportSubmenu->addAction(exportZoneFileAction);
        connect(exportZoneFileAction, &QAction::triggered, this, [](bool checked) {
            Q_UNUSED(checked);
        });
        QAction *exportFastFileAction = new QAction("Export Fast File");
        exportSubmenu->addAction(exportFastFileAction);
        connect(exportFastFileAction, &QAction::triggered, this, [](bool checked) {
            Q_UNUSED(checked);
        });
    } else if (activeItem && activeText.contains(".wav")) {
        XTreeWidgetItem *parentItem = dynamic_cast<XTreeWidgetItem*>(activeItem->parent());
        while (parentItem && !parentItem->text(0).contains(".zone")) {
            parentItem = dynamic_cast<XTreeWidgetItem*>(parentItem->parent());

            if (parentItem == invisibleRootItem()) {
                break;
            }
        }
        if (parentItem && parentItem != invisibleRootItem() && parentItem->text(0).contains(".zone")) {
            const QString fileStem = parentItem->text(0).section('.', 0, 0);
            QVector<SoundAsset> soundAssets = mZoneFiles[fileStem]->GetAssetMap().sounds;
            for (SoundAsset soundAsset : soundAssets) {
                for (Sound sound : soundAsset.sounds) {
                    if (sound.path.contains(activeText)) {
                        QMenu *exportSubmenu = new QMenu("Export...", this);
                        contextMenu->addMenu(exportSubmenu);

                        QAction *exportWAVAction = new QAction("Export as WAV File");
                        exportSubmenu->addAction(exportWAVAction);
                        connect(exportWAVAction, &QAction::triggered, this, [sound](bool checked) {
                            Q_UNUSED(checked);

                            QDir dir = QDir::currentPath();
                            if (!dir.exists("exports/")) {
                                dir.mkdir("exports/");
                            }

                            if (!dir.exists("exports/sounds/")) {
                                dir.mkdir("exports/sounds/");
                            }

                            const QString fileName = "exports/sounds/" + sound.path.split('/').last();
                            QFile wavFile(fileName);
                            if (!wavFile.open(QIODevice::WriteOnly)) {
                                qDebug() << "Failed to write wav file!";
                                return;
                            }
                            wavFile.write(sound.data);
                            wavFile.close();
                        });
                        break;
                    }
                }
            }
        }
    } else if (activeItem && activeText == "Sounds") {
        XTreeWidgetItem *parentItem = dynamic_cast<XTreeWidgetItem*>(activeItem->parent());
        while (parentItem && !parentItem->text(0).contains(".zone")) {
            parentItem = dynamic_cast<XTreeWidgetItem*>(parentItem->parent());

            if (parentItem == invisibleRootItem()) {
                break;
            }
        }
        if (parentItem && parentItem != invisibleRootItem() && parentItem->text(0).contains(".zone")) {
            const QString fileStem = parentItem->text(0).section('.', 0, 0);
            auto zoneFile = mZoneFiles[fileStem];

            QMenu *exportSubmenu = new QMenu("Export...", this);
            contextMenu->addMenu(exportSubmenu);

            QAction *exportAllWAVAction = new QAction("Export ALL as WAV Files");
            exportSubmenu->addAction(exportAllWAVAction);
            connect(exportAllWAVAction, &QAction::triggered, this, [zoneFile](bool checked) {
                Q_UNUSED(checked);

                for (SoundAsset soundAsset : zoneFile->GetAssetMap().sounds) {
                    for (Sound sound : soundAsset.sounds) {
                        if (!sound.dataLength) { continue; }

                        QDir dir = QDir::currentPath();
                        if (!dir.exists("exports/")) {
                            dir.mkdir("exports/");
                        }

                        if (!dir.exists("exports/sounds/")) {
                            dir.mkdir("exports/sounds/");
                        }

                        const QString fileName = "exports/sounds/" + sound.path.split('/').last();
                        QFile wavFile(fileName);
                        if (!wavFile.open(QIODevice::WriteOnly)) {
                            qDebug() << "Failed to write wav file!";
                            return;
                        }
                        wavFile.write(sound.data);
                        wavFile.close();
                    }
                }
            });
        }
    }

    QPoint pt(pos);
    contextMenu->exec(mapToGlobal(pt));

    delete contextMenu;
}

void XTreeWidget::ItemSelectionChanged() {
    if (selectedItems().isEmpty()) { return; }

    XTreeWidgetItem *selectedItem = dynamic_cast<XTreeWidgetItem*>(selectedItems().first());
    if (!selectedItem) { return; }
    if (selectedItem->text(0).isEmpty()) { return; }
    QString selectedText = selectedItem->text(0);
    emit ItemSelected(selectedText);

    const QString fileStem = selectedText.section(".", 0, 0);

    XTreeWidgetItem *parentItem = dynamic_cast<XTreeWidgetItem*>(selectedItem->parent());

    if (selectedText.contains(".dds")) {
        if (!mDDSFiles.contains(fileStem)) {
            LogManager::instance().addError("Could not find " + fileStem + " in DDS map!");
            return;
        }
        std::shared_ptr<DDSFile> ddsFile = mDDSFiles[fileStem];
        emit DDSFileSelected(ddsFile, fileStem);
    } else if (selectedText.contains(".iwi")) {
        if (!mIWIFiles.contains(fileStem)) {
            LogManager::instance().addError("Could not find " + fileStem + " in IWI map!");
            return;
        }
        emit IWIFileSelected(mIWIFiles[fileStem], fileStem);
    } else if (selectedText.contains(".ff")) {
        if (!mFastFiles.contains(fileStem)) {
            LogManager::instance().addError("Could not find " + fileStem + " in Fast File map!");
            return;
        }
        emit FastFileSelected(mFastFiles[fileStem], fileStem);
    } else if (selectedText.contains(".zone")) {
        if (!mZoneFiles.contains(fileStem)) {
            LogManager::instance().addError("Could not find " + fileStem + " in Zone File map!");
            return;
        }
        emit ZoneFileSelected(mZoneFiles[fileStem], fileStem);
    } else if (selectedText.contains(".str")) {
        if (!mZoneFiles.contains(fileStem)) {
            LogManager::instance().addError("Could not find " + fileStem + " in Zone File map!");
            return;
        }
        emit LocalStringSelected(mZoneFiles[fileStem], fileStem);
    } else if (selectedText.contains(".gsc")) {
        XTreeWidgetItem *zoneRoot = selectedItem;
        if (!zoneRoot) { return; }

        while (!zoneRoot->text(0).contains(".zone")) {
            zoneRoot = dynamic_cast<XTreeWidgetItem*>(zoneRoot->parent());
            if (!zoneRoot) { return; }
        }

        const QString fileStem = zoneRoot->text(0).section('.', 0, 0);
        if (!mZoneFiles.contains(fileStem)) {
            LogManager::instance().addError("Could not find " + fileStem + " in Zone File map!");
            return;
        }

        QVector<RawFile> rawFiles = mZoneFiles[fileStem]->GetAssetMap().rawFiles;
        for (RawFile rawFile : rawFiles) {
            if (rawFile.path.contains(selectedText)) {
                emit RawFileSelected(std::make_shared<RawFile>(rawFile), fileStem);
                return;
            }
        }
    } else if (parentItem && (parentItem->text(0) == "Images")) {
        XTreeWidgetItem *grandpaItem = dynamic_cast<XTreeWidgetItem*>(parentItem->parent());
        if (grandpaItem && grandpaItem->text(0).contains(".zone")) {
            const QString fileStem = grandpaItem->text(0).section('.', 0, 0);
            QVector<Image> images = mZoneFiles[fileStem]->GetAssetMap().images;
            for (Image image : images) {
                if (image.materialName == selectedText) {
                    emit ImageSelected(std::make_shared<Image>(image), fileStem);
                    break;
                }
            }
        }
    } else if (parentItem && (parentItem->text(0) == "Tech Sets")) {
        XTreeWidgetItem *grandpaItem = dynamic_cast<XTreeWidgetItem*>(parentItem->parent());
        if (grandpaItem && grandpaItem->text(0).contains(".zone")) {
            const QString fileStem = grandpaItem->text(0).section('.', 0, 0);
            auto techsets = mZoneFiles[fileStem]->GetAssetMap().techSets;
            for (auto techset : techsets) {
                if (techset.name == selectedText) {
                    emit TechSetSelected(std::make_shared<TechSet>(techset), fileStem);
                    break;
                }
            }
        }
    } else if (parentItem && (parentItem->text(0) == "Tech Sets")) {
        XTreeWidgetItem *grandpaItem = dynamic_cast<XTreeWidgetItem*>(parentItem->parent());
        if (grandpaItem && grandpaItem->text(0).contains(".zone")) {
            const QString fileStem = grandpaItem->text(0).section('.', 0, 0);
            auto techsets = mZoneFiles[fileStem]->GetAssetMap().techSets;
            for (auto techset : techsets) {
                if (techset.name == selectedText) {
                    emit TechSetSelected(std::make_shared<TechSet>(techset), fileStem);
                    break;
                }
            }
        }
    } else if (parentItem && (parentItem->text(0) == "Materials")) {
        XTreeWidgetItem *grandpaItem = dynamic_cast<XTreeWidgetItem*>(parentItem->parent());
        if (grandpaItem && grandpaItem->text(0).contains(".zone")) {
            const QString fileStem = grandpaItem->text(0).section('.', 0, 0);
            QVector<Material> materials = mZoneFiles[fileStem]->GetAssetMap().materials;
            for (Material material : materials) {
                if (material.name == selectedText) {
                    emit MaterialSelected(std::make_shared<Material>(material), fileStem);
                    break;
                }
            }
        }
    } else if (parentItem && selectedText.contains(".wav")) {
        XTreeWidgetItem *grandpaItem = dynamic_cast<XTreeWidgetItem*>(parentItem->parent());
        while (grandpaItem && !grandpaItem->text(0).contains(".zone")) {
            grandpaItem = dynamic_cast<XTreeWidgetItem*>(grandpaItem->parent());

            if (grandpaItem == invisibleRootItem()) {
                break;
            }
        }
        if (grandpaItem && grandpaItem != invisibleRootItem() && grandpaItem->text(0).contains(".zone")) {
            const QString fileStem = grandpaItem->text(0).section('.', 0, 0);
            QVector<SoundAsset> soundAssets = mZoneFiles[fileStem]->GetAssetMap().sounds;
            for (SoundAsset soundAsset : soundAssets) {
                for (Sound sound : soundAsset.sounds) {
                    if (sound.path.contains(selectedText)) {
                        emit SoundSelected(std::make_shared<Sound>(sound), fileStem);
                        break;
                    }
                }
            }
        }
    }
}

std::shared_ptr<ZoneFile> XTreeWidget::FindZoneFile(const QString aStem) {
    foreach (auto zoneFile, mZoneFiles) {
        if (zoneFile->GetStem() == aStem) {
            return zoneFile;
        }
    }
    return nullptr;
}

std::shared_ptr<FastFile> XTreeWidget::FindFastFile(const QString aStem) {
    foreach (auto fastFile, mFastFiles) {
        if (fastFile->GetStem() == aStem) {
            return fastFile;
        }
    }
    return nullptr;
}

bool XTreeWidget::HasZoneFile(const QString aStem) {
    return FindZoneFile(aStem) != nullptr;
}

bool XTreeWidget::HasFastFile(const QString aStem) {
    return FindFastFile(aStem) != nullptr;
}

void XTreeWidget::AddIWIFile(std::shared_ptr<IWIFile> aIWIFile) {
    const QString iwiFileName = QString(aIWIFile->fileStem + ".iwi");

    for (int i = 0; i < invisibleRootItem()->childCount(); i++) {
        auto iwiFileItem = invisibleRootItem()->child(i);
        if (iwiFileItem->text(0) == iwiFileName) {
            delete iwiFileItem;
        }
    }

    XTreeWidgetItem *iwiItem = new XTreeWidgetItem(this);
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

    XTreeWidgetItem *ddsItem = new XTreeWidgetItem(this);
    ddsItem->setIcon(0, QIcon(":/icons/icons/Icon_DDSFile.png"));
    ddsItem->setText(0, ddsFileName);
    mDDSFiles[aDDSFile->fileStem.section(".", 0, 0)] = aDDSFile;
}
