#include "ddsviewer.h"
#include "enums.h"
#include "ui_ddsviewer.h"

DDSViewer::DDSViewer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DDSViewer)
{
    ui->setupUi(this);
    mDDSFile = nullptr;
}

DDSViewer::~DDSViewer() {
    delete ui;
}

void DDSViewer::SetDDSFile(std::shared_ptr<DDSFile> aDDSFile) {
    mDDSFile.swap(aDDSFile);

    ui->label_Title->setText(mDDSFile->fileStem + ".dds");

    char magicData[5];
    magicData[0] = static_cast<char>(mDDSFile->header.magic & 0xFF);
    magicData[1] = static_cast<char>((mDDSFile->header.magic >> 8) & 0xFF);
    magicData[2] = static_cast<char>((mDDSFile->header.magic >> 16) & 0xFF);
    magicData[3] = static_cast<char>((mDDSFile->header.magic >> 24) & 0xFF);
    magicData[4] = '\0';

    // If you’re using Qt and want a QString:
    QString magicStr = QString::fromLatin1(magicData);
    ui->lineEdit_Magic->setText(magicStr);
    ui->spinBox_Size->setValue(mDDSFile->header.size);

    ui->checkBox_CapsValid->setChecked((mDDSFile->header.flags & DDSD_CAPS) != 0);
    ui->checkBox_HeightValid->setChecked((mDDSFile->header.flags & DDSD_HEIGHT) != 0);
    ui->checkBox_WidthValid->setChecked((mDDSFile->header.flags & DDSD_WIDTH) != 0);
    ui->checkBox_PitchValid->setChecked((mDDSFile->header.flags & DDSD_PITCH) != 0);
    ui->checkBox_PFValid->setChecked((mDDSFile->header.flags & DDSD_PIXELFORMAT) != 0);
    ui->checkBox_MipmapCountValid->setChecked((mDDSFile->header.flags & DDSD_MIPMAPCOUNT) != 0);
    ui->checkBox_LinearSizeValid->setChecked((mDDSFile->header.flags & DDSD_LINEARSIZE) != 0);
    ui->checkBox_DepthValid->setChecked((mDDSFile->header.flags & DDSD_DEPTH) != 0);

    ui->spinBox_PLSize->setValue(mDDSFile->header.pitchOrLinearSize);
    ui->spinBox_Depth->setValue(mDDSFile->header.depth);
    ui->spinBox_Width->setValue(mDDSFile->header.width);
    ui->spinBox_Height->setValue(mDDSFile->header.height);
    ui->spinBox_MipmapCount->setValue(mDDSFile->header.mipMapCount);

    ui->spinBox_Res1->setValue(mDDSFile->header.reserved1[0]);
    ui->spinBox_Res2->setValue(mDDSFile->header.reserved1[1]);
    ui->spinBox_Res3->setValue(mDDSFile->header.reserved1[2]);
    ui->spinBox_Res4->setValue(mDDSFile->header.reserved1[3]);
    ui->spinBox_Res5->setValue(mDDSFile->header.reserved1[4]);
    ui->spinBox_Res6->setValue(mDDSFile->header.reserved1[5]);
    ui->spinBox_Res7->setValue(mDDSFile->header.reserved1[6]);
    ui->spinBox_Res8->setValue(mDDSFile->header.reserved1[7]);
    ui->spinBox_Res9->setValue(mDDSFile->header.reserved1[8]);
    ui->spinBox_Res10->setValue(mDDSFile->header.reserved1[9]);
    ui->spinBox_Res11->setValue(mDDSFile->header.reserved1[10]);

    ui->spinBox_Res12->setValue(mDDSFile->header.reserved2);

    ui->spinBox_PF_Size->setValue(mDDSFile->header.pixelFormat.size);

    ui->checkBox_PF_AlphaPxValid->setChecked((mDDSFile->header.pixelFormat.flags & DDPF_ALPHAPIXELS) != 0);
    ui->checkBox_PF_AlphaOnlyValid->setChecked((mDDSFile->header.pixelFormat.flags & DDPF_ALPHA) != 0);
    ui->checkBox_PF_FormatValid->setChecked((mDDSFile->header.pixelFormat.flags & DDPF_FOURCC) != 0);
    ui->checkBox_PF_RGBValid->setChecked((mDDSFile->header.pixelFormat.flags & DDPF_RGB) != 0);
    ui->checkBox_PF_YUVValid->setChecked((mDDSFile->header.pixelFormat.flags & DDPF_YUV) != 0);
    ui->checkBox_PF_LuminanceValid->setChecked((mDDSFile->header.pixelFormat.flags & DDPF_LUMINANCE) != 0);

    QString formatStr = QString::number(mDDSFile->header.pixelFormat.format);
    switch (mDDSFile->header.pixelFormat.format) {
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
    ui->lineEdit_PF_Format->setText(formatStr);
    ui->spinBox_PF_RGBBitCount->setValue(mDDSFile->header.pixelFormat.rgbBitCount);
    ui->spinBox_RedBitCount->setValue(mDDSFile->header.pixelFormat.rBitMask);
    ui->spinBox_GreenBitCount->setValue(mDDSFile->header.pixelFormat.gBitMask);
    ui->spinBox_BlueBitCount->setValue(mDDSFile->header.pixelFormat.bBitMask);
    ui->spinBox_AlphaBitMask->setValue(mDDSFile->header.pixelFormat.aBitMask);

    ui->checkBox_Caps1_TextureValid->setChecked((mDDSFile->header.caps.caps1 & DDSCAPS_TEXTURE) != 0);
    ui->checkBox_Caps1_ComplexValid->setChecked((mDDSFile->header.caps.caps1 & DDSCAPS_COMPLEX) != 0);
    ui->checkBox_Caps1_MipmapValid->setChecked((mDDSFile->header.caps.caps1 & DDSCAPS_MIPMAP) != 0);

    ui->checkBox_Caps2_CubemapValid->setChecked((mDDSFile->header.caps.caps2 & DDSCAPS2_CUBEMAP) != 0);
    ui->checkBox_Caps2_CMPXValid->setChecked((mDDSFile->header.caps.caps2 & DDSCAPS2_CUBEMAP_POSITIVEX) != 0);
    ui->checkBox_Caps2_CMNXValid->setChecked((mDDSFile->header.caps.caps2 & DDSCAPS2_CUBEMAP_NEGATIVEX) != 0);
    ui->checkBox_Caps2_CMPYValid->setChecked((mDDSFile->header.caps.caps2 & DDSCAPS2_CUBEMAP_POSITIVEY) != 0);
    ui->checkBox_Caps2_CMNYValid->setChecked((mDDSFile->header.caps.caps2 & DDSCAPS2_CUBEMAP_NEGATIVEY) != 0);
    ui->checkBox_Caps2_CMPZValid->setChecked((mDDSFile->header.caps.caps2 & DDSCAPS2_CUBEMAP_POSITIVEZ) != 0);
    ui->checkBox_Caps2_CMNZValid->setChecked((mDDSFile->header.caps.caps2 & DDSCAPS2_CUBEMAP_NEGATIVEZ) != 0);
    ui->checkBox_Caps2_VolumeValid->setChecked((mDDSFile->header.caps.caps2 & DDSCAPS2_VOLUME) != 0);

    ui->spinBox_Caps_DDSX->setValue(mDDSFile->header.caps.dDSX);
    ui->spinBox_Caps_Res->setValue(mDDSFile->header.caps.reserved);

    ui->comboBox_Mipmap->clear();
    for (auto mipmap : mDDSFile->mipmaps) {
        ui->comboBox_Mipmap->addItem(QString("%1x%2").arg(mipmap.width).arg(mipmap.height));
    }

    connect(ui->comboBox_Mipmap, &QComboBox::currentIndexChanged, this, &DDSViewer::MipmapIndexChanged);

    if (!mDDSFile->mipmaps.empty()) {
        MipmapIndexChanged(0);
    }
}

void DDSViewer::MipmapIndexChanged(int aMipmapIndex) {
    if (aMipmapIndex == -1) { return; }

    auto mipmaps = mDDSFile->mipmaps;
    auto mipmap = mipmaps[aMipmapIndex];

    ui->spinBox_MipmapSize->setValue(mipmap.size);
    ui->spinBox_MipmapWidth->setValue(mipmap.width);
    ui->spinBox_MipmapHeight->setValue(mipmap.height);

    // Validate Data
    if (mipmap.size <= 0) {
        qDebug() << "Error: Mipmap data is empty!";
        return;
    }
    if (mipmap.width <= 0 || mipmap.height <= 0) {
        qDebug() << "Error: Invalid mipmap dimensions!";
        return;
    }

    // Ensure data size matches expected size
    int bytesPerPixel = 4; // RGBA8888
    quint32 expectedSize = mipmap.width * mipmap.height * bytesPerPixel;
    if (mipmap.size < expectedSize) {
        qDebug() << "Error: Mipmap data size mismatch! Expected:" << expectedSize << ", Got:" << mipmap.size;
        return;
    }

    // Create QImage
    const unsigned char* imageData = reinterpret_cast<const unsigned char*>(mipmap.data.constData());
    QImage image(reinterpret_cast<const uchar*>(imageData),
                 mipmap.width, mipmap.height,
                 mipmap.width * bytesPerPixel, // Stride
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

