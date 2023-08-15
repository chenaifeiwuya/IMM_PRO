#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QWidget>
#include <QMessageBox>
#include <QKeyEvent>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QProgressBar>
#include "pakdef.h"
#include "mytablewidget.h"

namespace Ui {
class chatDialog;
}

class chatDialog : public QWidget
{
    Q_OBJECT

public:
    explicit chatDialog(QWidget *parent = 0);
    ~chatDialog();



public:
    void setId(int id,QString name);  //设置对应的id
    void insertFileRows(FileInfo* fileInfo);
    void updateProcess(FileInfo* fileInfo);
signals:
    void SIG_sendChatMessage(int id,QString text);
    void SIG_sendFile(int id,QString path);
    void SIG_sendFileBlockRq(int friendId, int timestamp);

private slots:
    void on_pb_send_clicked();

    void on_pb_openFile_clicked();

    void on_tb_fileInfo_cellDoubleClicked(int row, int column);

public:
    void dealChatRq(QString text ,QString name="");
    void keyPressEvent(QKeyEvent* event) override;

private:
    Ui::chatDialog *ui;
public:
    int id;  //用于记录当前聊天窗口是和谁的聊天窗口
    QString name;
};

#endif // CHATDIALOG_H
