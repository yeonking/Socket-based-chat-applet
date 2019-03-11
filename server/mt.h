#ifndef __MT_H__
#define __MT_H__
#include "LSocket.h"
#include "stdafx.h"
#include "聊天服务器.h"
#include "聊天服务器Dlg.h"
#include "Msg.h"
#include "Resource.h"
#include "CSocket.h"

UINT mtButtonListen(LPVOID pParam)
{
	AfxMessageBox("启动监听线程QwQ");
	if (pParam==NULL) AfxEndThread(NULL);
	//获取函数调用的参数，函数调用的入口参数
	CHAT* PP;
	CLSocket* m_pLSocket;
	PP=(CHAT*)pParam;
	m_pLSocket=PP->n_pLsocket;
	//启动监听套接字，准备接受客户机的链接请求
	if(!m_pLSocket->Listen())
	{
		delete m_pLSocket;
		m_pLSocket=NULL;
		AfxMessageBox("启动监听错误");
		exit(1);
	}
	return 0;
}

UINT mtAccept(LPVOID pParam)
{
	AfxMessageBox("启动连接线程QwQ");
	if (pParam==NULL) AfxEndThread(NULL);
	//获取函数调用的参数，函数调用的入口参数
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
	if(m_pLSocket->Accept(*pSocket))	//接受客户机的链接请求
	{
		pSocket->Initialize();
		(*(m_connList)).AddTail(pSocket);
		CString strTemp;
		strTemp.Format("在线人数: %d",(*(m_connList)).GetCount());
		(*(m_staNum)).SetWindowText(strTemp);
	}else delete pSocket;

	return 0;
}



#endif