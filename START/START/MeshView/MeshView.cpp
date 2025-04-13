#include "MeshView.h"

MeshView::MeshView(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // === 动态生成需要删除的控件 ===
    // 标签和输入框
    radiusLabel = new QLabel("Radius:", ui.centralWidget);
    radiusLineEdit = new QLineEdit(ui.centralWidget);
    xLabel = new QLabel("X:", ui.centralWidget);
    xLineEdit = new QLineEdit(ui.centralWidget);
    yLabel = new QLabel("Y:", ui.centralWidget);
    yLineEdit = new QLineEdit(ui.centralWidget);
    zLabel = new QLabel("Z:", ui.centralWidget);
    zLineEdit = new QLineEdit(ui.centralWidget);

    // 设置输入框大小
    radiusLineEdit->setFixedWidth(150);
    xLineEdit->setFixedWidth(150);
    yLineEdit->setFixedWidth(150);
    zLineEdit->setFixedWidth(150);

    // 按钮
    loadModelButtonA = new QPushButton("Load Model A", ui.centralWidget);
    loadModelButtonA->setFixedWidth(200);
    loadModelButtonB = new QPushButton("Load Model B", ui.centralWidget);
    loadModelButtonB->setFixedWidth(200);
    loadModelButtonC = new QPushButton("Load Model C", ui.centralWidget);
    loadModelButtonC->setFixedWidth(200);
    loadModelButtonD = new QPushButton("Load Model D", ui.centralWidget);
    loadModelButtonD->setFixedWidth(200);
    backButton = new QPushButton("Back", ui.centralWidget);
    backButton->setFixedWidth(200);
    generateModelButton = new QPushButton("Generate Model", ui.centralWidget);
    generateModelButton->setFixedWidth(200);

    // === 将动态控件添加到静态布局 ===
    // 输入框区域（GridLayout）
    ui.gridLayout->setHorizontalSpacing(10); // 设置标签和输入框之间的间距
    ui.gridLayout->addWidget(radiusLabel, 0, 0);
    ui.gridLayout->addWidget(radiusLineEdit, 0, 1);
    ui.gridLayout->addWidget(xLabel, 1, 0);
    ui.gridLayout->addWidget(xLineEdit, 1, 1);
    ui.gridLayout->addWidget(yLabel, 2, 0);
    ui.gridLayout->addWidget(yLineEdit, 2, 1);
    ui.gridLayout->addWidget(zLabel, 3, 0);
    ui.gridLayout->addWidget(zLineEdit, 3, 1);

    // 按钮区域（VerticalLayout）
    ui.verticalLayout->setAlignment(Qt::AlignCenter);
    ui.verticalLayout->addWidget(loadModelButtonA);
    ui.verticalLayout->addWidget(loadModelButtonB);
    ui.verticalLayout->addWidget(loadModelButtonC);
    ui.verticalLayout->addWidget(loadModelButtonD);

    ui.verticalLayout_2->setAlignment(Qt::AlignCenter);
    ui.verticalLayout_2->addWidget(backButton);
    ui.verticalLayout_2->addWidget(generateModelButton);

    // === 信号槽连接 ===
    connect(backButton, &QPushButton::clicked, this, &MeshView::onBackButtonClicked);
    connect(loadModelButtonA, &QPushButton::clicked, this, &MeshView::onLoadModelButtonAClicked);
    connect(xLineEdit, &QLineEdit::textChanged, this, &MeshView::validateInputs);
    connect(yLineEdit, &QLineEdit::textChanged, this, &MeshView::validateInputs);
    connect(zLineEdit, &QLineEdit::textChanged, this, &MeshView::validateInputs);
    connect(radiusLineEdit, &QLineEdit::textChanged, this, &MeshView::validateInputs);

    // === 设置初始状态 ===
    backButton->setEnabled(false);
    generateModelButton->setEnabled(false);
    loadModelButtonA->setEnabled(false);
    loadModelButtonB->setEnabled(false);
    loadModelButtonC->setEnabled(false);
    loadModelButtonD->setEnabled(false);
    isGenerateModelButtonEnable = false;
}

