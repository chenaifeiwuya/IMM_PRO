#pragma once

#include <mysql/mysql.h>

#pragma comment(lib,"libmysql.lib")
//
#include <list>
using namespace std;
#include<string>
class CMySql
{
public:
    CMySql(void);
    ~CMySql(void);
public:                    //ip,ÓÃ»§Ãû,ÃÜÂë£¬Êý¾Ý¿â£¬¶Ë¿ÚºÅ
    bool  ConnectMySql(const char *host, const char *user, const char *pass, const char *db,short nport = 3306);
    void  DisConnect(); 
    bool  SelectMySql(char* szSql,int nColumn,list<string>& lstStr);
	//»ñµÃÊý¾Ý¿âÖÐµÄ±í
    bool GetTables(char* szSql,list<string>& lstStr);
    //¸üÐÂ£ºÉ¾³ý¡¢²åÈë¡¢ÐÞ¸Ä
    bool  UpdateMySql(char* szSql);
 
private:
    MYSQL *m_sock;   
	MYSQL_RES *m_results;   
	MYSQL_ROW m_record; 
   
};

