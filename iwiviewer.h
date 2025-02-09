#ifndef IWIVIEWER_H
#define IWIVIEWER_H

#include "iwifile.h"
#include <QWidget>

namespace Ui {
class IWIViewer;
}

class IWIViewer : public QWidget
{
    Q_OBJECT

public:
    explicit IWIViewer(QWidget *parent = nullptr);
    ~IWIViewer();

    void MipmapIndexChanged(int aMipmapIndex);

    void SetIWIFile(std::shared_ptr<IWIFile> aIWIFile);
private:
    Ui::IWIViewer *ui;
    std::shared_ptr<IWIFile> mIWIFile;
};

#endif // IWIVIEWER_H
