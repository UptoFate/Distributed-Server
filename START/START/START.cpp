#include "START.h"

#include <QPainterPath>
#include <QRegion>
#include <QTimer>
#include "tcpMgr.h"

START::START(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::STARTClass()),_login_dlg(new LoginDialog(this))
{
    ///////////
    connect(_login_dlg, &LoginDialog::switchRegister, this, &START::SlotSwitchReg);
    ///////////


    ui->setupUi(this);
    ui->centralwidget->setMouseTracking(true);
#ifdef Q_OS_LINUX
    ui->verticalLayout->setContentsMargins(0, 0, 0, 0);
    cornerRadius = 0;
#endif

    QTimer* t = new QTimer(this);
    connect(t, &QTimer::timeout, this, [=]() {Init(); });
    t->setSingleShot(true);
    t->start(10);

    connect(ui->adjSizeBtn, &QPushButton::clicked, this, [=]() {controlWindowScale(); });

    //连接登录界面忘记密码信号
    //connect(_login_dlg, &LoginDialog::switchReset, this, &START::SlotSwitchReset);

    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_switch_maindlg, this, &START::SlotSwitchMain);

}

START::~START()
{
    delete ui;
}

void START::Init()
{
    //圆角
#ifdef Q_OS_LINUX
    QPainterPath path;
    path.addRect(ui->mainWidget->rect());
#else
    QPainterPath path;
    path.addRoundedRect(ui->mainWidget->rect(), cornerRadius - 1, cornerRadius - 1);
#endif
    //蒙版&阴影 mask
    QRegion mask(path.toFillPolygon().toPolygon());
    ui->mainWidget->setMask(mask);

    QString mainStyle;
    ui->mainWidget->setObjectName("mainWidget");
    mainStyle = "QWidget#mainWidget{background-color:" + mainBackGround.name() + QString::asprintf(";border-radius:%dpx", cornerRadius) + "}";
    ui->mainWidget->setStyleSheet(mainStyle);

#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
#ifdef Q_OS_WINDOWS
    windowShadow = new QGraphicsDropShadowEffect(this);
    windowShadow->setBlurRadius(30);
    windowShadow->setColor(QColor(0, 0, 0));
    windowShadow->setOffset(0, 0);
    ui->mainWidget->setGraphicsEffect(windowShadow);
#endif
#endif
    //圆角边框 border
#ifdef Q_OS_WINDOWS
    border = new QWidget(this);
    border->move(ui->mainWidget->pos() - QPoint(1, 1));
    border->resize(ui->mainWidget->size() + QSize(2, 2));
    QString borderStyle;
    borderStyle = "background-color:#00FFFFFF;border:1.5px solid #686868; border-radius:" + QString::asprintf("%d", cornerRadius) + "px";
    border->setStyleSheet(borderStyle);
    border->setAttribute(Qt::WA_TransparentForMouseEvents);
    border->show();
#endif

    ui->displayLayout->addWidget(_login_dlg);
    _reg_dlg = new RegisterDialog(this);
    ui->displayLayout->addWidget(_reg_dlg);
    ui->displayLayout->setAlignment(Qt::AlignCenter);
    _reg_dlg->hide();
    
}

void START::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        mousePressed = true;
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
        lastPos = event->globalPosition().toPoint() - this->frameGeometry().topLeft();
#else
        lastPos = event->globalPos() - this->frameGeometry().topLeft();
#endif
    }
}

void START::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() == Qt::NoButton)
        mousePressed = false;
    if (!mousePressed) {
        mouseState = 0;
        if (!maximized && abs(event->pos().x() - ui->mainWidget->pos().x()) < 5)
            mouseState |= AT_LEFT;
        if (!maximized && abs(event->pos().y() - ui->mainWidget->pos().y()) < 5)
            mouseState |= AT_TOP;
        if (!maximized && abs(event->pos().x() - ui->mainWidget->pos().x() - ui->mainWidget->width()) < 5)
            mouseState |= AT_RIGHT;
        if (!maximized && abs(event->pos().y() - ui->mainWidget->pos().y() - ui->mainWidget->height()) < 5)
            mouseState |= AT_BOTTOM;
        if (mouseState == AT_TOP_LEFT || mouseState == AT_BOTTOM_RIGHT)
            setCursor(Qt::SizeFDiagCursor);
        else if (mouseState == AT_TOP_RIGHT || mouseState == AT_BOTTOM_LEFT)
            setCursor(Qt::SizeBDiagCursor);
        else if (mouseState & (AT_LEFT | AT_RIGHT))
            setCursor(Qt::SizeHorCursor);
        else if (mouseState & (AT_TOP | AT_BOTTOM))
            setCursor(Qt::SizeVerCursor);
        else
            unsetCursor();
    }
    else {
        if (mouseState == 0) {
            if (maximized) {
                qreal wRatio = (double)event->pos().x() / (double)ui->mainWidget->width();
                controlWindowScale();
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
                this->move(QPoint(event->globalPosition().x() - ui->mainWidget->width() * wRatio, -30));
#else
                this->move(QPoint(event->globalPos().x() - ui->mainWidget->width() * wRatio, -30));
#endif
                lastPos = QPoint(ui->mainWidget->width() * wRatio, event->pos().y());
            }
            else
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
                this->move(event->globalPosition().toPoint() - lastPos);
#else
                this->move(event->globalPos() - lastPos);
#endif
        }
        else {
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
            QPoint d = event->globalPosition().toPoint() - frameGeometry().topLeft() - lastPos;
#else
            QPoint d = event->globalPos() - frameGeometry().topLeft() - lastPos;
#endif
            if (mouseState & AT_LEFT) {
                this->move(this->frameGeometry().x() + d.x(), this->frameGeometry().y());
                this->resize(this->width() - d.x(), this->height());
            }
            if (mouseState & AT_RIGHT) {
                this->resize(this->width() + d.x(), this->height());
            }
            if (mouseState & AT_TOP) {
                this->move(this->frameGeometry().x(), this->frameGeometry().y() + d.y());
                this->resize(this->width(), this->height() - d.y());
            }
            if (mouseState & AT_BOTTOM) {
                this->resize(this->width(), this->height() + d.y());
            }
        }
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
        lastPos = event->globalPosition().toPoint() - this->frameGeometry().topLeft();
#else
        lastPos = event->globalPos() - this->frameGeometry().topLeft();
#endif
    }
}

