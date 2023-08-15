#include "CKernel.h"

CKernel::CKernel()
{

	initMapFunc();
	m_pMediator = new TcpServerMediator(this);
	//´ò¿ªÍøÂç
	if (!m_pMediator->OpenNet())
	{
        cout << "Inet open failed" << endl;
		exit(0);
	}

	//Á´½ÓÊý¾Ý¿â
	//±¾´ÎÊý¾Ý¿âÊ¹ÓÃµÄÊÇÔø¾­´´½¨µÄÊý¾Ý¿â£¬²¢Î´ÐÂ´´½¨
    if (!m_sql.ConnectMySql("127.0.0.1", "root", "mmm959825", "IMMSQL"))
	{
		//Èç¹ûÁ¬½ÓÊ§°Ü
        cout << "MySQL connect failed!" << endl;
		exit(0);
	}
	else
	{
        cout << "MySQL connect success!" << endl;
	}

}

CKernel::~CKernel()
{
	//»ØÊÕ×ÊÔ´
	//1:»ØÊÕÖÐ½éÕßÀà  ¹Ø±ÕÍøÂ·
	if (m_pMediator) {
		m_pMediator->CloseNet();
		delete m_pMediator;
		m_pMediator = NULL;
	}
	
}

void CKernel::initMapFunc()
{
	BIND_PROTOCOL_PFUNC(_DEF_TCP_REGISTER_RQ) = &CKernel::dealRegisterRq;
	BIND_PROTOCOL_PFUNC(_DEF_TCP_LOGIN_RQ) = &CKernel::dealLoginRq;
	BIND_PROTOCOL_PFUNC(_DEF_TCP_FRIEND_INFO) = &CKernel::dealFriendInfoRq;
	BIND_PROTOCOL_PFUNC(_DEF_TCP_OFFLINE) = &CKernel::dealOfflineRq;
	BIND_PROTOCOL_PFUNC(_DEF_PROTOCOL_CHAT_RQ) = &CKernel::dealChatRq;
	BIND_PROTOCOL_PFUNC(_DEF_TCP_ADD_FRIEND_RQ) = &CKernel::dealAddFriednRq;
	BIND_PROTOCOL_PFUNC(_DEF_TCP_ADD_FRIEND_RS) = &CKernel::dealAddFriendRs;
    BIND_PROTOCOL_PFUNC(_DEF_TCP__FILE_INFO_RQ) = &CKernel::dealFileInfoRq;
    BIND_PROTOCOL_PFUNC(_DEF_TCP__FILE_INFO_RS) = &CKernel::dealFileInfoRs;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_FILE_BLOCK_RQ) = &CKernel::dealFileBlockRq;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_FILE_BLOCK_RS) = &CKernel::dealFileBlockRs;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_FILE_BLOCK_MD5_RQ) = &CKernel::dealFileBlockMd5Rq;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_FILE_BLOCK_MD5_RS) = &CKernel::dealFileBlockMd5Rs;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_FILE_ALL_TRAN_RESULT) =&CKernel::dealFileAllTranResult;
    BIND_PROTOCOL_PFUNC(_DRF_TCP_FILE_CONTINUE_TRAN_RQ) = &CKernel::dealFileContinueTranRq;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_ADD_CHAT_GROUP_RQ) = &CKernel::dealAddChatGroupRq;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_ADD_CHAT_GROUP_RS) = &CKernel::dealAddChatGroupRs;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_CHAT_GROUP_CHAT_INFO_RQ) = &CKernel::dealGroupChatRq;
    BIND_PROTOCOL_PFUNC(_DEF_TCP_CREATE_CHAT_GROUP_RQ) = &CKernel::dealCreateGroupRq;

	//int num = _DEF_TCP_REGISTER_RQ - _DEF_PROTOCOL_BASE - 1;
	//m_pFunc[] = &CKernel::dealRegisterRq;
}

void CKernel::dealReadyData(long Ip, char* buf, int len)    //×¢Òâ£¬ÕâÀïµÄIp±£´æµÄÊÇÒ»¸öSOCKETÀàÐÍ£¬ÊÇsocketÌ×½Ó×Ö
{
	int num = *(int*)buf;
	num -= (_DEF_PROTOCOL_BASE+1);
	if (num >= 0 && num < PROTOCOL_NUM)
	{
		(this->*(m_pFunc[num]))(Ip, buf, len);
	}
	else
	{
		cout << "dealReadyData Error" << endl;
	}
	return;
}

