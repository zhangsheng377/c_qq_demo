/*****************************************************
*		   聊天软件-服务端				     		 *
*	       by:Sucoder QQ:330729793	     			 *
*				2013.01.25    				  		 *
*主头文件,把要用到的头文件都放在这,设置数据库信息..  *
*****************************************************/

#ifndef SERVER_H
#define SERVER_H

#include "../include/datauct.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>
#include <netdb.h>
#include <strings.h>
#include <mysql/mysql.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <syslog.h>


#define DBHOST 	   "localhost"  //数据库主机IP
#define DBPORT	   0		//数据库端口
#define DBUSER	   "root"	//数据用户名
#define DBPASSWD   "root"	//数据库密码
#define DBNAME     "mychat"   //数据库名
#define TABLENAME  "usertable" //用户表名
#define USERID	   "userid"	//用户id
#define USERNAME   "username"   //用户昵称
#define USERPASSWD "passwd"	//用户密码

#endif

