#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "enums.h"
#include "structs.h"
#include "utils.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>
#include <QDebug>
#include <QTableWidgetItem>
#include <QTreeWidgetItem>
#include <QSettings>
#include <QQueue>

#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>>

#include <Qt3DInput/QInputAspect>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DRender/QGeometryRenderer>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DRender/qcamera.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtGui/QScreen>

#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qtechnique.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/qpointlight.h>

#include <Qt3DCore/qtransform.h>
#include <Qt3DCore/qaspectengine.h>

#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DExtras/qforwardrenderer.h>

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>

#include <Qt3DExtras/QNormalDiffuseMapMaterial>

#include <windows.h>
#include <dxcapi.h>
#include <atlbase.h>
#include <atlcom.h>

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

    QByteArray DecompressZLIB(QByteArray compressedData);

private slots:
    void on_pushButton_FastFile_clicked();
    void on_pushButton_ZoneFile_clicked();

    void LogOpenedFile(QString aFileName);
    void RefreshRecentFileMenu();

    QString GetFastFilePath();
    QString GetZoneFilePath();

    QByteArray OpenFastFile(QString aFastFilePath);
    QByteArray OpenZoneFile(QString aZoneFilePath);

    void ParseFFHeader(QByteArray aFastFileData);
    void ParseFFCompany(QDataStream *aFastFileStream);
    void ParseFFFileType(QDataStream *afastFileStream);
    void ParseFFSignage(QDataStream *afastFileStream);
    void ParseFFMagic(QDataStream *afastFileStream);
    void ParseFFVersion(QDataStream *afastFileStream);

    void ParseZoneFile(QByteArray aDecompressedData);
    void ParseZoneHeader(QDataStream *aZoneFileStream);
    void ParseZoneSize(QDataStream *aZoneFileStream);

    void ParseZoneUnknownsA(QDataStream *aZoneFileStream);
    void ParseZoneUnknownsB(QDataStream *aZoneFileStream);
    void ParseZoneUnknownsC(QDataStream *aZoneFileStream);
    void ParseZoneTagCount(QDataStream *aZoneFileStream);
    void ParseZoneRecordCount(QDataStream *aZoneFileStream);
    void ParseZoneTags(QDataStream *aZoneFileStream);
    void ParseZoneIndex(QDataStream *aZoneFileStream);

    void ParseAsset_XAnim(QDataStream *aZoneFileStream);
    void ParseAsset_XModel(QDataStream *aZoneFileStream);
    void ParseAsset_Material(QDataStream *aZoneFileStream);
    void ParseAsset_TechSet(QDataStream *aZoneFileStream);
    void ParseAsset_LoadedSound(QDataStream *aZoneFileStream);
    void ParseAsset_ColMapMP(QDataStream *aZoneFileStream);
    void ParseAsset_PixelShader(QDataStream *aZoneFileStream);
    void ParseAsset_D3DBSP(QDataStream *aZoneFileStream);
    void ParseAsset_Font(QDataStream *aZoneFileStream);
    void ParseAsset_MenuFile(QDataStream *aZoneFileStream);
    void ParseAsset_LocalString(QDataStream *aZoneFileStream);
    void ParseAsset_Weapon(QDataStream *aZoneFileStream);
    void ParseAsset_FX(QDataStream *aZoneFileStream);
    void ParseAsset_RawFile(QDataStream *aZoneFileStream);
    void ParseAsset_StringTable(QDataStream *aZoneFileStream);

    int LoadFile_D3DBSP(const QString aFilePath);

    void ScriptSelected();
    void StrTableSelected(QString aStrTableName);

private:
    Ui::MainWindow *ui;
    QMap<QString, int> mTypeMap;
    QStringList mTypeOrder;
    quint32 mTagCount;
    quint32 mRecordCount;
    QMap<QString, QString> mRawFileMap;
    QMap<QString, QTreeWidgetItem*> mTreeMap;
    QMap<QString, QVector<QPair<QString, QString>>> mStrTableMap;
    QQueue<QString> mRecentFiles;
    bool mSettingsValid;

    QVector<QAction*> mRecentFileActions;

    quint32 mBSPVersion;
    quint32 mDiskLumpCount;
    QVector<quint32> mDiskLumpOrder;
    QMap<quint32, Lump> mLumps;

};
#endif // MAINWINDOW_H
