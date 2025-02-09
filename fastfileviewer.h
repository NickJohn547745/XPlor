#ifndef FASTFILEVIEWER_H
#define FASTFILEVIEWER_H

#include "asset_structs.h"
#include "fastfile.h"
#include <QWidget>

namespace Ui {
class FFViewer;
}

class FastFileViewer : public QWidget
{
    Q_OBJECT

public:
    explicit FastFileViewer(QWidget *parent = nullptr);
    ~FastFileViewer();

    void SetFastFile(std::shared_ptr<FastFile> aFastFile);
private:
    Ui::FFViewer *ui;
    std::shared_ptr<FastFile> mFastFile;
};

#endif // FASTFILEVIEWER_H
