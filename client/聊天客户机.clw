; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "聊天客户机.h"

ClassCount=4
Class1=CMyApp
Class2=CMyDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CCSocket
Resource3=IDD_MY_DIALOG

[CLS:CMyApp]
Type=0
HeaderFile=聊天客户机.h
ImplementationFile=聊天客户机.cpp
Filter=N

[CLS:CMyDlg]
Type=0
HeaderFile=聊天客户机Dlg.h
ImplementationFile=聊天客户机Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CMyDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=聊天客户机Dlg.h
ImplementationFile=聊天客户机Dlg.cpp
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
ControlCount=23
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_CNAME,edit,1350631552
Control5=IDC_EDIT_SNAME,edit,1350631552
Control6=IDC_EDIT_MSG,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_PORT,edit,1350631552
Control9=IDC_BUTTON_CLOSE,button,1342242816
Control10=IDC_BUTTON_CONN,button,1342242816
Control11=IDOK,button,1342242816
Control12=IDC_LIST_MSG,listbox,1352728835
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT_FTP,edit,1350631552
Control17=IDC_EDIT_NAME,edit,1350631552
Control18=IDC_STATIC,static,1342308352
Control19=IDC_EDIT_PWD,edit,1350631552
Control20=IDC_LIST_FILE,listbox,1352728833
Control21=SEARCH,button,1342242816
Control22=IDC_DOWNLOAD,button,1342242816
Control23=IDC_UPLOAD,button,1342242816

[CLS:CCSocket]
Type=0
HeaderFile=CSocket.h
ImplementationFile=CSocket.cpp
BaseClass=CSocket
Filter=N
LastObject=CCSocket

