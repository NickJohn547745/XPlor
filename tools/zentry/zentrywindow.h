#ifndef ZENTRYWINDOW_H
#define ZENTRYWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMimeData>
#include <QDragEnterEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class ZentryWindow;
}
QT_END_NAMESPACE

class ZentryWindow : public QMainWindow
{
    Q_OBJECT

public:
    ZentryWindow(QWidget *parent = nullptr);
    ~ZentryWindow();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    Ui::ZentryWindow *ui;
};
#endif // ZENTRYWINDOW_H
