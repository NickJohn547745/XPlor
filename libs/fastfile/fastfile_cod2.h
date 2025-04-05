#ifndef FASTFILE_COD2_H
#define FASTFILE_COD2_H

#include "fastfile.h"

class FastFile_COD2 : public FastFile
{
public:
    FastFile_COD2();
    ~FastFile_COD2();

    QByteArray GetBinaryData() override;

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD2_H
