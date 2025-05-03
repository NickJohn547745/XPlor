#include "fastfileviewer.h"
#include "asset_structs.h"
#include "ui_fastfileviewer.h"

FastFileViewer::FastFileViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FFViewer)
    , mFastFile(nullptr)
{
    ui->setupUi(this);
}

FastFileViewer::~FastFileViewer()
{
    delete ui;
}

void FastFileViewer::SetFastFile(std::shared_ptr<FastFile> aFastFile) {
    mFastFile.swap(aFastFile);

    ui->label_Title->setText(mFastFile->GetStem());
    ui->comboBox_Company->setCurrentIndex(mFastFile->GetCompany());
    ui->comboBox_FileType->setCurrentIndex(mFastFile->GetType());
    ui->checkBox_Signed->setChecked(mFastFile->GetSignage() == SIGNAGE_SIGNED);
    ui->lineEdit_Magic->setText(mFastFile->GetMagic());
    ui->spinBox_Version->setValue(mFastFile->GetVersion());
}
