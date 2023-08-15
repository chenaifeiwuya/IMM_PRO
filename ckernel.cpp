#include "ckernel.h"


#define BIND_PROTOCOL_PFUNC(x)  (m_pFunc[(x)-_DEF_PROTOCOL_BASE-1])

CKernel::CKernel()
{
    m_sql = new CSqlite;


    initMapFunc();



    m_pMediator=new tcpClientMediator;
    if(!m_pMediator->OpenNet())
    {
        exit(0);   //网络打开失败
    }
    //char *buf = "hello world!";
    //m_pMediator->SendData(0,buf,sizeof("hello world!"));
    QObject::connect(m_pMediator,SIGNAL(SIG_dealData(long,char*,int)),this,SLOT(slot_dealReadyData(long,char*,int)));

    //绑定登录注册界面类与本类的信号和槽
    QObject::connect(&m_loginWindow,SIGNAL(SIG_registerRq(QString,QString,QString)),this,SLOT(slot_registerRq(QString, QString,QString)));
    QObject::connect(&m_loginWindow,SIGNAL(SIG_loginRq(QString,QString)),this,SLOT(slot_loginRq(QString,QString)));


    //绑定好友界面类与本类的信号和槽
    QObject::connect(this,SIGNAL(SIG_updataFriendInfo(int,QString,int,QString ,int)),  \
                     &m_friendListWindow,SLOT(slot_updataFriendinfo(int,QString,int,QString ,int)));
    QObject::connect(this,SIGNAL(SIG_updataUserInfo(QString,QString )),  \
                     &m_friendListWindow,SLOT(slot_updataUserInfo(QString,QString)));
    QObject::connect(&m_friendListWindow,SIGNAL(SIG_sendChatMessage(int,QString)), \
                     this,SLOT(slot_sendChatMessage(int ,QString )));
    QObject::connect(&m_friendListWindow,SIGNAL(SIG_addFriend(QString)), \
                     this,SLOT(slot_addFriend(QString )));
    QObject::connect(&m_friendListWindow,SIGNAL(SIG_sendFile(int,QString)), \
                     this,SLOT(slot_sendFile(int,QString )));
    QObject::connect(this,SIGNAL(SIG_insertFileRows(int,FileInfo*)), \
                     &m_friendListWindow,SLOT(slot_insertFileRows(int,FileInfo* )));
    QObject::connect(&m_friendListWindow,SIGNAL(SIG_sendFileBlockRq(int,int)), \
                     this,SLOT(slot_continueSendFileBlockRq(int,int )));
    QObject::connect(&m_friendListWindow,SIGNAL(SIG_sendGroupChatInfo(QString,int)),\
                     this,SLOT(slot_sendGroupChatInfo(QString ,int)));
    QObject::connect(&m_friendListWindow,SIGNAL(SIG_addGroupChat(QString)), \
                     this,SLOT(slot_addGroupChat(QString)));
    QObject::connect(&m_friendListWindow,SIGNAL(SIG_createGroup(QString)),\
                     this,SLOT(slot_createGroupChat(QString)));
    m_loginWindow.show();   //显示登录注册界面



}

CKernel::~CKernel()
{
    slot_exit();
}

//初始化
void CKernel::initMapFunc()
{
    BIND_PROTOCOL_PFUNC(_DEF_TCP_REGISTER_RS) = &CKernel::slot_dealRegisterRs;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_LOGIN_RS) = &CKernel::slot_dealLoginRs;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_FRIEND_INFO) = &CKernel::slot_dealFriendInfoRq;
    BIND_PROTOCOL_PFUNC(_DEF_PROTOCOL_CHAT_RQ) = &CKernel::slot_dealChatRq;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_ADD_FRIEND_RQ) = &CKernel::slot_dealAddFriendRq;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_ADD_FRIEND_RS) = &CKernel::slot_dealAddFriendRs;
    BIND_PROTOCOL_PFUNC(_DEF_TCP__FILE_INFO_RQ) = &CKernel::slot_dealFileInfoRq;
    BIND_PROTOCOL_PFUNC(_DEF_TCP__FILE_INFO_RS) = &CKernel::slot_dealFileInfoRs;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_FILE_BLOCK_RQ) = &CKernel::slot_dealFileBlockRq;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_FILE_BLOCK_RS) = &CKernel::slot_dealFileBlockRs;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_FILE_BLOCK_MD5_RQ) = &CKernel::slot_dealFileBlockMd5Rq;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_FILE_BLOCK_MD5_RS) = &CKernel::slot_dealFIleBlockMd5Rs;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_FILE_ALL_TRAN_RESULT) = &CKernel::slot_dealFileTranResult;
    BIND_PROTOCOL_PFUNC(_DRF_TCP_FILE_CONTINUE_TRAN_RQ) =&CKernel::slot_dealFileContinueTranRq;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_CREATE_CHAT_GROUP_RS) = &CKernel::slot_dealCreateGroupRs;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_ADD_CHAT_GROUP_RQ) = &CKernel::slot_dealAddChatGroupRq;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_ADD_CHAT_GROUP_RS) = &CKernel::slot_dealAddChatGroupRs;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_CHAT_GROUP_INFO_RQ) = &CKernel::slot_dealChatGroupInfoRq;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_CHAT_GROUP_CHAT_INFO_RQ) = &CKernel::slot_dealChatGroupChatInfoRq;
}


void CKernel::slot_dealReadyData(long Ip, char* buf, int len)
{
    int num=*(int*)buf;
    num -= (_DEF_PROTOCOL_BASE+1);
    if(num>=0 && num<PROTOCOL_NUM)  //判断num是否合法
    {
        (this->*(m_pFunc[num]))(Ip,buf,len);
    }
    else
    {
        qDebug()<<"deal ReadyData Error!";
    }
    delete[] buf;
    return;
}


//处理注册回复
void CKernel::slot_dealRegisterRs(long Ip, char *buf, int len)
{
    STRU_TCP_REGISTER_RS* rs = (STRU_TCP_REGISTER_RS*)buf;
    qDebug()<<len<<"   "<<sizeof(STRU_TCP_REGISTER_RS)<<endl;
    if(rs->result == REGISTER_SUCCESS)
    {
        QMessageBox::about(&m_loginWindow,"提示","注册成功！");
    }
    else
    {
        QMessageBox::about(&m_loginWindow,"提示","注册失败，用户已存在!");
    }
    return ;
}

