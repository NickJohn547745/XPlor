#ifndef ZONEFILE_COD7_H
#define ZONEFILE_COD7_H

#include "zonefile.h"

class ZoneFile_COD7 : public ZoneFile
{
public:
    ZoneFile_COD7();
    ~ZoneFile_COD7();

    bool Load(const QByteArray aFileData, const QString aStem, FF_PLATFORM aPlatform) override;
    QString AssetTypeToString(const QString aAssetType);

protected:
    void pParseZoneHeader(QDataStream *aZoneFileStream) override;
    quint32 pParseZoneSize(QDataStream *aZoneFileStream) override;
    void pParseZoneUnknownsA(QDataStream *aZoneFileStream) override;
    quint32 pParseZoneTagCount(QDataStream *aZoneFileStream) override;
    quint32 pParseZoneRecordCount(QDataStream *aZoneFileStream) override;
    void pParseZoneUnknownsB(QDataStream *aZoneFileStream) override;
    void pParseZoneUnknownsC(QDataStream *aZoneFileStream) override;
    QStringList pParseZoneTags(QDataStream *aZoneFileStream, quint32 tagCount) override;
    QStringList pParseZoneIndex(QDataStream *aZoneFileStream, quint32 recordCount) override;
    AssetMap pParseAssets(QDataStream *aZoneFileStream, QStringList assetOrder) override;
    LocalString pParseAsset_LocalString(QDataStream *aZoneFileStream) override;
    RawFile pParseAsset_RawFile(QDataStream *aZoneFileStream) override;
    void pParseAsset_PhysPreset(QDataStream *aZoneFileStream) override;
    Model pParseAsset_Model(QDataStream *aZoneFileStream) override;
    Material pParseAsset_Material(QDataStream *aZoneFileStream) override;
    Shader pParseAsset_Shader(QDataStream *aZoneFileStream) override;
    TechSet pParseAsset_TechSet(QDataStream *aZoneFileStream) override;
    Image pParseAsset_Image(QDataStream *aZoneFileStream) override;
    SoundAsset pParseAsset_Sound(QDataStream *aZoneFileStream) override;
    void pParseAsset_ColMapMP(QDataStream *aZoneFileStream) override;
    void pParseAsset_GameMapSP(QDataStream *aZoneFileStream) override;
    void pParseAsset_GameMapMP(QDataStream *aZoneFileStream) override;
    void pParseAsset_LightDef(QDataStream *aZoneFileStream) override;
    void pParseAsset_UIMap(QDataStream *aZoneFileStream) override;
    void pParseAsset_SNDDriverGlobals(QDataStream *aZoneFileStream) override;
    void pParseAsset_AIType(QDataStream *aZoneFileStream) override;
    void pParseAsset_FX(QDataStream *aZoneFileStream) override;
    Animation pParseAsset_Animation(QDataStream *aZoneFileStream) override;
    MenuFile pParseAsset_MenuFile(QDataStream *aZoneFileStream) override;
    void pParseAsset_Weapon(QDataStream *aZoneFileStream) override;
    void pParseAsset_D3DBSP(QDataStream *aZoneFileStream) override;
    StringTable pParseAsset_StringTable(QDataStream *aZoneFileStream) override;
};

#endif // ZONEFILE_COD7_H
