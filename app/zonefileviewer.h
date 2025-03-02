#ifndef ZONEFILEVIEWER_H
#define ZONEFILEVIEWER_H

#include "zonefile.h"
#include "utils.h"

#include <QWidget>

namespace Ui {
class ZoneFileViewer;
}

class ZoneFileViewer : public QWidget
{
    Q_OBJECT

public:
    explicit ZoneFileViewer(QWidget *parent = nullptr);
    ~ZoneFileViewer();

    void SetZoneFile(std::shared_ptr<ZoneFile> aZoneFile);
private:
    Ui::ZoneFileViewer *ui;
    std::shared_ptr<ZoneFile> aZoneFile;
};

#endif // ZONEFILEVIEWER_H
