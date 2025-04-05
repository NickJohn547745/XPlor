#include "zonefile.h"
#include "utils.h"
#include "logmanager.h"

#include <QFile>
#include <QDataStream>
#include <QDebug>

ZoneFile::ZoneFile() :
    mStem(),
    mSize(),
    mTagCount(),
    mTags(),
    mRecordCount(),
    mRecords(),
    mAssetMap() {

}

ZoneFile::~ZoneFile() {

}

ZoneFile::ZoneFile(const ZoneFile &aZoneFile) {
    mStem = aZoneFile.mStem;
    mSize = aZoneFile.mSize;
    mTagCount = aZoneFile.mTagCount;
    mTags = aZoneFile.mTags;
    mRecordCount = aZoneFile.mRecordCount;
    mRecords = aZoneFile.mRecords;
    mAssetMap = aZoneFile.mAssetMap;
}

ZoneFile &ZoneFile::operator=(const ZoneFile &other) {
    if (this != &other) {
        mStem = other.mStem;
        mSize = other.mSize;
        mTagCount = other.mTagCount;
        mTags = other.mTags;
        mRecordCount = other.mRecordCount;
        mRecords = other.mRecords;
        mAssetMap = other.mAssetMap;
    }
    return *this;
}

QIcon ZoneFile::AssetStrToIcon(const QString aAssetStr) {
    const QString cleanedType = aAssetStr.toUpper();
    if (cleanedType == "LOCAL STRING") {        // localized string       PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_StringFile.png");
    } else if (cleanedType == "RAW FILE") { // raw_file               PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_RawFile.png");
    } else if (cleanedType == "GSC FILE") { // raw_file               PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_GSCFile.png");
    } else if (cleanedType == "EFFECT") { // fx                     PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_Effect.png");
    } else if (cleanedType == "SOUND") { // loaded_sound           PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_Sound.png");
    } else if (cleanedType == "ANIMATION") { // x_anim                 PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_Animation.png");
    } else if (cleanedType == "COLLISION MAP") { // collision_map          PARTIALLY VERIFIED
        //return "COLLISION MAP";
    } else if (cleanedType == "STRING TABLE") { // string_table           PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_StringTable.png");
    } else if (cleanedType == "MENU") { // menu_file              PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_MenuFile.png");
    } else if (cleanedType == "TECH SET") { // tech set               PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_TechSetFile.png");
    } else if (cleanedType == "WEAPON") { // weapon                 PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_Weapon.png");
    } else if (cleanedType == "GFX MAP") { // gfx map                PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_FXMap.png");
    } else if (cleanedType == "LIGHT DEF") { // light_def              PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_LightDef.png");
    } else if (cleanedType == "FONT") { // font                   PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_Font.png");
    } else if (cleanedType == "MODEL") { // xmodel                 PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_Model.png");
    } else if (cleanedType == "D3DBSP") { // d3dbsp                 PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_BSP.png");
    } else if (cleanedType == "IMAGE") { // image                  PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_Image.png");
    } else if (cleanedType == "GAME MAP SP") { // game map sp            PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_GameMapSp.png");
    } else if (cleanedType == "COL MAP SP") { // col map sp             PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_ColMapSp.png");
    } else if (cleanedType == "PHYS PRESET") { // col map sp             PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_PhysPreset.png");
    } else if (cleanedType == "DESTRUCTIBLE") { // col map sp             PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_Destructible.png");
    }
    return QIcon();
}

bool ZoneFile::SaveZoneFile(const QString aZoneFilePath) {
    QFile zoneFile(aZoneFilePath);
    if (!zoneFile.open(QIODevice::WriteOnly)) {
        LogManager::instance().addEntry("Failed to write zone file! " + zoneFile.errorString());
        return false;
    }
    zoneFile.write(GetBinaryData());
    zoneFile.close();
    return true;
}

QString ZoneFile::GetStem() {
    return mStem;
}

quint32 ZoneFile::GetSize() {
    return mSize;
}

quint32 ZoneFile::GetTagCount() {
    return mTagCount;
}

QStringList ZoneFile::GetTags() {
    return mTags;
}

quint32 ZoneFile::GetRecordCount() {
    return mRecordCount;
}

QStringList ZoneFile::GetRecords() {
    return mRecords;
}

AssetMap ZoneFile::GetAssetMap() {
    return mAssetMap;
}

void ZoneFile::SetStem(const QString aStem) {
    mStem = aStem;
}

void ZoneFile::SetSize(quint32 aSize) {
    mSize = aSize;
}

void ZoneFile::SetTagCount(quint32 aTagCount) {
    mTagCount = aTagCount;
}

void ZoneFile::SetTags(const QStringList aTags) {
    mTags = aTags;
}

void ZoneFile::SetRecordCount(quint32 aRecordCount) {
    mRecordCount = aRecordCount;
}

void ZoneFile::SetRecords(const QStringList aRecords) {
    mRecords = aRecords;
}

void ZoneFile::SetAssetMap(const AssetMap aAssetMap) {
    mAssetMap = aAssetMap;
}

