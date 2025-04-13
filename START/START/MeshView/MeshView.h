#pragma once

#include <QtWidgets/QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QGraphicsScene>  // 添加场景头文件
#include <QObject> 
#include <QFileDialog>
#include <QGraphicsView>
#include <QMessageBox>
#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qcamera.h>
#include <Qt3DExtras/qphongmaterial.h>
#include <Qt3DExtras/qorbitcameracontroller.h>
#include <Qt3DCore/qentity.h>
#include <QWidget>
#include "ui_MeshView.h"

class MeshView : public QMainWindow
{
    Q_OBJECT

public:
    MeshView(QWidget *parent = nullptr);
    ~MeshView();
private:
    Ui::MeshViewClass ui;
private:
    Qt3DExtras::Qt3DWindow* m_3dWindow = nullptr; // 需初始化
    QWidget* m_3dContainer = nullptr;
    QLabel* radiusLabel;
    QLineEdit* radiusLineEdit;
    QLabel* xLabel;
    QLineEdit* xLineEdit;
    QLabel* yLabel;
    QLineEdit* yLineEdit;
    QLabel* zLabel;
    QLineEdit* zLineEdit;
    QPushButton* loadModelButtonA;
    QPushButton* loadModelButtonB;
    QPushButton* loadModelButtonC;
    QPushButton* loadModelButtonD;
    QPushButton* backButton;
    QPushButton* generateModelButton;
	bool isGenerateModelButtonEnable;
    void clearDynamicControls();
private slots:
    void onLoadModelButtonAClicked();
    void onBackButtonClicked();
    void validateInputs();
};
