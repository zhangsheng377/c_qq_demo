// chatclientDlg.h : header file
//

#if !defined(AFX_CHATCLIENTDLG_H__54D0E846_8CCE_441D_8424_8DE4B76A3464__INCLUDED_)
#define AFX_CHATCLIENTDLG_H__54D0E846_8CCE_441D_8424_8DE4B76A3464__INCLUDED_

#include "../include/datauct.h"
#define  MYWM_NOTIFYICON  WM_USER+1000 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChatclientDlg dialog

class CChatclientDlg : public CDialog
{
// Construction
public:
	CChatclientDlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	//{{AFX_DATA(CChatclientDlg)
	enum { IDD = IDD_CHATCLIENT_DIALOG };
	CListCtrl	m_onLineList;
	CString	m_id;
	CString	m_passwd;
	CString	m_zt;
	//}}AFX_DATA
	Regloginmsg loginmsg;//保存登陆信息
	Message regloginmsg;
	SOCKET m_socket;
	int m_client;
	bool login;
	CImageList m_listimagelist;//用户图标列表
	bool sound;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatclientDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	
// Implementation
protected:
	HICON m_hIcon;
	NOTIFYICONDATA m_tnid; //托盘图标
	// Generated message map functions
	//{{AFX_MSG(CChatclientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnQuxiao();
	afx_msg void OnButtonReg();
	afx_msg void OnDblclkListUser(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonSound();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATCLIENTDLG_H__54D0E846_8CCE_441D_8424_8DE4B76A3464__INCLUDED_)