void CKernel::dealRegisterRq(long Ip, char* buf, int len)
{
	cout << "dealRegisterRq" << endl;
	//´¦Àí×¢²áÇëÇó
	STRU_TCP_REGISTER_RQ* rq = (STRU_TCP_REGISTER_RQ*)buf;
	STRU_TCP_REGISTER_RS rs;

	//Ê×ÏÈ¶ÔÊý¾Ý½øÐÐÐ£Ñé(±¾ÏîÄ¿ÖÖ´Ë²½Ê¡ÂÔ)

	//È»ºó²éÑ¯Êý¾Ý¿â£¬²é¿´¸ÃÊÖ»úºÅÊÇ·ñÒÑ¾­×¢²á¹ýÁË
	char sqlBuf[1024];
	list<string> sqlList;
    sprintf(sqlBuf, "select tel from t_user where tel = \"%s\";", rq->tel);
	if (!m_sql.SelectMySql(sqlBuf, 1, sqlList))
	{
		//Ö´ÐÐ³ö´í·µ»Øfalse
		cout << "select failed with:  " << sqlBuf << endl;
	}
	//ÈôÒÑ×¢²á£¬Ôò·µ»ØÓÃ»§ÒÑ´æÔÚ
	if (sqlList.size() != 0)
	{
		rs.result = USER_IS_EXIST;
	}
	//ÈôÎ´×¢²á£¬Ôò½«ÐÅÏ¢Ð´Èë
	else
	{
		rs.result = REGISTER_SUCCESS;
		//½«ÐÅÏ¢Ð´Èë
        sprintf(sqlBuf, "insert into t_user (tel,password,name) values(\"%s\",\"%s\",\"%s\");", rq->tel, rq->password, rq->name);
		if (!m_sql.UpdateMySql(sqlBuf))
		{
			//Ö´ÐÐÊ§°Ü
			cout << "insert failed with:  " << sqlBuf << endl;
			return;
		}
		else
		{
			cout << "insert success!" << endl;
		}


	}	
	//·µ»Ø×¢²á³É¹¦µÄÐÅÏ¢
	m_pMediator->SendData(Ip, (char*)&rs, sizeof(rs));
}

void CKernel::dealLoginRq(long Ip, char* buf, int len)
{
	//´¦ÀíµÇÂ¼ÇëÇó
	STRU_TCP_LOGIN_RQ* rq = (STRU_TCP_LOGIN_RQ*)buf;
	STRU_TCP_LOGIN_RS rs;

	//²éÑ¯Êý¾Ý¿âÖÐÊÇ·ñ´æÔÚ¸ÃÓÃ»§
	char sqlBuf[1024];
	list<string> sqlList;
    sprintf(sqlBuf, "select id,password,name,feeling from t_user where tel = \"%s\";", rq->tel);
	if (!m_sql.SelectMySql(sqlBuf, 4, sqlList))
	{
		//Èç¹û²éÑ¯Ê§°Ü
		cout << "select failed with: " << sqlBuf << endl;
		return;
	}
	if (sqlList.size() == 0)
	{
		//²»´æÔÚ´ËÓÃ»§
		rs.result = USER_IS_NOTEXIST;
	}
	else
	{
		int id = atoi(sqlList.front().c_str());
		sqlList.pop_front();
		string password = sqlList.front();
		sqlList.pop_front();
		string name = sqlList.front();
		sqlList.pop_front();
		string feeling = sqlList.front();
		sqlList.pop_front();
		//ÏÈÅÐ¶ÏÆäÃÜÂëÊÇ·ñÕýÈ·
		if (password != rq->password)
		{
			//·µ»ØÃÜÂë´íÎó
			rs.result = PASSWORD_ERROR;
		}
        else{
			//´æÔÚ´ËÓÃ»§  ÇÒÃÜÂëÕýÈ·
			//ÅÐ¶ÏÆäÊÇ·ñÒÑÔÚÏß£¬ÈôÔÚÏßÔò×èÖ¹ÆäµÇÂ¼
            if (mpIdToSocket.count(id) > 0)   //´Ë¹¦ÄÜÔÝÊ±²»ÓÃ£¬·½±ã²âÊÔ
			{
				//ÒÑÉÏÏß
				rs.result = USER_IS_ONLINE;   //·µ»Ø¸æËßËûÓÃ»§ÒÑÔÚÏß
			}
			else
			{

				//·ñÔò£¬½«Æä±£´æµ½map
				mpIdToSocket[id] = Ip;    //ÕâÀïµÄIp±íÊ¾µÄÊÇÒ»¸öSOCKET
				//·µ»ØµÇÂ¼³É¹¦ÏûÏ¢
				rs.result = LOGIN_SUCCESS;
				rs.userId = id;
                strcpy(rs.name, name.c_str());
                strcpy(rs.feeling, feeling.c_str());
				//TODO  £º·¢ÏûÏ¢¸æËßËûµÄËùÓÐºÃÓÑµ±Ç°ÓÃ»§ÉÏÏßÁË
				sendOnlineInfo(id);
                sendGroupInfo(id);
				
			}
		}

	}
	m_pMediator->SendData(Ip, (char*)&rs, sizeof(rs));


}

