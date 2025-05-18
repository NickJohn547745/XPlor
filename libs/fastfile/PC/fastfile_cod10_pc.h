#ifndef FASTFILE_COD10_PC_H
#define FASTFILE_COD10_PC_H

#include "fastfile.h"

class FastFile_COD10_PC : public FastFile
{
public:
    FastFile_COD10_PC();
    FastFile_COD10_PC(const QByteArray &aData);
    FastFile_COD10_PC(const QString aFilePath);
    ~FastFile_COD10_PC();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD10_PC_H
