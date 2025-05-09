#include "materialviewer.h"
#include "ui_materialviewer.h"

MaterialViewer::MaterialViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MaterialViewer) {
    ui->setupUi(this);
}

MaterialViewer::~MaterialViewer() {
    delete ui;
}

QString ToHexStr(quint32 in) {
    return QString("%1").arg(in, 8, 16, QChar('0')).toUpper();
}

void MaterialViewer::SetMaterial(std::shared_ptr<Material> aMaterial) {
    ui->lineEdit_NamePtr->setText(ToHexStr(aMaterial->namePtr));
    ui->lineEdit_Name->setText(aMaterial->name);
    ui->lineEdit_RefPtr->setText(ToHexStr(aMaterial->refNamePtr));
    ui->lineEdit_RefName->setText(aMaterial->refName);
    QString unknownStr = "";
    foreach (quint32 unknownPtr, aMaterial->pointers) {
        unknownStr += ToHexStr(unknownPtr) + "\n";
    }
    ui->lineEdit_Unknowns->setText(unknownStr);
    ui->lineEdit_StateA->setText(ToHexStr(aMaterial->stateBits[0]));
    ui->lineEdit_StateA->setText(ToHexStr(aMaterial->stateBits[1]));
    ui->spinBox_TextureCount->setValue(aMaterial->textureCount);
    ui->spinBox_ConstCount->setValue(aMaterial->constCount);
    ui->lineEdit_TechSetPtr->setText(ToHexStr(aMaterial->techSetPtr));
    ui->lineEdit_TexturePtr->setText(ToHexStr(aMaterial->texturePtr));
    ui->lineEdit_ConstantPtr->setText(ToHexStr(aMaterial->constPtr));
}