//处理登录回复
void CKernel::slot_dealLoginRs(long Ip, char *buf, int len)
{

    //取出数据判断是否登录成功
    STRU_TCP_LOGIN_RS* rs=(STRU_TCP_LOGIN_RS*)buf;
    //若登录失败，则弹出消息窗口提示用户是因为什么登录失败
    if(rs->result == USER_IS_NOTEXIST)
    {
        QMessageBox::about(&m_loginWindow,"提示","登录失败，用户不存在!");
        return;
    }
    else if(rs->result == PASSWORD_ERROR)
    {
        QMessageBox::about(&m_loginWindow,"提示","登录失败，密码错误!");
        return;
    }
    else if(rs->result == USER_IS_ONLINE)
    {
        QMessageBox::about(&m_loginWindow,"提示","登录失败，您已在别处登录，若不是您登录请尽快修改密码!");
        return;
    }
    //若登录成功


    //更新用户信息
    //name 和 feeling可能会有汉字，编码格式需要转变
    QString name=GB2312_To_utf8(string(rs->name));
    QString feeling=GB2312_To_utf8(string(rs->feeling));
        m_id = rs->userId;
        m_name = name;
    Q_EMIT SIG_updataUserInfo(name,feeling);

        //登录窗口隐藏
    m_loginWindow.hide();
        //TODO:  显示主界面
    m_friendListWindow.show();
        //TODO:  并发送一个获取好友在线消息的请求
    getFriendInfo();    //获取好友信息

    //查看SQLite数据库内有没有需要处理的数据;
    //由于对窗口的操作是在主线程中，而接收到服务器发的好友信息后添加好友窗口也是在主线程中进行的
    //所以这就导致了直接调用loadSQLdata的话，调用时不管sleep多久都不会有好友窗口，因为主线程被阻塞了
    //所以我们这里采用定时器的方法

    QTimer *timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(loadSQLdata()));
    timer->setSingleShot(true);   //定时器只触发一次
    timer->start(500);   //500ms后触发

}



//处理好友信息请求
//需要注意的是：处理接收到的数据的函数到时候都不会和主线程在一个线程中，又由于Qt控件只有其拥有者线程才能改变，
//但是由于中介者是通过发信号的方式来通知kernel类的，所以此时的ckernel类的槽函数并非在接收数据线程里处理，
//而是在主线程中处理，所以这里可以直接对控件进行操作

void CKernel::slot_dealFriendInfoRq(long Ip, char *buf, int len)
{
    STRU_TCP_FRIEND_INFO* rq=(STRU_TCP_FRIEND_INFO*)buf;
    //转码
    QString name=GB2312_To_utf8(string(rq->name));
    QString feeling=GB2312_To_utf8(string(rq->feeling));
    SIG_updataFriendInfo(rq->userId,name,rq->iconId,feeling,rq->status);
}

//处理聊天信息请求
void CKernel::slot_dealChatRq(long Ip, char *buf, int len)
{
    STRU_TCP_CHAT_RQ* rq = (STRU_TCP_CHAT_RQ*)buf;
    //由于发送的时候没有转换编码格式
    //接收暂时也不转编码格式
    //直接将信息传递给好友窗口
    m_friendListWindow.dealChatRq(rq->userId,QString(rq->content));
}

//处理添加好友请求
void CKernel::slot_dealAddFriendRq(long Ip, char *buf, int len)
{
    STRU_TCP_ADD_FRIEND_RQ* rq=(STRU_TCP_ADD_FRIEND_RQ*)buf;
    STRU_TCP_ADD_FRIEND_RS rs;
    rs.friendId = m_id;
    //需要转变编码格式
    string rsName = utf8_To_GB2312(m_name);
    strcpy_s(rs.friendName,rsName.c_str());
    rs.userId = rq->userId;

    QString addName = GB2312_To_utf8(string(rq->userName));
    //弹出提示信息告诉用户是谁加他的好友
    if(QMessageBox::Yes == QMessageBox::information(&m_friendListWindow,"提示",QString("%1 请求添加您为好友，是否同意？").arg(addName),\
                             QMessageBox::Yes | QMessageBox::No))
    {
        //返回同意好友请求的数据包
        rs.result = ADD_FRIEND_SUCCESS;
    }
    else
    {
        //返回不同意好友请求的数据包
        rs.result = ADD_FRIEND_FAILED;
    }
    m_pMediator->SendData(0,(char*)&rs,sizeof(rs));
    //获取好友信息请求
    Sleep(10);
    getFriendInfo();
}

//处理添加好友回复
void CKernel::slot_dealAddFriendRs(long Ip, char *buf, int len)
{
    STRU_TCP_ADD_FRIEND_RS* rs = (STRU_TCP_ADD_FRIEND_RS*)buf;
    QString friendName=GB2312_To_utf8(string(rs->friendName));
    //判断是否添加成功
    if(rs->result == ADD_FRIEND_SUCCESS)
    {
        //提示添加成功
        //并向服务器发送一个获取好友信息的请求
        QMessageBox::information(&m_friendListWindow,"提示",QString("%1 已同意您的好友请求!").arg(friendName),QMessageBox::Ok);
        getFriendInfo();
    }
    else
    {
        //否则提示添加失败
        QMessageBox::information(&m_friendListWindow,"提示",QString("%1 拒绝了您的好友请求!").arg(friendName),QMessageBox::Ok);
    }
    return;
}

//处理文件信息回复
void CKernel::slot_dealFileInfoRs(long Ip, char *buf, int len)
{
    qDebug()<<__func__;
    //拆包
    STRU_TCP_FILE_INFO_RS* rs=(STRU_TCP_FILE_INFO_RS*)buf;
    //查看对方是否同意，若同意，则将文件信息写入SQLite，
    if(rs->result == FILEINFO_RESULT_ACCEPT)
    {
         qDebug()<<"对方同意接收文件"<<endl;
         int num=m_id * getNumber() + rs->timestamp;
         //map中已经在sendfile写入了，不必重复写
         FileInfo* fileInfo=&(mapIdTimestampToFileInfo[num]);
        //写入SQLite
        writeFileInfoToSql(rs->userId,fileInfo);
         //插入
         Q_EMIT SIG_insertFileRows(rs->userId,fileInfo);

        //然后开始发送文件块请求（注意，当对方返回接收成功回复时才能更改保存信息中传送成功的值
        //slot_sendFileBlockRq(rs->userId,mapIdTimestampToFileInfo[num]);
        //这里向对方发送第一片的md5请求
        //文件片的发送都通过md5请求开始

        //发送下一片的md5验证
        sendFileBlockMd5(rs->userId,fileInfo);
        return;


    }
    //若不同意，则将map中保存的文件信息删除,并关闭打开的文件

        int num=rs->targetId * getNumber() + rs->timestamp;
        if(mapIdTimestampToFileInfo.count(num) > 0)
        {
            fclose(mapIdTimestampToFileInfo[num].file);   //关闭文件指针
            auto ite=mapIdTimestampToFileInfo.find(num);
            mapIdTimestampToFileInfo.erase(ite);
        }
}

