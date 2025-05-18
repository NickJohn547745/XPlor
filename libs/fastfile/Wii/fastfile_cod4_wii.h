#ifndef FASTFILE_COD4_WII_H
#define FASTFILE_COD4_WII_H

#include "fastfile.h"

class FastFile_COD4_Wii : public FastFile
{
public:
    FastFile_COD4_Wii();
    FastFile_COD4_Wii(const QByteArray &aData);
    FastFile_COD4_Wii(const QString aFilePath);
    ~FastFile_COD4_Wii();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD4_WII_H
