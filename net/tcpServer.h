#pragma once
#include"INet.h"
#include"packDef.h"
#include<QMap>
#include "tcpServerMediator.h"
class tcpServer:public INet
{
public:
    tcpServer(INetMediator* pMediator);
    ~tcpServer();
    //³õÊ¼»¯ÍøÂç
    bool InitNet();
    //·¢ËÍÊý¾Ý
    bool SendData(long ISendIp, char* buf, int nLen);
    //¹Ø±ÕÍøÂç
    void UninitNet();

protected:
    //½ÓÊÕÊý¾Ý
    void RecvData();
    //   ½ÓÊÕÁ¬½ÓµÄÏß³Ì
    static void* RecvConnectThread(void* IpVoid);
    //½ÓÊÕÊý¾ÝµÄÏß³Ì
    static void* RecvThread(void* IpVoid);


    int m_sock;   //Ì×½Ó×Ö
    //HANDLE m_handle;   //Ïß³Ì¾ä±ú
    bool m_isStop;
    //±£´æÃ¿¸ö¿Í»§¶Ë¶ÔÓ¦µÄ½ÓÊÕÊý¾ÝµÄÏß³Ì¾ä±ú£¬keyÊÇ¿Í»§¶Ë¶ÔÓ¦µÄsocket
   // map<int, HANDLE> m_mapSocketToHandle;    //ÓÃÓÚÔÚ»ØÊÕ×ÊÔ´Ê±»ØÊÕ×ÊÔ´
    //±£´æ¸úÃ¿¸ö¿Í»§¶ËÍ¨ÐÅµÄsocket£¬keyÊÇÏß³Ìid
    QMap<pthread_t, int> m_mapThreadIdToSocket;    //ÓÃÓÚÔÚÏß³ÌÖÐ¸ù¾ÝÏß³Ìid»ñÈ¡SOCKET
    

  /*  map<long, SOCKET> sockAddr_Server_Client;*/
    //FILE* pFile;   //ÎÄ¼þÖ¸Õë
    //STRU_FILE_INFO_RQ rq;//µ±Ç°´«ÊäÎÄ¼þµÄÇëÇóÐÅÏ¢
    //sockaddr_in serverAddr;//sockaddr_inÊÇÏµÍ³·â×°µÄÒ»¸ö½á¹¹Ìå£¬¾ßÌå°üº¬ÁË³ÉÔ±±äÁ¿£ºsin_family¡¢sin_addr¡¢sin_zero
};

