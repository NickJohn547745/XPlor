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

    virtual bool Load(const QByteArray aFileData, const QString aFileStem, FF_PLATFORM platform = FF_PLATFORM_NONE) = 0;
    virtual QString AssetTypeToString(const QString aAssetType) = 0;

    QString GetStem();
    quint32 GetSize();
    quint32 GetTagCount();
    QStringList GetTags();
    quint32 GetRecordCount();
    QStringList GetRecords();
    AssetMap GetAssetMap();

protected:
    void SetStem(const QString aStem);
    void SetSize(quint32 aSize);
    void SetTagCount(quint32 aTagCount);
    void SetTags(const QStringList aTags);
    void SetRecordCount(quint32 aRecordCount);
    void SetRecords(const QStringList aRecords);
    void SetAssetMap(const AssetMap aAssetMap);

private slots:
    virtual void pParseZoneHeader(QDataStream *aZoneFileStream) = 0;
    virtual quint32 pParseZoneSize(QDataStream *aZoneFileStream) = 0;
    virtual void pParseZoneUnknownsA(QDataStream *aZoneFileStream) = 0;
    virtual quint32 pParseZoneTagCount(QDataStream *aZoneFileStream) = 0;
    virtual quint32 pParseZoneRecordCount(QDataStream *aZoneFileStream) = 0;
    virtual void pParseZoneUnknownsB(QDataStream *aZoneFileStream) = 0;
    virtual void pParseZoneUnknownsC(QDataStream *aZoneFileStream) = 0;
    virtual QStringList pParseZoneTags(QDataStream *aZoneFileStream, quint32 tagCount) = 0;
    virtual QStringList pParseZoneIndex(QDataStream *aZoneFileStream, quint32 recordCount) = 0;
    virtual AssetMap pParseAssets(QDataStream *aZoneFileStream, QStringList assetOrder) = 0;
    virtual LocalString pParseAsset_LocalString(QDataStream *aZoneFileStream) = 0;
    virtual RawFile pParseAsset_RawFile(QDataStream *aZoneFileStream) = 0;
    virtual void pParseAsset_PhysPreset(QDataStream *aZoneFileStream) = 0;
    virtual Model pParseAsset_Model(QDataStream *aZoneFileStream) = 0;
    virtual Material pParseAsset_Material(QDataStream *aZoneFileStream) = 0;
    virtual Shader pParseAsset_Shader(QDataStream *aZoneFileStream) = 0;
    virtual TechSet pParseAsset_TechSet(QDataStream *aZoneFileStream) = 0;
    virtual Image pParseAsset_Image(QDataStream *aZoneFileStream) = 0;
    virtual SoundAsset pParseAsset_Sound(QDataStream *aZoneFileStream) = 0;
    virtual void pParseAsset_ColMapMP(QDataStream *aZoneFileStream) = 0;
    virtual void pParseAsset_GameMapSP(QDataStream *aZoneFileStream) = 0;
    virtual void pParseAsset_GameMapMP(QDataStream *aZoneFileStream) = 0;
    virtual void pParseAsset_LightDef(QDataStream *aZoneFileStream) = 0;
    virtual void pParseAsset_UIMap(QDataStream *aZoneFileStream) = 0;
    virtual void pParseAsset_SNDDriverGlobals(QDataStream *aZoneFileStream) = 0;
    virtual void pParseAsset_AIType(QDataStream *aZoneFileStream) = 0;
    virtual void pParseAsset_FX(QDataStream *aZoneFileStream) = 0;
    virtual Animation pParseAsset_Animation(QDataStream *aZoneFileStream) = 0;
    virtual MenuFile pParseAsset_MenuFile(QDataStream *aZoneFileStream) = 0;
    virtual void pParseAsset_Weapon(QDataStream *aZoneFileStream) = 0;
    virtual void pParseAsset_D3DBSP(QDataStream *aZoneFileStream) = 0;
    virtual StringTable pParseAsset_StringTable(QDataStream *aZoneFileStream) = 0;

private:
    QString mStem;
    quint32 mSize;
    quint32 mTagCount;
    QStringList mTags;
    quint32 mRecordCount;
    QStringList mRecords;
    AssetMap mAssetMap;
    QString mPlatform;
    QString mGame;
};

#endif // ZONEFILE_H
