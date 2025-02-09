#ifndef FASTFILE_H
#define FASTFILE_H

#include "enums.h"
#include "zonefile.h"

#include <QString>
#include <QCryptographicHash>

class FastFile
{
public:
    FastFile();
    ~FastFile();
    FastFile(const FastFile &aFastFile);
    FastFile &operator=(const FastFile &other);

    bool Load(const QString aFilePath);
    bool Load(const QByteArray aData);

    QString GetFileStem() const;
    FF_COMPANY GetCompany() const;
    FF_FILETYPE GetFileType() const;
    FF_SIGNAGE GetSignage() const;
    QString GetMagic() const;
    quint32 GetVersion() const;
    ZoneFile GetZoneFile() const;
    QString GetGame() const;
    QString GetPlatform() const;

private:
    QString fileStem;
    FF_COMPANY company;
    FF_FILETYPE fileType;
    FF_SIGNAGE signage;
    QString magic;
    quint32 version;
    ZoneFile zoneFile;
    QString game;
    QString platform;

    QString pCalculateFFGame();
    QString pCalculateFFPlatform();
    QString pParseFFMagic(QDataStream *afastFileStream);
    FF_SIGNAGE pParseFFSignage(QDataStream *afastFileStream);
    FF_FILETYPE pParseFFFileType(QDataStream *afastFileStream);
    FF_COMPANY pParseFFCompany(QDataStream *afastFileStream);
    quint32 pParseFFVersion(QDataStream *afastFileStream);
};

#endif // FASTFILE_H
