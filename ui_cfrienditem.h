/********************************************************************************
** Form generated from reading UI file 'cfrienditem.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CFRIENDITEM_H
#define UI_CFRIENDITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CFriendItem
{
public:
    QLabel *lb_icon;
    QLabel *lb_name;
    QLabel *lb_signed;

    void setupUi(QWidget *CFriendItem)
    {
        if (CFriendItem->objectName().isEmpty())
            CFriendItem->setObjectName(QStringLiteral("CFriendItem"));
        CFriendItem->resize(400, 80);
        CFriendItem->setMinimumSize(QSize(400, 80));
        CFriendItem->setMaximumSize(QSize(400, 80));
        lb_icon = new QLabel(CFriendItem);
        lb_icon->setObjectName(QStringLiteral("lb_icon"));
        lb_icon->setGeometry(QRect(11, 11, 40, 40));
        lb_icon->setMinimumSize(QSize(40, 40));
        lb_icon->setMaximumSize(QSize(40, 40));
        lb_icon->setScaledContents(true);
        lb_name = new QLabel(CFriendItem);
        lb_name->setObjectName(QStringLiteral("lb_name"));
        lb_name->setGeometry(QRect(58, 11, 171, 16));
        lb_signed = new QLabel(CFriendItem);
        lb_signed->setObjectName(QStringLiteral("lb_signed"));
        lb_signed->setGeometry(QRect(60, 30, 331, 31));

        retranslateUi(CFriendItem);

        QMetaObject::connectSlotsByName(CFriendItem);
    } // setupUi

    void retranslateUi(QWidget *CFriendItem)
    {
        CFriendItem->setWindowTitle(QApplication::translate("CFriendItem", "Form", 0));
        lb_icon->setText(QApplication::translate("CFriendItem", "icon", 0));
        lb_name->setText(QApplication::translate("CFriendItem", "name", 0));
        lb_signed->setText(QApplication::translate("CFriendItem", "signed", 0));
    } // retranslateUi

};

namespace Ui {
    class CFriendItem: public Ui_CFriendItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CFRIENDITEM_H
