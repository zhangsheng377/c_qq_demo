// ChatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chatclient.h"
#include "ChatDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern "C" {
struct Itemdata{//用于存放用户附加数据并绑定到listctrl行附加数据上
	CChatDlg *chatdlg;
	CString msg;
	};
}
/////////////////////////////////////////////////////////////////////////////
// CChatDlg dialog


CChatDlg::CChatDlg(CWnd* pParent)
	: CDialog(CChatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatDlg)
	m_sendmsg = _T("");
	m_msg = _T("");
	//}}AFX_DATA_INIT
}


void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatDlg)
	DDX_Text(pDX, IDC_EDIT_SEND, m_sendmsg);
	DDX_Text(pDX, IDC_EDIT_MSG, m_msg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChatDlg, CDialog)
	//{{AFX_MSG_MAP(CChatDlg)
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatDlg message handlers

BOOL CChatDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CChatDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	UpdateData(TRUE);
	char *getid=(char*)malloc(30);
	struct Itemdata *data=NULL;
	for (int i=0;i<chatclientDlg->m_onLineList.GetItemCount();i++)
	{
		chatclientDlg->m_onLineList.GetItemText(i,1,getid,30);
		if (strcmp(getid,id)==0)
		{
			
			data=(Itemdata *)chatclientDlg->m_onLineList.GetItemData(i);
			if (m_msg!=""){
				m_msg+="\r\n";
			}
			if (data->msg!=""){
				m_msg+=data->msg;
				UpdateData(FALSE);
				pedit->LineScroll(pedit->GetLineCount());
			}				
			data->msg="";
			chatclientDlg->m_onLineList.SetItemData(i,(DWORD)data);			
			break;
		}
	}
	if (data==NULL){//证明聊天的对象已经掉线或下线
			time_t ostime;
			time(&ostime); 
			CTime time(ostime);
			CString timestr;
			timestr.Format("\r\n\r\n(%d:%d:%d) ",time.GetHour(),time.GetMinute(),time.GetSecond());
			m_msg+=timestr;
			m_msg+="系统消息:对方已下线,请关闭聊天窗口。";
			UpdateData(FALSE);
			pedit->LineScroll(pedit->GetLineCount());
			KillTimer(timeevn);//杀死Settimer事件	
	}
	free(getid);
	CDialog::OnTimer(nIDEvent);
}
void CChatDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	CString str;	
	str.Format("与 %s(%s) 聊天中...",name,id);
	SetWindowText(str);
	pedit=(CEdit *)GetDlgItem(IDC_EDIT_MSG);
	SetTimer(timeevn,1000,NULL);
	OnTimer(timeevn);//执行一次定时函数，用户不用等待1秒才收到以前发的消息.
}

void CChatDlg::OnDestroy() 
{
	char getid[30];
	for (int i=0;i<chatclientDlg->m_onLineList.GetItemCount();i++)
	{
		chatclientDlg->m_onLineList.GetItemText(i,1,getid,sizeof(getid));
		if (strcmp(getid,id)==0)
		{			
			struct Itemdata *data;
			data=(Itemdata *)chatclientDlg->m_onLineList.GetItemData(i);
			data->chatdlg=NULL;
			chatclientDlg->m_onLineList.SetItemData(i,(DWORD)data);
			break;
		}
	}
	KillTimer(timeevn);//杀死Settimer事件
	CDialog::OnDestroy();
	delete this;//释放聊天窗口
	// TODO: Add your message handler code here
	
}

void CChatDlg::OnOK() //发送消息
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if (m_sendmsg=="")
	{
		MessageBox("不能发送内空为空的消息!","提示",MB_OK);
		GetDlgItem(IDC_EDIT_SEND)->SetFocus();//设置输入框为焦点
		return;
	}
	if (m_sendmsg.GetLength()>=UMSGLEN)
	{
		MessageBox("发送的内容超出限制,不能发送!","提示",MB_OK);
		GetDlgItem(IDC_EDIT_SEND)->SetFocus();//设置输入框为焦点
		return;
	}
	memset(&msg,0,sizeof(msg));
	memset(&usermsg,0,sizeof(usermsg));
	usermsg.disid=atoi(id);
	usermsg.srcid=chatclientDlg->loginmsg.id;
	memcpy(usermsg.disname,name,sizeof(name));
	memcpy(usermsg.srcname,chatclientDlg->loginmsg.username,sizeof(chatclientDlg->loginmsg.username));
	memcpy(usermsg.data,m_sendmsg,strlen(m_sendmsg));
	msg.type=MSGDATA;
	memcpy(msg.data,&usermsg,sizeof(usermsg));
	send(chatclientDlg->m_socket,(char*)&msg,sizeof(msg),0);
	if (m_msg!="")
	{
		m_msg+="\r\n";
	}
	time_t ostime;
	time(&ostime); 
	CTime time(ostime);
	CString timestr;
	timestr.Format("(%d:%d:%d) ",time.GetHour(),time.GetMinute(),time.GetSecond());
	m_msg+=timestr;
	m_msg+="我说:\r\n    ";
	m_msg+=m_sendmsg;

	m_sendmsg="";
	UpdateData(FALSE);
	pedit->LineScroll(pedit->GetLineCount());
	GetDlgItem(IDC_EDIT_SEND)->SetFocus();//设置输入框为焦点
}

void CChatDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
	DestroyWindow();
}
