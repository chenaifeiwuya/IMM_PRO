/********************************************************************************
** Form generated from reading UI file 'chatdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATDIALOG_H
#define UI_CHATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chatDialog
{
public:
    QTextBrowser *tb_chatRecord;
    QPushButton *pb_send;
    QTextEdit *le_insert;
    QPushButton *pb_openFile;
    QScrollArea *sca_fileTran;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QTableWidget *tb_fileInfo;

    void setupUi(QWidget *chatDialog)
    {
        if (chatDialog->objectName().isEmpty())
            chatDialog->setObjectName(QStringLiteral("chatDialog"));
        chatDialog->resize(938, 469);
        tb_chatRecord = new QTextBrowser(chatDialog);
        tb_chatRecord->setObjectName(QStringLiteral("tb_chatRecord"));
        tb_chatRecord->setGeometry(QRect(0, 0, 401, 321));
        pb_send = new QPushButton(chatDialog);
        pb_send->setObjectName(QStringLiteral("pb_send"));
        pb_send->setGeometry(QRect(290, 430, 93, 28));
        le_insert = new QTextEdit(chatDialog);
        le_insert->setObjectName(QStringLiteral("le_insert"));
        le_insert->setGeometry(QRect(0, 340, 401, 81));
        pb_openFile = new QPushButton(chatDialog);
        pb_openFile->setObjectName(QStringLiteral("pb_openFile"));
        pb_openFile->setGeometry(QRect(50, 430, 93, 28));
        sca_fileTran = new QScrollArea(chatDialog);
        sca_fileTran->setObjectName(QStringLiteral("sca_fileTran"));
        sca_fileTran->setGeometry(QRect(409, 0, 501, 360));
        sca_fileTran->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 499, 358));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tb_fileInfo = new QTableWidget(scrollAreaWidgetContents);
        if (tb_fileInfo->columnCount() < 4)
            tb_fileInfo->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tb_fileInfo->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tb_fileInfo->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tb_fileInfo->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tb_fileInfo->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tb_fileInfo->setObjectName(QStringLiteral("tb_fileInfo"));
        tb_fileInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);

        verticalLayout->addWidget(tb_fileInfo);

        sca_fileTran->setWidget(scrollAreaWidgetContents);

        retranslateUi(chatDialog);

        QMetaObject::connectSlotsByName(chatDialog);
    } // setupUi

    void retranslateUi(QWidget *chatDialog)
    {
        chatDialog->setWindowTitle(QApplication::translate("chatDialog", "Form", 0));
        pb_send->setText(QApplication::translate("chatDialog", "\345\217\221\351\200\201", 0));
        pb_openFile->setText(QApplication::translate("chatDialog", "\345\217\221\351\200\201\346\226\207\344\273\266", 0));
        QTableWidgetItem *___qtablewidgetitem = tb_fileInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("chatDialog", "\346\226\207\344\273\266\345\220\215\347\247\260", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tb_fileInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("chatDialog", "\344\270\212\344\274\240/\344\270\213\350\275\275", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tb_fileInfo->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("chatDialog", "\350\277\233\345\272\246", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tb_fileInfo->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("chatDialog", "openFile", 0));
    } // retranslateUi

};

namespace Ui {
    class chatDialog: public Ui_chatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIALOG_H
