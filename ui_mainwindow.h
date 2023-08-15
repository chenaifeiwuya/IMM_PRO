/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *Login;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QFormLayout *formLayout_login;
    QLabel *lb_tel_login;
    QLineEdit *le_tel_login;
    QLabel *lb_password_login;
    QLineEdit *le_password_login;
    QPushButton *pb_login;
    QWidget *Register;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout_register;
    QLineEdit *le_tel_register;
    QLabel *lb_name_register;
    QLineEdit *le_name_register;
    QLabel *lb_password_register;
    QLineEdit *le_password_register;
    QLabel *lb_tel_register;
    QPushButton *pb_register;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(412, 310);
        MainWindow->setMinimumSize(QSize(412, 310));
        MainWindow->setMaximumSize(QSize(412, 310));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(394, 255));
        tabWidget->setMaximumSize(QSize(394, 255));
        tabWidget->setElideMode(Qt::ElideLeft);
        Login = new QWidget();
        Login->setObjectName(QStringLiteral("Login"));
        layoutWidget = new QWidget(Login);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 80, 241, 129));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        formLayout_login = new QFormLayout();
        formLayout_login->setSpacing(6);
        formLayout_login->setObjectName(QStringLiteral("formLayout_login"));
        lb_tel_login = new QLabel(layoutWidget);
        lb_tel_login->setObjectName(QStringLiteral("lb_tel_login"));
        lb_tel_login->setMinimumSize(QSize(30, 0));

        formLayout_login->setWidget(0, QFormLayout::LabelRole, lb_tel_login);

        le_tel_login = new QLineEdit(layoutWidget);
        le_tel_login->setObjectName(QStringLiteral("le_tel_login"));

        formLayout_login->setWidget(0, QFormLayout::FieldRole, le_tel_login);

        lb_password_login = new QLabel(layoutWidget);
        lb_password_login->setObjectName(QStringLiteral("lb_password_login"));

        formLayout_login->setWidget(1, QFormLayout::LabelRole, lb_password_login);

        le_password_login = new QLineEdit(layoutWidget);
        le_password_login->setObjectName(QStringLiteral("le_password_login"));

        formLayout_login->setWidget(1, QFormLayout::FieldRole, le_password_login);


        verticalLayout_2->addLayout(formLayout_login);

        pb_login = new QPushButton(layoutWidget);
        pb_login->setObjectName(QStringLiteral("pb_login"));

        verticalLayout_2->addWidget(pb_login);

        tabWidget->addTab(Login, QString());
        Register = new QWidget();
        Register->setObjectName(QStringLiteral("Register"));
        layoutWidget1 = new QWidget(Register);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(60, 50, 241, 116));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        formLayout_register = new QFormLayout();
        formLayout_register->setSpacing(6);
        formLayout_register->setObjectName(QStringLiteral("formLayout_register"));
        le_tel_register = new QLineEdit(layoutWidget1);
        le_tel_register->setObjectName(QStringLiteral("le_tel_register"));

        formLayout_register->setWidget(0, QFormLayout::FieldRole, le_tel_register);

        lb_name_register = new QLabel(layoutWidget1);
        lb_name_register->setObjectName(QStringLiteral("lb_name_register"));

        formLayout_register->setWidget(1, QFormLayout::LabelRole, lb_name_register);

        le_name_register = new QLineEdit(layoutWidget1);
        le_name_register->setObjectName(QStringLiteral("le_name_register"));

        formLayout_register->setWidget(1, QFormLayout::FieldRole, le_name_register);

        lb_password_register = new QLabel(layoutWidget1);
        lb_password_register->setObjectName(QStringLiteral("lb_password_register"));

        formLayout_register->setWidget(2, QFormLayout::LabelRole, lb_password_register);

        le_password_register = new QLineEdit(layoutWidget1);
        le_password_register->setObjectName(QStringLiteral("le_password_register"));

        formLayout_register->setWidget(2, QFormLayout::FieldRole, le_password_register);

        lb_tel_register = new QLabel(layoutWidget1);
        lb_tel_register->setObjectName(QStringLiteral("lb_tel_register"));
        lb_tel_register->setMinimumSize(QSize(30, 0));

        formLayout_register->setWidget(0, QFormLayout::LabelRole, lb_tel_register);


        verticalLayout->addLayout(formLayout_register);

        pb_register = new QPushButton(layoutWidget1);
        pb_register->setObjectName(QStringLiteral("pb_register"));

        verticalLayout->addWidget(pb_register);

        tabWidget->addTab(Register, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        lb_tel_login->setText(QApplication::translate("MainWindow", "tel", 0));
        le_tel_login->setText(QApplication::translate("MainWindow", "18845621867", 0));
        lb_password_login->setText(QApplication::translate("MainWindow", "password", 0));
        le_password_login->setText(QApplication::translate("MainWindow", "mmm959825", 0));
        pb_login->setText(QApplication::translate("MainWindow", "\347\231\273\345\275\225", 0));
        tabWidget->setTabText(tabWidget->indexOf(Login), QApplication::translate("MainWindow", "\347\231\273\345\275\225", 0));
        lb_name_register->setText(QApplication::translate("MainWindow", "name", 0));
        lb_password_register->setText(QApplication::translate("MainWindow", "password", 0));
        lb_tel_register->setText(QApplication::translate("MainWindow", "tel", 0));
        pb_register->setText(QApplication::translate("MainWindow", "\346\263\250\345\206\214", 0));
        tabWidget->setTabText(tabWidget->indexOf(Register), QApplication::translate("MainWindow", "\346\263\250\345\206\214", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
