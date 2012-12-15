/********************************************************************************
** Form generated from reading UI file 'gomain.ui'
**
** Created: Fri Dec 14 21:54:35 2012
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
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GoMain
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GoMain)
    {
        if (GoMain->objectName().isEmpty())
            GoMain->setObjectName(QString::fromUtf8("GoMain"));
        GoMain->resize(409, 312);
        centralWidget = new QWidget(GoMain);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        GoMain->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(GoMain);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 409, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        GoMain->setMenuBar(menuBar);
        statusBar = new QStatusBar(GoMain);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GoMain->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());

        retranslateUi(GoMain);

        QMetaObject::connectSlotsByName(GoMain);
    } // setupUi

    void retranslateUi(QMainWindow *GoMain)
    {
        GoMain->setWindowTitle(QApplication::translate("GoMain", "GoMain", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("GoMain", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GoMain: public Ui_GoMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GOMAIN_H
