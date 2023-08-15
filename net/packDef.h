#pragma once

#include <memory.h>
#include <string>

#define _DEF_UDP_PORT		(23145)
#define _DEF_MAX_SIZE		(100)
#define _MAX_SIZE           (100)
#define _DEF_CONTENT_MAX    (1024)
#define _DEF_BUFFER_SIZE    (4096)
#define _DEF_TCP_PORT       (23146)
#define _DEF_TCP_SERVER_IP  ("192.168.174.131")


//协议头
#define _DEF_PROTOCOL_BASE        (1000)

//上线请求和回复
#define _DEF_PROTOCOL_ONLINE_RQ   (_DEF_PROTOCOL_BASE + 1)
#define _DEF_PROTOCOL_ONLINE_RS   (_DEF_PROTOCOL_BASE + 2)

//聊天请求
#define _DEF_PROTOCOL_CHAT_RQ       (_DEF_PROTOCOL_BASE + 3)
//下线请求
#define _DEF_PROTOCOL_OFFLINE_RQ     (_DEF_PROTOCOL_BASE + 4)



//注册
#define _DEF_TCP_REGISTER_RQ      (_DEF_PROTOCOL_BASE + 10)
#define _DEF_TCP_REGISTER_RS      (_DEF_PROTOCOL_BASE + 11)

//登录
#define _DEF_TCP_LOGIN_RQ         (_DEF_PROTOCOL_BASE + 12)
#define _DEF_TCP_LOGIN_RS		  (_DEF_PROTOCOL_BASE + 13)

//好友信息
#define _DEF_TCP_FRIEND_INFO      (_DEF_PROTOCOL_BASE + 14)
//t添加好友
#define _DEF_TCP_ADD_FRIEND_RQ    (_DEF_PROTOCOL_BASE + 15)
#define _DEF_TCP_ADD_FRIEND_RS    (_DEF_PROTOCOL_BASE + 16)
//下线
#define _DEF_TCP_OFFLINE          (_DEF_PROTOCOL_BASE + 17)


//文件信息请求/回复
#define _DEF_TCP__FILE_INFO_RQ     (_DEF_PROTOCOL_BASE + 18)
#define _DEF_TCP__FILE_INFO_RS     (_DEF_PROTOCOL_BASE + 19)

//文件块请求/回复
#define _DEF_TCP_FILE_BLOCK_RQ      (_DEF_PROTOCOL_BASE + 20)
#define _DEF_TCP_FILE_BLOCK_RS      (_DEF_PROTOCOL_BASE + 21)

//文件分片后每片的md5验证请求
#define _DEF_TCP_FILE_BLOCK_MD5_RQ   (_DEF_PROTOCOL_BASE + 22)
#define _DEF_TCP_FILE_BLOCK_MD5_RS   (_DEF_PROTOCOL_BASE + 23)

//文件传输结果通知
#define _DEF_TCP_FILE_ALL_TRAN_RESULT  (_DEF_PROTOCOL_BASE + 24)

//断点续传请求
#define _DRF_TCP_FILE_CONTINUE_TRAN_RQ  (_DEF_PROTOCOL_BASE + 25)

//添加群聊请求/回复
#define _DEF_TCP_ADD_CHAT_GROUP_RQ      (_DEF_PROTOCOL_BASE + 26)
#define _DEF_TCP_ADD_CHAT_GROUP_RS      (_DEF_PROTOCOL_BASE + 27)

//群聊消息请求
#define _DEF_TCP_CHAT_GROUP_CHAT_INFO_RQ     (_DEF_PROTOCOL_BASE + 28)

//创建群聊请求/回复
#define _DEF_TCP_CREATE_CHAT_GROUP_RQ   (_DEF_PROTOCOL_BASE + 29)
#define _DEF_TCP_CREATE_CHAT_GROUP_RS   (_DEF_PROTOCOL_BASE + 30)

//群聊信息发送
#define _DEF_TCP_CHAT_GROUP_INFO_RQ     (_DEF_PROTOCOL_BASE + 31)

//用于表示协议末尾以及协议数量
#define _DEF_PROTOCOL_END           (_DEF_PROTOCOL_BASE + 32)
#define PROTOCOL_NUM                (_DEF_PROTOCOL_END - _DEF_PROTOCOL_BASE - 1)

//UDP   协议结构体
//上线请求和回复
//上线请求/回复：协议头，自己的名字
struct STRU_ONLINE
{
    STRU_ONLINE() :type(_DEF_PROTOCOL_ONLINE_RQ)
    {
        memset(name, 0, _DEF_MAX_SIZE);   //初始化字符数组name为全0
    }
    int type;
    //unsigned long ip;
    char name[_DEF_MAX_SIZE];
};

