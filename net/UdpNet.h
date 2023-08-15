#pragma once
#include "INet.h"
#include<iostream>
#include<list>
#include<map>



class UdpNet :public INet
{
public:
	UdpNet(INetMediator* pMediator);
	~UdpNet();
	//³õÊ¼»¯ÍøÂç
    bool InitNet();
	//·¢ËÍÊý¾Ý
	bool SendData(long ISendlp, char* buf, int nLen);
	//¹Ø±ÕÍøÂç
	void UninitNet();

	//typedef struct RecvInfo {
	//	long ISendIp;
	//	char* buf;
	//	int nLen;
	//};
	//static std::list<RecvInfo*> RecvInfoLst;
	//static SOCKET sock;


protected:
	//½ÓÊÕÊý¾Ý
	void RecvData();
	//Ïß³Ìº¯Êý£¬½ÓÊÕÊý¾Ý
     static void* RecvThread(void* IpVoid);


    int m_sock;
	bool m_isStop;

	//±£´æÓÃ»§id¶ÔÓ¦µÄipµØÖ·£¨UDP£©
	map<long, sockaddr_in> m_mapIdToSockAddr_in;   //ÒòÎªÉÏÏßÇëÇóºÍÏÂÏßÇëÇóÊÇÔÚtcpÖÐÊµÏÖµÄ£¬ËùÒÔ´Ë³ÉÔ±Ó¦Í¬Ê±ÅäºÏ×ÅTcp²¿·Öº¯ÊýÊ¹ÓÃ
	long num;   //¶ÔsockµØÖ·±àºÅ·½±ã²éÕÒ


};