void CKernel::slot_dealFileBlockRq(long Ip, char *buf, int len)
{
    qDebug()<<__func__;
    //处理接收到的文件信息块
    //拆包
    STRU_TCP_FILE_BLOCK_RQ* rq=(STRU_TCP_FILE_BLOCK_RQ*)buf;
    //取出userId和timestamp
    long long num = rq->userId * getNumber() + rq->timestamp;
    if(mapIdTimestampToFileInfo.count(num) > 0)
    {
        //如果存在该文件信息结构体
        //开始写入
        FileInfo* fileInfo=&(mapIdTimestampToFileInfo[num]);
        int seekMove = fileInfo->cutNow * fileInfo->cutSize + fileInfo->nowSize;
        fseek(fileInfo->file,seekMove,SEEK_SET);
        int writeSize = fwrite(rq->fileBlock,1,rq->size,fileInfo->file);
        //TODO: 需要判断写入是否成功,写入失败字节数不对的话需要返回一个接收失败的包

        //更新文件信息结构体
        fileInfo->nowSize += writeSize;
        //更新进度条
        m_friendListWindow.updateProcess(rq->userId,fileInfo);


        //判断文件传输是否结束
        if(seekMove + writeSize >= fileInfo->size)
        {
            //文件传输结束
            //仍然要先发送一个回复包告诉发送者，本次数据收到了
            STRU_TCP_FILE_BLOCK_RS rs;
            rs.userId = m_id;
            rs.friendId = rq->userId;
            rs.timestamp = rq->timestamp;
            rs.size = writeSize;
            rs.result = FILE_TRAN_SUCCESS;
            m_pMediator->SendData(0,(char*)&rs,sizeof(rs));
            //对整个文件进行MD5校验
            fclose(fileInfo->file);
            fileInfo->file=NULL;
            string md5All=getMd5(fileInfo->filePath);

            STRU_TCP_FILE_ALL_TRAN_RESULT tranResult;
            tranResult.userId = m_id;
            tranResult.friendId = rq->userId;
            tranResult.timestamp = rq->timestamp;

            //开始进行比较
            if(strcmp(fileInfo->md5,md5All.c_str()) == 0)
            {
                //若相等，则返回一个文件发送成功的数据包
                tranResult.result = FILE_TRAN_ALL_SUCCESS;
                //TODO: 提示文件传输成功
                //提示成功
                QMessageBox::information(&m_friendListWindow,"提示",QString("%1 文件传输成功").arg(fileInfo->filePath));

            }
            else
            {
                //否则返回一个文件发送失败的数据包
                tranResult.result = FILE_TRAN_ALL_FAILED;

                //TODO: 提示文件传输失败
                //提示成功
                QMessageBox::information(&m_friendListWindow,"提示",QString("%1 文件传输失败").arg(fileInfo->filePath));
            }

           m_pMediator->SendData(0,(char*)&tranResult,sizeof(tranResult));

            auto ite=mapIdTimestampToFileInfo.find(num);
           //关闭打开的文件指针    前面已经关闭过了，这里不必重复关闭
//           fclose((*ite).file);
//           (*ite).file=NULL;
            //将SQLite中的文件信息删除
            FileInfo fileInfo=*ite;
            deleteFileInfoToSql(&fileInfo);
            //将map中的文件信息删除
            mapIdTimestampToFileInfo.erase(ite);

            return;
        }

        //判断当前分片是否结束
        if(fileInfo->nowSize >= fileInfo->cutSize)
        {
            //TODO：对当前分片进行MD5校验
            string md5Str = getMd5(fileInfo->filePath,fileInfo->cutNow * fileInfo->cutSize, fileInfo->cutSize);
            //将其与fileInfo的md5进行比较，查看是否相等
            //如果相等，更新fileInfo，并发送下一片的信息请求
            if(strcmp(fileInfo->md5Now,md5Str.c_str()) == 0)  //相等时返回值等于0
            {
                //更新fileInfo
                fileInfo->cutNow ++;
                fileInfo->nowSize=0;

                //更新SQLite
                upDateFileInfoToSql(fileInfo);


                //若文件尚未结束，则开始请求下一片文件块
                STRU_TCP_FILE_BLOCK_RS rs;
                rs.userId = m_id;
                rs.friendId = rq->userId;
                rs.timestamp = rq->timestamp;
                rs.size = writeSize;
                rs.result = FILE_TRAN_SUCCESS;
                m_pMediator->SendData(0,(char*)&rs,sizeof(rs));
                return;
            }
            else
            {
                fileInfo->nowSize=0;
                //如果不相等，将fileInfo信息还原当当前片传输前，并重新请求当前片信息
                STRU_TCP_FILE_BLOCK_RS rs;
                rs.userId = m_id;
                rs.friendId = rq->userId;
                rs.timestamp = rq->timestamp;
                rs.size = writeSize;
                rs.result = FILE_TRAN_FAILED;
                m_pMediator->SendData(0,(char*)&rs,sizeof(rs));
                return;
            }

        }
        //若当前分片尚未结束，则继续请求
        else
        {
            STRU_TCP_FILE_BLOCK_RS rs;
            rs.userId = m_id;
            rs.friendId = rq->userId;
            rs.timestamp = rq->timestamp;
            rs.size = writeSize;
            rs.result = FILE_TRAN_NOTEND;
            m_pMediator->SendData(0,(char*)&rs,sizeof(rs));
            return;
        }
    }
}

void CKernel::slot_dealFileBlockRs(long Ip, char *buf, int len)
{
    qDebug()<<__func__;
    STRU_TCP_FILE_BLOCK_RS* rs=(STRU_TCP_FILE_BLOCK_RS*)buf;


    int num = m_id * getNumber() + rs->timestamp;
    if(mapIdTimestampToFileInfo.count(num) > 0)
    {
        //更新文件信息结构体
        FileInfo *fileInfo = &(mapIdTimestampToFileInfo[num]);

        //首先判断是否文件都传输完毕，若都传输完毕则直接返回
        fileInfo->nowSize += rs->size;
        if(fileInfo->cutNow * fileInfo->cutSize + fileInfo->nowSize == fileInfo->size)
        {
            //更新进度
            //文件信息删除等不在这里，而是在后面收到的文件传输最终结果处理函数中
            m_friendListWindow.updateProcess(rs->userId,fileInfo);
            return;   //文件传输完毕
        }

        if(rs->result == FILE_TRAN_NOTEND)
        {
            //本片尚未传输结束
            m_friendListWindow.updateProcess(rs->userId,fileInfo);
            slot_sendFileBlockRq(rs->userId,*fileInfo);
            return;
        }
        else if(rs->result == FILE_TRAN_FAILED)
        {
            //本片传输失败
            //文件信息倒退
            fileInfo->nowSize = 0;
            m_friendListWindow.updateProcess(rs->userId,fileInfo);
            slot_sendFileBlockRq(rs->userId,*fileInfo);
            return;
        }
        else if(rs->result == FILE_TRAN_SUCCESS)
        {
            //本片传输成功
                //更新文件信息
            fileInfo->cutNow++;
                //更新进度条
            m_friendListWindow.updateProcess(rs->userId,fileInfo);
                //更新SQLite
            upDateFileInfoToSql(fileInfo);
            fileInfo->nowSize=0;
            //发送下一片的md5验证
            sendFileBlockMd5(rs->userId,fileInfo);

        }
    }
    //若没有找到这个文件信息结构体则直接返回即可



}