//聊天请求：协议头，聊天内容
struct STRU_CHAT
{
    STRU_CHAT() :type(_DEF_PROTOCOL_CHAT_RQ)
    {
        memset(content, 0, _DEF_CONTENT_MAX);
    }
    int type;
    char content[_DEF_CONTENT_MAX];
};


//下线请求：协议头
struct STRU_OFFLINE
{
    STRU_OFFLINE() :type(_DEF_PROTOCOL_OFFLINE_RQ)
    {

    }
    int type;
};


//TCP协议请求
//注册

typedef int PackType;
// 注册请求:协议头、手机号、昵称、密码
typedef struct STRU_TCP_REGISTER_RQ {
    STRU_TCP_REGISTER_RQ() :type(_DEF_TCP_REGISTER_RQ)
    {
        memset(tel, 0, _DEF_MAX_SIZE);
        memset(name, 0, _DEF_MAX_SIZE);
        memset(password, 0, _DEF_MAX_SIZE);
    }
    PackType type;
    char tel[_DEF_MAX_SIZE];
    char name[_DEF_MAX_SIZE];
    char password[_DEF_MAX_SIZE];
}STRU_TCP_REGISTER_RQ;

// 注册回复:协议头、注册结果(用户已经存在、注册成功)

#define REGISTER_SUCCESS (0)
#define USER_IS_EXIST (1)

typedef struct STRU_TCP_REGISTER_RS {
    STRU_TCP_REGISTER_RS() : type(_DEF_TCP_REGISTER_RS), result(REGISTER_SUCCESS)
    {

    }
    PackType type;
    int result;
}STRU_TCP_REGISTER_RS;


//登录请求：协议头
typedef struct STRU_TCP_LOGIN_RQ {
    STRU_TCP_LOGIN_RQ() :type(_DEF_TCP_LOGIN_RQ)
    {
        memset(tel, 0, _DEF_MAX_SIZE);
        memset(password, 0, _DEF_MAX_SIZE);
    }
    PackType type;
    char tel[_DEF_MAX_SIZE];
    char password[_DEF_MAX_SIZE];
}STRU_TCP_LOGIN_RQ;

//登录回复：协议头，登录结果
#define LOGIN_SUCCESS (0)
#define PASSWORD_ERROR (1)
#define USER_IS_NOTEXIST (2)
#define USER_IS_ONLINE (3)
typedef struct STRU_TCP_LOGIN_RS {
    STRU_TCP_LOGIN_RS() :type(_DEF_TCP_LOGIN_RS), userId(0), result(LOGIN_SUCCESS)
    {
        memset(name, 0, _DEF_MAX_SIZE);
        memset(feeling, 0, _DEF_MAX_SIZE);
    }
    PackType type;
    int userId;
    char name[_DEF_MAX_SIZE];
    char feeling[_DEF_MAX_SIZE];
    int result;
}STRU_TCP_LOGIN_RS;




//聊天请求：协议头，聊天内容，我是谁userId， 发给谁friendId
typedef struct STRU_TCP_CHAT_RQ {
    STRU_TCP_CHAT_RQ() :type(_DEF_PROTOCOL_CHAT_RQ), userId(0), friendId(0)
    {
        memset(content, 0, _DEF_CONTENT_MAX);
    }
    PackType type;
    int userId;
    int friendId;
    char content[_DEF_CONTENT_MAX];
}STRU_TCP_CHAT_RQ;



//添加好友请求：协议头
typedef struct STRU_TCP_ADD_FRIEND_RQ {
    STRU_TCP_ADD_FRIEND_RQ() : type(_DEF_TCP_ADD_FRIEND_RQ), userId(0)
    {
        memset(userName, 0, _DEF_MAX_SIZE);
        memset(friendName, 0, _DEF_MAX_SIZE);
    }
    PackType type;
    int userId;
    char userName[_DEF_MAX_SIZE];
    char friendName[_DEF_MAX_SIZE];
}STRU_TCP_ADD_FRIEND_RQ;

//添加好友回复：协议头
#define ADD_FRIEND_SUCCESS (0)
#define ADD_FRIEND_FAILED (1)
typedef struct STRU_TCP_ADD_FRIEND_RS {
    STRU_TCP_ADD_FRIEND_RS() : type(_DEF_TCP_ADD_FRIEND_RS), userId(0)
    {

        memset(friendName, 0, _DEF_MAX_SIZE);
    }
    PackType type;
    int userId;
    int friendId;
    int result;
    char friendName[_DEF_MAX_SIZE];
}STRU_TCP_ADD_FRIEND_RS;

//下线请求：协议头
typedef struct STRU_TCP_OFFLINE_RQ {
    STRU_TCP_OFFLINE_RQ() :type(_DEF_TCP_OFFLINE), userId(0)
    {

    }
    PackType type;
    int userId;
}STRU_TCP_OFFLINE_RQ;



