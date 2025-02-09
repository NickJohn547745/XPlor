#include "ddsfile.h"
#include "enums.h"
#include "iwifile.h"

DDSPixelFormat DDSFile::CalculatePixelFormat(quint8 aIWIFormat) {
    DDSPixelFormat ddsPixelFormat = {};
    ddsPixelFormat.size = 16; // Fixed
    ddsPixelFormat.format = 0;

    switch (aIWIFormat) {
    case IWI_FORMAT_ARGB32:
        ddsPixelFormat.flags = DDPF_RGB | DDPF_ALPHAPIXELS;
        ddsPixelFormat.rgbBitCount = 32;
        ddsPixelFormat.rBitMask = 0x00ff0000;
        ddsPixelFormat.gBitMask = 0x0000ff00;
        ddsPixelFormat.bBitMask = 0x000000ff;
        ddsPixelFormat.aBitMask = 0xff000000;
        break;
    case IWI_FORMAT_DXT1:
        ddsPixelFormat.flags = DDPF_FOURCC;
        ddsPixelFormat.format = 0x31545844;
        break;
    case IWI_FORMAT_DXT3:
        ddsPixelFormat.flags = DDPF_FOURCC;
        ddsPixelFormat.format = 0x33545844;
        break;
    case IWI_FORMAT_DXT5:
        ddsPixelFormat.flags = DDPF_FOURCC;
        ddsPixelFormat.format = 0x35545844;
        break;
    default:
        qDebug() << "Error: Invalid IWI format: " << aIWIFormat;
        return {};
    }
    return ddsPixelFormat;
}

void DDSFile::SetupExportDirs() {
    QDir dir = QDir::currentPath();
    if (!dir.exists("exports/")) {
        dir.mkdir("exports/");
    }

    if (!dir.exists("exports/iwi/")) {
        dir.mkdir("exports/iwi/");
    }
    if (!dir.exists("exports/dds/")) {
        dir.mkdir("exports/dds/");
    }
    if (!dir.exists("exports/png/")) {
        dir.mkdir("exports/png/");
    }
    if (!dir.exists("exports/jpg/")) {
        dir.mkdir("exports/jpg/");
    }
}

DDSFile::DDSFile() :
    fileStem(),
    header(),
    mipmaps() {

}

QByteArray DDSFile::ReadDDSFile(const QString &aFilePath) {
    if (!aFilePath.endsWith(".dds", Qt::CaseInsensitive)) {
        qDebug() << "Error: Invalid filename " << aFilePath;
        return {};
    }

    if (!QFile::exists(aFilePath)) {
        qDebug() << "Error: File does not exist!";
        return {};
    }

    QFile file(aFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error: Failed to read DDS file.";
        return {};
    }

    const QByteArray ddsData = file.readAll();
    file.close();
    return ddsData;
}

DDSFile::DDSFile(const QString &aFilePath)
    : DDSFile(ReadDDSFile(aFilePath), aFilePath.split('.').first().split('/').last()) {
}