void CKernel::slot_dealFileBlockMd5Rq(long Ip, char *buf, int len)
{
    qDebug()<<__func__;
    STRU_TCP_FILE_BLOCK_MD5_RQ* rq=(STRU_TCP_FILE_BLOCK_MD5_RQ*)buf;
    //更新md5
    int num = rq->userId * getNumber() + rq->timstamp;
    if(mapIdTimestampToFileInfo.count(num) > 0)
    {
        FileInfo* fileInfo=&(mapIdTimestampToFileInfo[num]);
        memset(fileInfo->md5Now,0,sizeof(fileInfo->md5Now));
        strcpy(fileInfo->md5Now,rq->md5);

        STRU_TCP_FILE_BLOCK_MD5_RS rs;
        rs.userId = m_id;
        rs.friendId = rq->userId;
        rs.timestamp=rq->timstamp;

        //发送md5请求的回复
        m_pMediator->SendData(0,(char*)&rs,sizeof(rs));
    }
    return;
}

void CKernel::slot_dealFIleBlockMd5Rs(long Ip, char *buf, int len)
{
    qDebug()<<__func__;
    STRU_TCP_FILE_BLOCK_MD5_RS* rs=(STRU_TCP_FILE_BLOCK_MD5_RS*)buf;
    int num = m_id * getNumber() + rs->timestamp;
    if(mapIdTimestampToFileInfo.count(num) > 0)
    {
        //继续发送文件块信息
        //发送下一片的数据
        FileInfo* fileInfo=&(mapIdTimestampToFileInfo[num]);
        slot_sendFileBlockRq(rs->userId,*fileInfo);
    }
}

void CKernel::slot_dealFileTranResult(long Ip, char *buf, int len)
{
    qDebug()<<__func__;
    STRU_TCP_FILE_ALL_TRAN_RESULT* result=(STRU_TCP_FILE_ALL_TRAN_RESULT*)buf;
    int num=m_id* getNumber() + result->timestamp;
    if(mapIdTimestampToFileInfo.count(num)>0)
    {
        FileInfo* fileInfo=&(mapIdTimestampToFileInfo[num]);
        //判断成功还是失败
        if(result->result == FILE_TRAN_ALL_SUCCESS)
        {
            //提示成功
            QMessageBox::information(&m_friendListWindow,"提示",QString("%1 文件传输成功").arg(fileInfo->filePath));
        }
        else
        {
            //提示失败
            QMessageBox::information(&m_friendListWindow,"提示",QString("%1 文件传输失败").arg(fileInfo->filePath));
        }

        //从SQLite中删除文件信息
        deleteFileInfoToSql(fileInfo);


        fclose(fileInfo->file);
        fileInfo->file=NULL;
        auto ite=mapIdTimestampToFileInfo.find(num);
        mapIdTimestampToFileInfo.erase(ite);
    }
}

//处理断点续传请求
void CKernel::slot_dealFileContinueTranRq(long Ip, char *buf, int len)
{
    STRU_TCP_FILE_CONTINUE_TRAN_RQ* rq = (STRU_TCP_FILE_CONTINUE_TRAN_RQ*)buf;
    int num = m_id * getNumber() + rq->timestamp;
    if(mapIdTimestampToFileInfo.count(num) > 0)
    {
        FileInfo* fileInfo = &(mapIdTimestampToFileInfo[num]);
        fileInfo->cutNow = rq->cutNow;
        fileInfo->nowSize =rq->nowSize;

        //开始给对方发送当前片的md5请求

        sendFileBlockMd5(rq->userId,fileInfo);
    }
}

void CKernel::slot_dealAddChatGroupRq(long Ip, char *buf, int len)
{
    STRU_TCP_ADD_CHAT_GROUP_RQ* rq=(STRU_TCP_ADD_CHAT_GROUP_RQ*)buf;
    //弹出一个消息提示框，让群主决定是否添加
    STRU_TCP_ADD_CHAT_GROUP_RS rs;
    if(QMessageBox::Yes == QMessageBox::information(&m_friendListWindow,"提示",QString("%1 申请加入您创建的群聊 %2， 您是否同意？").arg(rq->userName).arg(rq->groupName),QMessageBox::Yes | QMessageBox::No))
    {
        //返回一个同意的回复包
        rs.result = ADD_CHAT_GROUP_SUCCESS;
        rs.userId = m_id;
        rs.groupId = rq->groupId;
        rs.friendId = rq->userId;

    }
    else
    {
        //返回一个不同意的回复包
        rs.result = ADD_CHAT_GROUP_FAILED;
        rs.userId = m_id;
        rs.groupId = rq->groupId;
        rs.friendId = rq->userId;
    }
    m_pMediator->SendData(0,(char*)&rs,sizeof(rs));
}

void CKernel::slot_dealAddChatGroupRs(long Ip, char *buf, int len)
{
    STRU_TCP_ADD_CHAT_GROUP_RS* rs=(STRU_TCP_ADD_CHAT_GROUP_RS*)buf;
    //判断是否添加成功
    if(rs->result == ADD_CHAT_GROUP_GROUPER_OFFLINE)
    {
        QMessageBox::information(&m_friendListWindow,"提示","群主当前未在线，请另选时间添加群主",QMessageBox::Ok);
        return;
    }
    else if(rs->result == ADD_CHAT_GROUP_FAILED)
    {
        QMessageBox::information(&m_friendListWindow,"提示","群主拒绝了您的添加请求！",QMessageBox::Ok);
        return;
    }
    else if(rs->result ==ADD_CHAT_GROUP_NOT_EXIST)
    {
        QMessageBox::information(&m_friendListWindow,"提示","不存在此群！",QMessageBox::Ok);
        return;
    }
    else{
        QMessageBox::information(&m_friendListWindow,"提示",QString("您成功添加了群： %1").arg(rs->groupId),QMessageBox::Ok);
        return;
    }
}

void CKernel::slot_dealCreateGroupRs(long Ip, char *buf, int len)
{
    STRU_TCP_CREATE_CHAT_GROUP_RS * rs = (STRU_TCP_CREATE_CHAT_GROUP_RS*)buf;
    //判断创建群聊的结果
    if(rs->result == CREATE_GROUP_SUCCESS)
    {
        //弹出消息框，提示创建成功
        QMessageBox::information(&m_friendListWindow,"提示","群组创建成功，快去邀请好友来添加群组吧!",QMessageBox::Ok);

        //在列表中添加群聊
        m_friendListWindow.addChatGroup(QString(rs->groupName),rs->groupId);
    }
    else
    {
        //弹出消息框，提示创建失败
        QMessageBox::information(&m_friendListWindow,"提示","群组创建失败！请更换群组名后再次尝试",QMessageBox::Ok);
        return;
    }
}

