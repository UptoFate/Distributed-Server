#include "MeshView.h"

MeshView::MeshView(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

MeshView::~MeshView()
{
    if (m_3dWindow) {
        delete m_3dWindow;
        m_3dWindow = nullptr;
    }

    if (m_3dContainer) {
        delete m_3dContainer;
        m_3dContainer = nullptr;
    }
}

void MeshView::onLoadModelClicked() {
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Model File"),
        "",
        tr("3D Model Files (*.obj *.stl *.ply);;All Files (*)"));

    if (fileName.isEmpty()) {
        return;
    }
  
    try {
        // 1. 如果已有3D窗口，先清理旧资源
        //if (m_3dWindow) {
        //    delete m_3dWindow->rootEntity(); // 删除场景实体
        //    delete m_3dContainer->layout(); // 删除旧布局
        //}

        // 2. 创建Qt3D窗口并嵌入到预置的modelContainer中
        m_3dWindow = new Qt3DExtras::Qt3DWindow();
        m_3dContainer = QWidget::createWindowContainer(m_3dWindow, ui.modelContainer);
        m_3dContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        // 3. 设置容器布局（填充modelContainer）
        QVBoxLayout* layout = new QVBoxLayout(ui.modelContainer);
        layout->addWidget(m_3dContainer);
        layout->setContentsMargins(0, 0, 0, 0);


        // 创建场景根实体
        Qt3DCore::QEntity* rootEntity = new Qt3DCore::QEntity();

        // 添加网格组件
        Qt3DRender::QMesh* mesh = new Qt3DRender::QMesh(rootEntity);
        mesh->setSource(QUrl::fromLocalFile(fileName));

        // 添加材质
        Qt3DExtras::QPhongMaterial* material = new Qt3DExtras::QPhongMaterial(rootEntity);

        // 创建模型实体
        Qt3DCore::QEntity* modelEntity = new Qt3DCore::QEntity(rootEntity);
        modelEntity->addComponent(mesh);
        modelEntity->addComponent(material);

        // 设置相机
        Qt3DRender::QCamera* camera = m_3dWindow->camera();
        camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
        camera->setPosition(QVector3D(0, 0, 20));
        camera->setViewCenter(QVector3D(0, 0, 0));

        // 添加相机控制器
        Qt3DExtras::QOrbitCameraController* camController =
            new Qt3DExtras::QOrbitCameraController(rootEntity);
        camController->setLinearSpeed(50.0f);
        camController->setLookSpeed(180.0f);
        camController->setCamera(camera);

        m_3dWindow->setRootEntity(rootEntity);
    }
    catch (...) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to load model file."));
    }
}