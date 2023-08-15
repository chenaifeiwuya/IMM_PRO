#ifndef CGROUPCHAT_H
#define CGROUPCHAT_H

#include <QDialog>
#include <QTime>


namespace Ui {
class CGroupChat;
}

class CGroupChat : public QDialog
{
    Q_OBJECT

public:
    explicit CGroupChat(QWidget *parent = 0);
    ~CGroupChat();

signals:
    void SIG_sendGroupChatInfo(QString,int);

public:
    void dealGroupChatInfo(QString text,QString userName);

private:
    Ui::CGroupChat *ui;

public:
    int groupId;
private slots:
    void on_pb_send_clicked();
};

#endif // CGROUPCHAT_H
