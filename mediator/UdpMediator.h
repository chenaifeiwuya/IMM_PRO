#pragma once
#include"INetMediator.h"

class UdpMediator :public INetMediator
{
   



    //°Ñ½ÓÊÕµ½µÄÊý¾Ý·¢ËÍ¸økernel
    void SIG_ReadData(long lSendIp , char* buf , int nLen);

public:
	UdpMediator(CKernel* kernel);
	~UdpMediator();
	//´ò¿ªÍøÂç
    bool OpenNet();
	//·¢ËÍÊý¾Ý
	bool SendData(long ISendIp, char* buf, int nLen);
	//¹Ø±ÕÍøÂç
	void CloseNet();
	//½ÓÊÕÊý¾Ý
	void DealData(long ISendIp, char* buf, int nLen);
};
