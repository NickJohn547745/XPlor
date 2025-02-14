#ifndef FASTFILE_H
#define FASTFILE_H

#include "enums.h"
#include "zonefile.h"

#include <QString>
#include <QCryptographicHash>

class FastFile
{
public:
    virtual ~FastFile();
    virtual FastFile &operator=(const FastFile &other);

    virtual bool Load(const QString aFilePath) = 0;
    virtual bool Load(const QByteArray aData) = 0;

    virtual QString GetStem() const { return mStem; }
    virtual FF_FILETYPE GetType() const { return mType; }
    virtual FF_COMPANY GetCompany() const { return mCompany; }
    virtual FF_SIGNAGE GetSignage() const { return mSignage; }
    virtual QString GetMagic() const { return mMagic; }
    virtual quint32 GetVersion() const { return mVersion; }
    virtual ZoneFile GetZoneFile() const { return mZoneFile; }
    virtual QString GetGame() const { return mGame; }
    virtual QString GetPlatform() const { return mPlatform; }

    virtual void SetStem(const QString aStem) { mStem = aStem; }
    virtual void SetType(const FF_FILETYPE aType) { mType = aType; }
    virtual void SetCompany(const FF_COMPANY aCompany) { mCompany = aCompany; }
    virtual void SetSignage(const FF_SIGNAGE aSignage) { mSignage = aSignage; }
    virtual void SetMagic(const QString aMagic) { mMagic = aMagic; }
    virtual void SetVersion(const quint32 aVersion) { mVersion = aVersion; }
    virtual void SetZoneFile(const ZoneFile aZoneFile) { mZoneFile = aZoneFile; }
    virtual void SetGame(const QString aGame) { mGame = aGame; }
    virtual void SetPlatform(const QString aPlatform) { mPlatform = aPlatform; }

private:
    QString mStem;
    FF_FILETYPE mType;
    FF_COMPANY mCompany;
    FF_SIGNAGE mSignage;
    QString mMagic;
    quint32 mVersion;
    ZoneFile mZoneFile;
    QString mGame;
    QString mPlatform;
};

#endif // FASTFILE_H
