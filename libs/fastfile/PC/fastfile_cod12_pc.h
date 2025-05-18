#ifndef FASTFILE_COD12_PC_H
#define FASTFILE_COD12_PC_H

#include "fastfile.h"

class FastFile_COD12_PC : public FastFile
{
public:
    FastFile_COD12_PC();
    FastFile_COD12_PC(const QByteArray &aData);
    FastFile_COD12_PC(const QString aFilePath);
    ~FastFile_COD12_PC();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD12_PC_H
