// LSocket.cpp : implementation file
//

#include "stdafx.h"
#include "聊天服务器.h"
#include "LSocket.h"
#include "聊天服务器Dlg.h"//自写

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLSocket

CLSocket::CLSocket(CMyDlg* pDlg)
{
	m_pDlg=pDlg;
}

CLSocket::~CLSocket()
{
	m_pDlg=NULL;
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CLSocket, CSocket)
	//{{AFX_MSG_MAP(CLSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CLSocket member functions

void CLSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnAccept(nErrorCode);
	m_pDlg->OnAccept();//自写
}

IMPLEMENT_DYNAMIC(CLSocket,CSocket)//自写，动态类语句

