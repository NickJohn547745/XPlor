#include "zonefile.h"
#include "utils.h"

#include <QFile>
#include <QDataStream>
#include <QDebug>

ZoneFile::ZoneFile() :
    fileStem(),
    size(),
    tagCount(),
    tags(),
    recordCount(),
    records(),
    assetMap() {

}

ZoneFile::~ZoneFile() {

}

ZoneFile::ZoneFile(const ZoneFile &aZoneFile) {
    fileStem = aZoneFile.fileStem;
    size = aZoneFile.size;
    tagCount = aZoneFile.tagCount;
    tags = aZoneFile.tags;
    recordCount = aZoneFile.recordCount;
    records = aZoneFile.records;
    assetMap = aZoneFile.assetMap;
}

ZoneFile &ZoneFile::operator=(const ZoneFile &other) {
    if (this != &other) {
        fileStem = other.fileStem;
        size = other.size;
        tagCount = other.tagCount;
        tags = other.tags;
        recordCount = other.recordCount;
        records = other.records;
        assetMap = other.assetMap;
    }
    return *this;
}

bool ZoneFile::Load(const QString aFilePath, FF_PLATFORM platform) {
    Q_UNUSED(platform);

    if (aFilePath.isEmpty()) {
        return false;
    }

    fileStem = aFilePath.split('/').last();

    // Check zone file can be read
    QFile *zoneFileObj = new QFile(aFilePath);
    if (!zoneFileObj->open(QIODevice::ReadOnly)) {
        qDebug() << QString("Error: %1 could not be read!.").arg(aFilePath);
        return false;
    } else if (!Load(zoneFileObj->readAll())) {
        qDebug() << "Error: Failed to load from zone data";
        return false;
    }

    // Clean up zone file
    zoneFileObj->close();
    delete zoneFileObj;

    return true;
}

bool ZoneFile::Load(const QByteArray aFileData, const QString aFileStem, FF_PLATFORM platform) {
    // Open zone file as little endian stream
    QDataStream zoneFileStream(aFileData);
    if (platform == FF_PLATFORM_PC) {
        zoneFileStream.setByteOrder(QDataStream::LittleEndian);
    } else {
        zoneFileStream.setByteOrder(QDataStream::BigEndian);
    }

    // Parse data from zone file header
    pParseZoneHeader(&zoneFileStream);
    fileStem = aFileStem;
    records =
        pParseZoneIndex(&zoneFileStream, recordCount);
    assetMap =
        pParseAssets(&zoneFileStream, records);

    return true;
}

QString ZoneFile::GetFileStem() {
    return fileStem;
}

quint32 ZoneFile::GetSize() {
    return size;
}

quint32 ZoneFile::GetTagCount() {
    return tagCount;
}

QStringList ZoneFile::GetTags() {
    return tags;
}

quint32 ZoneFile::GetRecordCount() {
    return recordCount;
}

QStringList ZoneFile::GetRecords() {
    return records;
}

AssetMap ZoneFile::GetAssetMap() {
    return assetMap;
}

void ZoneFile::pParseZoneHeader(QDataStream *aZoneFileStream) {
    size = pParseZoneSize(aZoneFileStream);
    pParseZoneUnknownsA(aZoneFileStream);

    tagCount = pParseZoneTagCount(aZoneFileStream);
    pParseZoneUnknownsB(aZoneFileStream);

    recordCount = pParseZoneRecordCount(aZoneFileStream);

    if (tagCount) {
        pParseZoneUnknownsC(aZoneFileStream);
        if (tagCount > 1) {
            tags = pParseZoneTags(aZoneFileStream, tagCount);
        }
    } else {
        aZoneFileStream->skipRawData(4);
    }
}

quint32 ZoneFile::pParseZoneSize(QDataStream *aZoneFileStream) {
    quint32 zoneFileSize;
    *aZoneFileStream >> zoneFileSize;
    if (zoneFileSize <= 0) {
        qDebug() << "Tried to open empty zone file!";
        exit(-1);
    }
    zoneFileSize += 36;
    return zoneFileSize;
}

/*
    ParseZoneUnknownsA()

    Parses the 1st section of unknowns as hex vals and uint32s
*/
void ZoneFile::pParseZoneUnknownsA(QDataStream *aZoneFileStream) {
    // Byte 4-7, 8-11, 12-15: unknown
    QByteArray unknown1(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown1.data(), 4);

    QByteArray unknown2(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown2.data(), 4);

    QByteArray unknown3(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown3.data(), 4);

    // Byte 16-19, 20-23: empty/unknown
    QByteArray unknown4(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown4.data(), 4);

    QByteArray unknown5(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown5.data(), 4);

    // Byte 24-27: somehow related to the filesize, but smaller value
    QByteArray unknown6(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown6.data(), 4);

    // Byte 28-31, 32-35: unknown
    QByteArray unknown7(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown7.data(), 4);

    QByteArray unknown8(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown8.data(), 4);
}

/*
    ParseZoneTagCount()

    Parses the number of string tags in the zone index
*/
quint32 ZoneFile::pParseZoneTagCount(QDataStream *aZoneFileStream) {
    quint32 tagCount;
    *aZoneFileStream >> tagCount;
    return tagCount;
}

