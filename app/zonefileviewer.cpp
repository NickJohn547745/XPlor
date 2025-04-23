#include "zonefileviewer.h"
#include "ui_zonefileviewer.h"

ZoneFileViewer::ZoneFileViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ZoneFileViewer) {
    ui->setupUi(this);

    aZoneFile = nullptr;

    ui->tableWidget_RecordCounts->setColumnCount(4);
    ui->tableWidget_RecordCounts->setHorizontalHeaderLabels({ "Identifier", "Asset", "Count", "Icon" });
    ui->tableWidget_RecordCounts->horizontalHeader()->setStretchLastSection(true);

    ui->tableWidget_RecordOrder->setColumnCount(4);
    ui->tableWidget_RecordOrder->setHorizontalHeaderLabels({ "Identifier", "Asset", "Count", "Icon" });
    ui->tableWidget_RecordOrder->horizontalHeader()->setStretchLastSection(true);
}

ZoneFileViewer::~ZoneFileViewer() {
    delete ui;
}

void ZoneFileViewer::SetZoneFile(std::shared_ptr<ZoneFile> aZoneFile) {
    ui->tableWidget_RecordCounts->clearContents();
    ui->tableWidget_RecordOrder->clearContents();
    ui->listWidget_Tags->clear();

    const QStringList tags = aZoneFile->GetTags();
    ui->listWidget_Tags->addItems(tags);
    ui->label_Title->setText(aZoneFile->GetStem() + ".zone");

    if (tags.isEmpty()) {
        ui->groupBox_Tags->hide();
    } else {
        ui->groupBox_Tags->show();
    }

    QString lastAsset = "";
    QString lastRecord = "";
    QIcon assetIcon;
    int consecutiveCount = 1;
    int consecutiveIndex = 0;
    const QStringList records = aZoneFile->GetRecords();
    QMap<QString, int> recordCounts = QMap<QString, int>();
    for (const QString &record : records) {
        lastRecord = record;
        if (record == "ffffffff") { break; }
        if (!recordCounts.contains(record)) {
            recordCounts[record] = 0;
        }
        recordCounts[record]++;

        QString assetType = aZoneFile->AssetTypeToString(record);
        if (assetIcon.isNull()) {
            qDebug() << "Icon is null for record: " << record;
        }

        if (lastAsset.isEmpty()) {
            lastAsset = assetType;
            lastRecord = record;
        } else if (lastAsset == assetType) {
            consecutiveCount++;
        } else {
            ui->tableWidget_RecordOrder->setRowCount(consecutiveIndex + 1);

            QTableWidgetItem *recordItem = new QTableWidgetItem(lastRecord.toUpper());
            QTableWidgetItem *recordStrItem = new QTableWidgetItem(lastAsset);
            QTableWidgetItem *recordCountItem = new QTableWidgetItem(QString::number(consecutiveCount));
            QTableWidgetItem *recordIconItem = new QTableWidgetItem();
            assetIcon = aZoneFile->AssetStrToIcon(lastAsset);
            recordIconItem->setIcon(assetIcon);

            ui->tableWidget_RecordOrder->setItem(consecutiveIndex, 0, recordItem);
            ui->tableWidget_RecordOrder->setItem(consecutiveIndex, 1, recordStrItem);
            ui->tableWidget_RecordOrder->setItem(consecutiveIndex, 2, recordCountItem);
            ui->tableWidget_RecordOrder->setItem(consecutiveIndex, 3, recordIconItem);

            consecutiveCount = 1;
            consecutiveIndex++;
            lastAsset = assetType;
            lastRecord = record;
        }
    }
    ui->tableWidget_RecordOrder->setRowCount(consecutiveIndex + 1);

    QTableWidgetItem *recordItem = new QTableWidgetItem(lastRecord.toUpper());
    QTableWidgetItem *recordStrItem = new QTableWidgetItem(lastAsset);
    QTableWidgetItem *recordCountItem = new QTableWidgetItem(QString::number(consecutiveCount));
    QTableWidgetItem *recordIconItem = new QTableWidgetItem();
    assetIcon = aZoneFile->AssetStrToIcon(lastAsset);
    recordIconItem->setIcon(assetIcon);

    ui->tableWidget_RecordOrder->setItem(consecutiveIndex, 0, recordItem);
    ui->tableWidget_RecordOrder->setItem(consecutiveIndex, 1, recordStrItem);
    ui->tableWidget_RecordOrder->setItem(consecutiveIndex, 2, recordCountItem);
    ui->tableWidget_RecordOrder->setItem(consecutiveIndex, 3, recordIconItem);

    int recordIndex = 0;
    for (const QString &record : recordCounts.keys()) {
        int recordCount = recordCounts[record];

        QString assetType = aZoneFile->AssetTypeToString(record);
        assetIcon = aZoneFile->AssetStrToIcon(assetType);
        if (assetIcon.isNull()) {
            qDebug() << "Icon is null for record: " << record;
        }

        ui->tableWidget_RecordCounts->setRowCount(recordIndex + 1);

        QTableWidgetItem *recordCountStrItem = new QTableWidgetItem(assetType);
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
