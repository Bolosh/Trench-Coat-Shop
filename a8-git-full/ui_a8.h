/********************************************************************************
** Form generated from reading UI file 'a8.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_A8_H
#define UI_A8_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_a8Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *a8Class)
    {
        if (a8Class->objectName().isEmpty())
            a8Class->setObjectName("a8Class");
        a8Class->resize(600, 400);
        menuBar = new QMenuBar(a8Class);
        menuBar->setObjectName("menuBar");
        a8Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(a8Class);
        mainToolBar->setObjectName("mainToolBar");
        a8Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(a8Class);
        centralWidget->setObjectName("centralWidget");
        a8Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(a8Class);
        statusBar->setObjectName("statusBar");
        a8Class->setStatusBar(statusBar);

        retranslateUi(a8Class);

        QMetaObject::connectSlotsByName(a8Class);
    } // setupUi

    void retranslateUi(QMainWindow *a8Class)
    {
        a8Class->setWindowTitle(QCoreApplication::translate("a8Class", "a8", nullptr));
    } // retranslateUi

};

namespace Ui {
    class a8Class: public Ui_a8Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_A8_H