//´¦Àí»ñÈ¡ºÃÓÑÐÅÏ¢µÄÇëÇó
void CKernel::dealFriendInfoRq(long Ip, char* buf, int len)
{
	STRU_TCP_FRIEND_INFO* rq = (STRU_TCP_FRIEND_INFO*)buf;
	STRU_TCP_FRIEND_INFO rs;
	//²éÑ¯Êý¾Ý¿â£¬»ñµÃµ±Ç°ÇëÇóÕßµÄËùÓÐºÃÓÑÐÅÏ¢
	char sqlBuf[1024];
	list<string> sqlList;
    sprintf(sqlBuf, "select id,name,icon,feeling from t_user where id in (select idB from t_friend where idA = %d);", rq->userId);

	if (!m_sql.SelectMySql(sqlBuf, 4, sqlList))
	{
		//Èç¹û²éÑ¯Ê§°Ü£¬´òÓ¡´íÎó£¬²¢·µ»Ø
		cout << "select failed with :  " << sqlBuf << endl;
		return;
	}
	//¿ªÊ¼½«ËùÓÐÐÅÏ¢·¢ËÍ¸øµ±Ç°id³ÖÓÐÕß
	if (mpIdToSocket.count(rq->userId) == 0)
	{
		cout << "id is not exist in map" << endl;
		return;
	}
    int sock = mpIdToSocket[rq->userId];
	while (sqlList.size() != 0)
	{
		rs.userId = atoi(sqlList.front().c_str());
		sqlList.pop_front();
        strcpy(rs.name, sqlList.front().c_str());
		sqlList.pop_front();
        //rs.iconId = atoi(sqlList.front().c_str());   //头像暂时不写
		sqlList.pop_front();
        strcpy(rs.feeling, sqlList.front().c_str());
		sqlList.pop_front();
		
		//ÅÐ¶ÏºÃÓÑÊÇ·ñÔÚÏßÉÏ
		if (mpIdToSocket.count(rs.userId) > 0)
		{
			rs.status = STATUS_ONLINE;
		}
		else
		{
			rs.status = STATUS_OFFLINE;
		}

		m_pMediator->SendData(sock, (char*)&rs, sizeof(rs));
	}

}

void CKernel::dealOfflineRq(long Ip, char* buf, int len)
{
	//´¦ÀíÏÂÏßÇëÇó
	STRU_TCP_OFFLINE_RQ* rq = (STRU_TCP_OFFLINE_RQ*)buf;
	//ÏÈÅÐ¶ÏÆäÊÇ·ñÔÚÁ¬½Ó»º´æÖÐ
	if (mpIdToSocket.count(rq->userId) > 0)
	{
		//Èç¹ûÔÚ×Ô¼ºµÄ»º´æÁ¬½ÓÖÐ
		auto ite = mpIdToSocket.find(rq->userId);
		mpIdToSocket.erase(ite);


		//±éÀúÆäËùÓÐºÃÓÑ£¬½«ÏÂÏßÐÅÏ¢·¢¸øËûµÄËùÓÐºÃÓÑ
		sendOfflineInfo(rq->userId);
		
	}
}