//获取好友信息：协议头， 用户id， 昵称， 签名， 头像id， 状态
#define STATUS_ONLINE (0)
#define STATUS_OFFLINE (1)
typedef struct STRU_TCP_FRIEND_INFO {
    STRU_TCP_FRIEND_INFO() :type(_DEF_TCP_FRIEND_INFO), userId(0), iconId(0), status(STATUS_ONLINE)
    {

    }
    PackType type;
    int userId;
    int iconId;    //头像id
    int status;
    char name[_DEF_MAX_SIZE];
    char feeling[_DEF_MAX_SIZE];
}STRU_TCP_FRIEND_INFO;




//文件信息

#define _CUT_YES (0)   //是的，要切片
#define _CUT_NO  (1)    //不切片

#define _DEF_CUT_SIZE  (2 * 1000 * 1024)    //每片大小
#define _DEF_CUT_LIMIT (2 * 1000 * 1024)    //是否切片的标记位

#define FILE_IS_PAUSE (0)
#define FILE_IS_STARTED (1)

struct FileInfo{
    FileInfo():file(NULL),userId(0),isCut(_CUT_NO),cutNum(0),cutNow(0),cutSize(_DEF_CUT_SIZE),nowSize(0),pause(FILE_IS_STARTED){
        memset(filePath,0,_DEF_MAX_SIZE);
        memset(md5,0,_MAX_SIZE);
    }

    FILE* file;
    int userId;      //用户id    用户id是发送这个文件者的id
    int timestamp;   //时间戳,用户id和时间戳唯一确定一个传输文件
    int size;     //总大小
    int isCut;   //是否分片的标记位
    int cutNum;  //若切片，共切分成几片
    int cutNow;   //若切片，当前是第几片
    int cutSize;  //一片有多大
    int nowSize;   //当前成功传输了当前片的多少数据
    char filePath[_DEF_MAX_SIZE];   //文件保存地址
    char md5[_MAX_SIZE];   //这是整个项目中的md5
    char md5Now[_MAX_SIZE];   //这个是当前分片的md5
    int friendId;              //这个是对端的id，只在从数据库中加载上传文件时用到
    int pause;
};

//文件信息请求
//文件名  文件的唯一标识（通过发送者id + 时间来唯一标识）  文件整体MD5校验码  是否分片  分成多少片
//_DEF_TCP__FILE_INFO_RQ



struct STRU_TCP_FILE_INFO_RQ{
    STRU_TCP_FILE_INFO_RQ(): type(_DEF_TCP__FILE_INFO_RQ),userid(0),size(0),isCut(_CUT_NO)
    {
        memset(fileName,0,_MAX_SIZE);
        memset(md5,0,_MAX_SIZE);
    }

    PackType type;
    char fileName[_MAX_SIZE];
    int userid;
    int targetId;
    int size;    //记录当前文件的大小
    int isCut;   //是否分片的标记位
    int cutNum;  //若切片，共切分成几片
    int timestamp;   //时间戳,文件唯一标识
    char md5[_MAX_SIZE];   //整体文件的md5
};


#define FILEINFO_RESULT_ACCEPT (0)
#define FILEINFO_RESULT_REFUSED (1)

//文件信息回复
struct STRU_TCP_FILE_INFO_RS{
    STRU_TCP_FILE_INFO_RS(): type(_DEF_TCP__FILE_INFO_RS),userId(0),result(FILEINFO_RESULT_ACCEPT)
    {

    }

    PackType type;
    int timestamp;   //时间戳,文件唯一标识
    int result;     //是否接收
    int targetId;
    int userId;     //文件信息接收者的id
};

//文件传输块
#define FILE_BLOCK_SIZE         (20*1024)    //每次传输文件的大小
#define FILE_TRAN_SUCCESS       (0)     //表示当前分片传输成功
#define FILE_TRAN_FAILED        (1)     //表示当前分片传输出错
#define FILE_TRAN_NOTEND        (2)     //表示当前分片未到结尾

struct STRU_TCP_FILE_BLOCK_RQ{
    STRU_TCP_FILE_BLOCK_RQ():type(_DEF_TCP_FILE_BLOCK_RQ),userId(0),friendId(0),timestamp(0){
        memset(fileBlock,0,FILE_BLOCK_SIZE);
    }
    PackType type;
    int userId;
    int friendId;
    int timestamp;
    int size;  //当前传输块的大小
    char fileBlock[FILE_BLOCK_SIZE];
};

struct STRU_TCP_FILE_BLOCK_RS{
    STRU_TCP_FILE_BLOCK_RS():type(_DEF_TCP_FILE_BLOCK_RS),userId(0),friendId(0),timestamp(0),result(FILE_TRAN_SUCCESS){
    }
    PackType type;
    int userId;
    int friendId;
    int timestamp;
    int size;      //写入大小
    int result;
};


