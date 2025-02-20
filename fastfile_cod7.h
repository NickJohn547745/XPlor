#ifndef FASTFILE_COD7_H
#define FASTFILE_COD7_H

#include "fastfile.h"

class FastFile_COD7 : public FastFile
{
public:
    FastFile_COD7();
    ~FastFile_COD7();

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD7_H
