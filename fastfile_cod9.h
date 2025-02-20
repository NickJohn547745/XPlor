#ifndef FASTFILE_COD9_H
#define FASTFILE_COD9_H

#include "fastfile.h"

class FastFile_COD9 : public FastFile
{
public:
    FastFile_COD9();
    ~FastFile_COD9();

    bool Load(const QString aFilePath) override;
    bool Load(const QByteArray aData) override;
};

#endif // FASTFILE_COD9_H