//´¦ÀíÁÄÌìÐÅÏ¢ÇëÇó
void CKernel::dealChatRq(long Ip, char* buf, int len)
{
	//²ð°ü
	STRU_TCP_CHAT_RQ* rq = (STRU_TCP_CHAT_RQ*)buf;

	//²é¿´ÊÇ·¢¸øË­µÄ
	//Ê×ÏÈ¿´¶Ô·½ÉÏÏßÃ»ÓÐ£¬Èç¹ûÎ´ÉÏÏß£¬ÔòÖ±½Ó·µ»Ø
	if (mpIdToSocket.count(rq->friendId) == 0)
		return;
	//ÈôÉÏÏßÁË£¬Ôò½«°ü×ª·¢¸øËû
	m_pMediator->SendData(mpIdToSocket[rq->friendId], buf, len);
}

void CKernel::dealAddFriednRq(long Ip, char* buf, int len)
{
	//²ð°ü²é¿´ÊÇÌí¼ÓË­µÄ
	//TODO
	STRU_TCP_ADD_FRIEND_RQ* rq = (STRU_TCP_ADD_FRIEND_RQ*)buf;
	//¸ù¾Ýname²éÑ¯±»Ìí¼ÓÓÃ»§µÄid
	char sqlBuf[1024];
	list<string> sqlList;
    sprintf(sqlBuf,"select id from t_user where name = \"%s\"; ",rq->friendName);
	if (!m_sql.SelectMySql(sqlBuf, 1, sqlList))
	{
		cout << "select failed with:  " << sqlBuf << endl;
		return;
	}
	if (sqlList.size() == 0)   //Èç¹ûÊý¾Ý¿âÖÐÃ»ÓÐ£¬ÔòÖ±½Ó·µ»Ø¼´¿É
		return;
	int id = atoi(sqlList.front().c_str());   //×Ö·û´®×ªÕûÐÍ
	//ÔÙ¸ù¾Ýid²éÑ¯¸ÃÓÃ»§µ±Ç°ÊÇ·ñÔÚÏßÉÏ£¬Èç¹û²»ÔÚÏßÉÏÔòÖ±½Ó·µ»Ø
	if (mpIdToSocket.count(id) > 0)
	{
		//Èç¹ûÔÚÏßÉÏ£¬ÔòÏòÆä·¢ËÍÌí¼ÓºÃÓÑÇëÇó
		m_pMediator->SendData(mpIdToSocket[id], buf, len);

	}
	//Èç¹û²»ÔÚÏßÉÏÔòÖ±½Ó·µ»Ø
	return;


}

//´¦ÀíÌí¼ÓºÃÓÑ»Ø¸´
void CKernel::dealAddFriendRs(long Ip, char* buf, int len)
{
	//²ð°ü
	STRU_TCP_ADD_FRIEND_RS* rs = (STRU_TCP_ADD_FRIEND_RS*)buf;
	//ÅÐ¶ÏÊÇ·ñÌí¼Ó³É¹¦
	if (rs->result == ADD_FRIEND_SUCCESS)
	{
		//ÈôÌí¼Ó³É¹¦£¬ÔòÐ´ÈëÊý¾Ý¿â£¬²¢·¢ËÍ¸øÌí¼ÓÕßÌí¼Ó³É¹¦µÄÏûÏ¢
		//Ð´ÈëÊý¾Ý¿â
		char sqlBuf[1024];
        sprintf(sqlBuf, "insert into t_friend values (%d , %d);", rs->userId, rs->friendId);
		if (!m_sql.UpdateMySql(sqlBuf))
		{
			cout << "insert failed with:  " << sqlBuf << endl;
			return;
		}
        sprintf(sqlBuf, "insert into t_friend values (%d , %d);", rs->friendId, rs->userId);
		if (!m_sql.UpdateMySql(sqlBuf))
		{
			cout << "insert failed with:  " << sqlBuf << endl;
			return;
		}
	}
	
	//½«Ìí¼Ó½á¹û·µ»¹¸øÌí¼ÓÕß
	if (mpIdToSocket.count(rs->userId) > 0)
	{
		//ÏÈÅÐ¶ÏÆäÊÇ·ñ»¹ÔÚÏß
		//Èç¹ûÔÚÏß
		m_pMediator->SendData(mpIdToSocket[rs->userId], buf, len);
	}
	return;

}

