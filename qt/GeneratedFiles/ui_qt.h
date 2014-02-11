/********************************************************************************
** Form generated from reading UI file 'qt.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_H
#define UI_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qtClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qtClass)
    {
        if (qtClass->objectName().isEmpty())
            qtClass->setObjectName(QStringLiteral("qtClass"));
        qtClass->resize(800, 600);
        centralWidget = new QWidget(qtClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        qtClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(qtClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        qtClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(qtClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        qtClass->setStatusBar(statusBar);

        retranslateUi(qtClass);

        QMetaObject::connectSlotsByName(qtClass);
    } // setupUi

    void retranslateUi(QMainWindow *qtClass)
    {
        qtClass->setWindowTitle(QApplication::translate("qtClass", "qt", 0));
    } // retranslateUi

};

namespace Ui {
    class qtClass: public Ui_qtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_H
