#if !defined(AFX_REGDLG_H__20CDA4CB_8673_405D_B457_B0A94EC9EAA9__INCLUDED_)
#define AFX_REGDLG_H__20CDA4CB_8673_405D_B457_B0A94EC9EAA9__INCLUDED_

#include "../include/datauct.h"
#include "chatclientDlg.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRegDlg dialog

class CRegDlg : public CDialog
{
// Construction
public:

	CRegDlg(CWnd* pParent=NULL,CChatclientDlg* pchatclientDlg=NULL);
// Dialog Data
	//{{AFX_DATA(CRegDlg)
	enum { IDD = IDD_REG_DIALOG };
	CString	m_passwd;
	CString	m_name;
	CString	m_passwd2;
	//}}AFX_DATA
	CChatclientDlg *chatclientDlg;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	Regloginmsg regmsg;
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRegDlg)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGDLG_H__20CDA4CB_8673_405D_B457_B0A94EC9EAA9__INCLUDED_)
