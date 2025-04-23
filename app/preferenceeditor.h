#ifndef PREFERENCEEDITOR_H
#define PREFERENCEEDITOR_H

#include <QDialog>

namespace Ui {
class PreferenceEditor;
}

class PreferenceEditor : public QDialog
{
    Q_OBJECT

public:
    explicit PreferenceEditor(QWidget *parent = nullptr);
    ~PreferenceEditor();

private:
    Ui::PreferenceEditor *ui;
};

#endif // PREFERENCEEDITOR_H
