#ifndef FASTFILE_COD12_360_H
#define FASTFILE_COD12_360_H

#include "fastfile.h"

class FastFile_COD12_360 : public FastFile
{
public:
    FastFile_COD12_360();
    FastFile_COD12_360(const QByteArray &aData);
    FastFile_COD12_360(const QString aFilePath);
    ~FastFile_COD12_360();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD12_360_H