void CKernel::dealFileInfoRq(long Ip, char *buf, int len)
{
    cout<<"dealFileInfoRq"<<endl;
    //zhuan fa
    STRU_TCP_FILE_INFO_RQ* rq=(STRU_TCP_FILE_INFO_RQ*)buf;
    // check if the user is onLine
    if(mpIdToSocket.count(rq->targetId) > 0)
    {
        //online
        m_pMediator->SendData(mpIdToSocket[rq->targetId],buf,len);
    }
}

void CKernel::dealFileInfoRs(long Ip, char *buf, int len)
{
    cout<<"dealFileInfoRs"<<endl;
    STRU_TCP_FILE_INFO_RS* rs=(STRU_TCP_FILE_INFO_RS*)buf;
    // check if the user is onLine
    if(mpIdToSocket.count(rs->targetId) > 0)
    {
        //online
        m_pMediator->SendData(mpIdToSocket[rs->targetId],buf,len);
    }
}

void CKernel::dealFileBlockRq(long Ip, char *buf, int len)
{
    cout<<"dealFileBlockRq"<<endl;
    STRU_TCP_FILE_BLOCK_RQ *rq=(STRU_TCP_FILE_BLOCK_RQ*)buf;
    if(mpIdToSocket.count(rq->friendId) > 0)
    {
        m_pMediator->SendData(mpIdToSocket[rq->friendId],buf,len);
    }
}

void CKernel::dealFileBlockRs(long Ip, char *buf, int len)
{
    cout<<"dealFileBlockRs"<<endl;
    STRU_TCP_FILE_BLOCK_RS *rs=(STRU_TCP_FILE_BLOCK_RS*)buf;
    if(mpIdToSocket.count(rs->friendId) > 0)
    {
        m_pMediator->SendData(mpIdToSocket[rs->friendId],buf,len);
    }
}

void CKernel::dealFileBlockMd5Rq(long Ip, char *buf, int len)
{
    cout<<"dealFileBlockMd5Rq"<<endl;
    STRU_TCP_FILE_BLOCK_MD5_RQ* rq=(STRU_TCP_FILE_BLOCK_MD5_RQ*)buf;
    if(mpIdToSocket.count(rq->friendId) > 0)
    {
        m_pMediator->SendData(mpIdToSocket[rq->friendId],buf,len);
    }
}

void CKernel::dealFileBlockMd5Rs(long Ip, char *buf, int len)
{
    cout<<"dealFileBlockMd5Rs"<<endl;
    STRU_TCP_FILE_BLOCK_MD5_RS* rs=(STRU_TCP_FILE_BLOCK_MD5_RS*)buf;
    if(mpIdToSocket.count(rs->friendId) > 0)
    {
        m_pMediator->SendData(mpIdToSocket[rs->friendId],buf,len);
    }
}

void CKernel::dealFileAllTranResult(long Ip, char *buf, int len)
{
    cout<<"dealFileAllTranResult"<<endl;
    STRU_TCP_FILE_ALL_TRAN_RESULT *rq=(STRU_TCP_FILE_ALL_TRAN_RESULT*)buf;
    if(mpIdToSocket.count(rq->friendId) > 0)
    {
        m_pMediator->SendData(mpIdToSocket[rq->friendId],buf,len);
    }
}

void CKernel::dealFileContinueTranRq(long Ip, char *buf, int len)
{
    cout<<"dealFileAllTranResult"<<endl;
    STRU_TCP_FILE_CONTINUE_TRAN_RQ* rq = (STRU_TCP_FILE_CONTINUE_TRAN_RQ*)buf;
    if(mpIdToSocket.count(rq->friendId) > 0)
    {
        m_pMediator->SendData(mpIdToSocket[rq->friendId],buf,len);
    }
}