DDSFile::DDSFile(const QByteArray aDDSData, const QString aFileStem) {
    QDataStream ddsIn(aDDSData);
    ddsIn.setByteOrder(QDataStream::LittleEndian);

    DDSHeader ddsHeader;
    if (ddsIn.readRawData(reinterpret_cast<char*>(&ddsHeader), sizeof(DDSHeader)) != sizeof(DDSHeader)) {
        qDebug() << "Error: Failed to read DDSHeader from QByteArray!";
        return;
    }

    fileStem = aFileStem;
    header = ddsHeader;

    // Ensure DevIL is initialized once globally
    static bool devilInitialized = false;
    if (!devilInitialized) {
        ilInit();
        devilInitialized = true;
    }

    // Generate and bind an image
    ILuint imageID;
    ilGenImages(1, &imageID);
    ilBindImage(imageID);

    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_UPPER_LEFT);

    // Load DDS file
    if (!ilLoadL(IL_DDS, aDDSData.constData(), aDDSData.size())) {
        ILuint devilError = ilGetError();
        qDebug() << "DevIL Error while loading DDS: " << devilError;
        ilDeleteImages(1, &imageID);
        return;
    }

    // Get mipmap count
    ILint numMipmaps = ilGetInteger(IL_NUM_MIPMAPS);
    qDebug() << "Number of mipmaps: " << numMipmaps;

    // Loop over all mipmap levels (0 is the base image)
    for (ILint level = 0; level <= numMipmaps; ++level) {
        ilBindImage(imageID);
        if (!ilActiveMipmap(level)) {
            qDebug() << "DevIL failed to activate mipmap level" << level;
            continue;
        }

        // Get mipmap properties
        int width = ilGetInteger(IL_IMAGE_WIDTH);
        int height = ilGetInteger(IL_IMAGE_HEIGHT);
        int depth = ilGetInteger(IL_IMAGE_DEPTH);
        int format = ilGetInteger(IL_IMAGE_FORMAT);
        int bpp = 0;

        switch (format) {
        case IL_RGB:
            bpp = 3;
            break;
        case IL_RGBA:
            bpp = 4;
            break;
        default:
            qDebug() << "Unsupported image format.";
            continue;
        }

        int dataSize = width * height * depth * bpp;

        ILubyte *data = ilGetData();
        if (!data) {
            qDebug() << "Error: DevIL returned null data for mipmap level" << level;
            continue;
        }

        // Create a mipmap structure
        DDSMipmap mipmap;
        mipmap.width = width;
        mipmap.height = height;
        mipmap.data = QByteArray(reinterpret_cast<const char*>(data), dataSize);
        mipmap.size = dataSize;

        // Store in DDS file
        mipmaps.append(mipmap);
    }

    ilDeleteImages(1, &imageID);
}

DDSFile::DDSFile(const DDSFile &ddsFile) :
    fileStem(ddsFile.fileStem),
    header(ddsFile.header),
    mipmaps(ddsFile.mipmaps) {

}

DDSFile::DDSFile(const IWIFile &aIWIFile)
    : DDSFile(IWItoDDSData(aIWIFile), aIWIFile.fileStem) {
}

QByteArray DDSFile::IWItoDDSData(const IWIFile &aIWIFile) {
    DDSHeader ddsHeader = {};
    ddsHeader.magic = 0x20534444; // 'DDS '
    ddsHeader.size = 124;
    ddsHeader.flags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT | DDSD_LINEARSIZE;
    ddsHeader.height = aIWIFile.info.Height;
    ddsHeader.width = aIWIFile.info.Width;
    ddsHeader.depth = 0;
    ddsHeader.mipMapCount = aIWIFile.mipmaps.size();

    DDSPixelFormat ddsPixelFormat = CalculatePixelFormat(aIWIFile.info.Format);
    if (ddsPixelFormat.flags & DDPF_FOURCC) {
        ddsHeader.flags |= DDSD_LINEARSIZE;
    } else {
        ddsHeader.flags |= DDSD_PITCH;
    }
    ddsHeader.pixelFormat = ddsPixelFormat;

    // Calculate pitch/linear size
    if (ddsPixelFormat.flags & DDPF_FOURCC) {
        int blockSize = (ddsPixelFormat.format == 0x31545844) ? 8 : 16;
        ddsHeader.pitchOrLinearSize = fmax(1, (ddsHeader.width + 3) / 4) * blockSize * (ddsHeader.height / 4);
    } else {
        ddsHeader.pitchOrLinearSize = ddsHeader.width * (ddsPixelFormat.rgbBitCount / 8);
    }

    DDSCaps ddsCaps = {};
    ddsCaps.caps1 = DDSCAPS_TEXTURE;
    ddsCaps.caps2 = 0;
    ddsCaps.dDSX = 0;
    ddsCaps.reserved = 0;
    ddsHeader.caps = ddsCaps;

    QByteArray ddsData;
    QDataStream out(&ddsData, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::LittleEndian);

    // Write DDS header
    out.writeRawData(reinterpret_cast<const char*>(&ddsHeader), sizeof(DDSHeader));

    for (auto mipmap : aIWIFile.mipmaps) {
        if (!mipmap.data.size()) { continue; }

        // Write mipmap data
        out.writeRawData(reinterpret_cast<const char*>(mipmap.data.constData()), mipmap.data.size());
    }

    return ddsData;
}

