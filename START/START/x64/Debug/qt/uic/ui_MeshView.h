/********************************************************************************
** Form generated from reading UI file 'MeshView.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESHVIEW_H
#define UI_MESHVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MeshViewClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QPushButton *loadModelButton;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer_5;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_4;
    QGridLayout *gridLayout_3;
    QWidget *modelContainer;
    QSpacerItem *horizontalSpacer_2;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MeshViewClass)
    {
        if (MeshViewClass->objectName().isEmpty())
            MeshViewClass->setObjectName("MeshViewClass");
        MeshViewClass->resize(788, 576);
        MeshViewClass->setMinimumSize(QSize(600, 450));
        centralWidget = new QWidget(MeshViewClass);
        centralWidget->setObjectName("centralWidget");
        gridLayout_4 = new QGridLayout(centralWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName("gridLayout_4");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(10, 10, 10, 10);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(10, 10, 10, 10);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(10, 10, 10, 10);
        loadModelButton = new QPushButton(centralWidget);
        loadModelButton->setObjectName("loadModelButton");

        verticalLayout->addWidget(loadModelButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout->addWidget(pushButton_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName("pushButton_3");

        verticalLayout->addWidget(pushButton_3);


        verticalLayout_3->addLayout(verticalLayout);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_5);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(10, 10, 10, 10);
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName("lineEdit_2");

        gridLayout->addWidget(lineEdit_2, 2, 1, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 0, 1, 1);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName("lineEdit");

        gridLayout->addWidget(lineEdit, 1, 1, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName("lineEdit_3");

        gridLayout->addWidget(lineEdit_3, 3, 1, 1, 1);

        lineEdit_4 = new QLineEdit(centralWidget);
        lineEdit_4->setObjectName("lineEdit_4");

        gridLayout->addWidget(lineEdit_4, 4, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);


        horizontalLayout->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(10, 10, 10, 10);
        modelContainer = new QWidget(centralWidget);
        modelContainer->setObjectName("modelContainer");
        modelContainer->setMinimumSize(QSize(400, 400));

        gridLayout_3->addWidget(modelContainer, 0, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_4->addLayout(horizontalLayout, 0, 0, 1, 1);

        MeshViewClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MeshViewClass);
        statusBar->setObjectName("statusBar");
        statusBar->setEnabled(true);
        MeshViewClass->setStatusBar(statusBar);

        retranslateUi(MeshViewClass);
        QObject::connect(loadModelButton, SIGNAL(clicked()), MeshViewClass, SLOT(onLoadModelClicked()));

        QMetaObject::connectSlotsByName(MeshViewClass);
    } // setupUi

    void retranslateUi(QMainWindow *MeshViewClass)
    {
        MeshViewClass->setWindowTitle(QCoreApplication::translate("MeshViewClass", "MeshView", nullptr));
        loadModelButton->setText(QCoreApplication::translate("MeshViewClass", "\350\275\275\345\205\245\346\250\241\345\236\213", nullptr));
        pushButton->setText(QCoreApplication::translate("MeshViewClass", "\345\217\257\351\200\211\346\231\266\350\203\236\347\261\273\345\236\2131", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MeshViewClass", "\345\217\257\351\200\211\346\231\266\350\203\236\347\261\273\345\236\2132", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MeshViewClass", "\345\217\257\351\200\211\346\231\266\350\203\236\347\261\273\345\236\2133", nullptr));
        label_3->setText(QCoreApplication::translate("MeshViewClass", "y:", nullptr));
        label_2->setText(QCoreApplication::translate("MeshViewClass", "x:", nullptr));
        label->setText(QCoreApplication::translate("MeshViewClass", "\345\215\212\345\276\204\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("MeshViewClass", "z:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MeshViewClass: public Ui_MeshViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESHVIEW_H
