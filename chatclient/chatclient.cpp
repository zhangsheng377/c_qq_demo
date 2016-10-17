// chatclient.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "chatclient.h"
#include "chatclientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatclientApp

BEGIN_MESSAGE_MAP(CChatclientApp, CWinApp)
	//{{AFX_MSG_MAP(CChatclientApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatclientApp construction

CChatclientApp::CChatclientApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CChatclientApp object

CChatclientApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CChatclientApp initialization

BOOL CChatclientApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization

	CChatclientDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
