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

    std::shared_ptr<ZoneFile> FindZoneFile(const QString aStem);
    std::shared_ptr<FastFile> FindFastFile(const QString aStem);

    bool HasZoneFile(const QString aStem);
    bool HasFastFile(const QString aStem);

    void CloseFastFile(const QString aFFName);
signals:
    void DDSFileSelected(std::shared_ptr<DDSFile> aDDSFile, const QString aParentName);
    void IWIFileSelected(std::shared_ptr<IWIFile> aIWIFile, const QString aParentName);
    void FastFileSelected(std::shared_ptr<FastFile> aFastFile, const QString aParentName);
    void ZoneFileSelected(std::shared_ptr<ZoneFile> aZoneFile, const QString aParentName);
    void LocalStringSelected(std::shared_ptr<ZoneFile> aZoneFile, const QString aParentName);
    void RawFileSelected(std::shared_ptr<RawFile> aRawFile, const QString aParentName);
    void ImageSelected(std::shared_ptr<Image> aImage, const QString aParentName);
    void TechSetSelected(std::shared_ptr<TechSet> aZoneFile, const QString aParentName);
    void StrTableSelected(std::shared_ptr<StringTable> aStrTable, const QString aParentName);
    void MenuSelected(std::shared_ptr<Menu> aMenu, const QString aParentName);
    void SoundSelected(std::shared_ptr<Sound> aSound, const QString aParentName);
    void MaterialSelected(std::shared_ptr<Material> aMaterial, const QString aParentName);
    void ItemSelected(const QString itemText);

    void ItemClosed(const QString itemText);
    void Cleared();

protected:
    void ItemSelectionChanged();
    void PrepareContextMenu(const QPoint &pos);

private:
    QMap<QString, std::shared_ptr<FastFile>> mFastFiles;
    QMap<QString, std::shared_ptr<ZoneFile>> mZoneFiles;
    QMap<QString, std::shared_ptr<DDSFile>> mDDSFiles;
    QMap<QString, std::shared_ptr<IWIFile>> mIWIFiles;
};

#endif // XTREEWIDGET_H
