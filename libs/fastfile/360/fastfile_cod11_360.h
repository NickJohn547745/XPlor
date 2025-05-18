#ifndef FASTFILE_COD11_360_H
#define FASTFILE_COD11_360_H

#include "fastfile.h"

class FastFile_COD11_360 : public FastFile
{
public:
    FastFile_COD11_360();
    FastFile_COD11_360(const QByteArray &aData);
    FastFile_COD11_360(const QString aFilePath);
    ~FastFile_COD11_360();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD11_360_H
