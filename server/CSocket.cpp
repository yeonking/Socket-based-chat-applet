// CSocket.cpp : implementation file
//

#include "stdafx.h"
#include "���������.h"
#include "CSocket.h"
#include "���������Dlg.h"
#include "Msg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCSocket

CCSocket::CCSocket(CMyDlg* pDlg)
{
	m_pDlg=pDlg;
	m_pFile=NULL;
	m_pArchiveIn=NULL;
	m_pArchiveOut=NULL;
	
}

CCSocket::~CCSocket()
{
	m_pDlg=NULL;
	if(m_pArchiveOut!=NULL)	delete m_pArchiveOut;
	if(m_pArchiveIn!=NULL)	delete m_pArchiveIn;
	if(m_pFile!=NULL)	delete m_pFile;
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

void CCSocket::Initialize()
{
	m_pFile=new CSocketFile(this,TRUE);//��������׽�����Ӧ��CSocketFile����
	m_pArchiveIn=new CArchive(m_pFile,CArchive::load);//��������׽�����Ӧ��CArchive����
	m_pArchiveOut=new CArchive(m_pFile,CArchive::store);
}

void CCSocket::SendMessage(CMsg *pMsg)
{
	if(m_pArchiveOut!=NULL)
	{
		//������Ϣ������л�������������Ϣ
		pMsg->Serialize(*m_pArchiveOut);
		//��CArchive�����е�����ǿ����д��CSocketFile�ļ���
		m_pArchiveOut->Flush();
	}
}

void CCSocket::ReceiveMessage(CMsg *pMsg)
{
	//������Ϣ������л�������������Ϣ
	pMsg->Serialize(*m_pArchiveIn);
}

void CCSocket::OnReceive(int nErrorCode)
{
	CSocket::OnReceive(nErrorCode);
	m_pDlg->OnReceive(this);
}

IMPLEMENT_DYNAMIC(CCSocket,CSocket)