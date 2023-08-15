#ifndef CFRIENDLIST_H
#define CFRIENDLIST_H

#include "cfrienditem.h"
#include <QWidget>
#include <QLayout>
#include <QMap>
#include <QMessageBox>
#include <QCloseEvent>
#include <QInputDialog>
#include <QMenu>
#include "pakdef.h"
#include "cchatgroupitem.h"

namespace Ui {
class CFriendList;
}

class CFriendList : public QWidget
{
    Q_OBJECT

public:
    explicit CFriendList(QWidget *parent = 0);
    ~CFriendList();

signals:
    void SIG_exit();
    void SIG_sendChatMessage(int id,QString text);
    void SIG_addFriend(QString name);
    void SIG_sendFile(int id,QString path);
    void SIG_sendFileBlockRq(int,int);
    void SIG_addGroupChat(QString tel);
    void SIG_createGroup(QString groupName);
    void SIG_sendGroupChatInfo(QString text,int groupId);


public slots:
    void slot_updataFriendinfo(int id,QString name,int iconid, QString feeling, int status);
    void slot_updataUserInfo(QString name,QString feeling);   //更新用户name，  更新用户签名
    void slot_sendChatMessage(int id,QString text);
    void slot_sendFile(int id,QString path);
    void slot_insertFileRows(int friendId,FileInfo* fileInfo);
    void slot_sendFileBlockRq(int friendId,int timestamp);
    void slot_sendGroupChatInfo(QString text,int groupId);

public:
     void closeEvent(QCloseEvent *event) override;
     void dealChatRq(int id,QString text);
     void updateProcess(int friendId,FileInfo* fileInfo);
     void addChatGroup(QString groupName,int groupId);
     void dealGroupChatInfo(int groupId,QString text,QString userName);   //处理群聊信息请求

private slots:
     void on_pb_addFriend_clicked();
     void slot_dealMenu(QAction* );

private:
    Ui::CFriendList *ui;
public:
    QVBoxLayout* m_layoutOnline;    //QVBoxLayout垂直布局的层(要在大控件中装小控件就需要布局（画布）)
    QVBoxLayout* m_layoutOffline;
    QMap<int,CFriendItem*> mapItToFriendItem;    //key值为id，实值为好友窗口对象
    QMap<int,CChatGroupItem*> mapIdtoChatGroupItem;  //key为群组id，实值为群组窗口对象
    int OnlineNum;   //在线人数数量
    int OfflineNum;     //离线人数数量
    QMenu* m_menu;
};

#endif // CFRIENDLIST_H
