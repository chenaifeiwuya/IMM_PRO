/********************************************************************************
** Form generated from reading UI file 'cgroupchat.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CGROUPCHAT_H
#define UI_CGROUPCHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_CGroupChat
{
public:
    QTextEdit *te_enter;
    QTextBrowser *tb_chathistory;
    QPushButton *pb_send;

    void setupUi(QDialog *CGroupChat)
    {
        if (CGroupChat->objectName().isEmpty())
            CGroupChat->setObjectName(QStringLiteral("CGroupChat"));
        CGroupChat->resize(708, 477);
        te_enter = new QTextEdit(CGroupChat);
        te_enter->setObjectName(QStringLiteral("te_enter"));
        te_enter->setGeometry(QRect(0, 320, 711, 121));
        tb_chathistory = new QTextBrowser(CGroupChat);
        tb_chathistory->setObjectName(QStringLiteral("tb_chathistory"));
        tb_chathistory->setGeometry(QRect(0, 0, 711, 311));
        pb_send = new QPushButton(CGroupChat);
        pb_send->setObjectName(QStringLiteral("pb_send"));
        pb_send->setGeometry(QRect(270, 450, 93, 28));

        retranslateUi(CGroupChat);

        QMetaObject::connectSlotsByName(CGroupChat);
    } // setupUi

    void retranslateUi(QDialog *CGroupChat)
    {
        CGroupChat->setWindowTitle(QApplication::translate("CGroupChat", "Dialog", 0));
        pb_send->setText(QApplication::translate("CGroupChat", "Send", 0));
    } // retranslateUi

};

namespace Ui {
    class CGroupChat: public Ui_CGroupChat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CGROUPCHAT_H
