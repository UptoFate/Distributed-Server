#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_START.h"

#include <qevent.h>
#include <QMainWindow>
#include <QVector>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QEasingCurve>
#include <QPoint>

#include "logindialog.h"
#include "registerdialog.h"
#include "MeshView/MeshView.h"

QT_BEGIN_NAMESPACE
namespace Ui { class STARTClass; };
QT_END_NAMESPACE

class START : public QMainWindow
{
    Q_OBJECT

private:
    int cornerRadius = 20;
    QWidget* border = nullptr;
    //QWidget* defaultPage;
    QGraphicsDropShadowEffect* windowShadow;
    QColor mainBackGround = QColor(251, 251, 251);

    void Init();

    enum {
        AT_LEFT = 1, AT_TOP = 2, AT_RIGHT = 4, AT_BOTTOM = 8,
        AT_TOP_LEFT = 3, AT_TOP_RIGHT = 6, AT_BOTTOM_LEFT = 9, AT_BOTTOM_RIGHT = 12
    };
    bool mousePressed = false;
    int mouseState;
    QPoint lastPos;
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event) {
        mousePressed = false;
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
        if (event->globalPosition().y() < 2)
            controlWindowScale();
#else
        if (event->globalPos().y() < 2)
            controlWindowScale();
#endif
    }
    void resizeEvent(QResizeEvent* event);

    bool maximized = false;
    QRect lastGeometry;
    void controlWindowScale();
    void switchWidget(QWidget* oldWidget, QWidget* newWidget);

public:
    START(QWidget *parent = nullptr);
    ~START();

private:
    Ui::STARTClass *ui;
    LoginDialog* _login_dlg;
    RegisterDialog* _reg_dlg;
    MeshView* _main_dlg;

public slots:
    void SlotSwitchReg();
    void SlotSwitchLogin();
    void SlotSwitchMain();
};