/*
    ParseZoneRecordCount()

    Parses the number of records in the zone index
*/
quint32 ZoneFile::pParseZoneRecordCount(QDataStream *aZoneFileStream) {
    quint32 recordCount;
    *aZoneFileStream >> recordCount;
    return recordCount;
}

/*
    ParseZoneUnknownsB()

    Parses the 2nd section of unknowns as hex vals and uint32s
*/
void ZoneFile::pParseZoneUnknownsB(QDataStream *aZoneFileStream) {
    // Byte 44-47: Unknown/empty?
    QByteArray unknown9(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown9.data(), 4);
}

/*
    pParseZoneUnknownsC()

    Parses the 3rd section of unknowns as hex vals and uint32s
*/
void ZoneFile::pParseZoneUnknownsC(QDataStream *aZoneFileStream) {
    // Byte 40-43: Unknown/empty?
    QByteArray unknown10(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown10.data(), 4);

    // Byte 44-47: Unknown/empty?
    QByteArray unknown11(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown11.data(), 4);
}

/*
    ParseZoneTags()

    Parses the string tags ate the start of zone file
*/
QStringList ZoneFile::pParseZoneTags(QDataStream *aZoneFileStream, quint32 tagCount) {
    QStringList tags;

    // Byte 48-51: Repeated separators? ÿÿÿÿ x i
    aZoneFileStream->skipRawData(4 * (tagCount - 1));

    // Parse tags/strings before index
    QString zoneTag;
    char zoneTagChar;
    for (quint32 i = 0; i < tagCount; i++) {
        *aZoneFileStream >> zoneTagChar;
        while (zoneTagChar != 0) {
            zoneTag += zoneTagChar;
            *aZoneFileStream >> zoneTagChar;
        }
        tags << zoneTag;
        zoneTag.clear();

        qDebug() << "Peek: " << aZoneFileStream->device()->peek(8) << aZoneFileStream->device()->peek(8).contains(QByteArray::fromHex("FFFFFFFF"));
        if (aZoneFileStream->device()->peek(8).contains(QByteArray::fromHex("FFFFFFFF"))) { break; }
    }
    return tags;
}

/*
    ParseZoneIndex()

    Parse the binary zone index data and populate table
*/
QStringList ZoneFile::pParseZoneIndex(QDataStream *aZoneFileStream, quint32 recordCount) {
    QStringList result;

    // Don't parse if no records
    if (!recordCount) { return result; }

    // Parse index & map found asset types
    for (quint32 i = 0; i <= recordCount; i++) {
        // Skip record start
        QByteArray rawAssetType(4, Qt::Uninitialized);
        aZoneFileStream->readRawData(rawAssetType.data(), 4);
        result << rawAssetType.toHex();

        // Skip separator
        aZoneFileStream->skipRawData(4);
    }
    return result;
}

AssetMap ZoneFile::pParseAssets(QDataStream *aZoneFileStream, QStringList assetOrder) {
    AssetMap result;

    aZoneFileStream->device()->seek(aZoneFileStream->device()->pos() - 8);

    for (int i = 0; i < assetOrder.size(); i++) {
        const QString typeHex = assetOrder[i];
        const QString typeStr = Utils::AssetTypeToString(typeHex);

        if (typeStr == "LOCAL STRING") { // localized string asset
            result.localStrings << pParseAsset_LocalString(aZoneFileStream);
        } else if (typeStr == "RAW FILE") { // gsc
            auto rawFile = pParseAsset_RawFile(aZoneFileStream);
            if (rawFile.length) {
                result.rawFiles << rawFile;
            }
        } else if (typeStr == "PHYS PRESET") { // physpreset
            pParseAsset_PhysPreset(aZoneFileStream);
        } else if (typeStr == "MODEL") { // xmodel
            result.models << pParseAsset_Model(aZoneFileStream);
        } else if (typeStr == "MATERIAL") { // material
            pParseAsset_Material(aZoneFileStream);
        } else if (typeStr == "SHADER") { // pixelshader
            pParseAsset_Shader(aZoneFileStream);
        } else if (typeStr == "TECH SET") { // techset include
            result.techSets << pParseAsset_TechSet(aZoneFileStream);
        } else if (typeStr == "IMAGE") { // image
            result.images << pParseAsset_Image(aZoneFileStream);
        } else if (typeStr == "SOUND") { // loaded_sound
            pParseAsset_LoadedSound(aZoneFileStream);
        } else if (typeStr == "COLLISION MAP") { // col_map_mp
            pParseAsset_ColMapMP(aZoneFileStream);
        } else if (typeStr == "MP MAP") { // game_map_sp
            pParseAsset_GameMapSP(aZoneFileStream);
        } else if (typeStr == "SP MAP") { // game_map_mp
            pParseAsset_GameMapMP(aZoneFileStream);
        } else if (typeStr == "LIGHT DEF") { // lightdef
            pParseAsset_LightDef(aZoneFileStream);
        } else if (typeStr == "UI MAP") { // ui_map
            pParseAsset_UIMap(aZoneFileStream);
        } else if (typeStr == "SND DRIVER GLOBALS") { // snddriverglobals
            pParseAsset_SNDDriverGlobals(aZoneFileStream);
        } else if (typeStr == "AI TYPE") { // aitype
            pParseAsset_AIType(aZoneFileStream);
        } else if (typeStr == "EFFECT") { // aitype
            pParseAsset_FX(aZoneFileStream);
        } else if (typeStr == "ANIMATION") { // aitype
            result.animations << pParseAsset_Animation(aZoneFileStream);
        } else if (typeStr == "STRING TABLE") { // string_table
            result.stringTables << pParseAsset_StringTable(aZoneFileStream);
        } else if (typeStr == "MENU") { // string_table
            result.menuFiles << pParseAsset_MenuFile(aZoneFileStream);
        } else if (typeStr == "WEAPON") { // string_table
            pParseAsset_Weapon(aZoneFileStream);
        } else if (typeStr == "D3DBSP DUMP") { // string_table
            pParseAsset_D3DBSP(aZoneFileStream);
        } else if (typeStr != "UNKNOWN") {
            qDebug() << "Found bad asset type!" << typeStr;
        }
    }
    return result;
}

