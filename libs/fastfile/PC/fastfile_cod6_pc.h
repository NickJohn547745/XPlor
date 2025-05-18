#ifndef FASTFILE_COD6_PC_H
#define FASTFILE_COD6_PC_H

#include "fastfile.h"

class FastFile_COD6_PC : public FastFile
{
public:
    FastFile_COD6_PC();
    FastFile_COD6_PC(const QByteArray &aData);
    FastFile_COD6_PC(const QString aFilePath);
    ~FastFile_COD6_PC();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD6_PC_H
