#ifndef CKERNEL_H
#define CKERNEL_H
#include <QObject>
#include "tcpClientMediator.h"
#include <QDebug>
#include "pakdef.h"
#include "mainwindow.h"
#include "cfriendlist.h"
#include <QTextCodec>
#include <QMap>
#include "cfrienditem.h"
#include <QTime>
#include <QCoreApplication>
#include "md5.h"
#include "csqlite.h"
#include <QTimer>

class CKernel;
typedef void (CKernel::*(pFunc))(long, char*, int);    //函数指针数组


class CKernel:public QObject
{
    Q_OBJECT
public:
    CKernel();
    ~CKernel();

signals:
    void SIG_updataFriendInfo(int,QString,int,QString ,int status);
    void SIG_updataUserInfo(QString ,QString);
    void SIG_insertFileRows(int friendId,FileInfo* fileInfo);

    //处理服务器信息槽函数
public slots:
    void slot_dealReadyData(long Ip, char* buf, int len);
    void slot_dealRegisterRs(long Ip,char* buf, int len);
    void slot_dealLoginRs(long Ip, char* buf, int len);
    void slot_dealFriendInfoRq(long Ip,char* buf, int len);
    void slot_dealChatRq(long Ip,char* buf,int len);
    void slot_dealAddFriendRq(long Ip,char* buf, int len);
    void slot_dealAddFriendRs(long Ip, char* buf, int len);
    void slot_dealFileInfoRq(long Ip,char* buf, int len);     //处理接收到的文件信息
    void slot_dealFileInfoRs(long Ip,char* buf, int len);     //处理接收到的文件信息回复
    void slot_dealFileBlockRq(long Ip,char* buf, int len);     //处理接收到的文件信息块
    void slot_dealFileBlockRs(long Ip,char* buf, int len);     //处理接收到的文件信息块请求的回复
    void slot_dealFileBlockMd5Rq(long Ip,char* buf,int len);   //处理接收到的文件块的md5请求
    void slot_dealFIleBlockMd5Rs(long Ip,char* buf,int len);   //处理md5请求的回复
    void slot_dealFileTranResult(long Ip,char* bug, int len);  //处理接收到的文件传输结果
    void slot_dealFileContinueTranRq(long Ip,char* bug, int len);   //处理断点续传请求
    void slot_dealAddChatGroupRq(long Ip,char* bug, int len);    //处理收到的添加群聊请求
    void slot_dealAddChatGroupRs(long Ip,char* buf,int len);     //处理收到的添加群聊的回复
    void slot_dealCreateGroupRs(long Ip,char* buf,int len);      //处理创建群聊回复
    void slot_dealChatGroupInfoRq(long Ip,char* buf,int len);      //处理群聊信息请求
    void slot_dealChatGroupChatInfoRq(long Ip,char* buf, int len);  //处理群聊的聊天信息请求



    //处理本地信息槽函数
    void slot_registerRq(QString tel, QString name, QString password);
    void slot_loginRq(QString tel,QString password);
    void slot_exit();
    void slot_sendChatMessage(int id,QString text);
    void slot_addFriend(QString name);
    void slot_sendFile(int id,QString path);
    void slot_sendFileBlockRq(int friendId, FileInfo file);   //发送文件块请求
    void slot_continueSendFileBlockRq(int friendId,int timestamp);   //请求对方继续发送文件块给当前用户
    void loadSQLdata();   //将FileInfo写入SQLite
    void sendFileBlockMd5(int friendId, FileInfo* fileInfo);
    void slot_addGroupChat(QString groupId);
    void slot_createGroupChat(QString groupName);
    void slot_sendGroupChatInfo(QString text,int groupId);

public:
    void getFriendInfo();    //发送获取好友信息的请求

    int getNumber();

    void writeFileInfoToSql(int friendId,FileInfo *fileInfo);  //将文件信息写道SQLite数据库中
    void upDateFileInfoToSql(FileInfo *fileInfo);  //更新SQLite中的文件信息
    void deleteFileInfoToSql(FileInfo *fileInfo);   //删除SQLite中保存的文件信息

    QList<FileInfo> getUploadTask();
    QList<FileInfo> getDownloadTask();

    static string getMd5(QString path);   //获取整个文件的md5验证
    static string getMd5(char* path, int start, int size);    //获取某段文件的md5验证





public:
    static string utf8_To_GB2312(const QString &utf8);
    static QString GB2312_To_utf8(const string& GB2312);
    void initMapFunc();
private:
    INetMediator* m_pMediator;
    MainWindow m_loginWindow;
    CFriendList m_friendListWindow;
    pFunc m_pFunc[PROTOCOL_NUM];

    int m_id;   //我的id
    QString m_name;  //我的name
    CSqlite *m_sql;  //SQLite数据库

    QMap<long long, FileInfo> mapIdTimestampToFileInfo;   //唯一标识对应的文件信息

};

#endif // CKERNEL_H