//文件块md5验证请求
struct STRU_TCP_FILE_BLOCK_MD5_RQ{
    STRU_TCP_FILE_BLOCK_MD5_RQ():type(_DEF_TCP_FILE_BLOCK_MD5_RQ),userId(0),friendId(0){
        memset(md5,0,_MAX_SIZE);
    }

    PackType type;
    int userId;
    int friendId;
    int timstamp;   //时间戳
    char md5[_MAX_SIZE];    //返回的验证码
};

//文件块md5验证回复
struct STRU_TCP_FILE_BLOCK_MD5_RS{
    STRU_TCP_FILE_BLOCK_MD5_RS():type(_DEF_TCP_FILE_BLOCK_MD5_RS),userId(0),friendId(0){

    }

    PackType type;
    int userId;
    int friendId;
    int timestamp;  //时间戳
};


#define FILE_TRAN_ALL_SUCCESS  (0)   //文件传输成功
#define FILE_TRAN_ALL_FAILED   (1)      //文件传输失败

struct STRU_TCP_FILE_ALL_TRAN_RESULT{
    STRU_TCP_FILE_ALL_TRAN_RESULT():type(_DEF_TCP_FILE_ALL_TRAN_RESULT){

    }

    PackType type;
    int userId;
    int friendId;
    int timestamp;
    int result;
};


struct STRU_TCP_FILE_CONTINUE_TRAN_RQ{
    STRU_TCP_FILE_CONTINUE_TRAN_RQ():type(_DRF_TCP_FILE_CONTINUE_TRAN_RQ){

    }

    PackType type;
    int userId;
    int friendId;
    int timestamp;
    int cutNow;    //请求的是从第几片开始传输
    int nowSize;   //当前片传输了多少字节了
};



//添加群聊请求
struct STRU_TCP_ADD_CHAT_GROUP_RQ{
    STRU_TCP_ADD_CHAT_GROUP_RQ():type(_DEF_TCP_ADD_CHAT_GROUP_RQ){
        memset(userName,0,_MAX_SIZE);
    }
    PackType type;
    int userId;
    int groupId;
    char userName[_MAX_SIZE];
    char groupName[_MAX_SIZE];   //群聊名字，添加群聊用户不用写入该字段，而是由服务器查询写入
};

//添加群聊回复
#define ADD_CHAT_GROUP_SUCCESS  (0)             //添加成功
#define ADD_CHAT_GROUP_FAILED   (1)             //添加失败
#define ADD_CHAT_GROUP_GROUPER_OFFLINE (2)      //群主不在线的回复
#define ADD_CHAT_GROUP_NOT_EXIST  (3)
struct STRU_TCP_ADD_CHAT_GROUP_RS{
    STRU_TCP_ADD_CHAT_GROUP_RS():type(_DEF_TCP_ADD_CHAT_GROUP_RS){

    }
    PackType type;
    int userId;
    int friendId;
    int groupId;
    int result;   //添加结果
};


//群聊聊天结构体
struct STRU_TCP_CHAT_GROUP_CHAT_INFO_RQ{
    STRU_TCP_CHAT_GROUP_CHAT_INFO_RQ():type(_DEF_TCP_CHAT_GROUP_CHAT_INFO_RQ){
        memset(userName,0,_MAX_SIZE);
        memset(info,0,_MAX_SIZE);
    }
    PackType type;
    int userId;
    int groupId;
    char userName[_MAX_SIZE];
    char info[_MAX_SIZE];
};


//创建群聊请求结构体
struct STRU_TCP_CREATE_CHAT_GROUP_RQ{
    STRU_TCP_CREATE_CHAT_GROUP_RQ():type(_DEF_TCP_CREATE_CHAT_GROUP_RQ){
        memset(groupName,0,_MAX_SIZE);
    }
    PackType type;
    int userId;
    char groupName[_MAX_SIZE];
};

//创建群聊回复
#define CREATE_GROUP_SUCCESS (0)
#define CREATE_GROUP_FAILED  (1)

struct STRU_TCP_CREATE_CHAT_GROUP_RS{
    STRU_TCP_CREATE_CHAT_GROUP_RS():type(_DEF_TCP_CREATE_CHAT_GROUP_RS){
        memset(groupName,0,_MAX_SIZE);
    }
    PackType type;
    int groupId;              //群组号
    int result;               //群聊创建结果
    char groupName[_MAX_SIZE];  //群组名称
};

//群聊信息请求
struct STRU_TCP_CHAT_GROUP_INFO_RQ{
    STRU_TCP_CHAT_GROUP_INFO_RQ():type(_DEF_TCP_CHAT_GROUP_INFO_RQ){
        memset(groupName,0,_MAX_SIZE);
    }
    PackType type;
    int groupId;
    char groupName[_MAX_SIZE];   //群组名称
};

