#ifndef FASTFILE_COD10_PS3_H
#define FASTFILE_COD10_PS3_H

#include "fastfile.h"

class FastFile_COD10_PS3 : public FastFile
{
public:
    FastFile_COD10_PS3();
    FastFile_COD10_PS3(const QByteArray &aData);
    FastFile_COD10_PS3(const QString aFilePath);
    ~FastFile_COD10_PS3();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD10_PS3_H