void START::resizeEvent(QResizeEvent* event) {
    //Resize border
    if (border)
        border->resize(ui->mainWidget->size() + QSize(2, 2));

    //Resize mask
    QPainterPath path;
#ifdef Q_OS_WINDOWS
    path.addRoundedRect(ui->mainWidget->rect(), cornerRadius - 1, cornerRadius - 1);
#else
    path.addRect(ui->mainWidget->rect());
#endif
    QRegion mask(path.toFillPolygon().toPolygon());
    ui->mainWidget->setMask(mask);

    //Resize all pages
//    for(int i = 0; i < pageList.size(); i++){
//        pageList[i]->resize(ui->mainWidget->width() * 0.4 < pageList[i]->preferWidth ? pageList[i]->preferWidth - 1 : ui->mainWidget->width() * 0.4 - 1, ui->mainWidget->height());
//        pageList[i]->resize(pageList[i]->width() + 1, pageList[i]->height());
//    }
}

void START::controlWindowScale() {
#ifdef Q_OS_WINDOWS
    if (!maximized) {
        lastGeometry = this->frameGeometry();
        windowShadow->setEnabled(false);
        ui->verticalLayout->setContentsMargins(0, 0, 0, 0);
        border->hide();
        QString mainStyle = "QWidget#mainWidget{background-color:" + mainBackGround.name() + ";border-radius:0px;}";
        ui->mainWidget->setStyleSheet(mainStyle);
        this->showMaximized();
        maximized = true;
        QPainterPath path;
        path.addRect(ui->mainWidget->rect());
        QRegion mask(path.toFillPolygon().toPolygon());
        ui->mainWidget->setMask(mask);
    }
    else {
        ui->verticalLayout->setContentsMargins(30, 30, 30, 30);
        this->showNormal();
        QString mainStyle = "QWidget#mainWidget{background-color:" + mainBackGround.name() + QString::asprintf(";border-radius:%dpx", cornerRadius) + "}";
        ui->mainWidget->setStyleSheet(mainStyle);
        QPainterPath path;
        path.addRoundedRect(ui->mainWidget->rect(), cornerRadius - 1, cornerRadius - 1);
        QRegion mask(path.toFillPolygon().toPolygon());
        ui->mainWidget->setMask(mask);
        border->show();
        windowShadow->setEnabled(true);
        this->resize(lastGeometry.width(), lastGeometry.height());
        this->move(lastGeometry.x(), lastGeometry.y());
        maximized = false;
    }
#endif
}

void START::SlotSwitchReg() {
    //setCentralWidget(_reg_dlg);

    
    connect(_reg_dlg, &RegisterDialog::sigSwitchLogin, this, &START::SlotSwitchLogin);

    //_login_dlg->hide();
    //_reg_dlg->show();
    switchWidget(_login_dlg, _reg_dlg);
}

void  START::SlotSwitchLogin()
{
    //_reg_dlg->hide();
    //_login_dlg->show();
    switchWidget(_reg_dlg, _login_dlg);

}

void START::SlotSwitchMain()
{
    _main_dlg = new MeshView(this);
    ui->displayLayout->addWidget(_main_dlg);
    _main_dlg->hide();
    switchWidget(_login_dlg, _main_dlg);
    delete _login_dlg;
    delete _reg_dlg;
}

void START::switchWidget(QWidget* oldWidget, QWidget* newWidget) {
    if (oldWidget == newWidget) return;

    QParallelAnimationGroup* group = new QParallelAnimationGroup(this);

    // 旧widget滑出动画
    //QPropertyAnimation* slideOutAnimation = new QPropertyAnimation(oldWidget, "pos");
    //slideOutAnimation->setDuration(500);
    //slideOutAnimation->setStartValue(oldWidget->pos());
    //slideOutAnimation->setEndValue(QPoint(-oldWidget->width(), 0));
    //slideOutAnimation->setEasingCurve(QEasingCurve::InOutExpo);
    oldWidget->hide();

    // 新widget滑入动画
    newWidget->show();
    newWidget->raise();
    QPropertyAnimation* slideInAnimation = new QPropertyAnimation(newWidget, "pos");
    slideInAnimation->setDuration(500);
    slideInAnimation->setStartValue(QPoint(ui->mainWidget->width(), 0));
    slideInAnimation->setEndValue(QPoint(0, 0));
    slideInAnimation->setEasingCurve(QEasingCurve::InOutExpo);

    //group->addAnimation(slideOutAnimation);
    group->addAnimation(slideInAnimation);

    connect(group, &QParallelAnimationGroup::finished, [=]() {
        //oldWidget->hide();
        delete group;
        });

    group->start();
}