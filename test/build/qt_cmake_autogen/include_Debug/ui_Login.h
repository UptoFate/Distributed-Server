/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginClass
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLineEdit *userNameEdit;
    QPushButton *Login;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *passWordEdit;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_8;
    QLineEdit *lineEditIP;
    QLineEdit *lineEditPort;
    QTextEdit *textEditRead;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LoginClass)
    {
        if (LoginClass->objectName().isEmpty())
            LoginClass->setObjectName("LoginClass");
        LoginClass->resize(600, 400);
        centralWidget = new QWidget(LoginClass);
        centralWidget->setObjectName("centralWidget");
        widget = new QWidget(centralWidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(140, 60, 254, 151));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        userNameEdit = new QLineEdit(widget);
        userNameEdit->setObjectName("userNameEdit");

        gridLayout->addWidget(userNameEdit, 0, 1, 1, 4);

        Login = new QPushButton(widget);
        Login->setObjectName("Login");

        gridLayout->addWidget(Login, 3, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(37, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 3, 4, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 5, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 3, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 5, 1, 1);

        passWordEdit = new QLineEdit(widget);
        passWordEdit->setObjectName("passWordEdit");

        gridLayout->addWidget(passWordEdit, 1, 1, 1, 4);

        horizontalSpacer_5 = new QSpacerItem(31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 3, 0, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 3, 3, 1, 1);

        lineEditIP = new QLineEdit(centralWidget);
        lineEditIP->setObjectName("lineEditIP");
        lineEditIP->setGeometry(QRect(200, 20, 113, 20));
        lineEditPort = new QLineEdit(centralWidget);
        lineEditPort->setObjectName("lineEditPort");
        lineEditPort->setGeometry(QRect(200, 50, 113, 20));
        textEditRead = new QTextEdit(centralWidget);
        textEditRead->setObjectName("textEditRead");
        textEditRead->setGeometry(QRect(140, 190, 311, 161));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(120, 20, 71, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(120, 50, 71, 16));
        LoginClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LoginClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 600, 22));
        LoginClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LoginClass);
        mainToolBar->setObjectName("mainToolBar");
        LoginClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LoginClass);
        statusBar->setObjectName("statusBar");
        LoginClass->setStatusBar(statusBar);

        retranslateUi(LoginClass);
        QObject::connect(Login, SIGNAL(clicked()), LoginClass, SLOT(pushButton1_Clicked()));

        QMetaObject::connectSlotsByName(LoginClass);
    } // setupUi

    void retranslateUi(QMainWindow *LoginClass)
    {
        LoginClass->setWindowTitle(QCoreApplication::translate("LoginClass", "Login", nullptr));
        Login->setText(QCoreApplication::translate("LoginClass", "Login", nullptr));
        lineEditIP->setText(QCoreApplication::translate("LoginClass", "192.168.88.129", nullptr));
        lineEditPort->setText(QCoreApplication::translate("LoginClass", "5050", nullptr));
        label->setText(QCoreApplication::translate("LoginClass", "Server ip:", nullptr));
        label_2->setText(QCoreApplication::translate("LoginClass", "Server port:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginClass: public Ui_LoginClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