LocalString ZoneFile::pParseAsset_LocalString(QDataStream *aZoneFileStream) {
    LocalString result;

    quint32 stringPtr, aliasPtr;
    *aZoneFileStream >> stringPtr >> aliasPtr;
    if (stringPtr == 4294967295) {
        // Parse local string asset contents
        QString localStr;
        char localStrChar;
        *aZoneFileStream >> localStrChar;
        while (localStrChar != 0) {
            result.string += localStrChar;
            *aZoneFileStream >> localStrChar;
        }
    } else {
        result.string = "String Ptr: " + QString::number(stringPtr);
    }

    if (aliasPtr == 4294967295) {
        // Parse rawfile name
        QString aliasName;
        char aliasNameChar;
        *aZoneFileStream >> aliasNameChar;
        while (aliasNameChar != 0) {
            result.alias += aliasNameChar;
            *aZoneFileStream >> aliasNameChar;
        }
    } else {
        result.string = "Alias Ptr: " + QString::number(aliasPtr);
    }

    return result;
}

RawFile ZoneFile::pParseAsset_RawFile(QDataStream *aZoneFileStream) {
    RawFile result;

    // Skip start separator FF FF FF FF (pointer?)
    aZoneFileStream->skipRawData(4);

    *aZoneFileStream >> result.length;

    // Skip unknown 4 byte data
    aZoneFileStream->skipRawData(4);

    // Parse rawfile path
    char scriptPathChar;
    *aZoneFileStream >> scriptPathChar;
    while (scriptPathChar != 0) {
        result.path += scriptPathChar;
        *aZoneFileStream >> scriptPathChar;
    }
    result.path.replace(",", "");
    const QStringList pathParts = result.path.split('/');
    if (pathParts.size() == 0) {
        qDebug() << "Failed to parse ff path! " << result.path;
        exit(-1);
    }

    // Parse gsc contents
    char rawFileContentsChar;
    *aZoneFileStream >> rawFileContentsChar;
    while (rawFileContentsChar != 0 && rawFileContentsChar != -1) {
        result.contents += rawFileContentsChar;
        *aZoneFileStream >> rawFileContentsChar;
    }
    return result;
}