//处理收到的群聊信息请求
void CKernel::slot_dealChatGroupInfoRq(long Ip, char *buf, int len)
{
    STRU_TCP_CHAT_GROUP_INFO_RQ *rq=(STRU_TCP_CHAT_GROUP_INFO_RQ*)buf;
    //将群聊信息添加到列表上
    m_friendListWindow.addChatGroup(rq->groupName,rq->groupId);
}

//处理群聊的聊天信息请求
void CKernel::slot_dealChatGroupChatInfoRq(long Ip, char *buf, int len)
{
    STRU_TCP_CHAT_GROUP_CHAT_INFO_RQ *rq = (STRU_TCP_CHAT_GROUP_CHAT_INFO_RQ*)buf;
    m_friendListWindow.dealGroupChatInfo(rq->groupId,rq->info,rq->userName);
    return;
}

void CKernel::slot_dealFileInfoRq(long Ip, char *buf, int len)
{
    qDebug()<<__func__;
    //拆包
    STRU_TCP_FILE_INFO_RQ* rq = (STRU_TCP_FILE_INFO_RQ*)buf;
     STRU_TCP_FILE_INFO_RS rs;
     rs.targetId = rq->userid;
     rs.userId = m_id;
     rs.timestamp = rq->timestamp;
    //首先找到聊天框弹出
    //首先判断是否存在该好友

    if(m_friendListWindow.mapItToFriendItem.count(rq->userid) == 0)
    {
        //如果不存在，则直接返回
        return;
    }
    //将该好友的聊天窗口弹出
    chatDialog *dialog =   &(m_friendListWindow.mapItToFriendItem[rq->userid]->dialog);
    dialog->showNormal();
    //然后弹出一个消息框，询问用户是否同意接收该文件
    if(QMessageBox::Yes == QMessageBox::information(dialog,"提示",QString("%1 给您发来了文件 %2 ，请问您是否接收?")\
                             .arg(dialog->name).arg(QString(rq->fileName))\
                             ,QMessageBox::Yes | QMessageBox::No))
    {
        //如果接受
        //则打开文件系统，让它选择保存位置
         QString saveFilePath = QFileDialog::getSaveFileName(nullptr, "保存文件", "", "All Files (*.*)");
         //然后在该地址处创建一个文件，并保存
         string fileName = utf8_To_GB2312(QString(rq->fileName));
         //saveFilePath = saveFilePath + "\\" + QString(fileName.c_str());
         FILE* file = fopen(saveFilePath.toStdString().c_str(),"wb");   //以覆盖写的方式创建一个该文件
         long long num = rq->userid * getNumber() + rq->timestamp;
         FileInfo fileInfo;
         fileInfo.file = file;
         fileInfo.isCut = rq->isCut;
         fileInfo.cutNum = rq->cutNum;
         fileInfo.size = rq->size;
         fileInfo.cutNow = 0;  //若有切片，则当前片为0，否则此字段无效
         //fileInfo.filePath = saveFilePath;
         strcpy(fileInfo.filePath,saveFilePath.toStdString().c_str());
         fileInfo.timestamp = rq->timestamp;
         fileInfo.userId = rq->userid;
         //fileInfo.md5 = rq->md5;
         strcpy(fileInfo.md5,rq->md5);
         mapIdTimestampToFileInfo[num] = fileInfo;    //保存到这里面

         //TODO: 将数据写入SQLite数据库
        writeFileInfoToSql(rq->userid,&fileInfo);
        //在聊天界面上插入控件
        Q_EMIT SIG_insertFileRows(fileInfo.userId,&fileInfo);


    }
    else
    {
        //否则返回一个拒绝接收的消息
        rs.result = FILEINFO_RESULT_REFUSED;
        rs.timestamp = rq->timestamp;
        rs.targetId  = rq->userid;
        rs.userId = m_id;
    }
    m_pMediator->SendData(0,(char*)&rs,sizeof(rs));

}


//发送注册请求
void CKernel::slot_registerRq(QString tel, QString name, QString password)
{
    STRU_TCP_REGISTER_RQ rq;
    //name可能会有汉字  需要utf8 转 GB2312
    string Strname=utf8_To_GB2312(name);
    strcpy_s(rq.name,Strname.c_str());
    strcpy_s(rq.tel,tel.toStdString().c_str());
    strcpy_s(rq.password,password.toStdString().c_str());

    m_pMediator->SendData(0,(char*)&rq,sizeof(rq));
}

//发送登录请求
void CKernel::slot_loginRq(QString tel, QString password)
{
    STRU_TCP_LOGIN_RQ rq;
    //没有汉字，所以不用utf8转 GB2312
    strcpy_s(rq.tel,tel.toStdString().c_str());
    strcpy_s(rq.password,password.toStdString().c_str());

    m_pMediator->SendData(0,(char*)&rq,sizeof(rq));
}

//资源回收函数
void CKernel::slot_exit()
{
    //首先告诉服务器，自己要下线了
    STRU_TCP_OFFLINE_RQ rq;
    rq.userId = m_id;
    m_pMediator->SendData(0,(char*)&rq,sizeof(rq));
    //然后开始回收资源
    m_loginWindow.hide();
    m_friendListWindow.hide();
    m_pMediator->CloseNet();  //关闭网络
    Sleep(20);  //等待20ms，让线程自己退出
    delete m_pMediator;      //回收资源
    exit(0);  //退出，程序结束
}

void CKernel::slot_sendChatMessage(int id, QString text)
{
    qDebug()<<__func__;
    STRU_TCP_CHAT_RQ rq;
    rq.userId = m_id;
    rq.friendId = id;
    strcpy_s(rq.content,text.toStdString().c_str());
    m_pMediator->SendData(0,(char*)&rq,sizeof(rq));
}

//发送添加好友请求
void CKernel::slot_addFriend(QString name)
{
    //判断是否为自己的name，若是则提示不能添加自己为好友
    if(name == m_name)
    {
        QMessageBox::information(&m_friendListWindow,"提示","请勿添加自己为好友",QMessageBox::Ok);
        return ;
    }
    STRU_TCP_ADD_FRIEND_RQ rq;
    //需要转变编码格式
    string rqName = utf8_To_GB2312(name);
    strcpy_s(rq.friendName,rqName.c_str());
    rq.userId = m_id;
    string myName = utf8_To_GB2312(m_name);
    strcpy_s(rq.userName,myName.c_str());
    m_pMediator->SendData(0,(char*)&rq,sizeof(rq));
}

