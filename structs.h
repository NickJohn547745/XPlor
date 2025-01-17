#ifndef STRUCTS_H
#define STRUCTS_H

#include "enums.h"

#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QMap>

// Define Lump Structure
struct Lump {
    QByteArray content;
    quint32 size = 0;
    bool isEmpty = true;
};

// Lump Index Entry Structure
struct LumpIndexEntry {
    quint32 type;
    quint32 length;
};

struct LocalString {
    QString string;
    QString alias;
};

struct RawFile {
    quint32 length;
    QString path;
    QString contents;
};

struct TechSet {
    QString name;
};

struct Animation {
    quint16 dataByteCount;
    quint16 dataShortCount;
    quint16 dataIntCount;
    quint16 randomDataByteCount;
    quint16 randomDataIntCount;
    quint16 numframes;
    bool isLooped;
    bool isDelta;
    quint8 noneRotatedBoneCount;
    quint8 twoDRotatedBoneCount;
    quint8 normalRotatedBoneCount;
    quint8 twoDStaticRotatedBoneCount;
    quint8 normalStaticRotatedBoneCount;
    quint8 normalTranslatedBoneCount;
    quint8 preciseTranslatedBoneCount;
    quint8 staticTranslatedBoneCount;
    quint8 noneTranslatedBoneCount;
    quint8 totalBoneCount;
    quint8 otherBoneCount1;
    quint8 otherBoneCount2;
    quint8 notifyCount;
    quint8 assetType;
    bool pad;
    unsigned int randomDataShortCount;
    unsigned int indexCount;
    float frameRate;
    float frequency;
    quint32 boneIDsPtr;
    quint32 dataBytePtr;
    quint32 dataShortPtr;
    quint32 dataIntPtr;
    quint32 randomDataShortPtr;
    quint32 randomDataBytePtr;
    quint32 randomDataIntPtr;
    quint32 longIndiciesPtr;
    quint32 notificationsPtr;
    quint32 deltaPartsPtr;
    QString name;
};

struct StringTable {
    quint32 columnCount;
    quint32 rowCount;
    QString name;
};

struct AssetMap {
    QVector<LocalString> localStrings;
    QVector<RawFile> rawFiles;
    //QVector<PhysPreset> phyPresets;
    //QVector<Model> models;
    //QVector<Material> rawFiles;
    //QVector<Shader> shaders;
    QVector<TechSet> techSets;
    //QVector<Image> images;
    //QVector<Sound> sounds;
    //QVector<CollisionMap> collMaps;
    //QVector<LightDefinition> lightDefs;
    //QVector<UiMap> uiMaps;
    //QVector<DriverGlobal> driverGlobals;
    //QVector<AiType> aiType;
    //QVector<Effect> effects;
    QVector<Animation> animations;
    QVector<StringTable> stringTables;
    //QVector<Menu> menus;
    //QVector<Weapon> weapons;
    //QVector<D3DBSP> d3dbspDumps;
    //QVector<SingleplayerMap> spMaps;
};

struct ZoneFile {
    quint32 size;
    quint32 tagCount;
    QStringList tags;
    quint32 recordCount;
    QStringList records;
    AssetMap assetMap;
};

struct FastFile {
    FF_COMPANY company;
    FF_FILETYPE fileType;
    FF_SIGNAGE signage;
    QString magic;
    quint32 version;

    ZoneFile zoneFile;
};

#endif // STRUCTS_H
