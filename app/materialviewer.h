#ifndef MATERIALVIEWER_H
#define MATERIALVIEWER_H

#include "asset_structs.h"
#include <QWidget>

namespace Ui {
class MaterialViewer;
}

class MaterialViewer : public QWidget
{
    Q_OBJECT

public:
    explicit MaterialViewer(QWidget *parent = nullptr);
    ~MaterialViewer();

    void SetMaterial(std::shared_ptr<Material> aMaterial);

private:
    Ui::MaterialViewer *ui;
};

#endif // MATERIALVIEWER_H
