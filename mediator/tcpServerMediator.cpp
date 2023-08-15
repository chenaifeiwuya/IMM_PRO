#include "tcpServerMediator.h"
#include "../CKernel.h"

TcpServerMediator::TcpServerMediator(CKernel* kernel)
{
    m_pNet = new tcpServer(this);   //½áºÏUdpNetµÄ¹¹Ôìº¯ÊýÀ´¿´
    p_Kernel = kernel;

}

TcpServerMediator::~TcpServerMediator()
{
    m_pNet->UninitNet();
    delete m_pNet;
    m_pNet = NULL;
}

//´ò¿ªÍøÂç£º½¨Á¢Á¬½Ó
bool TcpServerMediator::OpenNet()
{
    if (m_pNet->InitNet())
    {
        return true;
    }
    return false;
}

//·¢ËÍÊý¾Ý
bool TcpServerMediator::SendData(long ISendIp, char* buf, int nLen)
{
    if (m_pNet->SendData(ISendIp, buf, nLen))  
        return true;

    return false;
}

//¹Ø±ÕÍøÂç
void TcpServerMediator::CloseNet()
{
    return;
}

//½ÓÊÕÊý¾Ý
void TcpServerMediator::DealData(long ISendIp, char* buf, int nLen)
{
    //TODO:Í¨¹ýÐÅºÅ°Ñ½ÓÊÕµ½µÄÊý¾Ý·¢¸øckernel
    cout << "TcpServerMediator::DealData " << buf << endl;
    //²âÊÔ´úÂë
    //SendData(ISendIp, buf, nLen);
//Q_EMIT SIG_ReadData(0,buf,0);

    //°Ñ½ÓÊÜµ½µÄÊý¾Ý·¢¸økernel
    p_Kernel->dealReadyData(ISendIp, buf, nLen);
}
