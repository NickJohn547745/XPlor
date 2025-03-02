#ifndef TECHSETVIEWER_H
#define TECHSETVIEWER_H

#include "asset_structs.h"
#include <QWidget>

namespace Ui {
class TechSetViewer;
}

class TechSetViewer : public QWidget
{
    Q_OBJECT

public:
    explicit TechSetViewer(QWidget *parent = nullptr);
    ~TechSetViewer();

    void SetTechSet(std::shared_ptr<TechSet> aTechSet);

private:
    Ui::TechSetViewer *ui;
};

#endif // TECHSETVIEWER_H
