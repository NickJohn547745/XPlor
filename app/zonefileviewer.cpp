#include "zonefileviewer.h"
#include "ui_zonefileviewer.h"

ZoneFileViewer::ZoneFileViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ZoneFileViewer) {
    ui->setupUi(this);

    mZoneFile = nullptr;

    ui->tableWidget_RecordCounts->setColumnCount(4);
    ui->tableWidget_RecordCounts->setHorizontalHeaderLabels({ "Identifier", "Asset", "Count", "Icon" });
    ui->tableWidget_RecordCounts->horizontalHeader()->setStretchLastSection(true);

    ui->tableWidget_RecordOrder->setColumnCount(4);
    ui->tableWidget_RecordOrder->setHorizontalHeaderLabels({ "Identifier", "Asset", "Count", "Icon" });
    ui->tableWidget_RecordOrder->horizontalHeader()->setStretchLastSection(true);

    connect(ui->lineEdit_TagSearch, &QLineEdit::textChanged, this, &ZoneFileViewer::SortTags);
    connect(ui->tableWidget_RecordCounts, &QTableWidget::itemSelectionChanged, this, &ZoneFileViewer::HighlightRecordInOrder);
}

ZoneFileViewer::~ZoneFileViewer() {
    delete ui;
}

void ZoneFileViewer::HighlightRecordInOrder() {
    ui->tableWidget_RecordOrder->clearSelection();

    foreach (auto selectedItem, ui->tableWidget_RecordCounts->selectedItems()) {
        int selectedRow = selectedItem->row();
        const QString assetId = ui->tableWidget_RecordCounts->item(selectedRow, 0)->text();

        for (int i = 0; i < ui->tableWidget_RecordOrder->rowCount(); i++) {
            const QString testAssetId = ui->tableWidget_RecordOrder->item(i, 0)->text();
            if (testAssetId != assetId) { continue; }

            ui->tableWidget_RecordOrder->selectRow(i);
            ui->tableWidget_RecordOrder->item(i, 0)->setSelected(true);
            ui->tableWidget_RecordOrder->item(i, 1)->setSelected(true);
            ui->tableWidget_RecordOrder->item(i, 2)->setSelected(true);
            ui->tableWidget_RecordOrder->item(i, 3)->setSelected(true);
        }
    }
}

void ZoneFileViewer::SortTags(const QString &aSearchText) {
    ui->listWidget_Tags->clear();

    const QStringList tags = mZoneFile->GetTags();
    if (aSearchText.isEmpty()) {
        ui->listWidget_Tags->addItems(tags);
        return;
    }

    QStringList sortedTags;
    foreach (const QString tag, tags) {
        if (tag.contains(aSearchText)) {
            sortedTags << tag;
        }
    }

    ui->listWidget_Tags->addItems(sortedTags);
}

void ZoneFileViewer::SetZoneFile(std::shared_ptr<ZoneFile> aZoneFile) {
    mZoneFile = aZoneFile;

    ui->tableWidget_RecordCounts->clearContents();
    ui->tableWidget_RecordOrder->clearContents();
    ui->listWidget_Tags->clear();

    const QStringList tags = mZoneFile->GetTags();
    ui->listWidget_Tags->addItems(tags);
    ui->label_Title->setText(mZoneFile->GetStem() + ".zone");

    if (tags.isEmpty()) {
        ui->groupBox_Tags->hide();
    } else {
        ui->groupBox_Tags->show();
    }

    QMap<QString, int> recordCounts = QMap<QString, int>();
    QVector<QPair<QString, int>> assetOccurances = QVector<QPair<QString, int>>();
    for (const QString &record : mZoneFile->GetRecords()) {
        if (!recordCounts.contains(record)) {
            recordCounts[record] = 0;
        }
        recordCounts[record]++;

        if (!assetOccurances.isEmpty() && assetOccurances.last().first == record) {
            assetOccurances.last().second++;
            continue;
        }

        QPair<QString, int> assetOccurance(record, 1);
        assetOccurances << assetOccurance;
    }
    ui->tableWidget_RecordOrder->setRowCount(assetOccurances.size());

    int assetIndex = 0;
    foreach (auto assetOccurance, assetOccurances) {
        const QString record = assetOccurance.first;
        AssetType assetType = mZoneFile->AssetStrToEnum(record);
        int assetCount = assetOccurance.second;

        QIcon assetIcon = mZoneFile->AssetTypeToIcon(assetType);
        if (assetIcon.isNull()) {
            qDebug() << "Icon is null for record: " << record;
        }

        QTableWidgetItem *recordItem = new QTableWidgetItem(record.toUpper());
        QTableWidgetItem *recordStrItem = new QTableWidgetItem(mZoneFile->AssetEnumToStr(assetType));
        QTableWidgetItem *recordCountItem = new QTableWidgetItem(QString::number(assetCount));
        QTableWidgetItem *recordIconItem = new QTableWidgetItem();
        recordIconItem->setIcon(assetIcon);

        ui->tableWidget_RecordOrder->setItem(assetIndex, 0, recordItem);
        ui->tableWidget_RecordOrder->setItem(assetIndex, 1, recordStrItem);
        ui->tableWidget_RecordOrder->setItem(assetIndex, 2, recordCountItem);
        ui->tableWidget_RecordOrder->setItem(assetIndex, 3, recordIconItem);

        assetIndex++;
    }

    int recordIndex = 0;
    for (const QString &record : recordCounts.keys()) {
        int recordCount = recordCounts[record];

        AssetType assetType = mZoneFile->AssetStrToEnum(record);
        QIcon assetIcon = mZoneFile->AssetTypeToIcon(assetType);
        if (assetIcon.isNull()) {
            qDebug() << "Icon is null for record: " << record;
        }

        ui->tableWidget_RecordCounts->setRowCount(recordIndex + 1);

        QTableWidgetItem *recordCountStrItem = new QTableWidgetItem(mZoneFile->AssetEnumToStr(assetType));
        QTableWidgetItem *recordItem = new QTableWidgetItem(record.toUpper());
        QTableWidgetItem *recordCountItem = new QTableWidgetItem(QString::number(recordCount));
        QTableWidgetItem *recordIconItem = new QTableWidgetItem();
        recordIconItem->setIcon(assetIcon);

        ui->tableWidget_RecordCounts->setItem(recordIndex, 0, recordItem);
        ui->tableWidget_RecordCounts->setItem(recordIndex, 1, recordCountStrItem);
        ui->tableWidget_RecordCounts->setItem(recordIndex, 2, recordCountItem);
        ui->tableWidget_RecordCounts->setItem(recordIndex, 3, recordIconItem);

        recordIndex++;
    }

    ui->tableWidget_RecordOrder->resizeColumnsToContents();
    ui->tableWidget_RecordCounts->resizeColumnsToContents();
}
