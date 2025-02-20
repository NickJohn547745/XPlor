#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "d3dbsp_structs.h"
#include "asset_structs.h"
#include "ddsviewer.h"
#include "fastfileviewer.h"
#include "ipak_structs.h"
#include "iwiviewer.h"
#include "localstringviewer.h"
#include "modelviewer.h"
#include "imagewidget.h"
#include "xtreewidget.h"
#include "zonefileviewer.h"
#include "techsetviewer.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QDebug>
#include <QTableWidgetItem>
#include <QTreeWidgetItem>
#include <QDockWidget>
#include <QPlainTextEdit>
#include <QMimeData>
#include <QProgressBar>
#include <windows.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Reset();

private slots:
    bool OpenFastFile(const QString aFastFilePath);
    bool OpenFastFile();

    bool OpenZoneFile(const QString aZoneFilePath, bool fromFF = false);
    bool OpenZoneFile();

    int LoadFile_D3DBSP(const QString aFilePath);
    int LoadFile_IPAK(const QString aFilePath);
    int LoadFile_XSUB(const QString aFilePath);
    int LoadFile_IWI(const QString aFilePath);
    int LoadFile_DDS(const QString aFilePath);
    int LoadFile_DDSFiles(const QStringList aFilePaths);

    void HandleStatusUpdate(const QString &message, int timeout);
    void HandleProgressUpdate(const QString &message, int progress, int max);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    Ui::MainWindow *ui;
    QMap<QString, int> mTypeMap;
    QStringList mTypeOrder;
    quint32 mTagCount;
    quint32 mRecordCount;
    QMap<QString, QString> mRawFileMap;
    QMap<QString, Image> mImageMap;
    QMap<QString, QTreeWidgetItem*> mTreeMap;
    QMap<QString, QVector<QPair<QString, QString>>> mStrTableMap;
    XTreeWidget *mTreeWidget;
    QProgressBar *mProgressBar;

    quint32 mBSPVersion;
    quint32 mDiskLumpCount;
    QVector<quint32> mDiskLumpOrder;
    QMap<quint32, Lump> mLumps;
};
#endif // MAINWINDOW_H
