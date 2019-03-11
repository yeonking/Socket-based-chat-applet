; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "聊天服务器.h"

ClassCount=5
Class1=CMyApp
Class2=CMyDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CLSocket
Class5=CCSocket
Resource3=IDD_MY_DIALOG

[CLS:CMyApp]
Type=0
HeaderFile=聊天服务器.h
ImplementationFile=聊天服务器.cpp
Filter=N

[CLS:CMyDlg]
Type=0
HeaderFile=聊天服务器Dlg.h
ImplementationFile=聊天服务器Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CMyDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=聊天服务器Dlg.h
ImplementationFile=聊天服务器Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MY_DIALOG]
Type=1
Class=CMyDlg
ControlCount=6
Control1=IDC_STATIC_PORT,static,1342308352
Control2=IDC_EDIT_PORT,edit,1350631552
Control3=IDC_BUTTON_LISTEN,button,1342242816
Control4=IDOK,button,1342242816
Control5=IDC_LIST_MSG,listbox,1352728833
Control6=IDC_STATIC_NUM,static,1342308352

[CLS:CLSocket]
Type=0
HeaderFile=LSocket.h
ImplementationFile=LSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CLSocket

[CLS:CCSocket]
Type=0
HeaderFile=CSocket.h
ImplementationFile=CSocket.cpp
BaseClass=CSocket
Filter=N
LastObject=CCSocket
VirtualFilter=uq

