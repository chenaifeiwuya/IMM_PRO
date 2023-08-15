/********************************************************************************
** Form generated from reading UI file 'cchatgroupitem.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CCHATGROUPITEM_H
#define UI_CCHATGROUPITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CChatGroupItem
{
public:
    QLabel *lb_icon;
    QLabel *lb_name;
    QLabel *lb_groupId;
    QLabel *label;

    void setupUi(QWidget *CChatGroupItem)
    {
        if (CChatGroupItem->objectName().isEmpty())
            CChatGroupItem->setObjectName(QStringLiteral("CChatGroupItem"));
        CChatGroupItem->resize(400, 80);
        CChatGroupItem->setMinimumSize(QSize(400, 80));
        CChatGroupItem->setMaximumSize(QSize(400, 80));
        lb_icon = new QLabel(CChatGroupItem);
        lb_icon->setObjectName(QStringLiteral("lb_icon"));
        lb_icon->setGeometry(QRect(20, 20, 40, 40));
        lb_icon->setMinimumSize(QSize(40, 40));
        lb_icon->setMaximumSize(QSize(40, 40));
        lb_icon->setPixmap(QPixmap(QString::fromUtf8("../../../colin3stage_os/Qt_FeiQAndImmCode/IM/images/qq151217-02.png")));
        lb_icon->setScaledContents(true);
        lb_name = new QLabel(CChatGroupItem);
        lb_name->setObjectName(QStringLiteral("lb_name"));
        lb_name->setGeometry(QRect(73, 20, 191, 20));
        lb_name->setMinimumSize(QSize(191, 20));
        lb_name->setMaximumSize(QSize(191, 20));
        lb_groupId = new QLabel(CChatGroupItem);
        lb_groupId->setObjectName(QStringLiteral("lb_groupId"));
        lb_groupId->setGeometry(QRect(70, 50, 201, 16));
        lb_groupId->setMinimumSize(QSize(201, 16));
        lb_groupId->setMaximumSize(QSize(201, 16));
        label = new QLabel(CChatGroupItem);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(280, 20, 81, 20));

        retranslateUi(CChatGroupItem);

        QMetaObject::connectSlotsByName(CChatGroupItem);
    } // setupUi

    void retranslateUi(QWidget *CChatGroupItem)
    {
        CChatGroupItem->setWindowTitle(QApplication::translate("CChatGroupItem", "Form", 0));
        lb_icon->setText(QString());
        lb_name->setText(QString());
        lb_groupId->setText(QString());
        label->setText(QApplication::translate("CChatGroupItem", "\347\276\244", 0));
    } // retranslateUi

};

namespace Ui {
    class CChatGroupItem: public Ui_CChatGroupItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CCHATGROUPITEM_H
