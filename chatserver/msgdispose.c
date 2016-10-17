/***********************************************
*		   聊天软件-服务端					   *
*	       by:Sucoder QQ:330729793			   *
*				2013.01.25					   *
*用户数据信息处理定义及处理方法..     	       *
***********************************************/

#include "server.h"
#include "dbinit.h"

int Dispose_msg(int socket,char *recvbuf,struct Seruserinfo *clientinfo,int clientnum,int index)
{
	struct Message *msg=(struct Message*)recvbuf;
	
	switch(msg->type){
		case USERREG:{	//用户注册
			struct Regloginmsg *regmsg=(struct Regloginmsg*)msg->data;
			int mynum = user_reg(regmsg);
			if(mynum<0){
			 send(socket,"sorry,注册失败请重新注册!",strlen("sorry,注册失败请重新注册!"),0);
			}
			else{
				msg->type=REGSERMSG;
				memset(msg->data,0,sizeof(msg->data));
				snprintf(msg->data,sizeof(msg->data),"您申请到的号码ID: %d \n\t请牢记\n",mynum);
				send(socket,msg,sizeof(struct Message),0);
				}
			}
			break;
		case LOGIN:{  //登陆 并把SOCKET，ID,用户名绑定在一起放在在线用户数组里
			struct Regloginmsg *loginmsg=(struct Regloginmsg*)msg->data;
			int login=0;
			for(login=0;login<clientnum;login++)//禁止重复登陆
			{
				if(clientinfo[login].id==loginmsg->id){
					struct Message *msgtemp=(struct Message*)malloc(sizeof(struct Message));
					memset(msgtemp,0,sizeof(struct Message));
					msgtemp->type=LOGINSERMSG;
					msgtemp->torf=-1;
					snprintf(msgtemp->data,sizeof(msgtemp->data),"登陆失败,此ID已经登陆,禁止重复登陆!\n");
					send(socket,msgtemp,sizeof(struct Message),0);
					free(msgtemp);
					return -1;
					}
				}
			clientinfo[index].id=loginmsg->id;
			login=user_login(loginmsg,clientinfo[index].username);
			memset(msg,0,sizeof(struct Message));
			msg->type=LOGINSERMSG;
			if(login<=0){
				clientinfo[index].id=-1;
				msg->torf=-1;				
				snprintf(msg->data,sizeof(msg->data),"登陆失败,用户ID或密码错误!\n");
				send(socket,msg,sizeof(struct Message),0);
			}
			else{
				msg->torf=1;
				snprintf(msg->data,sizeof(msg->data),"恭喜你,登陆成功!\n");
				send(socket,msg,sizeof(struct Message),0);
				for(login=0;login<clientnum;login++){//登陆成功后取当前在线所有用户，并通知在线用户增加新登陆用户
					memset(msg,0,sizeof(struct Message));
					msg->type=ADDCLIENT; 
					memcpy(msg->data,&clientinfo[login],sizeof(msg->data));
					if(clientinfo[login].id>0){
						send(socket,msg,sizeof(struct Message),0);
						if(clientinfo[login].id!=clientinfo[index].id){//如果不是自己,则发送自己上线的通知给其它在线用户
							memset(msg,0,sizeof(struct Message));
							msg->type=ADDCLIENT; 
							memcpy(msg->data,&clientinfo[index],sizeof(msg->data));
							send(clientinfo[login].socket,msg,sizeof(struct Message),0);
						    }
					}
				usleep(100000);
				}//for
				
				}
			}
			break;

		case MSGDATA:{ //给其它用户发送消息
			struct Usermsg *usermsg=(struct Usermsg*)msg->data;			
			usermsg->srcid=clientinfo[index].id;
			memcpy(usermsg->srcname,clientinfo[index].username,strlen(clientinfo[index].username));
			int i=0,dissocket=-1;
			for(i=0;i<=clientnum;i++)
			{
			 	if(clientinfo[i].id==usermsg->disid)
				{		
					dissocket=clientinfo[i].socket;
					memcpy(usermsg->disname,clientinfo[i].username,strlen(clientinfo[i].username));
					memcpy(msg->data,usermsg,sizeof(struct Usermsg));
					break;//找到了并且把消息结构体填好了,等待发送给接收方,接收方的socket保存在disocket
					}
			}
			if(dissocket<0){ //接收方用户ID没有上线或根本不存在,发送消息失败,通知发送方.
				msg->type=MSGSERMSG;
				memset(msg->data,0,sizeof(msg->data));
				snprintf(msg->data,sizeof(msg->data),"向用户ID: %d 发送消息失败,请稍候重试!\n",usermsg->disid);
				send(socket,msg,sizeof(struct Message),0);
				}
			else{//接收方用户在线就直接发送
				send(dissocket,msg,sizeof(struct Message),0);
			}
		}			
			break;
		default:
			break;

	}
	
	return 0;

}