//发送文件的槽函数
void CKernel::slot_sendFile(int id, QString path)
{
    qDebug()<<__func__;
    STRU_TCP_FILE_INFO_RQ rq;

    //首先将文件信息发送给对方：包括文件名  文件的唯一标识（通过时间来唯一标识）  文件整体MD5校验码  是否分片  分成多少片
    QFile file(path);
    strcpy(rq.fileName,file.fileName().toStdString().c_str());
    cout<<rq.fileName<<endl;
    rq.timestamp = QDateTime::currentDateTime().toString("hhmmsszzz").toInt();   //时间戳
                                                //这里请注意考虑时间戳是否有重合的可能性，请考虑如何避免？
    rq.size = file.size();
    //判断是否切片   //文件大小大于_DEF_CUT_LIMIT时则切片传输
    if(rq.size >= _DEF_CUT_LIMIT)
    {
        rq.isCut = _CUT_YES;
        rq.cutNum = rq.size / _DEF_CUT_SIZE;   //开始计算切片数量
        if(rq.size % _DEF_CUT_SIZE != 0)
        {
            rq.cutNum++;
        }

    }
    else    //否则不切片
    {
        rq.isCut = _CUT_NO;
    }
    rq.userid =m_id;
    string md5str=getMd5(path);
    strcpy(rq.md5,md5str.c_str());
    //发送文件信息给对方
    rq.targetId = id;
    m_pMediator->SendData(0,(char*)&rq,sizeof(rq));

    //然后将文件信息保存起来
    FileInfo fileInfo;
    /*
     *
     * fopen是C标准库的一个函数，函数内部是系统调用。Windows中调用CreateFile；Linux中调用open。
        Linux的系统编码为UTF-8，程序中统一UTF-8编码就可以正常打开文件，中文乱码问题也能解决。
        Windows的系统编码为GBK，如果文件名称是Unicode编码，那么在调用fopen前就必须要先把文件名称编码转为GBK，否则就打开失败。
        Qt 中默认的编码为UTF-8，故在windows下需要先转码才能打正确打开。
     */
    //char bufPath[_DEF_MAX_SIZE];
    string bufPath=utf8_To_GB2312(path);
    FILE* File=fopen(bufPath.c_str(),"rb");   //只读打开
    if(!File)
    {
        //打开失败
        qDebug()<<"file open failed!"<<endl;
        return;
    }
    fileInfo.file = File;
    strcpy(fileInfo.filePath,bufPath.c_str());
    //fileInfo.md5 = rq.md5;
    strcpy(fileInfo.md5,rq.md5);
    fileInfo.timestamp = rq.timestamp;
    fileInfo.userId = rq.userid;
    fileInfo.size = rq.size;
    if(rq.isCut == _CUT_YES)
    {
        fileInfo.isCut = _CUT_YES;
        fileInfo.cutNum = rq.cutNum;
        fileInfo.cutNow = 0;   //当前片为第0片，因为还没有开始传输
    }
    else
    {
        fileInfo.isCut = _CUT_NO;
    }
    long long num=m_id * getNumber() + rq.timestamp;
    mapIdTimestampToFileInfo[num] = fileInfo;


}

void CKernel::slot_sendFileBlockRq(int friendId, FileInfo fileInfo)
{
    qDebug()<<__func__;
    //通过file文件信息结构体中的内容来发送文件
    //由于分片大小默认为  _DEF_CUT_SIZE 大小，即50*1024*1024 B
    //所以每次传输数据量选定为 1024 * 2 大小,一片刚好能够被整除
    //计算当前起始传输位置
    int seekMove=0;
    //计算相较于文件头的偏移位置
    seekMove = _DEF_CUT_SIZE * fileInfo.cutNow + fileInfo.nowSize;


    fseek(fileInfo.file,seekMove,SEEK_SET);
    qDebug()<<seekMove;
    //然后从当前位置往后读1024*2个字节
    STRU_TCP_FILE_BLOCK_RQ rq;
    qDebug()<<ftell(fileInfo.file);
    int readSize=fread(rq.fileBlock,1,FILE_BLOCK_SIZE,fileInfo.file);  //一次读1个字节大小，读sizeof(rq.fileBlock)次
    if(readSize < 0)   //所有信息都读了，直接返回即可
    {
        perror("Error reading from file");
        return ;
    }
    else if(readSize==0)
    {
        qDebug()<<"文件传输完毕";
        return;
    }
    //没读满说明文件读完了

    rq.friendId = friendId;
    rq.userId = m_id;
    rq.timestamp = fileInfo.timestamp;
    rq.size = readSize;
    m_pMediator->SendData(0,(char*)&rq,sizeof(rq));

}

//断点续传
void CKernel::slot_continueSendFileBlockRq(int friendId, int timestamp)
{
    STRU_TCP_FILE_CONTINUE_TRAN_RQ rq;
    int num=friendId * getNumber() + timestamp;
    if(mapIdTimestampToFileInfo.count(num) > 0)
    {
        //发送断点续传请求
       rq.cutNow = mapIdTimestampToFileInfo[num].cutNow;
       rq.userId = m_id;
       rq.friendId = mapIdTimestampToFileInfo[num].userId;
       rq.timestamp = mapIdTimestampToFileInfo[num].timestamp;
        mapIdTimestampToFileInfo[num].nowSize = 0;
       rq.nowSize = 0;    //该字段当前暂时不用
       QFile file(mapIdTimestampToFileInfo[num].filePath);
       //将文件截断成整片大小
       file.resize(rq.cutNow * mapIdTimestampToFileInfo[num].cutSize);
        m_pMediator->SendData(0,(char*)&rq,sizeof(rq));
    }
}


//发送获取好友信息的请求
void CKernel::getFriendInfo()
{
    //发送一个空的好友信息结构体告诉服务器
    STRU_TCP_FRIEND_INFO rq;
    rq.userId = m_id;
    m_pMediator->SendData(0,(char*)&rq,sizeof(rq));

}

int CKernel::getNumber()
{
    return 1000000000;
}

//将FileInfo 写入 SQLite数据库
void CKernel::writeFileInfoToSql(int friendId, FileInfo *fileInfo)
{
    char sqlBuf[1024];
    //判断这是当前用户发出的还是当前用户接收的
    if(fileInfo->userId == m_id)    //当前用户发出的
    {
        sprintf(sqlBuf,(QString("insert into t_upload values(\
                           %1 , %2, %3, %4, %5, %6, %7, %8, '%9', '%10','%11');") \
                            .arg(fileInfo->userId).arg(fileInfo->timestamp).arg(fileInfo->size)\
                            .arg(fileInfo->isCut).arg(fileInfo->cutNum).arg(fileInfo->cutNow) \
                            .arg(fileInfo->cutSize).arg(fileInfo->nowSize).arg(fileInfo->filePath)\
                            .arg(fileInfo->md5).arg(friendId)).toStdString().c_str()  \
                            );

    }
    else   //当前用户接收的
    {
        sprintf(sqlBuf,(QString("insert into t_download values(\
                           %1 , %2, %3, %4, %5, %6, %7, %8, '%9', '%10');") \
                            .arg(fileInfo->userId).arg(fileInfo->timestamp).arg(fileInfo->size)\
                            .arg(fileInfo->isCut).arg(fileInfo->cutNum).arg(fileInfo->cutNow) \
                            .arg(fileInfo->cutSize).arg(fileInfo->nowSize).arg(fileInfo->filePath)\
                            .arg(fileInfo->md5)).toStdString().c_str()  \
                            );
    }
    if(!m_sql->UpdateSql(sqlBuf))  //插入数据
    {
        //若sql语句执行失败
        qDebug()<<"insert error with:  "<<sqlBuf;
    }
}

