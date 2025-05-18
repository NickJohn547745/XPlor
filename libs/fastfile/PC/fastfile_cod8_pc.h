#ifndef FASTFILE_COD8_PC_H
#define FASTFILE_COD8_PC_H

#include "fastfile.h"

class FastFile_COD8_PC : public FastFile
{
public:
    FastFile_COD8_PC();
    FastFile_COD8_PC(const QByteArray &aData);
    FastFile_COD8_PC(const QString aFilePath);
    ~FastFile_COD8_PC();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD8_PC_H
