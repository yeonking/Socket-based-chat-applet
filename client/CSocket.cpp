// CSocket.cpp : implementation file
//

#include "stdafx.h"
#include "聊天客户机.h"
#include "CSocket.h"
#include "聊天客户机Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCSocket
IMPLEMENT_DYNAMIC(CCSocket,CSocket)

CCSocket::CCSocket(CMyDlg* pDlg)
{
	m_pDlg=pDlg;
}

CCSocket::~CCSocket()
{
	m_pDlg=NULL;
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CCSocket, CSocket)
	//{{AFX_MSG_MAP(CCSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CCSocket member functions

void CCSocket::OnReceive(int nErrorCode)
{
	CSocket::OnReceive(nErrorCode);
	//调用CMyDlg类相应函数处理
	if(nErrorCode==0) m_pDlg->OnReceive();
}