DDSFile &DDSFile::operator=(const DDSFile &other) {
    if (this != &other) {
        fileStem = other.fileStem;
        header = other.header;
        mipmaps = other.mipmaps;
    }
    return *this;
}

// Write a DDS file from a DDSFile object
bool DDSFile::SaveDDS() {
    SetupExportDirs();

    QFile file("exports/dds/" + fileStem + ".dds");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Error: Unable to write DDS file" << fileStem + ".dds";
        return false;
    }

    QDataStream out(&file);
    out.setByteOrder(QDataStream::LittleEndian);

    // Write DDS Header
    out.writeRawData(reinterpret_cast<const char*>(&header), sizeof(DDSHeader));
    file.close();

    qDebug() << "Successfully wrote DDS file: " << fileStem + ".dds";
    return true;
}

bool DDSFile::SaveIWI() {
    SetupExportDirs();

    IWIFile iwiFile(*this);
    if (!iwiFile.SaveIWI()) {
        qDebug() << "Error: Unable to write IWI file" << fileStem + ".iwi";
        return false;
    }
    return true;
}

bool DDSFile::SavePNG() {
    SetupExportDirs();

    int mipmapIndex = 1;
    for (const DDSMipmap &mipmap : mipmaps) {
        QString subFilePath = "exports/png/" + fileStem + ".png";
        if (mipmaps.size() > 1) {
            subFilePath = "exports/png/" + fileStem + QString("_%1").arg(mipmapIndex) + ".png";
        }

        // Calculate bytes per line (stride)
        int bytesPerPixel = 4; // Assuming RGBA8888 (4 bytes per pixel)
        int bytesPerLine = mipmap.width * bytesPerPixel;

        QImage image(reinterpret_cast<const uchar*>(mipmap.data.constData()),
                     mipmap.width, mipmap.height, bytesPerLine, QImage::Format_RGBA8888);

        if (image.isNull()) {
            qDebug() << "Error: Failed to create QImage for mipmap" << mipmapIndex;
            return false;
        }

        if (!image.save(subFilePath)) {
            qDebug() << "Error: Unable to save PNG file" << subFilePath;
            return false;
        }

        mipmapIndex++;
    }
    return true;
}

bool DDSFile::SaveJPG() {
    SetupExportDirs();

    int mipmapIndex = 1;
    for (const DDSMipmap &mipmap : mipmaps) {
        QString subFilePath = "exports/jpg/" + fileStem + ".jpg";
        if (mipmaps.size() > 1) {
            subFilePath = "exports/jpg/" + fileStem + QString("_%1").arg(mipmapIndex) + ".jpg";
        }

        // Calculate bytes per line (stride)
        int bytesPerPixel = 4; // Assuming RGBA8888 (4 bytes per pixel)
        int bytesPerLine = mipmap.width * bytesPerPixel;

        QImage image(reinterpret_cast<const uchar*>(mipmap.data.constData()),
                     mipmap.width, mipmap.height, bytesPerLine, QImage::Format_RGBA8888);

        if (image.isNull()) {
            qDebug() << "Error: Failed to create QImage for mipmap" << mipmapIndex;
            return false;
        }

        if (!image.save(subFilePath, "JPG")) {
            qDebug() << "Error: Unable to save JPG file" << subFilePath;
            return false;
        }

        mipmapIndex++;
    }
    return true;
}

