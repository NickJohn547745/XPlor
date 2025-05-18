#ifndef FASTFILE_COD7_PC_H
#define FASTFILE_COD7_PC_H

#include "fastfile.h"

class FastFile_COD7_PC : public FastFile
{
public:
    FastFile_COD7_PC();
    FastFile_COD7_PC(const QByteArray &aData);
    FastFile_COD7_PC(const QString aFilePath);
    ~FastFile_COD7_PC();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD7_PC_H
