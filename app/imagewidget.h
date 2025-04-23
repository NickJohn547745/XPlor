#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include "enums.h"
#include "dds_structs.h"
#include "d3dbsp_structs.h"
#include "asset_structs.h"
#include "ipak_structs.h"

#include <QWidget>

namespace Ui {
class ImageWidget;
}

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget *parent = nullptr);
    ~ImageWidget();

    void SetImage(std::shared_ptr<Image> aImage);
    std::shared_ptr<Image> GetImage();

private:
    std::shared_ptr<Image> mImage;
    Ui::ImageWidget *ui;
};

#endif // IMAGEWIDGET_H
