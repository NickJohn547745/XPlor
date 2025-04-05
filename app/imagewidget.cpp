#include "imagewidget.h"
#include "ui_imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ImageWidget)
{
    ui->setupUi(this);
}

ImageWidget::~ImageWidget()
{
    delete ui;
}

void ImageWidget::SetImage(std::shared_ptr<Image> aImage)
{
    mImage = aImage;

    ui->lineEdit_Name->setText(aImage->name);
    ui->lineEdit_Role->setText(aImage->materialName);
    ui->comboBox_Compression->setCurrentIndex(aImage->compression);
}

std::shared_ptr<Image> ImageWidget::GetImage()
{
    return mImage;
}
