#include "zonefile_cod8_360.h"

#include <QDataStream>
#include <QFile>
#include <QDebug>

ZoneFile_COD8_360::ZoneFile_COD8_360()
{

}

ZoneFile_COD8_360::~ZoneFile_COD8_360()
{

}

bool ZoneFile_COD8_360::Load(const QByteArray aFileData) {
    // Open zone file as little endian stream
    QDataStream zoneFileStream(aFileData);
    zoneFileStream.setByteOrder(QDataStream::BigEndian);

    // Parse data from zone file header
    pParseZoneHeader(&zoneFileStream);
    zoneFileStream.device()->seek(zoneFileStream.device()->pos() - 1);
    SetRecords(pParseZoneIndex(&zoneFileStream, GetRecordCount()));
    SetAssetMap(pParseAssets(&zoneFileStream, GetRecords()));

    return true;
}

void ZoneFile_COD8_360::pParseZoneHeader(QDataStream *aZoneFileStream) {
    quint32 size = pParseZoneSize(aZoneFileStream);
    SetSize(size);

    pParseZoneUnknownsA(aZoneFileStream);

    quint32 tagCount = pParseZoneTagCount(aZoneFileStream);
    SetTagCount(tagCount);

    pParseZoneUnknownsB(aZoneFileStream);

    quint32 recordCount = pParseZoneRecordCount(aZoneFileStream);
    SetRecordCount(recordCount);

    if (tagCount) {
        pParseZoneUnknownsC(aZoneFileStream);
        SetTags(pParseZoneTags(aZoneFileStream, tagCount));
    } else {
        aZoneFileStream->skipRawData(4);
    }
}

