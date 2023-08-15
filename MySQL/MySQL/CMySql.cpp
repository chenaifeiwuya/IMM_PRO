//#include "stdafx.h"
#include "CMySql.h"


CMySql::CMySql(void)
{
    /*Õâ¸öº¯ÊýÓÃÀ´·ÖÅä»òÕß³õÊ¼»¯Ò»¸öMYSQL¶ÔÏó£¬ÓÃÓÚÁ¬½Ómysql·þÎñ¶Ë¡£
    Èç¹ûÄã´«ÈëµÄ²ÎÊýÊÇNULLÖ¸Õë£¬Ëü½«×Ô¶¯ÎªÄã·ÖÅäÒ»¸öMYSQL¶ÔÏó£¬
    Èç¹ûÕâ¸öMYSQL¶ÔÏóÊÇËü×Ô¶¯·ÖÅäµÄ£¬ÄÇÃ´ÔÚµ÷ÓÃmysql_closeµÄÊ±ºò£¬»áÊÍ·ÅÕâ¸ö¶ÔÏó*/
    m_sock = new MYSQL;
    mysql_init(m_sock);  
    mysql_set_character_set(m_sock, "gb2312"); //gb2312 ÖÐ»ªÈËÃñ¹²ºÍ¹ú¼òÌå×Ö±ê×¼
}


CMySql::~CMySql(void)
{
    if(m_sock) {
		delete m_sock;
		m_sock = NULL;
    }
}

void CMySql::DisConnect()
{
    mysql_close(m_sock);
}

bool CMySql::ConnectMySql(const char *host, const char *user,const char *pass,const char *db, short nport)
{
	if (!mysql_real_connect(m_sock, host, user, pass, db, nport, NULL, CLIENT_MULTI_STATEMENTS)) {
        //Á¬½Ó´íÎó
		return false;
	}
    return true;
}
 bool  CMySql::GetTables(char* szSql, list<string>& lstStr)
 {
    if(mysql_query(m_sock, szSql)) {
		return false;
	}

	m_results = mysql_store_result(m_sock);
    if(NULL == m_results) {
		return false;
	}
	while (m_record = mysql_fetch_row(m_results)) {
		lstStr.push_back(m_record[0]);
	}
    return true;
 }
bool CMySql::SelectMySql(char* szSql, int nColumn, list<string>& lstStr)
{
    //mysql_query() º¯ÊýÓÃÓÚÏò MySQL ·¢ËÍ²¢Ö´ÐÐ SQL Óï¾ä
	if(mysql_query(m_sock, szSql)) {
		return false;
	}

     /*¡¤mysql_store_result ¶ÔÓÚ³É¹¦¼ìË÷ÁËÊý¾ÝµÄÃ¿¸ö²éÑ¯(SELECT¡¢SHOW¡¢DESCRIBE¡¢EXPLAIN¡¢CHECK TABLEµÈ)
     ·µ»ØÖµ:
     . CR_COMMANDS_OUT_OF_SYNC ¡¡¡¡ÒÔ²»Ç¡µ±µÄË³ÐòÖ´ÐÐÁËÃüÁî¡£
 ¡¡¡¡¡¤ CR_OUT_OF_MEMORY ¡¡¡¡ÄÚ´æÒç³ö¡£
 ¡¡¡¡¡¤ CR_SERVER_GONE_ERROR ¡¡¡¡MySQL·þÎñÆ÷²»¿ÉÓÃ¡£
 ¡¡¡¡¡¤ CR_SERVER_LOST ¡¡¡¡ÔÚ²éÑ¯¹ý³ÌÖÐ£¬Óë·þÎñÆ÷µÄÁ¬½Ó¶ªÊ§¡£
 ¡¡¡¡¡¤ CR_UNKNOWN_ERROR ¡¡¡¡³öÏÖÎ´Öª´íÎó¡£*/
	m_results = mysql_store_result(m_sock);
    if(NULL == m_results)return false;
	//±éÀú±íÖÐµÄÏÂÒ»ÐÐ£¬È¡³öÄÚÈÝ·ÅÈëm_record ½á¹û¼¯
	while (m_record = mysql_fetch_row(m_results)) {
        
		for(int i = 0; i < nColumn; i++) {
			if(!m_record[i]) {
				lstStr.push_back("");
			} else {
				lstStr.push_back(m_record[i]);
			}
        }
	}
    return true;
}

 bool  CMySql::UpdateMySql(char* szSql)
 {
    if(!szSql) {
		return false;
	}
    if(mysql_query(m_sock, szSql)) {
		return false;
	}
    return true;
 }

 /*
 
 
 
 
 
 
 */


