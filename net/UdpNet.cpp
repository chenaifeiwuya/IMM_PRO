#include"UdpNet.h"
#include"UdpMediator.h"
#include"packDef.h"


//µ¼ÈëÍøÂçº¯Êý¿â
//#pragma comment(lib,"Ws2_32.lib")

UdpNet::UdpNet(INetMediator* pMediator):m_sock(0),m_isStop(false)
{
	m_pNediator = pMediator;


}




UdpNet::~UdpNet() {
	m_isStop = true;
	UninitNet();
}

//³õÊ¼»¯ÍøÂç£¬¼ÓÔØ¿â£¬´´½¨Ì×½Ó×Ö£¬°ó¶¨ipµØÖ·£¬´´½¨Ò»¸öÏß³Ì£¨½ÓÊÕÊý¾Ý£©
bool UdpNet::InitNet()
{
	//2:¹ÍÈË------´´½¨Ì×½Ó×Ö
	m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (-1 == m_sock)
	{
        strerror(errno);

		return false;
	}
	else {
		std::cout << "socket success." << std::endl;
	}

//	//ÉêÇë¹ã²¥È¨ÏÞ
//	BOOL bval = TRUE;
//	setsockopt(m_sock, SOL_SOCKET, SO_BROADCAST, (char*)&bval, sizeof(bval));




	//3.Ñ¡µØÖ·-----°ó¶¨ipµØÖ·
	sockaddr_in sockAddr;
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(_DEF_UDP_PORT);        //½«ÕûÐÍ±äÁ¿´ÓÖ÷»ú×Ö½ÚÐò±ä³ÉÍøÂç×Ö½ÚÐò
    sockAddr.sin_addr.s_addr = /*INADDR_ANY;  */  inet_addr _DEF_TCP_SERVER_IP;
    int err = bind(m_sock, (sockaddr*)&sockAddr, sizeof(sockAddr));
    if (-1 == err) {
        strerror(errno);
        return false;
    }
    else
    {
        std::cout << "bind success. " << std::endl;
    }

	//==================================================================
	//4:´´½¨Ïß³Ì½ÓÊÕÊý¾Ý
	//CreateThread¶ÔÓ¦µÄ½áÊøÏß³ÌµÄº¯ÊýÊÇExitThread.
	//ExitThreadÔÚ½áÊøÏß³ÌµÄÊ±ºò£¬Èç¹ûÏß³ÌÀïÃæÓÐc++ÔËÐÐÊ±¿âµÄº¯Êý£¬±ÈÈçstrcpy£¬ÕâÀàº¯ÊýÔÚÖ´ÐÐµÄÊ±ºò»áÉêÇë¿Õ¼ä£¬µ«²»»ØÊÕ¿Õ¼ä£¬
	//ExitThreadÔÚÍË³öµÄÊ±ºòÒ²²»»á°ïÃ¦»ØÊÕÉêÇëµÄ¿Õ¼ä£¬ÕâÑù¾Í»áÔì³ÉÄÚ´æÐ¹Â©¡£
	//beginthreadex¶ÔÓ¦µÄ½áÊøÏß³ÌµÄº¯ÊýÊÇ_endthreadex¡£_endthreadexÔÚ½áÊøÏß³ÌµÄÊ±ºò£¬»áÏÈ»ØÊÕÏß³ÌÖÐÉêÇëµÄ¿Õ¼ä£¬ÔÚµ÷ÓÃExitThread½áÊøÏß³Ì¡£

    //m_handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, (void*)this, 0, NULL);
    pthread_create(&m_tid,NULL,RecvThread,(void*)this);
	return true;
}


//Ïß³Ìº¯Êý£ºµ÷ÓÃ½ÓÊÕÊý¾ÝµÄº¯ÊýRecvData
void* UdpNet::RecvThread(void* IpVoid)
{
    pthread_detach(pthread_self());  //线程分离
	UdpNet* pThis = (UdpNet*)IpVoid;
	pThis->RecvData();
    return (void*)1;
}



//·¢ËÍÊý¾Ý
bool UdpNet::SendData(long lSendIp, char* buf, int nLen)
{
	if (m_mapIdToSockAddr_in.count(lSendIp) > 0)
	{
		sockaddr_in addr = m_mapIdToSockAddr_in[lSendIp];

		//        QString ip=QString("192.168.1.100");
			//addr.sin_addr.S_un.S_addr = inet_addr((ip.c_str())) ;   //½«ipµØÖ·¹Ì¶¨Îª·þÎñÆ÷µÄipµØÖ·
		if (sendto(m_sock, buf, nLen, 0, (sockaddr*)&addr, sizeof(addr)) <= 0) {
            strerror(errno);
			return false;
		}
		return true;
	}
	cout << " ÎÞ´ËÈË " << endl;
	return false;


}

//¹Ø±ÕÍøÂç
void UdpNet::UninitNet()
{
	//1:¹Ø±ÕÏß³Ì
	m_isStop = true;

	//2£º¹Ø±Õsocket
    close(m_sock);
}

//½ÓÊÕÊý¾Ý
void UdpNet::RecvData()
{


	int nRecvNum = 0;
    char recvBuf[10 *1024 ] = "";
	sockaddr_in addrFrom;
	int addrFromSize = sizeof(addrFrom);
	while (!m_isStop) {
        nRecvNum = recvfrom(m_sock, recvBuf, sizeof(recvBuf), 0, (sockaddr*)&addrFrom, ( socklen_t *)&addrFromSize);
		if (nRecvNum > 0) {
			//½ÓÊÕµ½Êý¾Ý£¬newÒ»¸öÐÂ¿Õ¼ä£¬ÓÃÀ´±£´æÊý¾Ý£¬·ÀÖ¹recvBuf±»ÔÙ´ÎÐ´Èë£¬ÉÏÒ»´Î½ÓÊÕµ½µÄÊý¾Ý¾ÍÃ»ÓÐÁË
			char* packBuf = new char[nRecvNum];
			memcpy(packBuf, recvBuf, nRecvNum);
			//´«¸øÖÐ½éÕß

				if (m_pNediator) {
                    m_pNediator->DealData(addrFrom.sin_addr.s_addr, packBuf, nRecvNum);
					//TODO£º»ØÊÕ¿Õ¼ädelete[]----kernelÖªµÀÊ²Ã´Ê±ºòÊ¹ÓÃÍêÊý¾Ý£¬ÔÙ»ØÊÕ
				}
			
		}
	}



}


