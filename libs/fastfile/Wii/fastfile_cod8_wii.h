#ifndef FASTFILE_COD8_WII_H
#define FASTFILE_COD8_WII_H

#include "fastfile.h"

class FastFile_COD8_Wii : public FastFile
{
public:
    FastFile_COD8_Wii();
    FastFile_COD8_Wii(const QByteArray &aData);
    FastFile_COD8_Wii(const QString aFilePath);
    ~FastFile_COD8_Wii();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD8_WII_H
