#include "techsetviewer.h"
#include "ui_techsetviewer.h"

TechSetViewer::TechSetViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TechSetViewer)
{
    ui->setupUi(this);
}

TechSetViewer::~TechSetViewer()
{
    delete ui;
}

void TechSetViewer::SetTechSet(std::shared_ptr<TechSet> aTechSet) {
    ui->listWidget_Ptrs->clear();
    ui->label_Title->setText(aTechSet->name);

    int ptrIndex = 1;
    for (auto ptr : aTechSet->pointers) {
        ui->listWidget_Ptrs->addItem(QString("Pointer %1: %2").arg(ptrIndex).arg(ptr));
        ptrIndex++;
    }
}