//处理添加群聊请求
void CKernel::dealAddChatGroupRq(long Ip, char *buf, int len)
{
    STRU_TCP_ADD_CHAT_GROUP_RQ * rq=(STRU_TCP_ADD_CHAT_GROUP_RQ*)buf;

    //select MySQL
    char sqlBuf[1024];
    sprintf(sqlBuf,"select grouper,groupName from t_group where groupId = %d",rq->groupId);
    list<string> sqlList;
    if(!m_sql.SelectMySql(sqlBuf,2,sqlList))
    {
        cout<<"select failed with:  "<<sqlBuf<<endl;
    }
    if(sqlList.size() == 0){
        STRU_TCP_ADD_CHAT_GROUP_RS rs;
        rs.result = ADD_CHAT_GROUP_NOT_EXIST;
        m_pMediator->SendData(Ip,(char*)&rs,sizeof(rs));
        return;
    }

    int targetId = atoi(sqlList.front().c_str());
    sqlList.pop_front();
    strcpy(rq->groupName,sqlList.front().c_str());
    sqlList.pop_front();
    //if grouper is Onlinek
    if(mpIdToSocket.count(targetId) > 0)
    {
        m_pMediator->SendData(mpIdToSocket[targetId],buf,len);
    }
    else
    {
        //grouper is not online
        STRU_TCP_ADD_CHAT_GROUP_RS rs;
        rs.result = ADD_CHAT_GROUP_GROUPER_OFFLINE;
        m_pMediator->SendData(Ip,(char*)&rs,sizeof(rs));
    }


}

void CKernel::dealAddChatGroupRs(long Ip, char *buf, int len)
{
    STRU_TCP_ADD_CHAT_GROUP_RS* rs=(STRU_TCP_ADD_CHAT_GROUP_RS*)buf;
    if(mpIdToSocket.count(rs->friendId) > 0)
    {
        if(rs->result == ADD_CHAT_GROUP_SUCCESS)
        {
            char sqlBuf[1024];
            sprintf(sqlBuf,"insert into t_groupMember (groupId,userId) values(%d,%d);",rs->groupId,rs->friendId);
            if(!m_sql.UpdateMySql(sqlBuf))
            {
                cout<<"insert into failed with:   "<<sqlBuf<<endl;
                return;
            }
        }
        m_pMediator->SendData(mpIdToSocket[rs->friendId],buf,len);
        //send group Info
        char sqlBuf[1024];
        list<string>sqlList;
        sprintf(sqlBuf,"select groupName from t_group where groupId = %d;",rs->groupId);
        if(!m_sql.SelectMySql(sqlBuf,1,sqlList))
        {
            cout<<"select failed with: "<<sqlBuf<<endl;
            return;
        }
        if(sqlList.size() != 0)
        {
            STRU_TCP_CHAT_GROUP_INFO_RQ rq;
            strcpy(rq.groupName,sqlList.front().c_str());
            rq.groupId = rs->groupId;
            m_pMediator->SendData(mpIdToSocket[rs->friendId],(char*)&rq,sizeof(rq));
        }
    }
}

void CKernel::dealGroupChatRq(long Ip, char *buf, int len)
{
    STRU_TCP_CHAT_GROUP_CHAT_INFO_RQ *rq=(STRU_TCP_CHAT_GROUP_CHAT_INFO_RQ*)buf;
    //select MySQL
    char sqlBuf[1024];
    list<string>sqlList;
    sprintf(sqlBuf,"select userId from t_groupMember where groupId = %d;",rq->groupId);
    if(!m_sql.SelectMySql(sqlBuf,1,sqlList))
    {
        cout<<"select failed with:  "<<sqlBuf<<endl;
        return;
    }
    while(sqlList.size() != 0)
    {
        int id=atoi(sqlList.front().c_str());
        sqlList.pop_front();
        if(mpIdToSocket.count(id)>0 && id!=rq->userId)
        {
            m_pMediator->SendData(mpIdToSocket[id],buf,len);
        }
    }

}

void CKernel::dealCreateGroupRq(long Ip, char *buf, int len)
{
    STRU_TCP_CREATE_CHAT_GROUP_RQ* rq=(STRU_TCP_CREATE_CHAT_GROUP_RQ*)buf;
    char sqlBuf[1024];
    list<string>sqlList;
    sprintf(sqlBuf,"select groupId from t_group where groupName = '%s';",rq->groupName);
    if(!m_sql.SelectMySql(sqlBuf,1,sqlList))
    {
        cout<<"select failed with:  "<<sqlBuf<<endl;
        return;
    }
    STRU_TCP_CREATE_CHAT_GROUP_RS rs;
    strcpy(rs.groupName,rq->groupName);
    if(sqlList.size() != 0)
    {
        //create failed!
        rs.result = CREATE_GROUP_FAILED;

    }
    else
    {
        sqlList.clear();
        //insert
        sprintf(sqlBuf,"insert into t_group (groupName,grouper) values('%s',%d);",rq->groupName,rq->userId);
        if(!m_sql.UpdateMySql(sqlBuf))
        {
            cout<<"insert failed with:  "<<sqlBuf<<endl;
            return;
        }
        sprintf(sqlBuf,"select groupId from t_group where groupName = '%s';",rq->groupName);
        if(!m_sql.SelectMySql(sqlBuf,1,sqlList))
        {
            cout<<"select failed with:  "<<sqlBuf<<endl;
            return;
        }
        rs.groupId = atoi(sqlList.front().c_str());
        rs.result = CREATE_GROUP_SUCCESS;

        sprintf(sqlBuf,"insert into t_groupMember (groupId,userId) values(%d,%d);",rs.groupId,rq->userId);
        if(!m_sql.UpdateMySql(sqlBuf))
        {
            cout<<"insert failed with: "<<sqlBuf<<endl;
            return;
        }
    }
    m_pMediator->SendData(Ip,(char*)&rs,sizeof(rs));

}

