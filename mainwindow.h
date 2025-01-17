#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "enums.h"
#include "structs.h"
#include "utils.h"
#include "aboutdialog.h"
#include "compression.h"
#include "ffparser.h"
#include "zfparser.h"
#include "modelviewer.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QDebug>
#include <QTableWidgetItem>
#include <QTreeWidgetItem>
#include <QDockWidget>
#include <QPlainTextEdit>
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

    bool OpenZoneFile(const QString aZoneFilePath);
    bool OpenZoneFile();

    int LoadFile_D3DBSP(const QString aFilePath);

private:
    Ui::MainWindow *ui;
    QMap<QString, int> mTypeMap;
    QStringList mTypeOrder;
    quint32 mTagCount;
    quint32 mRecordCount;
    QMap<QString, QString> mRawFileMap;
    QMap<QString, QTreeWidgetItem*> mTreeMap;
    QMap<QString, QVector<QPair<QString, QString>>> mStrTableMap;

    QTreeWidget *mTreeWidget;
    QTreeWidgetItem *mRootItem;
    QPlainTextEdit *mScriptEditor;
    ModelViewer *mModelViewer;

    quint32 mBSPVersion;
    quint32 mDiskLumpCount;
    QVector<quint32> mDiskLumpOrder;
    QMap<quint32, Lump> mLumps;

};
#endif // MAINWINDOW_H
