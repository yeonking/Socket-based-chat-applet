#ifndef __MT_H__
#define __MT_H__
#include "LSocket.h"
#include "stdafx.h"
#include "���������.h"
#include "���������Dlg.h"
#include "Msg.h"
#include "Resource.h"
#include "CSocket.h"

UINT mtButtonListen(LPVOID pParam)
{
	AfxMessageBox("���������߳�QwQ");
	if (pParam==NULL) AfxEndThread(NULL);
	//��ȡ�������õĲ������������õ���ڲ���
	CHAT* PP;
	CLSocket* m_pLSocket;
	PP=(CHAT*)pParam;
	m_pLSocket=PP->n_pLsocket;
	//���������׽��֣�׼�����ܿͻ�������������
	if(!m_pLSocket->Listen())
	{
		delete m_pLSocket;
		m_pLSocket=NULL;
		AfxMessageBox("������������");
		exit(1);
	}
	return 0;
}

UINT mtAccept(LPVOID pParam)
{
	AfxMessageBox("���������߳�QwQ");
	if (pParam==NULL) AfxEndThread(NULL);
	//��ȡ�������õĲ������������õ���ڲ���
	CHAT* PP;
	PP=(CHAT*)pParam;
	CLSocket* m_pLSocket;
	m_pLSocket=PP->n_pLsocket;
	CCSocket* pSocket;
	pSocket=PP->n_pSocket;
	CPtrList* m_connList;
	m_connList=PP->n_connList;
	CStatic* m_staNum;
	m_staNum=PP->m_staNum;
	if(m_pLSocket->Accept(*pSocket))	//���ܿͻ�������������
	{
		pSocket->Initialize();
		(*(m_connList)).AddTail(pSocket);
		CString strTemp;
		strTemp.Format("��������: %d",(*(m_connList)).GetCount());
		(*(m_staNum)).SetWindowText(strTemp);
	}else delete pSocket;

	return 0;
}



#endif