void CKernel::sendOnlineInfo(int id ) 
{
	STRU_TCP_FRIEND_INFO rq;
	rq.userId = id;
	rq.status = STATUS_ONLINE;
	char sqlBuf[1024];
	list<string> sqlList;
	
	//²éÑ¯µ±Ç°idÓµÓÐÕßµÄËùÓÐºÃÓÑ
    sprintf(sqlBuf, "select idB from t_friend where idA = %d;", id);
	if (!m_sql.SelectMySql(sqlBuf,1,sqlList))
	{
		//²éÑ¯³ö´í
		cout << "select error:  " << sqlBuf << endl;
		return;
	}
	int idFriend = 0;
	while (sqlList.size() != 0)
	{
		idFriend = atoi(sqlList.front().c_str());
		sqlList.pop_front();
		//ÅÐ¶ÏÆäºÃÓÑÊÇ·ñÔÚÏß,ÈôÔÚÏßÔò·¢ËÍ£¬·ñÔò²»·¢ËÍ
		if (mpIdToSocket.count(idFriend) > 0)
		{
			//ºÃÓÑÔÚÏß
			m_pMediator->SendData(mpIdToSocket[idFriend], (char*)&rq, sizeof(rq));
		}
	}
}

void CKernel::sendOfflineInfo(int id)
{
	STRU_TCP_FRIEND_INFO rq;
	rq.userId = id;
	rq.status = STATUS_OFFLINE;
	char sqlBuf[1024];
	list<string> sqlList;

	//²éÑ¯µ±Ç°idÓµÓÐÕßµÄËùÓÐºÃÓÑ
    sprintf(sqlBuf, "select idB from t_friend where idA = %d;", id);
	if (!m_sql.SelectMySql(sqlBuf, 1, sqlList))
	{
		//²éÑ¯³ö´í
		cout << "select error:  " << sqlBuf << endl;
		return;
	}
	int idFriend = 0;
	while (sqlList.size() != 0)
	{
		idFriend = atoi(sqlList.front().c_str());
		sqlList.pop_front();
		//ÅÐ¶ÏÆäºÃÓÑÊÇ·ñÔÚÏß,ÈôÔÚÏßÔò·¢ËÍ£¬·ñÔò²»·¢ËÍ
		if (mpIdToSocket.count(idFriend) > 0)
		{
			//ºÃÓÑÔÚÏß
			m_pMediator->SendData(mpIdToSocket[idFriend], (char*)&rq, sizeof(rq));
		}
    }
}

void CKernel::sendGroupInfo(int id)
{
    char sqlBuf[1024];
    list<string>sqlList;
    sprintf(sqlBuf,"select t_group.groupId,groupName from t_group inner join t_groupMember\
                on t_group.groupId=t_groupMember.groupId where userId = %d;",id);
    if(!m_sql.SelectMySql(sqlBuf,2,sqlList))
    {
        cout<<"select failed with:  "<<sqlBuf;
        return;
    }
    STRU_TCP_CHAT_GROUP_INFO_RQ rq;
    while(sqlList.size()!=0 && mpIdToSocket.count(id)>0)
    {
        rq.groupId = atoi(sqlList.front().c_str());
        sqlList.pop_front();
        strcpy(rq.groupName,sqlList.front().c_str());
        sqlList.pop_front();
        m_pMediator->SendData(mpIdToSocket[id],(char*)&rq,sizeof(rq));
    }
}
