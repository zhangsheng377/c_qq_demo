// chatclient.h : main header file for the CHATCLIENT application
//

#if !defined(AFX_CHATCLIENT_H__8AAEC1E0_5EE9_4DF7_8588_AB2EAC7B3188__INCLUDED_)
#define AFX_CHATCLIENT_H__8AAEC1E0_5EE9_4DF7_8588_AB2EAC7B3188__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CChatclientApp:
// See chatclient.cpp for the implementation of this class
//

class CChatclientApp : public CWinApp
{
public:
	CChatclientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatclientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CChatclientApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATCLIENT_H__8AAEC1E0_5EE9_4DF7_8588_AB2EAC7B3188__INCLUDED_)
