#include "xtreewidgetitem.h"

XTreeWidgetItem::XTreeWidgetItem(QTreeWidget *parent, bool group)
    : QTreeWidgetItem(parent), isGroup(group) {

}

XTreeWidgetItem::XTreeWidgetItem(QTreeWidgetItem *parent, bool group)
    : QTreeWidgetItem(parent), isGroup(group) {

}

bool XTreeWidgetItem::operator<(const QTreeWidgetItem &other) const {
    // Attempt to cast the other item to our custom type.
    const XTreeWidgetItem* otherItem = dynamic_cast<const XTreeWidgetItem*>(&other);
    if (otherItem) {
        if ((this->childCount() > 0) != (otherItem->childCount() > 0))
            return this->childCount() <= 0; // true if this item is a group and other is not
    }
    // Fallback to the default string comparison on the current sort column.
    return !QTreeWidgetItem::operator<(other);
}

XTreeWidgetItem& XTreeWidgetItem::operator=(const XTreeWidgetItem &other)
{
    if (this != &other) {
        // Copy text and icon for each column.
        const int colCount = other.columnCount();
        for (int i = 0; i < colCount; ++i) {
            setText(i, other.text(i));
            setIcon(i, other.icon(i));
        }
        // Copy custom members.
        this->isGroup = other.isGroup;
    }
    return *this;
}
