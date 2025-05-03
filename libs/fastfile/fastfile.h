#ifndef FASTFILE_H
#define FASTFILE_H

#include "enums.h"
#include "zonefile.h"

#include <QString>
#include <QCryptographicHash>

class ZoneFile;

class FastFile
{
public:
    FastFile();
    FastFile(const QByteArray& aData);
    FastFile(FastFile &fastFile);
    ~FastFile();

    virtual bool Load(const QString aFilePath) = 0;
    virtual bool Load(const QByteArray aData) = 0;

    virtual bool ExportFastFile(const QString aFastFilePath);

    virtual QByteArray GetBinaryData() = 0;

    virtual QString GetStem() const;
    virtual FF_FILETYPE GetType() const;
    virtual FF_COMPANY GetCompany() const;
    virtual FF_SIGNAGE GetSignage() const;
    virtual QString GetMagic() const;
    virtual quint32 GetVersion() const;
    virtual std::shared_ptr<ZoneFile> GetZoneFile() const;
    virtual QString GetGame() const;
    virtual QString GetPlatform() const;

    virtual void SetStem(const QString aStem);
    virtual void SetType(const FF_FILETYPE aType);
    virtual void SetCompany(const FF_COMPANY aCompany);
    virtual void SetSignage(const FF_SIGNAGE aSignage);
    virtual void SetMagic(const QString aMagic);
    virtual void SetVersion(const quint32 aVersion);
    virtual void SetZoneFile(const std::shared_ptr<ZoneFile> aZoneFile);
    virtual void SetGame(const QString aGame);
    virtual void SetPlatform(const QString aPlatform);

    static FF_COMPANY pParseFFCompany(QDataStream *afastFileStream, quint32 &aCompanyInt);
    static FF_COMPANY pParseFFCompany(QDataStream *afastFileStream);
    static FF_FILETYPE pParseFFFileType(QDataStream *afastFileStream);
    static FF_SIGNAGE pParseFFSignage(QDataStream *afastFileStream);
    static QString pParseFFMagic(QDataStream *afastFileStream);
    static quint32 pParseFFVersion(QDataStream *afastFileStream);
    static QString pCalculateFFPlatform(quint32 aVersion);
    static QString pCalculateFFGame(quint32 aVersion);

    static std::shared_ptr<FastFile> Open(const QString& aFilePath);

private:
    QString mStem;
    FF_FILETYPE mType;
    FF_COMPANY mCompany;
    FF_SIGNAGE mSignage;
    QString mMagic;
    quint32 mVersion;
    std::shared_ptr<ZoneFile> mZoneFile;
    QString mGame;
    QString mPlatform;
};

#endif // FASTFILE_H
