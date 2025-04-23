#ifndef DDSVIEWER_H
#define DDSVIEWER_H

#include "ddsfile.h"
#include <QWidget>

namespace Ui {
class DDSViewer;
}

class DDSViewer : public QWidget
{
    Q_OBJECT

public:
    explicit DDSViewer(QWidget *parent = nullptr);
    ~DDSViewer();

    void SetDDSFile(std::shared_ptr<DDSFile> aDDSFile);

private slots:
    void MipmapIndexChanged(int aMipmapIndex);

private:
    Ui::DDSViewer *ui;
    std::shared_ptr<DDSFile> mDDSFile;
};

#endif // DDSVIEWER_H