//更新SQLite中的文件信息
void CKernel::upDateFileInfoToSql(FileInfo *fileInfo)
{
    char sqlBuf[1024];
    //判断这是当前用户发出的还是当前用户接收的
    //需要注意的是，更新只会更新当前片，其他的一律不动
    //也就是说，当我们进行断点续传的时候都是从整片段处进行续传的
     if(fileInfo->userId == m_id)    //当前用户发出的
     {
         QString str=QString("update t_upload set cutNow = %1 where userId = %2 and tiemestamp = %3;")\
                 .arg(fileInfo->cutNow).arg(fileInfo->userId).arg(fileInfo->timestamp);
        sprintf(sqlBuf,str.toStdString().c_str());
     }
     else
     {
         QString str=QString("update t_download set cutNow = %1 where friendId = %2 and tiemestamp = %3;")\
                 .arg(fileInfo->cutNow).arg(fileInfo->userId).arg(fileInfo->timestamp);
         sprintf(sqlBuf,str.toStdString().c_str());
     }
     if(!m_sql->UpdateSql(sqlBuf))
     {
         qDebug()<<"Update failed with: "<<sqlBuf;
     }
}

void CKernel::deleteFileInfoToSql(FileInfo *fileInfo)
{
    char sqlBuf[1024];
    //判断这是当前用户发出的还是当前用户接收的
    if(fileInfo->userId == m_id)
    {
        sprintf(sqlBuf,"delete from t_upload where userId=%d and tiemestamp=%d;",fileInfo->userId,fileInfo->timestamp);
    }
    else
    {
        sprintf(sqlBuf,"delete from t_download where friendId=%d and tiemestamp=%d;",fileInfo->userId,fileInfo->timestamp);
    }
    if(!m_sql->UpdateSql(sqlBuf))
    {
        qDebug()<<"Update failed with: "<<sqlBuf;
    }
}

string CKernel::getMd5(QString path)
{
        MD5 md;
        //打开文件  读取文件内容  读到md5类里面， 生成md5
        FILE* pFile = nullptr;
        //fopen 如果有中文 支持ANSI编码  使用ascii码
        //path里面是utf8（qt 默认） 需要转码
        char buf[1000] = "";
       // Utf8ToGB2312(buf,1000, path);
       string pathStr = utf8_To_GB2312(path);
       strcpy(buf,pathStr.c_str());
        pFile=fopen(buf,"rb");  //二进制只读打开
        if(!pFile){
            qDebug()<<"file md5 open fail";
            return NULL;
        }
        int len=0;
        do{
            len = fread(buf, 1, 1000, pFile );   //缓冲区，一次读多少，读多少次，文件指针  返回值为读成功次数
            md.update(buf,len);
        }while(len > 0);
        fclose(pFile);

        qDebug() << "file md5:" <<md.toString().c_str();
        return md.toString();

}

string CKernel::getMd5(char* path, int start, int size)  //验证起始处  验证大小
{
    MD5 md;
    //打开文件  读取文件内容  读到md5类里面， 生成md5
    FILE* pFile = nullptr;
    //fopen 如果有中文 支持ANSI编码  使用ascii码
    //path里面是utf8（qt 默认） 需要转码
   // char buf[1000] = "";
    //Utf8ToGB2312(buf,1000, path);
    //string pathStr=utf8_To_GB2312(path);
   // strcpy(buf,pathStr.c_str());
    qDebug()<<path;
    pFile=fopen(path,"rb");  //二进制只读打开
    if(!pFile){
        qDebug()<<"file md5 open fail";
        return NULL;
    }
    int len=0;
    //开始偏移光标, 偏移到起始位置处
    fseek(pFile,start,SEEK_SET);
    //从起始位置处开始验证
    int readSize=0;
    char buffer[FILE_BLOCK_SIZE];
    do{
        readSize = fread(buffer,1,size,pFile);   //size为目标读取长度  ，readSize为实际读取长度
        md.update(buffer,readSize);
        size -= readSize;
    }while(size>0 && readSize>0);
    fclose(pFile);
    return md.toString();

}

//加载SQLite数据库文件
void CKernel::loadSQLdata()
{

    qDebug()<<__func__;
    //首先找到exe  去同级目录  创建数据文件 /datebase/id.db
    QString path = QCoreApplication::applicationDirPath() + "/datebase/";   //DirPath和FIlePath的区别！！
    QDir dir;
    if(!dir.exists(path)){   //如果不存在则创建
        dir.mkdir(path);
    }
    path = path + QString("%1.db").arg(m_id);

    QFileInfo info(path);
    if(info.exists())
    {
    //首先查看有没有这个文件
        //如果有的话则直接加载
            //连接
        m_sql->ConnectSql(path);
            //测试  读取数据

        QList<FileInfo> uploadTaskList=getUploadTask();
        QList<FileInfo> downloadTaskList=getDownloadTask();

        //对所有下载的信息，向对端发送下载请求
        if(downloadTaskList.size() > 0 )
        for(FileInfo & info: downloadTaskList){
            //如果这个文件没有了 不能继续（判断文件是否还存在）
            QFileInfo fi(info.filePath);
            if(!fi.exists()) continue;  //如果不存在,跳过本文件

            //打开文件，保存文件指针
            info.file = fopen(info.filePath,"ab");   //这时是追加写！
            //对所有下载信息，将其添加到信息框中
            Q_EMIT SIG_insertFileRows(info.userId,&info);
            //将信息添加到map中
            int num = info.userId * getNumber() + info.timestamp;
            mapIdTimestampToFileInfo[num] = info;
        }
        //处理上传信息
        if(uploadTaskList.size() > 0 )
        for(FileInfo & info : uploadTaskList)
        {
            //如果这个文件没有了不能继续
            QFileInfo fi(info.filePath);
            if(!fi.exists()) continue;

            //打开文件，保存文件指针
            info.file = fopen(info.filePath,"rb");
            //对所有下载信息，将其添加到信息框中
            Q_EMIT SIG_insertFileRows(info.friendId,&info);
            //将信息添加到map中

            int num = info.userId * getNumber() + info.timestamp;
            mapIdTimestampToFileInfo[num] = info;
        }



    }else{
        //没有  创建表
        QFile file(path);
        if(!file.open( QIODevice::WriteOnly )) return ;  //如果打开失败则返回
        file.close();
        //连接
        m_sql->ConnectSql(path);
        //创建表     //发送给别人的数据的表
        //上线的时候只主动请求我们从别人那里下载的文件，而我们上传给别人的文件则不主动请求，等别人来找我们请求
        QString sqlbuf = "create table t_upload( \
                userId int,      \
                tiemestamp int,   \
                size int ,  \
                isCut int ,  \
                cutNum int ,   \
                cutNow int ,   \
                cutSize int ,   \
                nowSize int ,   \
                filePath varchar(100),  \
                f_md5 varchar(60), friendId int)";
         m_sql->UpdateSql(sqlbuf);


            //接收别人数据的表
        sqlbuf = "create table t_download( \
                friendId int,      \
                tiemestamp int,   \
                size int ,  \
                isCut int ,  \
                cutNum int ,   \
                cutNow int ,   \
                cutSize int ,   \
                nowSize int ,   \
                filePath varchar(100),  \
                f_md5 varchar(60))";
         m_sql->UpdateSql(sqlbuf);
    }

    return;

}

