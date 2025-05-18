#ifndef FASTFILE_COD9_PC_H
#define FASTFILE_COD9_PC_H

#include "fastfile.h"

class FastFile_COD9_PC : public FastFile
{
public:
    FastFile_COD9_PC();
    FastFile_COD9_PC(const QByteArray &aData);
    FastFile_COD9_PC(const QString aFilePath);
    ~FastFile_COD9_PC();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD9_PC_H
