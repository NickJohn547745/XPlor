#include "iwifile.h"
#include "ddsfile.h"

IWIFile::IWIFile() :
    fileStem(),
    header(),
    info(),
    mipmaps() {

}

IWIFile::IWIFile(const QString &aFilePath) :
    fileStem(aFilePath.split('.').first().split('/').last()) {

    QFile file(aFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error: Unable to open IWI file" << aFilePath;
        return;
    }

    QDataStream in(&file);
    in.setByteOrder(QDataStream::LittleEndian);

    // Read header
    in.readRawData(reinterpret_cast<char*>(&header), sizeof(IWIHeader));

    if (!header.isSupported()) {
        qDebug() << "Error: Unsupported IWI version!";
        return;
    }

    // Adjust seek position for MW2/MW3
    if (header.Version == 0x08) {
        file.seek(0x08);
    }

    // Read info
    in.readRawData(reinterpret_cast<char*>(&info), sizeof(IWIInfo));

    // Determine offset array size
    QVector<qint32> offsets((header.Version == 0x1B) ? 8 : 4);

    if (header.Version == 0x0D || header.Version == 0x1B) {
        file.seek(header.Version == 0x1B ? 0x20 : 0x10);
    }

    // Read offsets
    for (qint32 &offset : offsets) {
        in >> offset;
    }

    // Compute mipmaps
    qint64 currentPos = file.pos();
    qint64 fileSize = file.size();
    QVector<quint64> positions = QVector<quint64>();

    for (int i = 0; i < offsets.size(); i++) {
        IWIMipmap m;
        if (i == 0) {
            m.offset = offsets[i];
            m.size = fileSize - offsets[i];
        } else if (i == offsets.size() - 1) {
            m.offset = currentPos;
            m.size = offsets[i] - currentPos;
        } else {
            m.offset = offsets[i];
            m.size = offsets[i - 1] - offsets[i];
        }

        quint64 pos = file.pos();

        // Read mipmap
        file.seek(m.offset);
        m.data = file.read(m.size);

        file.seek(pos);
        mipmaps.append(m);
    }

    // Close file
    file.close();
}

IWIFile::IWIFile(DDSFile &aDDSFile) {
    // Ensure the DDS file has mipmaps
    if (aDDSFile.mipmaps.isEmpty()) {
        qDebug() << "Error: No mipmaps found in DDS file!";
        return;
    }

    // Create IWIFile object
    fileStem = aDDSFile.fileStem;

    // Set header (Magic & Version)
    memcpy(header.Magic, "IWi", 3);
    header.Version = 0x06; // Default to CoD4/CoD5 version

    // Set IWI Texture Info
    info.Format = static_cast<quint8>(aDDSFile.header.pixelFormat.format);
    info.Width = aDDSFile.header.width;
    info.Height = aDDSFile.header.height;
    info.Depth = 1; // Default depth for 2D textures
    info.Usage = 0; // No specific usage

    // Convert DDS mipmaps to IWI mipmaps
    int offset = 28; // Standard offset start
    for (const auto& ddsMipmap : aDDSFile.mipmaps) {
        IWIMipmap iwiMipmap;
        iwiMipmap.offset = offset;
        iwiMipmap.size = ddsMipmap.data.size();
        iwiMipmap.data = ddsMipmap.data;

        offset += iwiMipmap.size;
        mipmaps.append(iwiMipmap);
    }
}

IWIFile::IWIFile(const IWIFile &iwiFile) {
    fileStem = iwiFile.fileStem;
    header = iwiFile.header;
    info = iwiFile.info;
    mipmaps = iwiFile.mipmaps;
}

IWIFile &IWIFile::operator=(const IWIFile &other) {
    if (this != &other) {
        fileStem = other.fileStem;
        header = other.header;
        info = other.info;
        mipmaps = other.mipmaps;
    }
    return *this;
}

IWIFile::~IWIFile() {

}

void IWIFile::SetupExportDirs() {
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

bool IWIFile::SaveIWI() {
    SetupExportDirs();
    QFile file("exports/iwi/" + fileStem + ".iwi");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Error: Unable to write IWI file " << fileStem + ".iwi";
        return false;
    }

    QDataStream out(&file);
    out.setByteOrder(QDataStream::LittleEndian);

    // Write IWI Header
    out.writeRawData(reinterpret_cast<const char*>(&header), sizeof(IWIHeader));

    // Adjust seek position for MW2/MW3
    if (header.Version == 0x08) {
        file.seek(0x08);
    }

    // Write IWI Texture Info
    out.writeRawData(reinterpret_cast<const char*>(&info), sizeof(IWIInfo));

    // Determine number of mipmaps based on version
    QVector<qint32> offsets((header.Version == 0x1B) ? 8 : 4);
    qint32 currentOffset = file.pos() + (offsets.size() * sizeof(qint32));

    // Compute offsets
    for (int i = 0; i < offsets.size(); i++) {
        offsets[i] = currentOffset;
        if (mipmaps.size() && i < mipmaps.size()) {
            currentOffset += mipmaps[i].size;
        }
    }

    // Seek and write offsets
    if (header.Version == 0x0D || header.Version == 0x1B) {
        file.seek(header.Version == 0x1B ? 0x20 : 0x10);
    }

    for (const qint32 &offset : offsets) {
        out << offset;
    }

    for (auto mipmap : mipmaps) {
        file.seek(mipmap.offset);
        file.write(mipmap.data);
    }

    file.close();

    qDebug() << "Successfully wrote IWI file: " << fileStem + ".iwi";
    return true;
}

bool IWIFile::SaveDDS() {
    SetupExportDirs();
    QFile file("exports/dds/" + fileStem + ".dds");
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Error: Unable to write DDS file " << fileStem + ".dds";
        return false;
    }

    DDSHeader ddsHeader = {};
    ddsHeader.magic = 0x20534444; // 'DDS '
    ddsHeader.size = 124;
    ddsHeader.flags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT | DDSD_LINEARSIZE;
    ddsHeader.height = info.Height;
    ddsHeader.width = info.Width;
    ddsHeader.depth = 0;
    ddsHeader.mipMapCount = mipmaps.size();

    DDSPixelFormat ddsPixelFormat = DDSFile::CalculatePixelFormat(info.Format);
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

    QDataStream out(&file);
    out.setByteOrder(QDataStream::LittleEndian);

    // Write DDS header
    out.writeRawData(reinterpret_cast<const char*>(&ddsHeader), sizeof(DDSHeader));

    for (auto mipmap : mipmaps) {
        if (!mipmap.data.size()) { continue; }

        // Write mipmap data
        out.writeRawData(reinterpret_cast<const char*>(mipmap.data.constData()), mipmap.data.size());
    }
    file.close();

    return true;
}

bool IWIFile::SavePNG() {
    DDSFile ddsFile(*this);
    if (!ddsFile.SavePNG()) {
        qDebug() << "Error: Failed to save PNG file: " << fileStem + ".png";
        return false;
    }
    return true;
}

bool IWIFile::SaveJPG() {
    DDSFile ddsFile(*this);
    if (!ddsFile.SavePNG()) {
        qDebug() << "Error: Failed to save JPG file: " << fileStem + ".jpg";
        return false;
    }
    return true;
}

// Check if the IWI version is supported
bool IWIHeader::isSupported() const {
    return (Magic[0] == 'I' && Magic[1] == 'W' && Magic[2] == 'i') &&
           supportedVersions.contains(Version);
}
