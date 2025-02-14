#ifndef XTREEWIDGET_H
#define XTREEWIDGET_H

#include "d3dbsp_structs.h"
#include "asset_structs.h"
#include "ddsfile.h"
#include "iwifile.h"
#include "fastfile.h"
#include "xtreewidgetitem.h"
#include "zonefile.h"

#include <QTreeWidget>

class XTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit XTreeWidget(QWidget *parent = nullptr);
    ~XTreeWidget();

    void AddFastFile(std::shared_ptr<FastFile> aFastFile);
    void AddZoneFile(std::shared_ptr<ZoneFile> aZoneFile, XTreeWidgetItem *aParentItem = nullptr);
    void AddIWIFile(std::shared_ptr<IWIFile> aIWIFile);
    void AddDDSFile(std::shared_ptr<DDSFile> aDDSFile);

signals:
    void DDSFileSelected(std::shared_ptr<DDSFile> aDDSFile);
    void IWIFileSelected(std::shared_ptr<IWIFile> aIWIFile);
    void FastFileSelected(std::shared_ptr<FastFile> aFastFile);
    void ZoneFileSelected(std::shared_ptr<ZoneFile> aZoneFile);
    void LocalStringSelected(std::shared_ptr<ZoneFile> aZoneFile);
    void RawFileSelected(std::shared_ptr<RawFile> aRawFile);
    void ImageSelected(std::shared_ptr<Image> aImage);
    void TechSetSelected(std::shared_ptr<TechSet> aZoneFile);
    void StrTableSelected(std::shared_ptr<StringTable> aStrTable);
    void MenuSelected(std::shared_ptr<Menu> aMenu);
    void SoundSelected(std::shared_ptr<Sound> aSound);
    void TabSelected(const QString aTabName);
    void Cleared();

protected:
    void ItemSelectionChanged();
    void PrepareContextMenu(const QPoint &pos);

private:
    QMap<QString, std::shared_ptr<FastFile>> mFastFiles;
    QMap<QString, std::shared_ptr<ZoneFile>> mZoneFiles;
    QMap<QString, std::shared_ptr<DDSFile>> mDDSFiles;
    QMap<QString, std::shared_ptr<IWIFile>> mIWIFiles;

    ZoneFile pFindZoneFile(const QString aFilePart);
    FastFile pFindFastFile(const QString aFilePart);
};

#endif // XTREEWIDGET_H
