#ifndef XTREEWIDGETITEM_H
#define XTREEWIDGETITEM_H

#include <QTreeWidget>
#include <QTreeWidgetItem>

// Custom item class
class XTreeWidgetItem : public QTreeWidgetItem
{
public:
    // Flag to indicate if the item is a collapsible group/header.
    bool isGroup;

    // Constructors: default to non-group unless specified.
    XTreeWidgetItem(QTreeWidget *parent, bool group = false);
    XTreeWidgetItem(QTreeWidgetItem *parent, bool group = false);

    // Override the less-than operator to customize sorting.
    bool operator<(const QTreeWidgetItem &other) const override;
    XTreeWidgetItem &operator =(const XTreeWidgetItem &other);
};


#endif // XTREEWIDGETITEM_H
