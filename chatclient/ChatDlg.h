#if !defined(AFX_CHATDLG_H__F8357316_CA11_45AE_990D_419B1FBE9649__INCLUDED_)
#define AFX_CHATDLG_H__F8357316_CA11_45AE_990D_419B1FBE9649__INCLUDED_
#include "../include/datauct.h"
#include "chatclientDlg.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChatDlg dialog

class CChatDlg : public CDialog
{
// Construction
public:
	CChatDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChatDlg)
	enum { IDD = IDD_CHAT_DIALOG };
	CString	m_sendmsg;
	CString	m_msg;
	//}}AFX_DATA
	CChatclientDlg *chatclientDlg;
	char name[30],id[30];
	Usermsg usermsg;
	Message msg;
	int timeevn;//settime 定时号
	CEdit *pedit;//用于聊天窗口内容显示区自动滚动到最后一条信息,取句柄在showwindow函数里!

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChatDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATDLG_H__F8357316_CA11_45AE_990D_419B1FBE9649__INCLUDED_)
