#pragma once
#include "tcpServerMediator.h"
#include "CMySql.h"
#include <map>
#include <list>
#include <string>

class CKernel;
#define BIND_PROTOCOL_PFUNC(x)  m_pFunc[(x)-_DEF_PROTOCOL_BASE-1]
typedef void (CKernel::*pFunc)(long, char*, int);    //º¯ÊýÖ¸ÕëÊý×é


class CKernel
{
public:
	CKernel();
	~CKernel();
public:
	void initMapFunc();


public:
	void dealReadyData(long Ip, char* buf, int len);
	void dealRegisterRq(long Ip, char* buf, int len);
	void dealLoginRq(long Ip, char* buf, int len);
	void dealFriendInfoRq(long Ip, char* buf, int len);
	void dealOfflineRq(long Ip, char* buf, int len);
	void dealChatRq(long Ip, char* buf, int len);
	void dealAddFriednRq(long Ip, char* buf, int len);
	void dealAddFriendRs(long Ip, char* buf, int len);
    void dealFileInfoRq(long Ip,char* buf, int len);       //
    void dealFileInfoRs(long Ip,char* buf,int len);
    void dealFileBlockRq(long Ip,char* buf,int len);
    void dealFileBlockRs(long Ip,char* buf,int len);
    void dealFileBlockMd5Rq(long Ip,char* buf,int len);
    void dealFileBlockMd5Rs(long Ip,char* buf,int len);
    void dealFileAllTranResult(long Ip,char* buf,int len);
    void dealFileContinueTranRq(long Ip,char* buf,int len);
    void dealAddChatGroupRq(long Ip,char* buf,int len);
    void dealAddChatGroupRs(long Ip,char* buf,int len);
    void dealGroupChatRq(long Ip,char* buf,int len);
    void dealCreateGroupRq(long Ip,char* buf,int len);


	void sendOnlineInfo(int id);   //ÏòidÖ¸¶¨ÓÃ»§µÄËùÓÐÔÚÏßºÃÓÑ·¢ËÍÆäÉÏÏßÏûÏ¢
	void sendOfflineInfo(int id);   //ÏòidÖ¸¶¨ÓÃ»§µÄËùÓÐÔÚÏßºÃÓÑ·¢ËÍÆäÏÂÏßÏûÏ¢
    void sendGroupInfo(int id);

public:
	INetMediator* m_pMediator;
	pFunc m_pFunc[PROTOCOL_NUM];
	CMySql m_sql;
    map<int, int> mpIdToSocket;    //±£´æÒÑÉÏÏßÓÃ»§id¶ÔÓ¦µÄsocket


};

