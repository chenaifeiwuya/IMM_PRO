#include"UdpMediator.h"
#include"UdpNet.h"
#include"../CKernel.h"

UdpMediator::UdpMediator(CKernel* kernel)
{
	m_pNet = new UdpNet(this);   //½áºÏUdpNetµÄ¹¹Ôìº¯ÊýÀ´¿´
	p_Kernel = kernel;
}

UdpMediator::~UdpMediator() {
	//»ØÊÕ×ÊÔ´
	if (m_pNet) {
		delete m_pNet;
		m_pNet = NULL;
	}
}

//´ò¿ªÍøÂç
bool UdpMediator::OpenNet()
{
    if (!m_pNet->InitNet()) {
		return false;
	}
	return true;
}

//·¢ËÍÊý¾Ý
bool UdpMediator::SendData(long ISendIp, char* buf, int nLen)
{
	if (!m_pNet->SendData(ISendIp, buf, nLen)) {
		return false;
	}
	return true;
}

//¹Ø±ÕÍøÂç
void UdpMediator::CloseNet()
{
	m_pNet->UninitNet();
}


//½ÓÊÕÊý¾Ý
void UdpMediator::DealData(long ISendIp, char* buf, int nLen)
{


        //°Ñ½ÓÊÕµ½µÄÊý¾Ý·¢¸øckernel
	p_Kernel->dealReadyData( ISendIp,  buf, nLen);
}
