#ifndef ZFPARSER_H
#define ZFPARSER_H

#include "qtypes.h"
#include "utils.h"
#include "structs.h"

#include <QString>
#include <QDebug>
#include <QDataStream>

class ZoneFileParser {
public:
    static ZoneFile ParseZoneHeader(QDataStream *aZoneFileStream) {
        ZoneFile result;

        result.size = ParseZoneSize(aZoneFileStream);
        ParseZoneUnknownsA(aZoneFileStream);

        result.tagCount = ParseZoneTagCount(aZoneFileStream);
        ParseZoneUnknownsB(aZoneFileStream);

        result.recordCount = ParseZoneRecordCount(aZoneFileStream);

        if (result.tagCount) {
            ParseZoneUnknownsC(aZoneFileStream);
            result.tags = ParseZoneTags(aZoneFileStream, result.tagCount);
        } else {
            aZoneFileStream->skipRawData(4);
        }

        return result;
    }

    static quint32 ParseZoneSize(QDataStream *aZoneFileStream) {
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
    static void ParseZoneUnknownsA(QDataStream *aZoneFileStream) {
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
    static quint32 ParseZoneTagCount(QDataStream *aZoneFileStream) {
        quint32 tagCount;
        *aZoneFileStream >> tagCount;
        return tagCount;
    }

    /*
    ParseZoneRecordCount()

    Parses the number of records in the zone index
*/
    static quint32 ParseZoneRecordCount(QDataStream *aZoneFileStream) {
        quint32 recordCount;
        *aZoneFileStream >> recordCount;
        return recordCount;
    }

    /*
    ParseZoneUnknownsB()

    Parses the 2nd section of unknowns as hex vals and uint32s
*/
    static void ParseZoneUnknownsB(QDataStream *aZoneFileStream) {
        // Byte 44-47: Unknown/empty?
        QByteArray unknown9(4, Qt::Uninitialized);
        aZoneFileStream->readRawData(unknown9.data(), 4);
    }

    /*
    ParseZoneUnknownsC()

    Parses the 3rd section of unknowns as hex vals and uint32s
*/
    static void ParseZoneUnknownsC(QDataStream *aZoneFileStream) {
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
    static QStringList ParseZoneTags(QDataStream *aZoneFileStream, quint32 tagCount) {
        QStringList tags;

        // Byte 48-51: Repeated separators? ÿÿÿÿ x i
        aZoneFileStream->skipRawData(4 * (tagCount - 1));

        // Parse tags/strings before index
        QString zoneTag;
        char zoneTagChar;
        for (quint32 i = 0; i < tagCount - 1; i++) {
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
    static QStringList ParseZoneIndex(QDataStream *aZoneFileStream, quint32 recordCount) {
        QStringList result;

        // Don't parse if no records
        if (!recordCount) { return result; }

        // Track past assets and counts
        QString lastAssetType = "";

        // Parse index & map found asset types
        for (quint32 i = 0; i < recordCount; i++) {
            // Skip record start
            QByteArray rawAssetType(4, Qt::Uninitialized);
            aZoneFileStream->readRawData(rawAssetType.data(), 4);
            result << rawAssetType.toHex();

            // Skip separator
            aZoneFileStream->skipRawData(4);
        }
        return result;
    }

    static AssetMap ParseAssets(QDataStream *aZoneFileStream, QStringList assetOrder) {
        AssetMap result;

        for (int i = 0; i < assetOrder.size(); i++) {
            const QString typeHex = assetOrder[i];
            const QString typeStr = Utils::AssetTypeToString(typeHex);

            if (typeStr == "LOCAL STRING") { // localized string asset
                result.localStrings << ParseAsset_LocalString(aZoneFileStream);
            } else if (typeStr == "RAW FILE") { // gsc
                result.rawFiles << ParseAsset_RawFile(aZoneFileStream);
            } else if (typeStr == "PHYS PRESET") { // physpreset
                ParseAsset_PhysPreset(aZoneFileStream);
            } else if (typeStr == "MODEL") { // xmodel
                ParseAsset_Model(aZoneFileStream);
            } else if (typeStr == "MATERIAL") { // material
                ParseAsset_Material(aZoneFileStream);
            } else if (typeStr == "SHADER") { // pixelshader
                ParseAsset_PixelShader(aZoneFileStream);
            } else if (typeStr == "TECH SET") { // techset include
                result.techSets << ParseAsset_TechSet(aZoneFileStream);
            } else if (typeStr == "IMAGE") { // image
                ParseAsset_Image(aZoneFileStream);
            } else if (typeStr == "SOUND") { // loaded_sound
                ParseAsset_LoadedSound(aZoneFileStream);
            } else if (typeStr == "COLLISION MAP") { // col_map_mp
                ParseAsset_ColMapMP(aZoneFileStream);
            } else if (typeStr == "MP MAP") { // game_map_sp
                ParseAsset_GameMapSP(aZoneFileStream);
            } else if (typeStr == "SP MAP") { // game_map_mp
                ParseAsset_GameMapMP(aZoneFileStream);
            } else if (typeStr == "LIGHT DEF") { // lightdef
                ParseAsset_LightDef(aZoneFileStream);
            } else if (typeStr == "UI MAP") { // ui_map
                ParseAsset_UIMap(aZoneFileStream);
            } else if (typeStr == "SND DRIVER GLOBALS") { // snddriverglobals
                ParseAsset_SNDDriverGlobals(aZoneFileStream);
            } else if (typeStr == "AI TYPE") { // aitype
                ParseAsset_AIType(aZoneFileStream);
            } else if (typeStr == "EFFECT") { // aitype
                ParseAsset_FX(aZoneFileStream);
            } else if (typeStr == "ANIMATION") { // aitype
                result.animations << ParseAsset_Animation(aZoneFileStream);
            } else if (typeStr == "STRING TABLE") { // string_table
                result.stringTables << ParseAsset_StringTable(aZoneFileStream);
            } else if (typeStr == "MENU") { // string_table
                ParseAsset_MenuFile(aZoneFileStream);
            } else if (typeStr == "WEAPON") { // string_table
                ParseAsset_Weapon(aZoneFileStream);
            } else if (typeStr == "D3DBSP DUMP") { // string_table
                ParseAsset_D3DBSP(aZoneFileStream);
            } else if (typeStr != "UNKNOWN") {
                qDebug() << "Found bad asset type!" << typeStr;
            }
        }
        return result;
    }

    static LocalString ParseAsset_LocalString(QDataStream *aZoneFileStream) {
        LocalString result;

        // Skip separator
        aZoneFileStream->skipRawData(8);

        // Parse local string asset contents
        QString localStr;
        char localStrChar;
        *aZoneFileStream >> localStrChar;
        while (localStrChar != 0) {
            result.string += localStrChar;
            *aZoneFileStream >> localStrChar;
        }

        // Parse rawfile name
        QString aliasName;
        char aliasNameChar;
        *aZoneFileStream >> aliasNameChar;
        while (aliasNameChar != 0) {
            result.alias += aliasNameChar;
            *aZoneFileStream >> aliasNameChar;
        }
        return result;
    }

    static RawFile ParseAsset_RawFile(QDataStream *aZoneFileStream) {
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

    static void ParseAsset_PhysPreset(QDataStream *aZoneFileStream) {
        Q_UNUSED(aZoneFileStream);
    }

    static void ParseAsset_Model(QDataStream *aZoneFileStream) {
        Q_UNUSED(aZoneFileStream);
    }

    static void ParseAsset_Material(QDataStream *aZoneFileStream) {
        Q_UNUSED(aZoneFileStream);
    }

    static void ParseAsset_PixelShader(QDataStream *aZoneFileStream) {
        Q_UNUSED(aZoneFileStream);
    }

    static TechSet ParseAsset_TechSet(QDataStream *aZoneFileStream) {
        TechSet result;

        aZoneFileStream->skipRawData(4);
        // Parse techset name
        char techSetNameChar;
        *aZoneFileStream >> techSetNameChar;
        while (techSetNameChar == 0) {
            *aZoneFileStream >> techSetNameChar;
        }
        while (techSetNameChar != 0) {
            result.name += techSetNameChar;
            *aZoneFileStream >> techSetNameChar;
        }
        result.name.replace(",", "");

        return result;
    }

    static void ParseAsset_Image(QDataStream *aZoneFileStream) {
        Q_UNUSED(aZoneFileStream);
    }

    static void ParseAsset_LoadedSound(QDataStream *aZoneFileStream) {
        Q_UNUSED(aZoneFileStream);
    }

    static void ParseAsset_ColMapMP(QDataStream *aZoneFileStream) {
        Q_UNUSED(aZoneFileStream);
    }

    static void ParseAsset_GameMapSP(QDataStream *aZoneFileStream) {
        Q_UNUSED(aZoneFileStream);
    }

    static void ParseAsset_GameMapMP(QDataStream *aZoneFileStream) {
        Q_UNUSED(aZoneFileStream);
    }

    static void ParseAsset_LightDef(QDataStream *aZoneFileStream) {
        Q_UNUSED(aZoneFileStream);
    }

    static void ParseAsset_UIMap(QDataStream *aZoneFileStream) {
        Q_UNUSED(aZoneFileStream);
    }

    static void ParseAsset_SNDDriverGlobals(QDataStream *aZoneFileStream) {
        Q_UNUSED(aZoneFileStream);
    }

    static void ParseAsset_AIType(QDataStream *aZoneFileStream) {
        Q_UNUSED(aZoneFileStream);
    }

    static void ParseAsset_FX(QDataStream *aZoneFileStream) {
        Q_UNUSED(aZoneFileStream);
    }

    static Animation ParseAsset_Animation(QDataStream *aZoneFileStream) {
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
            >> result.twoDStaticRotatedBoneCount
            >> result.normalStaticRotatedBoneCount
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

    static void ParseAsset_MenuFile(QDataStream *aZoneFileStream) {
        //MENU_FILE
        Q_UNUSED(aZoneFileStream);
    }

    static void ParseAsset_Weapon(QDataStream *aZoneFileStream) {
        //WEAPON_FILE
        Q_UNUSED(aZoneFileStream);
    }

    static void ParseAsset_D3DBSP(QDataStream *aZoneFileStream) {
        //D3DBSP_DUMP
        Q_UNUSED(aZoneFileStream);
    }

    static StringTable ParseAsset_StringTable(QDataStream *aZoneFileStream) {
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
};

#endif // ZFPARSER_H
