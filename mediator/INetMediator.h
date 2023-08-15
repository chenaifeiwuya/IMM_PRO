#pragma once

class CKernel; //¸æËß±àÒëÆ÷ÓÐÕâ¸öÀà£¬µ«ÊÇ»¹Î´±àÒë
class INet;//¸æËß±àÒëÆ÷ÓÐÕâ¸öÀà£¬µ«ÊÇ»¹Î´±àÒë
class INetMediator
{
   
public:
    INetMediator();
    virtual ~INetMediator();
	//´ò¿ªÍøÂç
    virtual bool OpenNet()=0;
	//·¢ËÍÊý¾Ý
	virtual bool SendData(long ISendIp, char* buf, int nLen) = 0;
	//¹Ø±ÕÍøÂç¡¢
	virtual void CloseNet() = 0;
	//½ÓÊÕÊý¾Ý
	virtual void DealData(long ISendIp, char* buf, int nLen) = 0;

protected:
	INet* m_pNet;    //ÍøÂç½Ó¿ÚÀàÖ¸Õë
	CKernel* p_Kernel;
};
