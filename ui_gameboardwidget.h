/********************************************************************************
** Form generated from reading UI file 'gameboardwidget.ui'
**
** Created: Tue Nov 13 10:39:47 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEBOARDWIDGET_H
#define UI_GAMEBOARDWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameBoardWidget
{
public:

    void setupUi(QWidget *GameBoardWidget)
    {
        if (GameBoardWidget->objectName().isEmpty())
            GameBoardWidget->setObjectName(QString::fromUtf8("GameBoardWidget"));
        GameBoardWidget->resize(400, 300);

        retranslateUi(GameBoardWidget);

        QMetaObject::connectSlotsByName(GameBoardWidget);
    } // setupUi

    void retranslateUi(QWidget *GameBoardWidget)
    {
        GameBoardWidget->setWindowTitle(QApplication::translate("GameBoardWidget", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GameBoardWidget: public Ui_GameBoardWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEBOARDWIDGET_H
