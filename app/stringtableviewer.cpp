#include "stringtableviewer.h"
#include "ui_stringtableviewer.h"

StringTableViewer::StringTableViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StringTableViewer)
{
    ui->setupUi(this);
}

StringTableViewer::~StringTableViewer()
{
    delete ui;
}

void StringTableViewer::SetStringTable(std::shared_ptr<StringTable> aStringTable) {
    ui->tableWidget_Strings->clear();

    ui->tableWidget_Strings->setRowCount(aStringTable->rowCount);
    ui->tableWidget_Strings->setColumnCount(aStringTable->columnCount);

    int currentIndex = 0;
    for (const QString &key : aStringTable->content.keys()) {
        const QString value = aStringTable->content[key];

        QTableWidgetItem *tableKeyItem = new QTableWidgetItem();
        tableKeyItem->setText(key);
        ui->tableWidget_Strings->setItem(currentIndex, 0, tableKeyItem);

        QTableWidgetItem *tableValItem = new QTableWidgetItem();
        tableValItem->setText(value);
        ui->tableWidget_Strings->setItem(currentIndex, 1, tableValItem);

        currentIndex++;
    }
}
