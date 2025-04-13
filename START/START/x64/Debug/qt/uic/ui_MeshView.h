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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MeshViewClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_4;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_4;
    QWidget *modelContainer;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MeshViewClass)
    {
        if (MeshViewClass->objectName().isEmpty())
            MeshViewClass->setObjectName("MeshViewClass");
        MeshViewClass->resize(788, 576);
        MeshViewClass->setMinimumSize(QSize(788, 576));
        centralWidget = new QWidget(MeshViewClass);
        centralWidget->setObjectName("centralWidget");
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName("gridLayout_3");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(10, 10, 10, 10);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(10, 10, 10, 10);
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(10, 10, 10, 10);

        verticalLayout_3->addLayout(verticalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(10, 10, 10, 10);

        verticalLayout_3->addLayout(verticalLayout_2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_4);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(10, 10, 10, 10);

        verticalLayout_3->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_3->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(10, 10, 10, 10);
        modelContainer = new QWidget(centralWidget);
        modelContainer->setObjectName("modelContainer");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(modelContainer->sizePolicy().hasHeightForWidth());
        modelContainer->setSizePolicy(sizePolicy);
        modelContainer->setMinimumSize(QSize(400, 400));

        verticalLayout_4->addWidget(modelContainer);


        horizontalLayout_3->addLayout(verticalLayout_4);


        gridLayout_3->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        MeshViewClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MeshViewClass);
        statusBar->setObjectName("statusBar");
        statusBar->setEnabled(true);
        MeshViewClass->setStatusBar(statusBar);

        retranslateUi(MeshViewClass);

        QMetaObject::connectSlotsByName(MeshViewClass);
    } // setupUi

    void retranslateUi(QMainWindow *MeshViewClass)
    {
        MeshViewClass->setWindowTitle(QCoreApplication::translate("MeshViewClass", "MeshView", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MeshViewClass: public Ui_MeshViewClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESHVIEW_H