MeshView::~MeshView()
{
}

void MeshView::onLoadModelButtonAClicked() {
	
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Model File"),
        "",
        tr("3D Model Files (*.obj *.stl *.ply);;All Files (*)"));

    if (fileName.isEmpty()) {
        return;
    }
  
    try {
        if (m_3dWindow) {
            delete m_3dWindow;  // 会自动删除关联的 m_3dContainer
            m_3dWindow = nullptr;
        }


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
        
       
        /*backButton->show();
        generateModelButton->show();
        loadModelButtonA->hide();
        loadModelButtonB->hide();
        loadModelButtonC->hide();
        loadModelButtonD->hide();
        radiusLabel->hide();
        radiusLineEdit->hide();*/
        backButton->setEnabled(true);
        // 清空所有 LineEdit 的文本内容
        radiusLineEdit->clear();
        xLineEdit->clear();
        yLineEdit->clear();
        zLineEdit->clear();
       
        isGenerateModelButtonEnable = true;
    }
    catch (...) {
        QMessageBox::critical(this, tr("Error"), tr("Failed to load model file."));
    }
}
void MeshView::clearDynamicControls()
{

    // 删除标签和输入框
    delete radiusLabel;      radiusLabel = nullptr;
    delete radiusLineEdit;   radiusLineEdit = nullptr;
    delete xLabel;          xLabel = nullptr;
    delete xLineEdit;       xLineEdit = nullptr;
    delete yLabel;          yLabel = nullptr;
    delete yLineEdit;       yLineEdit = nullptr;
    delete zLabel;          zLabel = nullptr;
    delete zLineEdit;       zLineEdit = nullptr;

    // 删除按钮
    delete loadModelButtonA; loadModelButtonA = nullptr;
    delete loadModelButtonB; loadModelButtonB = nullptr;
    delete loadModelButtonC; loadModelButtonC = nullptr;
    delete loadModelButtonD; loadModelButtonD = nullptr;
    delete backButton;      backButton = nullptr;
    delete generateModelButton; generateModelButton = nullptr;
}
void MeshView::onBackButtonClicked() {
	/*backButton->hide();
    generateModelButton->hide();
	loadModelButtonA->show();
    loadModelButtonB->show();
	loadModelButtonC->show();
	loadModelButtonD->show();
    radiusLabel->show();
    radiusLineEdit->show();*/

    backButton->setEnabled(false);
    generateModelButton->setEnabled(false);
    isGenerateModelButtonEnable = false;
    radiusLineEdit->clear();
    xLineEdit->clear();
    yLineEdit->clear();
    zLineEdit->clear();
    if (m_3dWindow) {
        delete m_3dWindow;  // 会自动删除 m_3dContainer
        m_3dWindow = nullptr;
    }
    QLayout* layout = ui.modelContainer->layout();
    if (layout) {
        delete layout;
    }
}

void MeshView::validateInputs()
{
	bool xValid, yValid, zValid, radiusValid;
	xLineEdit->text().toFloat(&xValid);
    yLineEdit->text().toFloat(&yValid);
    zLineEdit->text().toFloat(&zValid);
    radiusLineEdit->text().toFloat(&radiusValid);
	if (xValid && yValid && zValid && radiusValid&& isGenerateModelButtonEnable==false) {
		loadModelButtonA->setEnabled(true);
        loadModelButtonB->setEnabled(true);
        loadModelButtonC->setEnabled(true);
        loadModelButtonD->setEnabled(true);
        generateModelButton->setEnabled(false);
	}
	else if (xValid && yValid && zValid && radiusValid && isGenerateModelButtonEnable == true) {
        loadModelButtonA->setEnabled(false);
        loadModelButtonB->setEnabled(false);
        loadModelButtonC->setEnabled(false);
        loadModelButtonD->setEnabled(false);
        generateModelButton->setEnabled(true);
	}
	else {
		loadModelButtonA->setEnabled(false);
		loadModelButtonB->setEnabled(false);
		loadModelButtonC->setEnabled(false);
		loadModelButtonD->setEnabled(false);
        generateModelButton->setEnabled(false);
	}
}