quint32 ZoneFile_COD8_360::pParseZoneSize(QDataStream *aZoneFileStream) {
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
void ZoneFile_COD8_360::pParseZoneUnknownsA(QDataStream *aZoneFileStream) {
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
quint32 ZoneFile_COD8_360::pParseZoneTagCount(QDataStream *aZoneFileStream) {
    quint32 tagCount;
    *aZoneFileStream >> tagCount;
    return tagCount;
}

/*
    ParseZoneRecordCount()

    Parses the number of records in the zone index
*/
quint32 ZoneFile_COD8_360::pParseZoneRecordCount(QDataStream *aZoneFileStream) {
    quint32 recordCount;
    *aZoneFileStream >> recordCount;
    return recordCount;
}

/*
    ParseZoneUnknownsB()

    Parses the 2nd section of unknowns as hex vals and uint32s
*/
void ZoneFile_COD8_360::pParseZoneUnknownsB(QDataStream *aZoneFileStream) {
    // Byte 44-47: Unknown/empty?
    QByteArray unknown9(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(unknown9.data(), 4);
}

/*
    pParseZoneUnknownsC()

    Parses the 3rd section of unknowns as hex vals and uint32s
*/
void ZoneFile_COD8_360::pParseZoneUnknownsC(QDataStream *aZoneFileStream) {
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
QStringList ZoneFile_COD8_360::pParseZoneTags(QDataStream *aZoneFileStream, quint32 tagCount) {
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
    }
    return tags;
}

/*
    ParseZoneIndex()

    Parse the binary zone index data and populate table
*/
QStringList ZoneFile_COD8_360::pParseZoneIndex(QDataStream *aZoneFileStream, quint32 recordCount) {
    QStringList result;

    // Don't parse if no records
    if (!recordCount) { return result; }

    if (aZoneFileStream->device()->peek(4).toHex().contains("ffff")) {
        aZoneFileStream->device()->seek(aZoneFileStream->device()->pos() - 2);
    }

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

AssetMap ZoneFile_COD8_360::pParseAssets(QDataStream *aZoneFileStream, QStringList assetOrder) {
    AssetMap result;

    aZoneFileStream->device()->seek(aZoneFileStream->device()->pos() - 8);

    for (int i = 0; i < assetOrder.size(); i++) {
        const QString typeHex = assetOrder[i];
        const AssetType typeStr = AssetStrToEnum(typeHex);

        if (typeStr == ASSET_LOCAL_STRING) { // localized string asset
            result.localStrings << pParseAsset_LocalString(aZoneFileStream);
        } else if (typeStr == ASSET_RAW_FILE) { // gsc
            auto rawFile = pParseAsset_RawFile(aZoneFileStream);
            if (rawFile.length) {
                result.rawFiles << rawFile;
            }
        } else if (typeStr == ASSET_PHYS_PRESET) { // physpreset
            pParseAsset_PhysPreset(aZoneFileStream);
        } else if (typeStr == ASSET_MODEL) { // xmodel
            result.models << pParseAsset_Model(aZoneFileStream);
        } else if (typeStr == ASSET_MATERIAL) { // material
            pParseAsset_Material(aZoneFileStream);
        } else if (typeStr == ASSET_SHADER) { // pixelshader
            pParseAsset_Shader(aZoneFileStream);
        } else if (typeStr == ASSET_TECH_SET) { // techset include
            result.techSets << pParseAsset_TechSet(aZoneFileStream);
        } else if (typeStr == ASSET_IMAGE) { // image
            result.images << pParseAsset_Image(aZoneFileStream);
        } else if (typeStr == ASSET_SOUND) { // loaded_sound
            result.sounds << pParseAsset_Sound(aZoneFileStream);
        } else if (typeStr == ASSET_COLLISION_MAP) { // col_map_mp
            pParseAsset_ColMapMP(aZoneFileStream);
        } else if (typeStr == ASSET_MP_MAP) { // game_map_sp
            pParseAsset_GameMapSP(aZoneFileStream);
        } else if (typeStr == ASSET_SP_MAP) { // game_map_mp
            pParseAsset_GameMapMP(aZoneFileStream);
        } else if (typeStr == ASSET_LIGHT_DEF) { // lightdef
            pParseAsset_LightDef(aZoneFileStream);
        } else if (typeStr == ASSET_UI_MAP) { // ui_map
            pParseAsset_UIMap(aZoneFileStream);
        } else if (typeStr == ASSET_SND_DRIVER_GLOBALS) { // snddriverglobals
            pParseAsset_SNDDriverGlobals(aZoneFileStream);
        } else if (typeStr == ASSET_AI_TYPE) { // aitype
            pParseAsset_AIType(aZoneFileStream);
        } else if (typeStr == ASSET_EFFECT) { // aitype
            pParseAsset_FX(aZoneFileStream);
        } else if (typeStr == ASSET_ANIMATION) { // aitype
            result.animations << pParseAsset_Animation(aZoneFileStream);
        } else if (typeStr == ASSET_STRING_TABLE) { // string_table
            result.stringTables << pParseAsset_StringTable(aZoneFileStream);
        } else if (typeStr == ASSET_MENU) { // string_table
            result.menuFiles << pParseAsset_MenuFile(aZoneFileStream);
        } else if (typeStr == ASSET_WEAPON) { // string_table
            pParseAsset_Weapon(aZoneFileStream);
        } else if (typeStr == ASSET_D3DBSP) { // string_table
            pParseAsset_D3DBSP(aZoneFileStream);
        }
    }
    return result;
}

LocalString ZoneFile_COD8_360::pParseAsset_LocalString(QDataStream *aZoneFileStream) {
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

RawFile ZoneFile_COD8_360::pParseAsset_RawFile(QDataStream *aZoneFileStream) {
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

void ZoneFile_COD8_360::pParseAsset_PhysPreset(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

Model ZoneFile_COD8_360::pParseAsset_Model(QDataStream *aZoneFileStream) {
    Model result;

    *aZoneFileStream >> result.namePtr >> result.tagCount >> result.rootTagCount
            >> result.surfCount >> result.unknownCount >> result.boneNamePtr
            >> result.parentListPtr >> result.quatsPtr >> result.transPtr
            >> result.partClassPtr >> result.baseMatPtr
            >> result.surfsPtr >> result.materialHandlesPtr;

    // Parse XModelLodInfo
    for (int i = 1; i <= 4; i++) {
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

Material ZoneFile_COD8_360::pParseAsset_Material(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);

    return Material();
}

Shader ZoneFile_COD8_360::pParseAsset_Shader(QDataStream *aZoneFileStream) {
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

TechSet ZoneFile_COD8_360::pParseAsset_TechSet(QDataStream *aZoneFileStream) {
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

Image ZoneFile_COD8_360::pParseAsset_Image(QDataStream *aZoneFileStream) {
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

SoundAsset ZoneFile_COD8_360::pParseAsset_Sound(QDataStream *aZoneFileStream) {
    SoundAsset result;

    qDebug() << aZoneFileStream->device()->pos();

    QByteArray rootNamePtr(4, Qt::Uninitialized);
    aZoneFileStream->readRawData(rootNamePtr.data(), 4);

    aZoneFileStream->skipRawData(4);

    *aZoneFileStream >> result.count;

    if (rootNamePtr.toHex() == "ffffffff") {
        // Read in sound file name
        char soundNameChar;
        *aZoneFileStream >> soundNameChar;
        while (soundNameChar != 0) {
            result.name += soundNameChar;
            *aZoneFileStream >> soundNameChar;
        }
    }

    int tagCount = 0;
    int resultCount = 0;
    for (quint32 i = 0; i < result.count; i++) {
        aZoneFileStream->skipRawData(12);

        QByteArray tagPtr(4, Qt::Uninitialized);
        aZoneFileStream->readRawData(tagPtr.data(), 4);

        if (tagPtr.toHex() == "ffffffff") {
            tagCount++;
        }
        aZoneFileStream->skipRawData(4);

        QByteArray pathPtr(4, Qt::Uninitialized);
        aZoneFileStream->readRawData(pathPtr.data(), 4);

        if (pathPtr.toHex() == "ffffffff") {
            resultCount++;
        }

        aZoneFileStream->skipRawData(160);
    }

    for (int i = 0; i < tagCount; i++) {
        // Read in tag?
        QString tag;
        char tagChar;
        *aZoneFileStream >> tagChar;
        while (tagChar != 0) {
            tag += tagChar;
            *aZoneFileStream >> tagChar;
        }
    }

    for (int i = 0; i < resultCount; i++) {
        Sound sound;

        if (aZoneFileStream->device()->peek(12).toHex().contains("ffffffff00000000")) {
            aZoneFileStream->skipRawData(12);
        }

        aZoneFileStream->skipRawData(8);

        QByteArray aliasPtr(4, Qt::Uninitialized);
        aZoneFileStream->readRawData(aliasPtr.data(), 4);

        QByteArray namePtr(4, Qt::Uninitialized);
        aZoneFileStream->readRawData(namePtr.data(), 4);

        *aZoneFileStream >> sound.dataLength;

        if (aliasPtr.toHex() == "ffffffff") {
            // Read in sound alias name
            char soundAliasChar;
            *aZoneFileStream >> soundAliasChar;
            while (soundAliasChar != 0) {
                sound.alias += soundAliasChar;
                *aZoneFileStream >> soundAliasChar;
            }
        }

        if (aZoneFileStream->device()->peek(4) == "RIFF") {
            sound.path = sound.alias;
            sound.alias = "";
        } else if (namePtr.toHex() == "ffffffff") {
            // Read in sound file path
            char soundPathChar;
            *aZoneFileStream >> soundPathChar;
            while (soundPathChar != 0) {
                sound.path += soundPathChar;
                *aZoneFileStream >> soundPathChar;
            }
            sound.path.replace(",", "");
        }

        if (sound.dataLength) {
            QByteArray data(sound.dataLength, Qt::Uninitialized);
            aZoneFileStream->readRawData(data.data(), sound.dataLength);
            sound.data = data;
        }
        result.sounds.append(sound);
    }

    return result;
}

void ZoneFile_COD8_360::pParseAsset_ColMapMP(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

void ZoneFile_COD8_360::pParseAsset_GameMapSP(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

void ZoneFile_COD8_360::pParseAsset_GameMapMP(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

void ZoneFile_COD8_360::pParseAsset_LightDef(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

void ZoneFile_COD8_360::pParseAsset_UIMap(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

void ZoneFile_COD8_360::pParseAsset_SNDDriverGlobals(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

void ZoneFile_COD8_360::pParseAsset_AIType(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

void ZoneFile_COD8_360::pParseAsset_FX(QDataStream *aZoneFileStream) {
    Q_UNUSED(aZoneFileStream);
}

Animation ZoneFile_COD8_360::pParseAsset_Animation(QDataStream *aZoneFileStream) {
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

MenuFile ZoneFile_COD8_360::pParseAsset_MenuFile(QDataStream *aZoneFileStream) {
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

void ZoneFile_COD8_360::pParseAsset_Weapon(QDataStream *aZoneFileStream) {
    //WEAPON_FILE
    Q_UNUSED(aZoneFileStream);
}

void ZoneFile_COD8_360::pParseAsset_D3DBSP(QDataStream *aZoneFileStream) {
    //D3DBSP_DUMP
    Q_UNUSED(aZoneFileStream);
}

StringTable ZoneFile_COD8_360::pParseAsset_StringTable(QDataStream *aZoneFileStream) {
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

    for (quint32 i = 0; i < result.rowCount; i++) {
        QByteArray pointerData(4, Qt::Uninitialized);
        aZoneFileStream->readRawData(pointerData.data(), 4);
        result.tablePointers.push_back(pointerData.toHex());

        aZoneFileStream->skipRawData(4);
    }

    for (const QString &pointerAddr : result.tablePointers) {
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
        result.content[leadingContent] = content;
    }
    return result;
}

AssetType ZoneFile_COD8_360::AssetStrToEnum(const QString aAssetType) {
    const QString cleanedType = aAssetType.toUpper();
    if (cleanedType == "17000000") {        // localized string       PARTIALLY VERIFIED
        return ASSET_LOCAL_STRING;
    } else if (cleanedType == "20000000") { // raw_file               PARTIALLY VERIFIED
        return ASSET_RAW_FILE;
    } else if (cleanedType == "1A000000") { // fx                     PARTIALLY VERIFIED
        return ASSET_EFFECT;
    } else if (cleanedType == "09000000") { // loaded_sound           PARTIALLY VERIFIED
        return ASSET_SOUND;
    } else if (cleanedType == "04000000") { // x_anim                 PARTIALLY VERIFIED
        return ASSET_ANIMATION;
    } else if (cleanedType == "0C000000") { // collision_map          PARTIALLY VERIFIED
        return ASSET_COLLISION_MAP;
    } else if (cleanedType == "21000000") { // string_table           PARTIALLY VERIFIED
        return ASSET_STRING_TABLE;
    } else if (cleanedType == "15000000") { // menu_file              PARTIALLY VERIFIED
        return ASSET_MENU;
    } else if (cleanedType == "07000000") { // tech set               PARTIALLY VERIFIED
        return ASSET_TECH_SET;
    } else if (cleanedType == "18000000") { // weapon                 PARTIALLY VERIFIED
        return ASSET_WEAPON;
    } else if (cleanedType == "11000000") { // gfx map                PARTIALLY VERIFIED
        return ASSET_GFX_MAP;
    } else if (cleanedType == "12000000") { // light_def              PARTIALLY VERIFIED
        return ASSET_LIGHT_DEF;
    } else if (cleanedType == "14000000") { // font                   PARTIALLY VERIFIED
        return ASSET_FONT;
    } else if (cleanedType == "05000000") { // xmodel                 PARTIALLY VERIFIED
        return ASSET_MODEL;
    } else if (cleanedType == "0D000000") { // d3dbsp                 PARTIALLY VERIFIED
        return ASSET_D3DBSP;
    } else if (cleanedType == "06000000") { // image                  PARTIALLY VERIFIED
        return ASSET_IMAGE;
    } else if (cleanedType == "0E000000") { // game map sp            PARTIALLY VERIFIED
        return ASSET_GAME_MAP_SP;
    } else if (cleanedType == "0B000000") { // col map sp             PARTIALLY VERIFIED
        return ASSET_COL_MAP_SP;
    }
    return ASSET_NONE;
}

QByteArray ZoneFile_COD8_360::GetBinaryData() {
    QByteArray result;

    return result;
}