void CKernel::sendFileBlockMd5(int friendId, FileInfo *fileInfo)
{
    string md5Str=getMd5(fileInfo->filePath,fileInfo->cutNow*fileInfo->cutSize,fileInfo->cutSize);
    STRU_TCP_FILE_BLOCK_MD5_RQ rq;
    strcpy(rq.md5,md5Str.c_str());
    rq.userId=m_id;
    rq.friendId = friendId;
    rq.timstamp = fileInfo->timestamp;
    m_pMediator->SendData(0,(char*)&rq,sizeof(rq));
    return;
}

//发送添加群聊请求
void CKernel::slot_addGroupChat(QString tel)
{
    STRU_TCP_ADD_CHAT_GROUP_RQ rq;
    rq.groupId = tel.toInt();
    rq.userId = m_id;
    strcpy(rq.userName, m_name.toStdString().c_str());
    m_pMediator->SendData(0,(char*)&rq,sizeof(rq));
}

//创建群聊
void CKernel::slot_createGroupChat(QString groupName)
{
    STRU_TCP_CREATE_CHAT_GROUP_RQ rq;
    rq.userId = m_id;
    strcpy(rq.groupName,groupName.toStdString().c_str());
    m_pMediator->SendData(0,(char*)&rq,sizeof(rq));
}

//发送群聊的聊天信息
void CKernel::slot_sendGroupChatInfo(QString text, int groupId)
{
    STRU_TCP_CHAT_GROUP_CHAT_INFO_RQ rq;
    rq.userId = m_id;
    strcpy(rq.info,text.toStdString().c_str());
    strcpy(rq.userName,m_name.toStdString().c_str());
    rq.groupId = groupId;
    m_pMediator->SendData(0,(char*)&rq,sizeof(rq));
}

//获取上传任务列表
QList<FileInfo> CKernel::getUploadTask()
{
    char sqlBuf[1024];
    sprintf(sqlBuf,"select * from t_upload;");
    QStringList strLst;
    QList<FileInfo> fileInfoLst;
    if(!m_sql->SelectSql(sqlBuf,11,strLst))
    {
        qDebug()<<"select failed with: "<<sqlBuf;
        return fileInfoLst;
    }

    while(strLst.size() != 0)
    {
        FileInfo fileInfo;
        fileInfo.userId = QString(strLst.front()).toInt();
        strLst.pop_front();

        fileInfo.timestamp = QString(strLst.front()).toInt();
        strLst.pop_front();

        fileInfo.size = QString(strLst.front()).toInt();
        strLst.pop_front();

        fileInfo.isCut = QString(strLst.front()).toInt();
        strLst.pop_front();

        fileInfo.cutNum = QString(strLst.front()).toInt();
        strLst.pop_front();

        fileInfo.cutNow = QString(strLst.front()).toInt();
        strLst.pop_front();

        fileInfo.cutSize = QString(strLst.front()).toInt();
        strLst.pop_front();

        fileInfo.nowSize = QString(strLst.front()).toInt();
        strLst.pop_front();

        strcpy(fileInfo.filePath, QString(strLst.front()).toStdString().c_str());
        strLst.pop_front();

        strcpy(fileInfo.md5, QString(strLst.front()).toStdString().c_str());
        strLst.pop_front();

        fileInfo.friendId = QString(strLst.front()).toInt();
        strLst.pop_front();

        fileInfo.pause = FILE_IS_PAUSE;
        fileInfoLst.push_back(fileInfo);
    }

    return fileInfoLst;

}

//获取下载任务列表
QList<FileInfo> CKernel::getDownloadTask()
{
    char sqlBuf[1024];
    sprintf(sqlBuf,"select * from t_download;");
    QStringList strLst;
    QList<FileInfo> fileInfoLst;
    if(!m_sql->SelectSql(sqlBuf,10,strLst))
    {
        qDebug()<<"select failed with: "<<sqlBuf;
        return fileInfoLst;
    }

    while(strLst.size() != 0)
    {
        FileInfo fileInfo;
        fileInfo.userId = QString(strLst.front()).toInt();
        strLst.pop_front();

        fileInfo.timestamp = QString(strLst.front()).toInt();
        strLst.pop_front();

        fileInfo.size = QString(strLst.front()).toInt();
        strLst.pop_front();

        fileInfo.isCut = QString(strLst.front()).toInt();
        strLst.pop_front();

        fileInfo.cutNum = QString(strLst.front()).toInt();
        strLst.pop_front();

        fileInfo.cutNow = QString(strLst.front()).toInt();
        strLst.pop_front();

        fileInfo.cutSize = QString(strLst.front()).toInt();
        strLst.pop_front();

        fileInfo.nowSize = QString(strLst.front()).toInt();
        strLst.pop_front();

        strcpy(fileInfo.filePath, QString(strLst.front()).toStdString().c_str());
        strLst.pop_front();

        strcpy(fileInfo.md5, QString(strLst.front()).toStdString().c_str());
        strLst.pop_front();

        fileInfo.pause = FILE_IS_PAUSE;
        fileInfoLst.push_back(fileInfo);
    }

    return fileInfoLst;
}

string CKernel::utf8_To_GB2312(const QString &utf8_)    //由于服务器端改用Linux下Qt实现，所以省去转码环节
{
    QTextCodec* gb2312code = QTextCodec::codecForName("gb2312");
    QByteArray ba=gb2312code->fromUnicode(utf8_);
    char *buf=new char[ba.size()+1];
    strcpy_s(buf,ba.size()+1,ba.data());


//    QString str(utf8_);
//    string result=str.toStdString();

    string result(buf);
    delete buf;
    return result;
}

QString CKernel::GB2312_To_utf8(const string &GB2312)
{
    QTextCodec* gb2312code = QTextCodec::codecForName("gb2312");
    QString result=gb2312code->toUnicode(GB2312.c_str());

//    string str(GB2312);
//    QString result(str.c_str());

    return result;
}

