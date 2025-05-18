#ifndef FASTFILE_COD5_PC_H
#define FASTFILE_COD5_PC_H

#include "fastfile.h"

class FastFile_COD5_PC : public FastFile
{
public:
    FastFile_COD5_PC();
    FastFile_COD5_PC(const QByteArray &aData);
    FastFile_COD5_PC(const QString aFilePath);
    ~FastFile_COD5_PC();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD5_PC_H
