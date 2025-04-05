#ifndef FASTFILE_COD5_H
#define FASTFILE_COD5_H

#include "fastfile.h"

class FastFile_COD5 : public FastFile
{
public:
    FastFile_COD5();
    ~FastFile_COD5();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD5_H
