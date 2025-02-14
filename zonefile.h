#ifndef ZONEFILE_H
#define ZONEFILE_H

#include "asset_structs.h"

#include <QStringList>

class ZoneFile
{
public:
    ZoneFile();
    ~ZoneFile();
    ZoneFile(const ZoneFile &aZoneFile);
    ZoneFile &operator=(const ZoneFile &other);

    bool Load(const QString aFilePath, FF_PLATFORM platform = FF_PLATFORM_PC);
    bool Load(const QByteArray aFileData, const QString aFileStem, FF_PLATFORM platform = FF_PLATFORM_NONE, FF_GAME game = FF_GAME_NONE);

    QString GetFileStem();
    quint32 GetSize();
    quint32 GetTagCount();
    QStringList GetTags();
    quint32 GetRecordCount();
    QStringList GetRecords();
    AssetMap GetAssetMap();

private slots:
    void pParseZoneHeader(QDataStream *aZoneFileStream, FF_GAME game);
    quint32 pParseZoneSize(QDataStream *aZoneFileStream);
    void pParseZoneUnknownsA(QDataStream *aZoneFileStream);
    quint32 pParseZoneTagCount(QDataStream *aZoneFileStream);
    quint32 pParseZoneRecordCount(QDataStream *aZoneFileStream);
    void pParseZoneUnknownsB(QDataStream *aZoneFileStream);
    void pParseZoneUnknownsC(QDataStream *aZoneFileStream);
    QStringList pParseZoneTags(QDataStream *aZoneFileStream, quint32 tagCount, FF_GAME game);
    QStringList pParseZoneIndex(QDataStream *aZoneFileStream, quint32 recordCount, FF_GAME game);
    AssetMap pParseAssets(QDataStream *aZoneFileStream, QStringList assetOrder, FF_GAME game);
    LocalString pParseAsset_LocalString(QDataStream *aZoneFileStream);
    RawFile pParseAsset_RawFile(QDataStream *aZoneFileStream);
    void pParseAsset_PhysPreset(QDataStream *aZoneFileStream);
    Model pParseAsset_Model(QDataStream *aZoneFileStream);
    void pParseAsset_Material(QDataStream *aZoneFileStream);
    Shader pParseAsset_Shader(QDataStream *aZoneFileStream);
    TechSet pParseAsset_TechSet(QDataStream *aZoneFileStream);
    Image pParseAsset_Image(QDataStream *aZoneFileStream);
    SoundAsset pParseAsset_Sound(QDataStream *aZoneFileStream);
    void pParseAsset_ColMapMP(QDataStream *aZoneFileStream);
    void pParseAsset_GameMapSP(QDataStream *aZoneFileStream);
    void pParseAsset_GameMapMP(QDataStream *aZoneFileStream);
    void pParseAsset_LightDef(QDataStream *aZoneFileStream);
    void pParseAsset_UIMap(QDataStream *aZoneFileStream);
    void pParseAsset_SNDDriverGlobals(QDataStream *aZoneFileStream);
    void pParseAsset_AIType(QDataStream *aZoneFileStream);
    void pParseAsset_FX(QDataStream *aZoneFileStream);
    Animation pParseAsset_Animation(QDataStream *aZoneFileStream);
    MenuFile pParseAsset_MenuFile(QDataStream *aZoneFileStream);
    void pParseAsset_Weapon(QDataStream *aZoneFileStream);
    void pParseAsset_D3DBSP(QDataStream *aZoneFileStream);
    StringTable pParseAsset_StringTable(QDataStream *aZoneFileStream);

private:
    QString fileStem;
    quint32 size;
    quint32 tagCount;
    QStringList tags;
    quint32 recordCount;
    QStringList records;
    AssetMap assetMap;
    QString platform;
    QString game;
};

#endif // ZONEFILE_H
