#include "tcpServer.h"


tcpServer::tcpServer(INetMediator* pMediator)
{
	m_pNediator = pMediator;
}

tcpServer::~tcpServer()
{

}

bool tcpServer::InitNet()
{
    m_isStop = false;



    //2:¹ÍÈË--´´½¨Ì×½Ó×Ö

    m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  //´´½¨Ì×½Ó×Ö
    if (-1 == m_sock) {
        strerror(errno);

        return false;
    }
    else {
        cout << "socket success" << endl;
    }


    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(_DEF_TCP_PORT);
    serverAddr.sin_addr.s_addr =/* INADDR_ANY;*/ inet_addr _DEF_TCP_SERVER_IP;

    int err = bind(m_sock, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if (-1 == err) {
        strerror(errno);
        close(m_sock);

        return false;
    }
    else {
        cout << "bind success" << endl;
    }


    err = listen(m_sock, 10);
    if (-1 == err) {
        strerror(errno);
        close(m_sock);
        return false;
    }
    else
    {
        cout << "listen success" << endl;
    }


    //m_handle = (HANDLE)_beginthreadex(NULL, 0, &RecvConnectThread,(void*)this, 0, NULL);
    pthread_create(&m_tid,NULL,RecvConnectThread,(void*)this);
    return true;

}


bool tcpServer::SendData(long ISendIp, char* buf, int nLen)
{

    if (!buf || nLen <= 0) {
        cout << "send Error" << endl;
        return false;
    }


    if (send(ISendIp, (char*)&nLen, sizeof(int), 0) <= 0) {   //ISendIpÊ¹sockt
        strerror(errno);
        return false;
    }


    if (send(ISendIp, buf, nLen, 0) <= 0) {
        strerror(errno);
        return false;
    }

    return true;
}


void tcpServer::UninitNet()
{

    m_isStop = true;




    close(m_sock);

    for (auto ite = m_mapThreadIdToSocket.begin(); ite != m_mapThreadIdToSocket.end();)
    {
        int sock = ite.value();
        pthread_t tid=ite.key();
        close(sock);
        //这里不能在线程外让线程退出
        //转而选择采用非阻塞接收，程序结束时更新标志位
    }


}


void* tcpServer::RecvThread(void* IpVoid)
{
    pthread_detach(pthread_self());
    tcpServer* pThis = (tcpServer*)IpVoid;
    pThis->RecvData();
    return (void*)1;
}



void tcpServer::    RecvData()
{
    cout << " tcpServer::RecvData " << endl;

    usleep(10000);

    int sock = m_mapThreadIdToSocket[pthread_self()];


    int nRecvNum = 0;
    int nPackSize = 0;
    int offset = 0;
    while (!m_isStop) {

        nRecvNum = recv(sock, (char*)&nPackSize, sizeof(int), 0);   //阻塞接受
        if (nRecvNum > 0) {

            char* packBuf = new char[nPackSize];
            offset = 0;
            while (nPackSize > 0) {
                nRecvNum = recv(sock, packBuf + offset, nPackSize, 0);   //nPackSizeÎª´Ó»º³åÇøÈ¡µÄÊý¾ÝµÄ×î´ó³¤¶È
                if (nRecvNum > 0) {
                    offset += nRecvNum;
                    nPackSize -= nRecvNum;
                }
            }

            if (m_pNediator) {
                m_pNediator->DealData(sock, packBuf, offset);

            }
        }
        else if (0 == nRecvNum) {
            cout << "TcpServerNet::RecvData close connection" << endl;
            //»ØÊÕ×ÊÔ´
            auto ite = m_mapThreadIdToSocket.find(pthread_self());
            if(ite != m_mapThreadIdToSocket.end())
                m_mapThreadIdToSocket.erase(ite);
            close(sock);   //关闭套接字
            break;
        }
        else if(EAGAIN==nRecvNum || EWOULDBLOCK==nRecvNum ){
                //返回值为这两种则表示缓冲区没有数据
        }
        else
            {
            strerror(errno);
            cout<<"recv error!"<<endl;
        }
    }
    cout<<"recv thread exit success!"<<endl;
}


void* tcpServer::RecvConnectThread(void* IpVoid)
{
    pthread_detach(pthread_self());
    cout << " tcpServer::RecvConnectThread " << endl;
    tcpServer* pThis = (tcpServer*)IpVoid;
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);
    pthread_t threadId;
    while (!pThis->m_isStop)
    {
        cout << "TcpServerNet::AcceptThread accept" << endl;

        int sockWaiter = accept(pThis->m_sock, (sockaddr*)&clientAddr, (socklen_t*)&clientAddrSize);
        cout << "threadId: " << threadId << endl;
       // HANDLE handle = (HANDLE)_beginthreadex(NULL, 0, &RecvThread, (void*)pThis, 0, &threadId);
        pthread_create(&threadId,NULL,RecvThread,(void*)pThis);

        pThis->m_mapThreadIdToSocket[threadId] = sockWaiter;
    }
    cout<<"access thread exit success!"<<endl;
    return (void*)1;
}

