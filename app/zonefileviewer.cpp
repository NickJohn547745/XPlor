#include "zonefileviewer.h"
#include "ui_zonefileviewer.h"

ZoneFileViewer::ZoneFileViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ZoneFileViewer)
{
    ui->setupUi(this);

    aZoneFile = nullptr;

    ui->tableWidget_RecordCounts->setColumnCount(2);
    ui->tableWidget_RecordCounts->setHorizontalHeaderLabels({ "Asset", "Count" });
    ui->tableWidget_RecordCounts->horizontalHeader()->setStretchLastSection(true);

    ui->tableWidget_RecordOrder->setColumnCount(2);
    ui->tableWidget_RecordOrder->setHorizontalHeaderLabels({ "Asset", "Count" });
    ui->tableWidget_RecordOrder->horizontalHeader()->setStretchLastSection(true);
}

ZoneFileViewer::~ZoneFileViewer()
{
    delete ui;
}

void ZoneFileViewer::SetZoneFile(std::shared_ptr<ZoneFile> aZoneFile) {
    ui->tableWidget_RecordCounts->clear();
    ui->listWidget_Tags->clear();

    const QStringList tags = aZoneFile->GetTags();
    ui->listWidget_Tags->addItems(tags);
    ui->label_Title->setText(aZoneFile->GetStem());

    if (tags.isEmpty()) {
        ui->groupBox_Tags->hide();
    } else {
        ui->groupBox_Tags->show();
    }

    QString lastAsset = "";
    int consecutiveCount = 1;
    int consecutiveIndex = 0;
    const QStringList records = aZoneFile->GetRecords();
    QMap<QString, int> recordCounts = QMap<QString, int>();
    for (const QString &record : records) {
        if (record == "ffffffff") { break; }
        if (!recordCounts.contains(record)) {
            recordCounts[record] = 0;
        }
        recordCounts[record]++;

        QString assetType = aZoneFile->AssetTypeToString(record);
        if (lastAsset.isEmpty()) {
            lastAsset = assetType;
        } else if (lastAsset == assetType) {
            consecutiveCount++;
        } else {
            ui->tableWidget_RecordOrder->setRowCount(consecutiveIndex + 1);

            QTableWidgetItem *recordStrItem = new QTableWidgetItem(lastAsset);
            QTableWidgetItem *recordCountItem = new QTableWidgetItem(QString::number(consecutiveCount));

            ui->tableWidget_RecordOrder->setItem(consecutiveIndex, 0, recordStrItem);
            ui->tableWidget_RecordOrder->setItem(consecutiveIndex, 1, recordCountItem);

            consecutiveCount = 1;
            consecutiveIndex++;
            lastAsset = assetType;
        }
    }
    ui->tableWidget_RecordOrder->setRowCount(consecutiveIndex + 1);

    QTableWidgetItem *recordStrItem = new QTableWidgetItem(lastAsset);
    QTableWidgetItem *recordCountItem = new QTableWidgetItem(QString::number(consecutiveCount));

    ui->tableWidget_RecordOrder->setItem(consecutiveIndex, 0, recordStrItem);
    ui->tableWidget_RecordOrder->setItem(consecutiveIndex, 1, recordCountItem);

    int recordIndex = 0;
    for (const QString &record : recordCounts.keys()) {
        int recordCount = recordCounts[record];

        QString assetType = aZoneFile->AssetTypeToString(record);

        ui->tableWidget_RecordCounts->setRowCount(recordIndex + 1);

        QTableWidgetItem *recordCountStrItem = new QTableWidgetItem(assetType);
        QTableWidgetItem *recordCountItem = new QTableWidgetItem(QString::number(recordCount));

        ui->tableWidget_RecordCounts->setItem(recordIndex, 0, recordCountStrItem);
        ui->tableWidget_RecordCounts->setItem(recordIndex, 1, recordCountItem);

        recordIndex++;
    }

    auto assetMap = aZoneFile->GetAssetMap();
    for (LocalString localString : assetMap.localStrings) {
    }
    for (RawFile rawFile : assetMap.rawFiles) {
    }
    for (TechSet techSet : assetMap.techSets) {
    }
    for (Image image : assetMap.images) {
    }
    for (Animation animation : assetMap.animations) {
    }
    for (StringTable stringTable : assetMap.stringTables) {
    }
    for (MenuFile menuFile : assetMap.menuFiles) {
    }

}
