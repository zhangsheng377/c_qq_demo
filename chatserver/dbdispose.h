/***********************************************
*		   聊天软件-服务端	                   *
*	       by:Sucoder QQ:330729793	           *
*				2013.01.25                     *
*数据库操作函数接口头文件	     		       *
***********************************************/

int user_reg(struct Regloginmsg *regmsg); //新用户注册
int user_login(struct Regloginmsg *regmsg,char *username); //用户登陆
