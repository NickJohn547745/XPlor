#include "iwiviewer.h"
#include "enums.h"
#include "ui_iwiviewer.h"

IWIViewer::IWIViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IWIViewer)
{
    ui->setupUi(this);
}

IWIViewer::~IWIViewer()
{
    delete ui;
}

void IWIViewer::SetIWIFile(std::shared_ptr<IWIFile> aIWIFile) {
    mIWIFile.swap(aIWIFile);

    ui->label_Title->setText(mIWIFile->fileStem + ".iwi");

    // If you’re using Qt and want a QString:
    QString magicStr = QString::fromLatin1(mIWIFile->header.Magic, 3);
    ui->lineEdit_Magic->setText(magicStr);

    ui->spinBox_Version->setValue(mIWIFile->header.Version);
    ui->spinBox_Depth->setValue(mIWIFile->info.Depth);
    QString formatStr = "";
    switch (mIWIFile->info.Format) {
    case IWI_FORMAT_ARGB32:
        formatStr = "ARGB32";
        break;
    case IWI_FORMAT_RGB24:
        formatStr = "RGB24";
        break;
    case IWI_FORMAT_GA16:
        formatStr = "GA16";
        break;
    case IWI_FORMAT_A8:
        formatStr = "A8";
        break;
    case IWI_FORMAT_DXT1:
        formatStr = "DXT1";
        break;
    case IWI_FORMAT_DXT3:
        formatStr = "DXT3";
        break;
    case IWI_FORMAT_DXT5:
        formatStr = "DXT5";
        break;
    }
    ui->lineEdit_Format->setText(formatStr);
    ui->spinBox_Height->setValue(mIWIFile->info.Height);
    ui->spinBox_Width->setValue(mIWIFile->info.Width);
    ui->spinBox_Usage->setValue(mIWIFile->info.Usage);

    ui->comboBox_Mipmap->clear();
    for (auto mipmap : mIWIFile->mipmaps) {
        ui->comboBox_Mipmap->addItem(QString::number(mipmap.offset));
    }

    connect(ui->comboBox_Mipmap, &QComboBox::currentIndexChanged, this, &IWIViewer::MipmapIndexChanged);

    if (!mIWIFile->mipmaps.empty()) {
        MipmapIndexChanged(0);
    }
}

void IWIViewer::MipmapIndexChanged(int aMipmapIndex) {
    auto mipmaps = mIWIFile->mipmaps;

    if (aMipmapIndex == -1) { return; }

    auto mipmap = mipmaps[aMipmapIndex];
    ui->spinBox_MipmapSize->setValue(mipmap.size);
    ui->spinBox_MipmapOffset->setValue(mipmap.offset);

    const unsigned char* imageData = reinterpret_cast<const unsigned char*>(mipmap.data.constData());
    QImage image(reinterpret_cast<const uchar*>(imageData),
                 mIWIFile->info.Width, mIWIFile->info.Height,
                 QImage::Format_RGBA8888);

    if (image.isNull()) {
        qDebug() << "Error: QImage creation failed!";
        return;
    }

    // Convert to QPixmap
    QPixmap pixmap = QPixmap::fromImage(image);
    if (pixmap.isNull()) {
        qDebug() << "Error: QPixmap conversion failed!";
        return;
    }

    // Scale and display
    pixmap = pixmap.scaled(ui->label_Image->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_Image->setPixmap(pixmap);
}
