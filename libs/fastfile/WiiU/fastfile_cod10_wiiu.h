#ifndef FASTFILE_COD10_WIIU_H
#define FASTFILE_COD10_WIIU_H

#include "fastfile.h"

class FastFile_COD10_WiiU : public FastFile
{
public:
    FastFile_COD10_WiiU();
    FastFile_COD10_WiiU(const QByteArray &aData);
    FastFile_COD10_WiiU(const QString aFilePath);
    ~FastFile_COD10_WiiU();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD10_WIIU_H
