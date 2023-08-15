#pragma once
#include<iostream>
#include<QThread>
#include<pthread.h>
#include<set>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

using namespace std;

#pragma comment(lib,"Ws2_32.lib")

class INetMediator;   //ÏÈ¸æËß±àÒëÆ÷ÓÐÕâ¸öÀà£¬µ«ÊÇÃ»ÓÐ±àÒë
class INet
{
public:
	INet() {}
	virtual ~INet(){}

	//³õÊ¼»¯ÍøÂç
    virtual bool InitNet() = 0;
	//·¢ËÍÊý¾Ý
	 virtual bool SendData(long ISendIp, char* buf, int nLend=0)=0;

	//¹Ø±ÕÍøÂç
	virtual void UninitNet() = 0;


    //°ÑlongÀàÐÍµÄipµØÖ·×ª»»³ÉstringÀàÐÍµÄipµØÖ·
//    static std::string GetIpString(long ip)
//    {
//        sockaddr_in sockAddr;
//        sockAddr.sin_addr = ip;
//        return inet_ntoa(sockAddr.sin_addr);  //inet_ntoa()½«ÍøÂçµØÖ·×ª»»³É¡°.¡±µã¸ôµÄ×Ö·û´®¸ñÊ½
//    }
    //char*, std::string, QString (char*ÊÇ»ù´¡Êý¾ÝÀàÐÍ£¬std::stringºÍQStringÊÇ·â×°ºÃµÄÀà£¬»ù´¡Êý¾ÝÀàÐÍ¿ÉÒÔ¸øÀàÖ±½Ó¸³Öµ£©
    //std::string = char*, QString = char*
    //std::string µ÷ÓÃc_str()×ª»»³Échar*
    //QString ¿ÉÒÔµ÷ÓÃtoStdString×ª»»³Éstd::string

    //»ñÈ¡±¾µØIPµØÖ·ÁÐ±í
//    static set<long> GetValidIpList()
//    {
//        set<long> setIp;
//        long ip = 0;
//        int i=0;
//        //»ñÈ¡Ö÷»úÃû×Ö
//        char nameBuf[100]="";
//        gethostname(nameBuf, 100);
//        //2:¸ù¾ÝÖ÷»úÃû»ñÈ¡ipµØÖ·ÁÐ±í
//        struct hostent *remoteHost = gethostbyname(nameBuf);
//        while(remoteHost->h_addr_list[i] != 0){
//            ip = *(u_long *) remoteHost->h_addr_list[i++];
//            setIp.insert(ip);
//        }
//        return setIp;
//    }

protected:
	//½ÓÊÕÊý¾Ý
	virtual void RecvData() = 0;
	INetMediator* m_pNediator;   //ÖÐ½éÕßÀàÖ¸Õë£¬¸¸ÀàÖ¸ÕëÖ¸Ïò×ÓÀà½Ó¿Ú
    pthread_t m_tid;
};
