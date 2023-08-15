#pragma once
#include"INetMediator.h"
#include"tcpServer.h"
    class TcpServerMediator :public INetMediator
    {

    public:
        TcpServerMediator(CKernel* kernel);
        ~TcpServerMediator();
        //´ò¿ªÍøÂç
        bool OpenNet();
        //·¢ËÍÊý¾Ý
        bool SendData(long ISendIp, char* buf, int nLen);
        //¹Ø±ÕÍøÂç
        void CloseNet();
        //½ÓÊÕÊý¾Ý
        void DealData(long ISendIp, char* buf, int nLen);


      

    };



