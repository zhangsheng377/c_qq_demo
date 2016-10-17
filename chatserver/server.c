/***********************************************
*		   聊天软件-服务端	       *
*	       by:Sucoder QQ:330729793	       *
*				2013.01.25     *
*程序main函数入口..放置了守护进程函数..	       *
***********************************************/
#include "server.h"
#include "network.h"
#include "dbinit.h"

#ifndef LOCK
#define LOCK "/tmp/mychat.lock"
#endif

int deamon_init(void){ //守护进程初始化函数
 pid_t pid;
 if((pid = fork()) < 0){
	printf("fork()函数调用失败!\n");
	return -1;
	}
 else if(pid != 0)
	exit(0);
 else {
	setsid();
	chdir("/");
	umask(0);
	if((pid = fork()) < 0)
		return -1;
   	else if(pid != 0)
		exit(0);	
	}
 setsid();
 chdir("/");
 umask(0);
 int i=0;
 for(i=0;i<=_POSIX_OPEN_MAX;i++) //关闭所有描述符
	close(i);
 return 0;
}
	
int main(int argc,char *argv[])
{
  if(data_init() < 0)//初始化数据库,初始化失败或没有安装mysql数据库,退出程序
	exit(0);
  if(deamon_init() < 0)//调用守护进程初始化函数成为守护进程
	exit(0);
  if(Start_server()<0)//开始服务 因为绑定端口失败会自动退出,所以这里就可以不使用记录锁或文件锁
	exit(0);
  return 0;
}
