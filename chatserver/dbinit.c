/***********************************************
*		   聊天软件-服务端					   *
*	       by:Sucoder QQ:330729793		       *
*				2013.01.25					   *
*数据库初始化定义		     				   *
***********************************************/
#include "server.h"

//初始化数据库,判断是否存在用户数据库和用户表,如果不存在用户数据库和用户表,
//则创建数据库和表.如果没有安装mysql数据库,返回-1,程序将退出.
int data_init(){
	MYSQL *mysql;
	MYSQL_RES *res;
	char query[512]={0};
	if((mysql=mysql_init(NULL))==NULL){
	   printf("初始化MYSQL对象失败,可能是内存不足\n");
	   return -1;}
	if(!mysql_real_connect(mysql,DBHOST,DBUSER,DBPASSWD,NULL,DBPORT,NULL,0)){//数据库为NULL，如果连接失败,就是连接数据库失败或没安装数据库
	 	printf("连接数据库失败或没有安装数据库,请自行检查原因!\n");
		return -1;
		}
	if(mysql_select_db(mysql,DBNAME)){//返回非0证明数据库不存在,我们来创建数据库。
		
		printf("您是新安装用户,数据库必须进行初始化,请稍等!\n");
		memset(query,0,sizeof(query));
		snprintf(query,sizeof(query),"create database %s",DBNAME);	
		if(mysql_real_query(mysql,query,strlen(query))){
			printf("创建%s数据库失败!\n",DBNAME);
			return -1;
		}
		printf("创建%s数据库成功!\n",DBNAME);		
		mysql_select_db(mysql,DBNAME);	
	}
	memset(query,0,sizeof(query));
	snprintf(query,sizeof(query),"select * from %s",TABLENAME);
	if(mysql_real_query(mysql,query,strlen(query))){//返回非0证明数据库不存在,我们来创建数据表。
		memset(query,0,sizeof(query));
		snprintf(query,sizeof(query),"create table %s(%s int(4) not null primary key auto_increment,\
			%s char(100) not null,%s char(100) not null)auto_increment=10000",
			TABLENAME,USERID,USERNAME,USERPASSWD);
		if(mysql_real_query(mysql,query,strlen(query))){
			printf("创建%s数据表失败!\n",TABLENAME);
			return -1;
		}
	    printf("创建%s数据表成功!\n程序开始正常运行......\n",TABLENAME);
	}
	mysql_free_result(res=mysql_store_result(mysql));//前面select*了一次，必须释放掉结果集。
	mysql_close(mysql); // 关闭 Mysql 连接
	mysql=NULL;
	return 0;
}
