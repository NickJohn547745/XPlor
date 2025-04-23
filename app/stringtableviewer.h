#ifndef STRINGTABLEVIEWER_H
#define STRINGTABLEVIEWER_H

#include "asset_structs.h"
#include <QWidget>

namespace Ui {
class StringTableViewer;
}

class StringTableViewer : public QWidget
{
    Q_OBJECT

public:
    explicit StringTableViewer(QWidget *parent = nullptr);
    ~StringTableViewer();

    void SetStringTable(std::shared_ptr<StringTable> aStringTable);

private:
    Ui::StringTableViewer *ui;
};

#endif // STRINGTABLEVIEWER_H
