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
        bool thisIsGroup = this->childCount() > 0;
        bool otherIsGroup = otherItem->childCount() > 0;

        if (thisIsGroup != otherIsGroup) {
            return otherIsGroup; // Groups should come before non-groups
        }
    }
    // Fallback to the default string comparison on the current sort column.
    return QTreeWidgetItem::operator<(other);
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
