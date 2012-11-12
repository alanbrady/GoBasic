/********************************************************************************
** Form generated from reading UI file 'gomain.ui'
**
** Created: Mon Nov 12 00:45:03 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GOMAIN_H
#define UI_GOMAIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GoMain
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GoMain)
    {
        if (GoMain->objectName().isEmpty())
            GoMain->setObjectName(QString::fromUtf8("GoMain"));
        GoMain->resize(686, 640);
        centralWidget = new QWidget(GoMain);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        GoMain->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GoMain);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 686, 21));
        GoMain->setMenuBar(menuBar);
        statusBar = new QStatusBar(GoMain);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GoMain->setStatusBar(statusBar);

        retranslateUi(GoMain);

        QMetaObject::connectSlotsByName(GoMain);
    } // setupUi

    void retranslateUi(QMainWindow *GoMain)
    {
        GoMain->setWindowTitle(QApplication::translate("GoMain", "GoMain", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GoMain: public Ui_GoMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GOMAIN_H
