#ifndef MODELVIEWER_H
#define MODELVIEWER_H

#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QCommandLinkButton>
#include <QScreen>
#include <QHBoxLayout>
#include <QVBoxLayout>

// Qt3DCore includes
#include <QEntity>
#include <QTransform>
#include <QAspectEngine>
#include <qtransform.h>
#include <qaspectengine.h>
#include <qentity.h>
// Qt3DInput includes
#include <QInputAspect>
// Qt3DRender includes
#include <QRenderAspect>
#include <QGeometryRenderer>
#include <QCamera>
#include <QCameraLens>
#include <QMesh>
#include <QTechnique>
#include <QMaterial>
#include <QEffect>
#include <QTexture>
#include <QRenderPass>
#include <QSceneLoader>
#include <QPointLight>
// Qt3DExtras includes
#include <Qt3DWindow>
#include <QFirstPersonCameraController>
#include <QNormalDiffuseMapMaterial>
#include <QForwardRenderer>
#include <QPhongMaterial>
#include <QSphereMesh>
#include <QTorusMesh>

class ModelViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ModelViewer(QWidget *parent = nullptr);

signals:
};

#endif // MODELVIEWER_H
