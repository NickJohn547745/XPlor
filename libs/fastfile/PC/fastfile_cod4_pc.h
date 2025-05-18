#ifndef FASTFILE_COD4_PC_H
#define FASTFILE_COD4_PC_H

#include "fastfile.h"

class FastFile_COD4_PC : public FastFile
{
public:
    FastFile_COD4_PC();
    FastFile_COD4_PC(const QByteArray &aData);
    FastFile_COD4_PC(const QString aFilePath);
    ~FastFile_COD4_PC();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD4_PC_H
