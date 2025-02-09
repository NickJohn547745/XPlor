#include "modelviewer.h"

ModelViewer::ModelViewer(QWidget *parent)
    : QWidget{parent} {
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));

    QWidget *container = QWidget::createWindowContainer(view);
    QSize screenSize = view->screen()->size();
    container->setMinimumSize(QSize(200, 100));
    container->setMaximumSize(screenSize);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignTop);
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);

    // Root entity
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity();

    // Camera
    Qt3DRender::QCamera *cameraEntity = view->camera();

    cameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    cameraEntity->setPosition(QVector3D(0, 0, 50.0f)); // Move farther along Z-axis
    cameraEntity->setUpVector(QVector3D(0, 1, 0));
    cameraEntity->setViewCenter(QVector3D(0, 0, 0));

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    lightEntity->addComponent(light);

    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(cameraEntity->position());
    lightEntity->addComponent(lightTransform);

    // For camera controls
    Qt3DExtras::QFirstPersonCameraController *camController = new Qt3DExtras::QFirstPersonCameraController(rootEntity);
    camController->setCamera(cameraEntity);

    // Set root object of the scene
    view->setRootEntity(rootEntity);

    // Load custom 3D model
    Qt3DRender::QMesh *customMesh = new Qt3DRender::QMesh();
    customMesh->setSource(QUrl::fromLocalFile(":/obj/data/obj/defaultactor_LOD0.obj"));

    // Adjust the model transformation
    Qt3DCore::QTransform *customTransform = new Qt3DCore::QTransform();
    customTransform->setRotationX(-90);
    customTransform->setRotationY(-90);

    // Keep translation if necessary
    customTransform->setTranslation(QVector3D(0.0f, -100.0f, -200.0f));

    Qt3DExtras::QNormalDiffuseMapMaterial *customMaterial = new Qt3DExtras::QNormalDiffuseMapMaterial();

    Qt3DRender::QTextureLoader *normalMap = new Qt3DRender::QTextureLoader();
    normalMap->setSource(QUrl::fromLocalFile(":/obj/data/obj/normalmap.png"));
    customMaterial->setNormal(normalMap);

    Qt3DRender::QTextureLoader *diffuseMap = new Qt3DRender::QTextureLoader();
    diffuseMap->setSource(QUrl::fromLocalFile(":/obj/data/obj/diffusemap.png"));
    customMaterial->setDiffuse(diffuseMap);

    Qt3DCore::QEntity *m_torusEntity = new Qt3DCore::QEntity(rootEntity);
    m_torusEntity->addComponent(customMesh);
    m_torusEntity->addComponent(customMaterial);
    m_torusEntity->addComponent(customTransform);
}
