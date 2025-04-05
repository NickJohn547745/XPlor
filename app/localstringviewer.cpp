#include "localstringviewer.h"
#include "ui_localstringviewer.h"

LocalStringViewer::LocalStringViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LocalStringViewer),
    mVersion(),
    mConfigPath(),
    mFileNotes() {
    ui->setupUi(this);

    ui->tableWidget_Strings->setColumnCount(2);
    ui->tableWidget_Strings->setColumnWidth(0, 200);
    ui->tableWidget_Strings->horizontalHeader()->setStretchLastSection(true);
}

LocalStringViewer::~LocalStringViewer() {
    delete ui;
}

void LocalStringViewer::SetVersion(quint32 aVersion) {
    mVersion = aVersion;

    ui->spinBox_Version->setValue(mVersion);
}

void LocalStringViewer::SetConfigPath(const QString aConfigPath) {
    mConfigPath = aConfigPath;

    ui->lineEdit_Config->setText(mConfigPath);
}

void LocalStringViewer::SetFileNotes(const QString aFileNotes) {
    mFileNotes = aFileNotes;

    ui->plainTextEdit_FileNotes->setPlainText(mFileNotes);
}

void LocalStringViewer::AddLocalString(LocalString aLocalString) {
    mLocalStrings << aLocalString;

    ui->tableWidget_Strings->setRowCount(mLocalStrings.size());

    QTableWidgetItem *aliasItem = new QTableWidgetItem(aLocalString.alias);
    QTableWidgetItem *stringItem = new QTableWidgetItem(aLocalString.string);

    ui->tableWidget_Strings->setItem(mLocalStrings.size() - 1, 0, aliasItem);
    ui->tableWidget_Strings->setItem(mLocalStrings.size() - 1, 1, stringItem);
}

void LocalStringViewer::SetZoneFile(std::shared_ptr<ZoneFile> aZoneFile) {
    mLocalStrings.clear();
    ui->tableWidget_Strings->clear();

    ui->label_Title->setText(aZoneFile->GetStem().section('.', 0, 0) + ".str");
    for (LocalString localStr : aZoneFile->GetAssetMap().localStrings) {
        AddLocalString(localStr);
    }
}
