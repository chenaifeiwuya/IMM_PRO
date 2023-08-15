/********************************************************************************
** Form generated from reading UI file 'cfriendlist.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CFRIENDLIST_H
#define UI_CFRIENDLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CFriendList
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lb_name;
    QLabel *lb_icon;
    QLabel *lb_signed;
    QPushButton *pb_addFriend;
    QTabWidget *tbWidget_friend;
    QWidget *tb_online;
    QScrollArea *sca_online;
    QWidget *sca_inOnline;
    QVBoxLayout *verticalLayout_3;
    QWidget *wdg_online;
    QSpacerItem *verticalSpacer;
    QWidget *tb_offline;
    QScrollArea *sca_offline;
    QWidget *sca_inOffline;
    QVBoxLayout *verticalLayout_2;
    QWidget *wdg_offline;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *CFriendList)
    {
        if (CFriendList->objectName().isEmpty())
            CFriendList->setObjectName(QStringLiteral("CFriendList"));
        CFriendList->resize(467, 595);
        verticalLayout = new QVBoxLayout(CFriendList);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lb_name = new QLabel(CFriendList);
        lb_name->setObjectName(QStringLiteral("lb_name"));
        lb_name->setMinimumSize(QSize(150, 20));
        lb_name->setMaximumSize(QSize(150, 20));

        verticalLayout->addWidget(lb_name);

        lb_icon = new QLabel(CFriendList);
        lb_icon->setObjectName(QStringLiteral("lb_icon"));
        lb_icon->setMinimumSize(QSize(50, 50));
        lb_icon->setMaximumSize(QSize(50, 16777215));
        lb_icon->setScaledContents(true);

        verticalLayout->addWidget(lb_icon);

        lb_signed = new QLabel(CFriendList);
        lb_signed->setObjectName(QStringLiteral("lb_signed"));

        verticalLayout->addWidget(lb_signed);

        pb_addFriend = new QPushButton(CFriendList);
        pb_addFriend->setObjectName(QStringLiteral("pb_addFriend"));
        pb_addFriend->setMaximumSize(QSize(100, 16777215));
        QIcon icon;
        icon.addFile(QStringLiteral(":/tx/a3f92ae9_E771320_0737bafa.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_addFriend->setIcon(icon);
        pb_addFriend->setIconSize(QSize(20, 20));
        pb_addFriend->setCheckable(false);

        verticalLayout->addWidget(pb_addFriend);

        tbWidget_friend = new QTabWidget(CFriendList);
        tbWidget_friend->setObjectName(QStringLiteral("tbWidget_friend"));
        tb_online = new QWidget();
        tb_online->setObjectName(QStringLiteral("tb_online"));
        sca_online = new QScrollArea(tb_online);
        sca_online->setObjectName(QStringLiteral("sca_online"));
        sca_online->setGeometry(QRect(-1, 6, 430, 431));
        sca_online->setWidgetResizable(true);
        sca_inOnline = new QWidget();
        sca_inOnline->setObjectName(QStringLiteral("sca_inOnline"));
        sca_inOnline->setGeometry(QRect(0, 0, 400, 429));
        sca_inOnline->setMaximumSize(QSize(400, 16777215));
        verticalLayout_3 = new QVBoxLayout(sca_inOnline);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        wdg_online = new QWidget(sca_inOnline);
        wdg_online->setObjectName(QStringLiteral("wdg_online"));
        wdg_online->setMinimumSize(QSize(0, 51));
        wdg_online->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_3->addWidget(wdg_online);

        verticalSpacer = new QSpacerItem(375, 346, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        sca_online->setWidget(sca_inOnline);
        tbWidget_friend->addTab(tb_online, QString());
        tb_offline = new QWidget();
        tb_offline->setObjectName(QStringLiteral("tb_offline"));
        sca_offline = new QScrollArea(tb_offline);
        sca_offline->setObjectName(QStringLiteral("sca_offline"));
        sca_offline->setGeometry(QRect(-1, 6, 430, 431));
        sca_offline->setMaximumSize(QSize(485, 491));
        sca_offline->setWidgetResizable(true);
        sca_inOffline = new QWidget();
        sca_inOffline->setObjectName(QStringLiteral("sca_inOffline"));
        sca_inOffline->setGeometry(QRect(0, 0, 400, 429));
        sca_inOffline->setMaximumSize(QSize(400, 16777215));
        verticalLayout_2 = new QVBoxLayout(sca_inOffline);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        wdg_offline = new QWidget(sca_inOffline);
        wdg_offline->setObjectName(QStringLiteral("wdg_offline"));
        wdg_offline->setMinimumSize(QSize(406, 51));
        wdg_offline->setMaximumSize(QSize(406, 16777215));

        verticalLayout_2->addWidget(wdg_offline);

        verticalSpacer_2 = new QSpacerItem(20, 406, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        sca_offline->setWidget(sca_inOffline);
        tbWidget_friend->addTab(tb_offline, QString());

        verticalLayout->addWidget(tbWidget_friend);


        retranslateUi(CFriendList);

        tbWidget_friend->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CFriendList);
    } // setupUi

    void retranslateUi(QWidget *CFriendList)
    {
        CFriendList->setWindowTitle(QApplication::translate("CFriendList", "Form", 0));
        lb_name->setText(QApplication::translate("CFriendList", "name", 0));
        lb_icon->setText(QApplication::translate("CFriendList", "icon", 0));
        lb_signed->setText(QApplication::translate("CFriendList", "\350\277\231\344\270\252\345\256\266\344\274\231\345\276\210\346\207\222\357\274\214\344\273\200\344\271\210\344\271\237\346\262\241\347\225\231\344\270\213", 0));
        pb_addFriend->setText(QString());
        tbWidget_friend->setTabText(tbWidget_friend->indexOf(tb_online), QApplication::translate("CFriendList", "\345\234\250\347\272\277\345\245\275\345\217\213", 0));
        tbWidget_friend->setTabText(tbWidget_friend->indexOf(tb_offline), QApplication::translate("CFriendList", "\347\246\273\347\272\277\345\245\275\345\217\213", 0));
    } // retranslateUi

};

namespace Ui {
    class CFriendList: public Ui_CFriendList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CFRIENDLIST_H
