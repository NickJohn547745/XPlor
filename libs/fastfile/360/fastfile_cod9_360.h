#ifndef FASTFILE_COD9_360_H
#define FASTFILE_COD9_360_H

#include "fastfile.h"

class FastFile_COD9_360 : public FastFile
{
public:
    FastFile_COD9_360();
    FastFile_COD9_360(const QByteArray& aData);
    FastFile_COD9_360(const QString aFilePath);
    ~FastFile_COD9_360();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD9_360_H
