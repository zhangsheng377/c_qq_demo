/***********************************************
*		   聊天软件-服务端	     			   *
*	       by:Sucoder QQ:330729793	     	   *
*				2013.01.25     				   *
*网络模块定义,以及线程处理函数..		       *
***********************************************/

#include "server.h"
#include "network.h"
#include "msgdispose.h"
#include "dbdispose.h"
#include <pthread.h>

#define MAXLISTEN 20

struct threaddat{ //线程传递数据结构体
int socket;
int index;
int clientnum;
char recvbuf[MSGALLLEN];
struct Seruserinfo *clientinfo;
};

void* Msgisposethread(void *ptr){ //线程函数
	struct threaddat *threaddat=(struct threaddat *)ptr;
	Dispose_msg(threaddat->socket,threaddat->recvbuf,threaddat->clientinfo,threaddat->clientnum,threaddat->index);//进入函数处理用户数据
	free(threaddat);
	threaddat=NULL;
	pthread_exit(NULL);
}
int Accept_client(int serverfd) //使用IO多路复用开始接受客户端
{
 fd_set allfd,tmpfd;
 pthread_t thread;
 int client_fd,clientnum=0,maxfd=0,outline=0; 
 int index=0,len=0,addrlen=sizeof(struct sockaddr);
 char recvbuf[MSGALLLEN];
 struct timeval tv;
 struct sockaddr_in client_addr;
 struct Message msg;
 struct Seruserinfo clientinfo[MAXCONN]={-1}; //当前在线用户的连接和信息(在此注明一下：本来是想用链表的，但因为只是一个测试服务器，所以我就偷懒不用链表了哈)


 for(index=0;index<MAXCONN;index++){//初始化在线用户信息
	clientinfo[index].socket=-1;
	clientinfo[index].id=-1;
	memset(clientinfo[index].username,0,sizeof(clientinfo[index].username));
	}
 FD_ZERO(&allfd);
 FD_SET(serverfd,&allfd);
 maxfd=serverfd;
 while(1){
	tmpfd=allfd;
	tv.tv_sec=0;	
	tv.tv_usec=500000;//超时时间0.5秒
	index=select(maxfd+1,&tmpfd,NULL,NULL,&tv);
	if(-1==index){
		syslog(LOG_ERR|LOG_LPR,"select函数出错！\n");
		return -1;
		}
	else if(0==index) continue;//等待超时并且没有可读消息，返回继续询查
	if(FD_ISSET(serverfd,&tmpfd)){
		client_fd=accept(serverfd,(struct sockaddr*)&client_addr,&addrlen);
		for(index=0;index<=clientnum;index++){
			if(index==MAXCONN){//超过服务器限制的最大用户数，关闭此连接并跳出for循环
				close(client_fd);
				break;			
				}
			else if(clientinfo[index].socket==-1){
				FD_SET(client_fd,&allfd);
				clientinfo[index].socket=client_fd;
				if(index==clientnum){//判断当前用户是不是占用结构体数组中最后一个位置,如果是,增加一个位置
				  clientnum++;
				}
				break;	//已经找到空位，并设置为新的用户，跳出for循环
			}
		}//for
		if(client_fd>maxfd) maxfd=client_fd;
		continue;
	}
	for(index=0;index<=clientnum;index++){
		if(clientinfo[index].socket==-1)
				continue;		
		if(FD_ISSET(clientinfo[index].socket,&tmpfd)){
		  	bzero(recvbuf,sizeof(recvbuf));
			if((len=recv(clientinfo[index].socket,recvbuf,sizeof(recvbuf),0))<=0){ //用户断开了网络或关闭的客户端
				if(clientinfo[index].id>0){//如果是登陆用户,通知其它用户它已经下线
					for(outline=0;outline<clientnum;outline++){
						if(clientinfo[outline].id>0){
							msg.type=CUTCLIENT;				
							memset(msg.data,0,sizeof(msg.data));
							memcpy(msg.data,&clientinfo[index],sizeof(msg.data));
							send(clientinfo[outline].socket,&msg,sizeof(struct Message),0);
						}
					}//for
				}


				close(clientinfo[index].socket);
				FD_CLR(clientinfo[index].socket,&allfd);
				clientinfo[index].socket=-1;
				clientinfo[index].id=-1;
				memset(clientinfo[index].username,0,sizeof(clientinfo[index].username));
				thread=-1;
				break;
			}
			else{	//把收到的数据进行处理
				struct threaddat *threaddat=(struct threaddat *)malloc(sizeof(struct threaddat));	
				threaddat->socket=clientinfo[index].socket;
				threaddat->clientnum=clientnum;
				threaddat->index=index;
				memcpy(threaddat->recvbuf,recvbuf,sizeof(recvbuf));
				threaddat->clientinfo=clientinfo;
				pthread_create(&thread,NULL,Msgisposethread,(void*)threaddat);//创建线程处理用户数据
				pthread_detach(thread);//分离线程
				usleep(100000);//为安全起见,小睡0.1秒
				}
		 }
	}//for	
     }//while
    return 0;
}
int socket_init() //初始化网络套字接
{
 int server_fd;
 struct sockaddr_in server_addr;
 if((server_fd=socket(AF_INET,SOCK_STREAM,0))==-1){
   syslog(LOG_ERR|LOG_LPR,"创建监听套字接失败！\n");
   return -1;
	}
 bzero(&server_addr,sizeof(server_addr));
 server_addr.sin_family=AF_INET;
 server_addr.sin_port=htons(SERVERPORT);
 server_addr.sin_addr.s_addr = inet_addr(SERVERADDR);
if (server_addr.sin_addr.s_addr == INADDR_NONE)
	{   
		struct hostent *host= NULL;
		if ((host = gethostbyname(SERVERADDR)) != NULL)
		{
			memcpy(&(server_addr.sin_addr.s_addr), host->h_addr,host->h_length);
			server_addr.sin_family = host->h_addrtype;
		}
		else{
			syslog(LOG_ERR|LOG_LPR,"域名或IP地址错误,请检查域名或IP地址是否正确!\n");
			return -1;
		}
	}
 if(bind(server_fd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr))==-1){
   syslog(LOG_ERR|LOG_LPR,"邦定套字接失败！\n");
   	return -1;
	}
 if(listen(server_fd,MAXLISTEN)==-1){
   syslog(LOG_ERR|LOG_LPR,"监听套字接失败！\n");
  	 return -1;
	}
  return Accept_client(server_fd);
}

int Start_server()//开始服务
{
	return socket_init();
}

