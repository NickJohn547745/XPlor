#ifndef FASTFILE_COD11_PC_H
#define FASTFILE_COD11_PC_H

#include "fastfile.h"

class FastFile_COD11_PC : public FastFile
{
public:
    FastFile_COD11_PC();
    FastFile_COD11_PC(const QByteArray &aData);
    FastFile_COD11_PC(const QString aFilePath);
    ~FastFile_COD11_PC();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD11_PC_H
