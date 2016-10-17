/***********************************************
*		   聊天软件-服务端					   *
*	       by:Sucoder QQ:330729793			   *
*				2013.01.25					   *
*数据库操作函数接口定义	     		           *
***********************************************/

#include "server.h"

MYSQL* connectdb(){//连接数据库
	MYSQL *mysql;
	if((mysql=mysql_init(NULL))==NULL){
	   mysql=NULL;		
	   return mysql;}
	if(!mysql_real_connect(mysql,DBHOST,DBUSER,DBPASSWD,NULL,DBPORT,NULL,0)){
		   mysql=NULL;		
		   return mysql;
		}
	if(mysql_select_db(mysql,DBNAME)){
	   mysql=NULL;		
	   return mysql;
	}
     return mysql;
}

int user_reg(struct Regloginmsg *regmsg){//用户注册
	
	MYSQL *mysql=connectdb();
	if(mysql==NULL){
		syslog(LOG_ERR|LOG_LPR,"用户数据处理过程中,连接数据库失败！\n");
		return -1;
	}
	char query[512]={0};
	memset(query,0,sizeof(query));
        snprintf(query,sizeof(query),"insert into usertable(username,passwd) values('%s','%s')",regmsg->username,regmsg->passwd);
	if(mysql_real_query(mysql,query,strlen(query)))
	{
	 syslog(LOG_ERR|LOG_LPR,"执行sql数据库语句 %s 失败！\n",query);
	 return -1;
	}
	int index=mysql_insert_id(mysql);//返回用户注册的号码
	mysql_close(mysql); // 关闭 Mysql 连接
	mysql==NULL;
	return index;
}
int user_login(struct Regloginmsg *regmsg,char *username){//用户登陆
	MYSQL *mysql=connectdb();
	MYSQL_RES *res;
	MYSQL_ROW row;
	int   torf=-1;

	if(mysql==NULL){
		syslog(LOG_ERR|LOG_LPR,"用户数据处理过程中,连接数据库失败！\n");
		return -1;
		}
  	char query[512]={0};
	memset(query,0,sizeof(query));
	snprintf(query,sizeof(query),"select *from %s where %s=%d",TABLENAME,USERID,regmsg->id);
	if(mysql_real_query(mysql,query,strlen(query))){
	 syslog(LOG_ERR|LOG_LPR,"执行sql数据库语句 %s 失败！\n",query);
	 return -1;
	}
	res = mysql_store_result(mysql);
	while(row = mysql_fetch_row(res)){ // 重复读取行,并输出所有字段的值,直到 row 为 NULL		
		if(regmsg->id==atoi(row[0])&&(strcmp(regmsg->passwd,row[2])==0))
		{		
			memcpy(username,row[1],strlen(row[1]));		 	
			torf = 1;
		  }
	}//while
	mysql_free_result(res); // 释放结果集
	mysql_close(mysql); // 关闭 Mysql 连接
	mysql==NULL;
	return torf;	
}
