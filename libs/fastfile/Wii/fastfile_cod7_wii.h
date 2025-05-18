#ifndef FASTFILE_COD7_WII_H
#define FASTFILE_COD7_WII_H

#include "fastfile.h"

class FastFile_COD7_Wii : public FastFile
{
public:
    FastFile_COD7_Wii();
    FastFile_COD7_Wii(const QByteArray &aData);
    FastFile_COD7_Wii(const QString aFilePath);
    ~FastFile_COD7_Wii();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD7_WII_H
