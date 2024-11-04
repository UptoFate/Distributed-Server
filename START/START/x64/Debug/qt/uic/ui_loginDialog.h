/********************************************************************************
** Form generated from reading UI file 'loginDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ClickedLabel.h"

QT_BEGIN_NAMESPACE

class Ui_LoginDialogClass
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *err_tip;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *user_label;
    QLineEdit *user_edit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *pass_label;
    QLineEdit *pass_edit;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    ClickedLabel *forget_label;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *login_btn;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *reg_btn;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *LoginDialogClass)
    {
        if (LoginDialogClass->objectName().isEmpty())
            LoginDialogClass->setObjectName("LoginDialogClass");
        LoginDialogClass->resize(400, 300);
        LoginDialogClass->setMinimumSize(QSize(400, 300));
        LoginDialogClass->setMaximumSize(QSize(400, 300));
        verticalLayout_2 = new QVBoxLayout(LoginDialogClass);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(30, 10, 30, 10);
        err_tip = new QLabel(LoginDialogClass);
        err_tip->setObjectName("err_tip");
        err_tip->setMinimumSize(QSize(0, 20));
        err_tip->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(err_tip);

        widget = new QWidget(LoginDialogClass);
        widget->setObjectName("widget");

        verticalLayout->addWidget(widget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        user_label = new QLabel(LoginDialogClass);
        user_label->setObjectName("user_label");
        user_label->setMinimumSize(QSize(0, 25));
        user_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout->addWidget(user_label);

        user_edit = new QLineEdit(LoginDialogClass);
        user_edit->setObjectName("user_edit");
        user_edit->setMinimumSize(QSize(0, 25));
        user_edit->setMaximumSize(QSize(16777215, 25));

        horizontalLayout->addWidget(user_edit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pass_label = new QLabel(LoginDialogClass);
        pass_label->setObjectName("pass_label");
        pass_label->setMinimumSize(QSize(0, 25));
        pass_label->setMaximumSize(QSize(16777215, 25));
        pass_label->setSizeIncrement(QSize(0, 0));

        horizontalLayout_2->addWidget(pass_label);

        pass_edit = new QLineEdit(LoginDialogClass);
        pass_edit->setObjectName("pass_edit");
        pass_edit->setMinimumSize(QSize(0, 25));
        pass_edit->setMaximumSize(QSize(16777215, 25));
        pass_edit->setSizeIncrement(QSize(0, 0));

        horizontalLayout_2->addWidget(pass_edit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        forget_label = new ClickedLabel(LoginDialogClass);
        forget_label->setObjectName("forget_label");
        forget_label->setMinimumSize(QSize(0, 25));
        forget_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_3->addWidget(forget_label);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        login_btn = new QPushButton(LoginDialogClass);
        login_btn->setObjectName("login_btn");
        login_btn->setMinimumSize(QSize(100, 30));

        horizontalLayout_4->addWidget(login_btn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        reg_btn = new QPushButton(LoginDialogClass);
        reg_btn->setObjectName("reg_btn");
        reg_btn->setMinimumSize(QSize(100, 30));

        horizontalLayout_4->addWidget(reg_btn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(LoginDialogClass);

        QMetaObject::connectSlotsByName(LoginDialogClass);
    } // setupUi

    void retranslateUi(QDialog *LoginDialogClass)
    {
        LoginDialogClass->setWindowTitle(QCoreApplication::translate("LoginDialogClass", "LoginDialog", nullptr));
        err_tip->setText(QString());
        user_label->setText(QCoreApplication::translate("LoginDialogClass", "\347\224\250\346\210\267\345\220\215:", nullptr));
        pass_label->setText(QCoreApplication::translate("LoginDialogClass", "\345\257\206   \347\240\201:", nullptr));
        forget_label->setText(QCoreApplication::translate("LoginDialogClass", "\345\277\230\350\256\260\345\257\206\347\240\201", nullptr));
        login_btn->setText(QCoreApplication::translate("LoginDialogClass", "\347\231\273\345\275\225", nullptr));
        reg_btn->setText(QCoreApplication::translate("LoginDialogClass", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialogClass: public Ui_LoginDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
