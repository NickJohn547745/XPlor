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

QString ZoneFile::AssetEnumToStr(const AssetType aAssetType)
{
    if (aAssetType == ASSET_LOCAL_STRING) {
        return "ASSET_LOCAL_STRING";
    } else if (aAssetType == ASSET_RAW_FILE) {
        return "ASSET_RAW_FILE";
    } else if (aAssetType == ASSET_SCRIPT_PARSE_TREE) {
        return "ASSET_GSC_FILE";
    } else if (aAssetType == ASSET_EFFECT) {
        return "ASSET_EFFECT";
    } else if (aAssetType == ASSET_SOUND) {
        return "ASSET_SOUND";
    } else if (aAssetType == ASSET_ANIMATION) {
        return "ASSET_ANIMATION";
    } else if (aAssetType == ASSET_COLLISION_MAP) {
        return "ASSET_COLLISION_MAP";
    } else if (aAssetType == ASSET_STRING_TABLE) {
        return "ASSET_STRING_TABLE";
    } else if (aAssetType == ASSET_MENU) {
        return "ASSET_MENU";
    } else if (aAssetType == ASSET_TECH_SET) {
        return "ASSET_TECH_SET";
    } else if (aAssetType == ASSET_WEAPON) {
        return "ASSET_WEAPON";
    } else if (aAssetType == ASSET_GFX_MAP) {
        return "ASSET_GFX_MAP";
    } else if (aAssetType == ASSET_LIGHT_DEF) {
        return "ASSET_LIGHT_DEF";
    } else if (aAssetType == ASSET_FONT) {
        return "ASSET_FONT";
    } else if (aAssetType == ASSET_MODEL) {
        return "ASSET_MODEL";
    } else if (aAssetType == ASSET_D3DBSP) {
        return "ASSET_D3DBSP";
    } else if (aAssetType == ASSET_IMAGE) {
        return "ASSET_IMAGE";
    } else if (aAssetType == ASSET_GAME_MAP_SP) {
        return "ASSET_GAME_MAP_SP";
    } else if (aAssetType == ASSET_COL_MAP_SP) {
        return "ASSET_COL_MAP_SP";
    } else if (aAssetType == ASSET_COL_MAP_SP) {
        return "ASSET_COL_MAP_SP";
    } else if (aAssetType == ASSET_DESTRUCTIBLE) {
        return "ASSET_DESTRUCTIBLE";
    } else if (aAssetType == ASSET_MATERIAL) {
        return "ASSET_MATERIAL";
    } else if (aAssetType == ASSET_PHYS_PRESET) {
        return "ASSET_PHYS_PRESET";
    } else if (aAssetType == ASSET_COMPUTE_SHADER_SET) {
        return "ASSET_COMPUTE_SHADER_SET";
    } else if (aAssetType == ASSET_STRUCTURED_TABLE) {
        return "ASSET_STRUCTURED_TABLE";
    } else if (aAssetType == ASSET_LEADERBOARD_DEF) {
        return "ASSET_LEADERBOARD_DEF";
    } else if (aAssetType == ASSET_DDL) {
        return "ASSET_DDL";
    } else if (aAssetType == ASSET_SCRIPT_PARSE_TREE) {
        return "ASSET_SCRIPT_PARSE_TREE";
    } else if (aAssetType == ASSET_KEY_VALUE_PAIRS) {
        return "ASSET_KEY_VALUE_PAIRS";
    } else if (aAssetType == ASSET_SCRIPT_BUNDLE) {
        return "ASSET_SCRIPT_BUNDLE";
    } else if (aAssetType == ASSET_SCRIPT_BUNDLE_LIST) {
        return "ASSET_SCRIPT_BUNDLE_LIST";
    } else if (aAssetType == ASSET_LIGHT_DEF) {
        return "ASSET_LIGHT_DEF";
    } else if (aAssetType == ASSET_BIT_FIELD) {
        return "ASSET_BIT_FIELD";
    } else if (aAssetType == ASSET_MAP_TABLE) {
        return "ASSET_MAP_TABLE";
    } else if (aAssetType == ASSET_MAP_TABLE_LOADING_IMAGES) {
        return "ASSET_MAP_TABLE_LOADING_IMAGES";
    } else if (aAssetType == ASSET_SURFACE_SOUND_DEF) {
        return "ASSET_SURFACE_SOUND_DEF";
    } else if (aAssetType == ASSET_SURFACE_FX_TABLE) {
        return "ASSET_SURFACE_FX_TABLE";
    } else if (aAssetType == ASSET_RUMBLE) {
        return "ASSET_RUMBLE";
    } else if (aAssetType == ASSET_AIM_TABLE) {
        return "ASSET_AIM_TABLE";
    } else if (aAssetType == ASSET_MEDAL) {
        return "ASSET_MEDAL";
    } else if (aAssetType == ASSET_MEDAL_TABLE) {
        return "ASSET_MEDAL_TABLE";
    } else if (aAssetType == ASSET_OBJECTIVE) {
        return "ASSET_OBJECTIVE";
    } else if (aAssetType == ASSET_OBJECTIVE_LIST) {
        return "ASSET_OBJECTIVE_LIST";
    } else if (aAssetType == ASSET_LASER) {
        return "ASSET_LASER";
    } else if (aAssetType == ASSET_BEAM) {
        return "ASSET_BEAM";
    } else if (aAssetType == ASSET_STREAMER_HINT) {
        return "ASSET_STREAMER_HINT";
    } else if (aAssetType == ASSET_ANIM_SELECTOR_TABLE) {
        return "ASSET_ANIM_SELECTOR_TABLE";
    } else if (aAssetType == ASSET_ANIM_MAPPING_TABLE) {
        return "ASSET_ANIM_MAPPING_TABLE";
    } else if (aAssetType == ASSET_ANIM_STATE_MACHINE) {
        return "ASSET_ANIM_STATE_MACHINE";
    } else if (aAssetType == ASSET_BEHAVIOR_TREE) {
        return "ASSET_BEHAVIOR_TREE";
    } else if (aAssetType == ASSET_BEHAVIOR_STATE_MACHINE) {
        return "ASSET_BEHAVIOR_STATE_MACHINE";
    } else if (aAssetType == ASSET_FOOTSTEP_TABLE) {
        return "ASSET_FOOTSTEP_TABLE";
    } else if (aAssetType == ASSET_ENTITY_FX_IMPACTS) {
        return "ASSET_ENTITY_FX_IMPACTS";
    } else if (aAssetType == ASSET_ENTITY_SOUND_IMPACTS) {
        return "ASSET_ENTITY_SOUND_IMPACTS";
    } else if (aAssetType == ASSET_VEHICLE_FX_DEF) {
        return "ASSET_VEHICLE_FX_DEF";
    } else if (aAssetType == ASSET_VEHICLE_SOUND_DEF) {
        return "ASSET_VEHICLE_SOUND_DEF";
    } else if (aAssetType == ASSET_VEHICLE) {
        return "ASSET_VEHICLE";
    } else if (aAssetType == ASSET_VEHICLE_TRACER) {
        return "ASSET_VEHICLE_TRACER";
    } else if (aAssetType == ASSET_PLAYER_SOUNDS_TABLE) {
        return "ASSET_PLAYER_SOUNDS_TABLE";
    } else if (aAssetType == ASSET_PLAYER_FX_TABLE) {
        return "ASSET_PLAYER_FX_TABLE";
    } else if (aAssetType == ASSET_SHARED_WEAPON_SOUNDS) {
        return "ASSET_SHARED_WEAPON_SOUNDS";
    } else if (aAssetType == ASSET_ATTACHMENT) {
        return "ASSET_ATTACHMENT";
    } else if (aAssetType == ASSET_ATTACHMENT_UNIQUE) {
        return "ASSET_ATTACHMENT_UNIQUE";
    } else if (aAssetType == ASSET_WEAPON_CAMO) {
        return "ASSET_WEAPON_CAMO";
    } else if (aAssetType == ASSET_CUSTOMIZATION_TABLE) {
        return "ASSET_CUSTOMIZATION_TABLE";
    } else if (aAssetType == ASSET_CUSTOMIZATION_TABLE_FEIMAGES) {
        return "ASSET_CUSTOMIZATION_TABLE_FEIMAGES";
    } else if (aAssetType == ASSET_CUSTOMIZATION_TABLE_COLOR) {
        return "ASSET_CUSTOMIZATION_TABLE_COLOR";
    } else if (aAssetType == ASSET_PHYS_CONSTRAINTS) {
        return "ASSET_PHYS_CONSTRAINTS";
    } else if (aAssetType == ASSET_DESTRUCTIBLE_DEF) {
        return "ASSET_DESTRUCTIBLE_DEF";
    } else if (aAssetType == ASSET_MODEL_MESH) {
        return "ASSET_MODEL_MESH";
    } else if (aAssetType == ASSET_S_ANIM) {
        return "ASSET_S_ANIM";
    } else if (aAssetType == ASSET_SOUND) {
        return "ASSET_SOUND";
    } else if (aAssetType == ASSET_FONT_ICON) {
        return "ASSET_FONT_ICON";
    }
    return "ASSET_UNKNOWN";
}
QIcon ZoneFile::AssetTypeToIcon(const AssetType aAssetType) {
    if (aAssetType == ASSET_LOCAL_STRING) {        // localized string       PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_StringFile.png");
    } else if (aAssetType == ASSET_RAW_FILE) { // raw_file               PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_RawFile.png");
    } else if (aAssetType == ASSET_SCRIPT_PARSE_TREE) { // raw_file               PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_GSCFile.png");
    } else if (aAssetType == ASSET_EFFECT) { // fx                     PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_Effect.png");
    } else if (aAssetType == ASSET_SOUND) { // loaded_sound           PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_Sound.png");
    } else if (aAssetType == ASSET_ANIMATION) { // x_anim                 PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_Animation.png");
    } else if (aAssetType == ASSET_COLLISION_MAP) { // collision_map          PARTIALLY VERIFIED
        //return ASSET_COLLISION_MAP;
    } else if (aAssetType == ASSET_STRING_TABLE) { // string_table           PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_StringTable.png");
    } else if (aAssetType == ASSET_MENU) { // menu_file              PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_MenuFile.png");
    } else if (aAssetType == ASSET_TECH_SET) { // tech set               PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_TechSetFile.png");
    } else if (aAssetType == ASSET_WEAPON) { // weapon                 PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_Weapon.png");
    } else if (aAssetType == ASSET_GFX_MAP) { // gfx map                PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_FXMap.png");
    } else if (aAssetType == ASSET_LIGHT_DEF) { // light_def              PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_LightDef.png");
    } else if (aAssetType == ASSET_FONT) { // font                   PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_Font.png");
    } else if (aAssetType == ASSET_MODEL) { // xmodel                 PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_Model.png");
    } else if (aAssetType == ASSET_MATERIAL) { // xmodel                 PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_Material.png");
    } else if (aAssetType == ASSET_D3DBSP) { // d3dbsp                 PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_BSP.png");
    } else if (aAssetType == ASSET_IMAGE) { // image                  PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_Image.png");
    } else if (aAssetType == ASSET_GAME_MAP_SP) { // game map sp            PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_GameMapSp.png");
    } else if (aAssetType == ASSET_COL_MAP_SP) { // col map sp             PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_ColMapSp.png");
    } else if (aAssetType == ASSET_PHYS_PRESET) { // col map sp             PARTIALLY VERIFIED
        return QIcon(":/icons/icons/Icon_PhysPreset.png");
    } else if (aAssetType == ASSET_DESTRUCTIBLE) { // col map sp             PARTIALLY VERIFIED
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

