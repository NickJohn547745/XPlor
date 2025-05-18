#ifndef FASTFILE_COD9_WIIU_H
#define FASTFILE_COD9_WIIU_H

#include "fastfile.h"

class FastFile_COD9_WiiU : public FastFile
{
public:
    FastFile_COD9_WiiU();
    FastFile_COD9_WiiU(const QByteArray &aData);
    FastFile_COD9_WiiU(const QString aFilePath);
    ~FastFile_COD9_WiiU();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD9_WIIU_H
