// RegDlg.cpp : implementation file
//

#include "stdafx.h"
#include "chatclient.h"
#include "RegDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegDlg dialog


CRegDlg::CRegDlg(CWnd* pParent,CChatclientDlg* pchatclientDlg)
	: CDialog(CRegDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegDlg)
	m_passwd = _T("");
	m_name = _T("");
	m_passwd2 = _T("");
	//}}AFX_DATA_INIT
	chatclientDlg=pchatclientDlg;
}


void CRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegDlg)
	DDX_Text(pDX, IDC_EDIT_PASS, m_passwd);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Text(pDX, IDC_EDIT_PASS2, m_passwd2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegDlg, CDialog)
	//{{AFX_MSG_MAP(CRegDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegDlg message handlers

void CRegDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if(m_name==""){
		MessageBox("请输入昵称!","提示");
		return;
	}
	else{
		strncpy(regmsg.username,m_name,30);
	}
	if(m_passwd==""){
		MessageBox("请输入密码!","提示");
		return;
	}
	if(m_passwd2==""){
		MessageBox("请重复输入密码!","提示");
		return;
	}
	if (m_name.GetLength()>30||m_passwd.GetLength()>30||m_passwd2.GetLength()>30)
	{
		MessageBox("用户名或密码不能超过30个字符!","提示");
		return;
	}
	if(strcmp(m_passwd.GetBuffer(30),m_passwd2.GetBuffer(30))){
		MessageBox("两次密码输入不一值,请重新输入!","提示");
		m_passwd="";
		m_passwd2="";
		UpdateData(TRUE);
		return;
	}
	else{
		strncpy(regmsg.passwd,m_passwd,30);
	}
	chatclientDlg->regloginmsg.type=USERREG;
	memcpy(chatclientDlg->regloginmsg.data,&regmsg,sizeof(regmsg));
	CDialog::OnOK();
}

void CRegDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
