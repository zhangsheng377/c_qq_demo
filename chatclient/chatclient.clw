; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChatclientDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "chatclient.h"
LastPage=0

ClassCount=4
Class1=CChatclientApp
Class2=CChatclientDlg
Class3=CChatDlg
Class4=CRegDlg

ResourceCount=3
Resource1=IDD_REG_DIALOG
Resource2=IDD_CHATCLIENT_DIALOG
Resource3=IDD_CHAT_DIALOG

[CLS:CChatclientApp]
Type=0
BaseClass=CWinApp
HeaderFile=chatclient.h
ImplementationFile=chatclient.cpp
LastObject=CChatclientApp

[CLS:CChatclientDlg]
Type=0
BaseClass=CDialog
HeaderFile=chatclientDlg.h
ImplementationFile=chatclientDlg.cpp
LastObject=CChatclientDlg
Filter=D
VirtualFilter=dWC

[CLS:CChatDlg]
Type=0
BaseClass=CDialog
HeaderFile=ChatDlg.h
ImplementationFile=ChatDlg.cpp
LastObject=CChatDlg
Filter=D
VirtualFilter=dWC

[CLS:CRegDlg]
Type=0
BaseClass=CDialog
HeaderFile=RegDlg.h
ImplementationFile=RegDlg.cpp

[DLG:IDD_CHATCLIENT_DIALOG]
Type=1
Class=CChatclientDlg
ControlCount=16
Control1=IDOK,button,1342373889
Control2=IDC_STATIC_ZT,static,1342308352
Control3=IDC_STATIC_ID,static,1342308352
Control4=IDC_STATIC_PASS,static,1342308352
Control5=IDC_EDIT_ID,edit,1350631552
Control6=IDC_EDIT_PASS,edit,1350631584
Control7=IDC_QUXIAO,button,1342242816
Control8=IDC_STATIC_ZXNUM,static,1342308352
Control9=IDC_STATIC_MYID,static,1342308352
Control10=IDC_STATIC_MYNAME,static,1342308352
Control11=IDC_MYNAME,static,1342308352
Control12=IDC_MYID,static,1342308352
Control13=IDC_BUTTON_REG,button,1342242816
Control14=IDC_LIST_USER,SysListView32,1350664581
Control15=IDC_STATIC,static,1342308352
Control16=IDC_BUTTON_SOUND,button,1342259200

[DLG:IDD_CHAT_DIALOG]
Type=1
Class=CChatDlg
ControlCount=5
Control1=IDC_EDIT_SEND,edit,1350631492
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_EDIT_MSG,edit,1352728644
Control5=IDC_STATIC_TS,static,1342308352

[DLG:IDD_REG_DIALOG]
Type=1
Class=CRegDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_NAME,static,1342308352
Control4=IDC_STATIC_PASS,static,1342308352
Control5=IDC_EDIT_NAME,edit,1350631552
Control6=IDC_EDIT_PASS,edit,1350631584
Control7=IDC_STATIC_PASS2,static,1342308352
Control8=IDC_EDIT_PASS2,edit,1350631584