void ZoneFile::pParseAsset_PhysPreset(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

Model ZoneFile::pParseAsset_Model(QDataStream *aZoneFileStream) {
    Model result;

    qDebug() << "Model Info:";

    *aZoneFileStream >> result.namePtr >> result.tagCount >> result.rootTagCount
        >> result.surfCount >> result.unknownCount >> result.boneNamePtr
        >> result.parentListPtr >> result.quatsPtr >> result.transPtr
        >> result.partClassPtr >> result.baseMatPtr
        >> result.surfsPtr >> result.materialHandlesPtr;

    // Parse XModelLodInfo
    for (int i = 1; i <= 4; i++) {
        qDebug() << "- Lod Info " << i;

        quint32 intDist;
        *aZoneFileStream >> intDist;

        std::memcpy(&result.lodInfo[i].dist, &intDist, sizeof(result.lodInfo[i].dist));
        *aZoneFileStream >> result.lodInfo[i].numsurfs >> result.lodInfo[i].surfIndex;

        aZoneFileStream->skipRawData(4);

        *aZoneFileStream >> result.lodInfo[i].partBits[0]
            >> result.lodInfo[i].partBits[1]
            >> result.lodInfo[i].partBits[2]
            >> result.lodInfo[i].partBits[3];
    }

    *aZoneFileStream >> result.collSurfsPtr >> result.numCollSurfs >> result.contents >> result.boneInfoPtr;

    quint32 intRadius, intMins[3], intMaxs[3];
    *aZoneFileStream >> intRadius >> intMins[0] >> intMins[1]
        >> intMins[2] >> intMaxs[0] >> intMaxs[1] >> intMaxs[2];

    std::memcpy(&result.radius, &intRadius, sizeof(result.radius));

    std::memcpy(&result.mins[0], &intMins[0], sizeof(result.mins[0]));
    std::memcpy(&result.mins[1], &intMins[1], sizeof(result.mins[1]));
    std::memcpy(&result.mins[2], &intMins[2], sizeof(result.mins[2]));

    std::memcpy(&result.maxs[0], &intMaxs[0], sizeof(result.maxs[0]));
    std::memcpy(&result.maxs[1], &intMaxs[1], sizeof(result.maxs[2]));
    std::memcpy(&result.maxs[2], &intMaxs[2], sizeof(result.maxs[3]));

    *aZoneFileStream >> result.numLods >> result.collLod >> result.streamInfoPtr
        >> result.memUsage >> result.flags >> result.physPresetPtr >> result.physGeomsPtr;

    // Parse model name
    char modelNameChar;
    *aZoneFileStream >> modelNameChar;
    while (modelNameChar == 0) {
        *aZoneFileStream >> modelNameChar;
    }
    while (modelNameChar != 0) {
        result.modelName += modelNameChar;
        *aZoneFileStream >> modelNameChar;
    }
    return result;
}

void ZoneFile::pParseAsset_Material(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

Shader ZoneFile::pParseAsset_Shader(QDataStream *aZoneFileStream) {
    Shader result = Shader();

    quint8 minorVersion, majorVersion;
    *aZoneFileStream >> minorVersion >> majorVersion;

    quint32 magic;
    *aZoneFileStream >> magic;

    // Verify .fxc magic
    if (magic != 65534 && magic != 65535) { return result; }

    SHADER_TYPE type = SHADER_NONE;
    quint16 rawShaderType;
    *aZoneFileStream >> rawShaderType;
    if (rawShaderType == 65535) { // Pixel shader
        type = SHADER_PIXEL;
    } else if (rawShaderType == 65534) { // Vertex shader
        type = SHADER_VERTEX;
    }
    Q_UNUSED(type);

    while (true) {
        quint32 instructionToken;
        *aZoneFileStream >> instructionToken;

        SHADER_OPCODE opCode = (SHADER_OPCODE)(instructionToken & 0xffff);

        int size;
        if (opCode == OPCODE_End) {
            break;
        } else if (opCode == OPCODE_Comment) {
            size = (int)((instructionToken >> 16) & 0x7FFF);
        } else {
            size = (int)((instructionToken >> 24) & 0x0f);
        }
        Q_UNUSED(size);
    }


    return result;
}

bool ZoneFile::pReadUntilString(QDataStream* stream, const QString& targetString) {
    if (!stream || targetString.isEmpty()) {
        return false; // Invalid input
    }

    QByteArray buffer;
    QByteArray targetBytes = targetString.toUtf8(); // Handle multibyte characters
    const int targetLength = targetBytes.size();
    qDebug() << targetBytes << targetLength;

    // Read as unsigned bytes to handle all possible values (0-255)
    unsigned char byte;
    while (!stream->atEnd()) {
        // Read one byte at a time
        *stream >> byte;
        buffer.append(static_cast<char>(byte)); // Append as char for QByteArray

        // Keep buffer size limited to the target length
        if (buffer.size() > targetLength) {
            buffer.remove(0, 1);
        }

        // Check if the buffer matches the target string in raw bytes
        if (buffer == targetBytes) {
            // Backup to the start of the matched string
            stream->device()->seek(stream->device()->pos() - targetLength);
            return true;
        }
    }

    // Target string not found
    return false;
}

bool ZoneFile::pReadUntilHex(QDataStream* stream, const QString& hexString) {
    if (!stream || hexString.isEmpty() || hexString.size() % 2 != 0) {
        return false; // Invalid input
    }

    // Convert hex string to byte array
    QByteArray targetBytes = QByteArray::fromHex(hexString.toUtf8());
    const int targetLength = targetBytes.size();

    QByteArray buffer;
    unsigned char byte;

    while (!stream->atEnd()) {
        // Read one byte at a time
        *stream >> byte;
        buffer.append(static_cast<char>(byte)); // Append as char for QByteArray

        // Keep buffer size limited to the target length
        if (buffer.size() > targetLength) {
            buffer.remove(0, 1);
        }

        // Check if the buffer matches the target byte sequence
        if (buffer == targetBytes) {
            // Backup to the start of the matched sequence
            stream->device()->seek(stream->device()->pos() - targetLength);
            return true;
        }
    }

    // Target sequence not found
    return false;
}

TechSet ZoneFile::pParseAsset_TechSet(QDataStream *aZoneFileStream) {
    TechSet result;

    for (int i = 1; i <= 62; i++) {
        quint32 ptr;
        *aZoneFileStream >> ptr;

        result.pointers << ptr;
    }
    qDebug() << aZoneFileStream->device()->pos();

    // Parse techset name
    char techSetNameChar;
    *aZoneFileStream >> techSetNameChar;
    while (techSetNameChar != 0) {
        result.name += techSetNameChar;
        *aZoneFileStream >> techSetNameChar;
    }
    result.name.replace(",", "");

    return result;
}

Image ZoneFile::pParseAsset_Image(QDataStream *aZoneFileStream) {
    Image result;

    aZoneFileStream->skipRawData(4);
    *aZoneFileStream >> result.unknowna >> result.unknownb
        >> result.unknownc >> result.unknownd
        >> result.unknowne >> result.unknownf
        >> result.unknowng;

    aZoneFileStream->skipRawData(15 * 4);
    *aZoneFileStream >> result.unknownh >> result.unknowni;

    aZoneFileStream->skipRawData(4);
    *aZoneFileStream >> result.unknownj;

    aZoneFileStream->skipRawData(4);

    char materialNameChar;
    *aZoneFileStream >> materialNameChar;
    while (materialNameChar != 0) {
        result.materialName += materialNameChar;
        *aZoneFileStream >> materialNameChar;
    }
    result.materialName.replace(",", "");

    if (result.unknowna) {
        *aZoneFileStream >> result.unknownk;
        *aZoneFileStream >> result.unknownl;
        *aZoneFileStream >> result.unknownm;

        aZoneFileStream->skipRawData(4);

        *aZoneFileStream >> result.unknown1;

        aZoneFileStream->skipRawData(4);

        *aZoneFileStream >> result.unknown2 >> result.unknown3
            >> result.size1 >> result.size2
            >> result.unknown4 >> result.unknown5;

        aZoneFileStream->skipRawData(4);

        char imageNameChar;
        *aZoneFileStream >> imageNameChar;
        while (imageNameChar != 0) {
            result.name += imageNameChar;
            *aZoneFileStream >> imageNameChar;
        }

        *aZoneFileStream >> result.unknown6 >> result.unknown7;

        QByteArray compressionData(8, Qt::Uninitialized);
        aZoneFileStream->readRawData(compressionData.data(), 8);
        if (compressionData.contains("DXT1")) {
            result.compression = COMPRESSION_DXT1;
        } else if (compressionData.contains("DXT3")) {
            result.compression = COMPRESSION_DXT3;
        } else if (compressionData.contains("DXT5")) {
            result.compression = COMPRESSION_DXT5;
        } else {
            result.compression = COMPRESSION_NONE;
        }

        *aZoneFileStream >> result.unknown8 >> result.unknown9;
    }

    return result;
}

void ZoneFile::pParseAsset_LoadedSound(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

void ZoneFile::pParseAsset_ColMapMP(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

void ZoneFile::pParseAsset_GameMapSP(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

void ZoneFile::pParseAsset_GameMapMP(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

void ZoneFile::pParseAsset_LightDef(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

void ZoneFile::pParseAsset_UIMap(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

void ZoneFile::pParseAsset_SNDDriverGlobals(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

void ZoneFile::pParseAsset_AIType(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

void ZoneFile::pParseAsset_FX(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

Animation ZoneFile::pParseAsset_Animation(QDataStream *aZoneFileStream) {
    Animation result;

    aZoneFileStream->skipRawData(4);

    *aZoneFileStream
        >> result.dataByteCount
        >> result.dataShortCount
        >> result.dataIntCount
        >> result.randomDataByteCount
        >> result.randomDataIntCount
        >> result.numframes
        >> result.isLooped
        >> result.isDelta
        >> result.noneRotatedBoneCount
        >> result.twoDRotatedBoneCount
        >> result.normalRotatedBoneCount
        >> result.twoDRotatedBoneCount
        >> result.normalRotatedBoneCount
        >> result.normalTranslatedBoneCount
        >> result.preciseTranslatedBoneCount
        >> result.staticTranslatedBoneCount
        >> result.noneTranslatedBoneCount
        >> result.totalBoneCount
        >> result.otherBoneCount1
        >> result.otherBoneCount2
        >> result.notifyCount
        >> result.assetType
        >> result.pad
        >> result.randomDataShortCount
        >> result.indexCount
        >> result.frameRate
        >> result.frequency
        >> result.boneIDsPtr
        >> result.dataBytePtr
        >> result.dataShortPtr
        >> result.dataIntPtr
        >> result.randomDataShortPtr
        >> result.randomDataBytePtr
        >> result.randomDataIntPtr
        >> result.longIndiciesPtr
        >> result.notificationsPtr
        >> result.deltaPartsPtr;

    // Read in x_anim file name
    QString xAnimName;
    char xAnimNameChar;
    *aZoneFileStream >> xAnimNameChar;
    while (xAnimNameChar != 0) {
        result.name += xAnimNameChar;
        *aZoneFileStream >> xAnimNameChar;
    }

    // Parse x_anim index header
    QVector<quint8> sectionLengths;
    for (int i = 0; i < result.numframes; i++) {
        quint8 sectionlength;
        *aZoneFileStream >> sectionlength;
        sectionLengths.push_back(sectionlength);
        // Skip padding
        aZoneFileStream->skipRawData(1);
    }
    // Skip unknown section
    aZoneFileStream->skipRawData(2 * 8);

    return result;
}

MenuFile ZoneFile::pParseAsset_MenuFile(QDataStream *aZoneFileStream) {
    //MENU_FILE
    MenuFile result;

    aZoneFileStream->skipRawData(4); // Separator

    // Parse menu def count
    *aZoneFileStream >> result.menuCount;

    // Clearly misparsed, never have this much
    if (result.menuCount > 1000) {
        qDebug() << "Failure reported when parsing menu file.";
        return result;
    }
    for (uint i = 0; i < result.menuCount; i++) {
        Menu menu;

        aZoneFileStream->skipRawData(4); // Separator

        // Read in x_anim file name
        char menuFilepathChar;
        *aZoneFileStream >> menuFilepathChar;
        while (menuFilepathChar != 0) {
            menu.filePath += menuFilepathChar;
            *aZoneFileStream >> menuFilepathChar;
        }
        aZoneFileStream->skipRawData(4); // Separator

        *aZoneFileStream >> menu.menuNamePtr;

        float menuRectX, menuRectY, menuRectWidth, menuRectHeight;
        *aZoneFileStream >> menuRectX >> menuRectY >> menuRectWidth >> menuRectHeight;
        menu.rect = QRectF(menuRectX, menuRectY, menuRectWidth, menuRectHeight);

        quint32 hAlignInt, vAlignInt;
        *aZoneFileStream >> hAlignInt >> vAlignInt;
        menu.hAlign = (MENU_H_ALIGNMENT)hAlignInt;
        menu.vAlign = (MENU_V_ALIGNMENT)vAlignInt;

        float rectClientX, rectClientY, rectClientWidth, rectClientHeight;
        *aZoneFileStream >> rectClientX >> rectClientY >> rectClientWidth >> rectClientHeight;
        menu.clientRect = QRectF(rectClientX, rectClientY, rectClientWidth, rectClientHeight);

        quint32 hClientAlignInt, vClientAlignInt, styleInt, borderInt;
        *aZoneFileStream >> hClientAlignInt >> vClientAlignInt >> menu.groupPtr
            >> styleInt >> borderInt >> menu.ownerDraw >> menu.ownerDrawFlags
            >> menu.borderSize >> menu.staticFlags >> menu.dynamicFlags >> menu.nextTime;
        menu.hClientAlign = (MENU_H_ALIGNMENT)hClientAlignInt;
        menu.vClientAlign = (MENU_V_ALIGNMENT)vClientAlignInt;
        menu.style = (MENU_WINDOW_STYLE)styleInt;
        menu.border = (MENU_WINDOW_BORDER)borderInt;

        float foregroundColorR, foregroundColorG, foregroundColorB, foregroundColorA,
            backgroundColorR, backgroundColorG, backgroundColorB, backgroundColorA,
            borderColorR, borderColorG, borderColorB, borderColorA,
            outlineColorR, outlineColorG, outlineColorB, outlineColorA;
        *aZoneFileStream >> foregroundColorR >> foregroundColorG >> foregroundColorB >> foregroundColorA
            >> backgroundColorR >> backgroundColorG >> backgroundColorB >> backgroundColorA
            >> borderColorR >> borderColorG >> borderColorB >> borderColorA
            >> outlineColorR >> outlineColorG >> outlineColorB >> outlineColorA;

        menu.foregroundColor = QColor(foregroundColorR, foregroundColorG, foregroundColorB, foregroundColorA);
        menu.backgroundColor = QColor(backgroundColorR, backgroundColorG, backgroundColorB, backgroundColorA);
        menu.borderColor = QColor(borderColorR, borderColorG, borderColorB, borderColorA);
        menu.outlineColor = QColor(outlineColorR, outlineColorG, outlineColorB, outlineColorA);

        *aZoneFileStream >> menu.materialPtr >> menu.fontPtr >> menu.fullScreen >> menu.itemCount
            >> menu.fontIndex >> menu.cursorItem >> menu.fadeCycle >> menu.fadeClamp
            >> menu.fadeAmount >> menu.fadeInAmount >> menu.blurRadius >> menu.onOpenPtr
            >> menu.onFocusPtr >> menu.onClosePtr >> menu.onESCPtr >> menu.onKeyPtr
            >> menu.visibleExpCount >> menu.expEntryPtr >> menu.allowedBindingPtr
            >> menu.soundNamePtr >> menu.imageTrack;

        float focusColorR, focusColorG, focusColorB, focusColorA,
            disabledColorR, disabledColorG, disabledColorB, disabledColorA;
        *aZoneFileStream >> focusColorR >> focusColorG >> focusColorB >> focusColorA
            >> disabledColorR >> disabledColorG >> disabledColorB >> disabledColorA;
        menu.focusColor = QColor(focusColorR, focusColorG, focusColorB, focusColorA);
        menu.disabledColor = QColor(disabledColorR, disabledColorG, disabledColorB, disabledColorA);

        *aZoneFileStream >> menu.rectXExpCount >> menu.rectXExpPtr >> menu.rectYExpCount >> menu.rectYExpPtr;

        aZoneFileStream->skipRawData(4); // Separator

        char menuDefNameChar;
        int menuDefNameLen = 0;
        *aZoneFileStream >> menuDefNameChar;
        while (menuDefNameChar != 0 && menuDefNameLen < 30) {
            menuDefNameLen++;
            menu.name += menuDefNameChar;
            *aZoneFileStream >> menuDefNameChar;
        }

        char defStringChar;
        int defStringLen = 0;
        *aZoneFileStream >> defStringChar;
        while (defStringChar != 0 && defStringLen < 30) {
            defStringLen++;
            menu.definition += defStringChar;
            *aZoneFileStream >> defStringChar;
        }
        aZoneFileStream->skipRawData(4 * 10);

        *aZoneFileStream >> menu.itemWindowDefNamePtr;

        float itemRectX, itemRectY, itemRectWidth, itemRectHeight;
        *aZoneFileStream >> itemRectX >> itemRectY >> itemRectWidth >> itemRectHeight;
        menu.itemRect = QRectF(itemRectX, itemRectY, itemRectWidth, itemRectHeight);

        *aZoneFileStream >> menu.itemHAlignment >> menu.itemVAlignment >> menu.itemGroupPtr
            >> menu.itemWindowStyle >> menu.itemWindowBorder >> menu.itemOwnerDraw
            >> menu.itemOwnerDrawFlags >> menu.itemBorderSize >> menu.itemStaticFlags
            >> menu.itemDynamicFlags >> menu.itemNextTime;

        float itemForegroundColorR, itemForegroundColorG, itemForegroundColorB, itemForegroundColorA,
            itemBackgroundColorR, itemBackgroundColorG, itemBackgroundColorB, itemBackgroundColorA,
            itemBorderColorR, itemBorderColorG, itemBorderColorB, itemBorderColorA,
            itemOutlineColorR, itemOutlineColorG, itemOutlineColorB, itemOutlineColorA;
        *aZoneFileStream >> itemForegroundColorR >> itemForegroundColorG >> itemForegroundColorB >> itemForegroundColorA
            >> itemBackgroundColorR >> itemBackgroundColorG >> itemBackgroundColorB >> itemBackgroundColorA
            >> itemBorderColorR >> itemBorderColorG >> itemBorderColorB >> itemBorderColorA
            >> itemOutlineColorR >> itemOutlineColorG >> itemOutlineColorB >> itemOutlineColorA;

        menu.itemForegroundColor = QColor(itemForegroundColorR, itemForegroundColorG, itemForegroundColorB, itemForegroundColorA);
        menu.itemBackgroundColor = QColor(itemBackgroundColorR, itemBackgroundColorG, itemBackgroundColorB, itemBackgroundColorA);
        menu.itemBorderColor = QColor(itemBorderColorR, itemBorderColorG, itemBorderColorB, itemBorderColorA);
        menu.itemOutlineColor = QColor(itemOutlineColorR, itemOutlineColorG, itemOutlineColorB, itemOutlineColorA);

        *aZoneFileStream >> menu.itemMaterialPtr;

        float itemTextRectX, itemTextRectY, itemTextRectWidth, itemTextRectHeight;
        *aZoneFileStream >> itemTextRectX >> itemTextRectY >> itemTextRectWidth >> itemTextRectHeight;
        menu.itemTextRect = QRectF(itemTextRectX, itemTextRectY, itemTextRectWidth, itemTextRectHeight);

        quint32 hItemTextAlignInt, vItemTextAlignInt, itemType, fontTypeInt, textStyleInt;
        *aZoneFileStream >> hItemTextAlignInt >> vItemTextAlignInt >> itemType >> menu.dataType
            >> menu.alignment >> fontTypeInt >> menu.textAlignMode >> menu.textalignx >> menu.textaligny
            >> menu.textscale >> textStyleInt >> menu.gameMsgWindowIndex >> menu.gameMsgWindowMode
            >> menu.testPtr >> menu.textSavegameInfo >> menu.parentPtr;
        menu.itemText_hAlign = (MENU_H_ALIGNMENT)hItemTextAlignInt;
        menu.itemText_vAlign = (MENU_V_ALIGNMENT)vItemTextAlignInt;
        menu.itemType = (MENU_ITEM_TYPE)itemType;
        menu.fontEnum = (MENU_FONT_TYPE)fontTypeInt;
        menu.textStyle = (MENU_ITEM_TEXTSTYLE)textStyleInt;

        *aZoneFileStream >> menu.mouseEnterText >> menu.mouseExitText >> menu.mouseEnter >> menu.mouseExit
            >> menu.action >> menu.onAccept >> menu.onFocus >> menu.leaveFocus >> menu.dvar >> menu.dvarTest
            >> menu.keyHandlerPtr >> menu.enableDvarPtr >> menu.dvarFlags >> menu.focusSoundPtr
            >> menu.special >> menu.cursorPos;

        // itemDefData_t typeData;

        // listBoxDef_s *listBox;

        *aZoneFileStream >> menu.startPos >> menu.endPos >> menu.drawPadding;

        *aZoneFileStream >> menu.elementWidth >> menu.elementHeight;

        *aZoneFileStream >> menu.elementStyle >> menu.numColumns;

        //columnInfo_s columnInfo[16];

        *aZoneFileStream >> menu.doubleClickPtr;


        *aZoneFileStream >> menu.notselectable >> menu.noScrollBars >> menu.usePaging;

        float itemSelectBorderColorR, itemSelectBorderColorG, itemSelectBorderColorB, itemSelectBorderColorA,
            itemDisableColorR, itemDisableColorG, itemDisableColorB, itemDisableColorA,
            itemFocusColorR, itemFocusColorG, itemFocusColorB, itemFocusColorA;
        *aZoneFileStream >> itemSelectBorderColorR >> itemSelectBorderColorG >> itemSelectBorderColorB >> itemSelectBorderColorA
            >> itemDisableColorR >> itemDisableColorG >> itemDisableColorB >> itemDisableColorA
            >> itemFocusColorR >> itemFocusColorG >> itemFocusColorB >> itemFocusColorA;
        menu.itemSelectBorderColor = QColor(itemSelectBorderColorR, itemSelectBorderColorG, itemSelectBorderColorB, itemSelectBorderColorA);
        menu.itemDisableColor = QColor(itemDisableColorR, itemDisableColorG, itemDisableColorB, itemDisableColorA);
        menu.itemFocusColor = QColor(itemFocusColorR, itemFocusColorG, itemFocusColorB, itemFocusColorA);

        *aZoneFileStream >> menu.selectIconPtr >> menu.backgroundItemListboxPtr >> menu.highlightTexturePtr;

        // editFieldDef_s *editField;

        *aZoneFileStream >> menu.minVal >> menu.maxVal >> menu.defVal >> menu.range >> menu.maxChars
            >> menu.maxCharsGotoNext >> menu.maxPaintChars >> menu.paintOffset;

        // multiDef_s *multi;

        for (int i = 0; i < 32; i++) {
            quint32 dvarList;
            *aZoneFileStream >> dvarList;
            menu.dvarListPtrs.push_back(dvarList);
        }

        for (int i = 0; i < 32; i++) {
            quint32 dvarStr;
            *aZoneFileStream >> dvarStr;
            menu.dvarStrPtrs.push_back(dvarStr);
        }

        for (int i = 0; i < 32; i++) {
            float dvarValue;
            *aZoneFileStream >> dvarValue;
            menu.dvarValues.push_back(dvarValue);
        }

        *aZoneFileStream >> menu.count >> menu.strDef >> menu.enumDvarNamePtr;
        aZoneFileStream->skipRawData(4);
            //>> menu.dataPtr
        *aZoneFileStream >> menu.itemImageTrack;

        qDebug() << aZoneFileStream->device()->pos();

        //statement_s visibleExp;
        //statement_s textExp;
        //statement_s materialExp;
        //statement_s rectXExp;
        //statement_s rectYExp;
        //statement_s rectWExp;
        //statement_s rectHExp;
        //statement_s foreColorAExp;
        result.menuDefs << menu;
    }
    return result;
}

void ZoneFile::pParseAsset_Weapon(QDataStream *aZoneFileStream) {
    //WEAPON_FILE
    Q_UNUSED(aZoneFileStream);
}

void ZoneFile::pParseAsset_D3DBSP(QDataStream *aZoneFileStream) {
    //D3DBSP_DUMP
    Q_UNUSED(aZoneFileStream);
}

StringTable ZoneFile::pParseAsset_StringTable(QDataStream *aZoneFileStream) {
    StringTable result;

    aZoneFileStream->skipRawData(4);

    *aZoneFileStream
        >> result.columnCount
        >> result.rowCount;

    // Todo fix this
    result.columnCount = 0;
    result.rowCount = 0;

    aZoneFileStream->skipRawData(4);

    QString stringTableName;
    char stringTableNameChar;
    *aZoneFileStream >> stringTableNameChar;
    while (stringTableNameChar != 0) {
        result.name += stringTableNameChar;
        *aZoneFileStream >> stringTableNameChar;
    }

    QVector<QString> tablePointers = QVector<QString>();
    for (quint32 i = 0; i < result.rowCount; i++) {
        QByteArray pointerData(4, Qt::Uninitialized);
        aZoneFileStream->readRawData(pointerData.data(), 4);
        tablePointers.push_back(pointerData.toHex());

        aZoneFileStream->skipRawData(4);
    }

    for (const QString &pointerAddr : tablePointers) {
        QString leadingContent = "";
        if (pointerAddr == "FFFFFFFF") {
            char leadingContentChar;
            *aZoneFileStream >> leadingContentChar;
            while (leadingContentChar != 0) {
                leadingContent += leadingContentChar;
                *aZoneFileStream >> leadingContentChar;
            }
        } else {
            leadingContent = pointerAddr;
        }

        QString content;
        char contentChar;
        *aZoneFileStream >> contentChar;
        while (contentChar != 0) {
            content += contentChar;
            *aZoneFileStream >> contentChar;
        }
        QPair<QString, QString> tableEntry = QPair<QString, QString>();
        tableEntry.first = leadingContent;
        tableEntry.second = content;
        //if (!mStrTableMap.contains(stringTableName)) {
        //    mStrTableMap[stringTableName] = QVector<QPair<QString, QString>>();
        //}
        //mStrTableMap[stringTableName].push_back(tableEntry);
    }
    return result;
}
