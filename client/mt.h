#ifndef __MT_H__
#define __MT_H__

#include "stdafx.h"
#include "����ͻ���.h"
#include "����ͻ���Dlg.h"
#include "CSocket.h"
#include "Msg.h"
#include "Afxinet.h"

UINT mtQuery(LPVOID pParam)
{
	AfxMessageBox("������ѯ�߳�QwQ");
	if (pParam==NULL) AfxEndThread(NULL);
	//��ȡ�������õĲ������������õ���ڲ���
	FTP* PP;
	CListBox* m_pList;
	CString m_strFtp;
	CString m_strName;
	CString	m_strPwd;
	PP=(FTP*)pParam;
	m_pList=PP->pList;
	m_strFtp=PP->strFtp;
	m_strName=PP->strName;
	m_strPwd=PP->strPwd;

	CInternetSession* pSession;     //����Ự����ָ�����
	CFtpConnection* pConnection;   //�������Ӷ���ָ�����
	CFtpFileFind* pFileFind;          //�����ļ���ѯ����ָ�����
	CString strFileName;
	BOOL bContinue;

	pConnection=NULL;      //��ʼ��
	pFileFind=NULL;

	while(m_pList->GetCount()!=0) m_pList->DeleteString(0);  // ����б�������

	pSession=new CInternetSession(          // ����Internet�Ự�����
			AfxGetAppName(),1,PRE_CONFIG_INTERNET_ACCESS);
	try 
	{  // ��ͼ������ָ��FTP������������
		pConnection=
			pSession->GetFtpConnection(m_strFtp,m_strName,m_strPwd);
	}  catch (CInternetException* e)  {   
		e->Delete();                          // �޷��������ӣ����д�����
		pConnection=NULL;
	}

	if (pConnection!=NULL)
	{
		// ����CFtpFileFind�������캯������CFtpConnection�����ָ��
		pFileFind=new CFtpFileFind(pConnection);
		bContinue=pFileFind->FindFile("*");  // ���ҷ������ϵ�ǰĿ¼�������ļ�
		if (!bContinue)   // ���һ���ļ����Ҳ�������������
		{
			pFileFind->Close();
			pFileFind=NULL;
		}

		while (bContinue)  // �ҵ��˵�һ���ļ����������������ļ�
		{
			strFileName=pFileFind->GetFileName();  // ����ҵ����ļ����ļ���
			// ����ҵ����Ƿ�Ŀ¼����Ŀ¼������������
			if (pFileFind->IsDirectory())  strFileName="["+strFileName+"]";
			// ���ҵ����ļ���Ŀ¼����ʾ���б���С�
			m_pList->AddString(strFileName);
			bContinue=pFileFind->FindNextFile();    // ������һ���ļ�
		}

		if (pFileFind!=NULL)
		{
			pFileFind->Close();   // ������ѯ
			pFileFind=NULL;
		}
	}
	delete pFileFind;              // ɾ���ļ���ѯ����
	if (pConnection!=NULL)
	{
		pConnection->Close();
		delete pConnection;      // ɾ��FTP���Ӷ���
	}
	delete pSession;             // ɾ��Internet �Ự���� 
	return 0;
}

BOOL Download(CString strFtp,CString strName,CString strPwd,CString strSName, CString strDName)
{
	CInternetSession* pSession;      //����Ự�������ָ��
	CFtpConnection* pConnection;    //�������Ӷ������ָ��

	pConnection=NULL;

	//����Internet�Ự����
	pSession=new CInternetSession( AfxGetAppName(), 1,
	PRE_CONFIG_INTERNET_ACCESS);

	try
	{
		//����FTP����
		pConnection=pSession->GetFtpConnection(strFtp,
				strName, strPwd);
	}
	catch (CInternetException* e)
	{
		//������
		e->Delete();
		pConnection=NULL;
		return FALSE;
	}

	if (pConnection!=NULL)
	{
		//�����ļ�
		if (!pConnection->GetFile(strSName,strDName))
		{
			//�����ļ�����
			pConnection->Close();
			delete pConnection;
			delete pSession;
			return FALSE;
		}
	}

	//�������
	if (pConnection!=NULL)
	{
		pConnection->Close();
		delete pConnection;
	}
		delete pSession;

	return TRUE;
}

UINT mtDownload(LPVOID pParam)
{
	AfxMessageBox("���������߳�QwQ");
	if (pParam==NULL) AfxEndThread(NULL);
	//��ȡ�������õĲ������������õ���ڲ���
	FTP* PP;
	CListBox* m_pList;
	CString m_strFtp;
	CString m_strName;
	CString	m_strPwd;
	PP=(FTP*)pParam;
	m_pList=PP->pList;
	m_strFtp=PP->strFtp;
	m_strName=PP->strName;
	m_strPwd=PP->strPwd;

    int nSel=m_pList->GetCurSel();
	CString strSourceName;

	//����û����б���е�ѡ��
	m_pList->GetText(nSel,strSourceName);

	if (strSourceName.GetAt(0)!='[' )
	{
		//ѡ������ļ�
		CString strDestName;
		CFileDialog dlg(FALSE,"","*.*");   //������һ���ļ��Ի���������
		if (dlg.DoModal()==SEARCH)        //�����ļ��Ի���
		{
			//��������ļ��ڱ��ػ��ϴ洢��·��������
			strDestName=dlg.GetPathName();

			//���ú��������ļ�
			if (Download(m_strFtp,m_strName,m_strPwd,strSourceName,strDestName))
				AfxMessageBox("���سɹ���",MB_OK|MB_ICONINFORMATION);
			else{
				AfxMessageBox("����ʧ�ܣ�",MB_OK|MB_ICONSTOP);
				return FALSE;
			}
		}  else  {
			AfxMessageBox("��д���ļ�����",MB_OK|MB_ICONSTOP);
			return FALSE;
		}
	}  else  {
		//ѡ�����Ŀ¼
		AfxMessageBox("��������Ŀ¼!\n����ѡ!",MB_OK|MB_ICONSTOP);
		return FALSE;
	}

	return 0;
}

BOOL Upload(CString strFtp,CString strName,CString strPwd,CString strSName, CString strDName)
{
	CInternetSession* pSession;
	CFtpConnection* pConnection;

	pConnection=NULL;

	//����Internet�Ự
	pSession=new CInternetSession(	AfxGetAppName(), 1,
	PRE_CONFIG_INTERNET_ACCESS);

	try
	{
		//����FTP����
		pConnection=pSession->GetFtpConnection(strFtp,
		strName, strPwd);
	}
	catch (CInternetException* e)
	{
		//������
		e->Delete();
		pConnection=NULL;
		return FALSE;
	}

	if (pConnection!=NULL)
	{
		//�ϴ��ļ�
		if (!pConnection->PutFile(strSName,strDName))
		{
			//�ϴ��ļ�����
			pConnection->Close();
			delete pConnection;
			delete pSession;
			return FALSE;
		}
	}

	//�������
	if (pConnection!=NULL)
	{
		pConnection->Close();
		delete pConnection;
	}

	delete pSession;

	return TRUE;
}

UINT mtUpload(LPVOID pParam)
{
	AfxMessageBox("�����ϴ��߳�QwQ");
	if (pParam==NULL) AfxEndThread(NULL);
	//��ȡ�������õĲ������������õ���ڲ���
	FTP* PP;
	CListBox* m_pList;
	CString m_strFtp;
	CString m_strName;
	CString	m_strPwd;
	PP=(FTP*)pParam;
	m_pList=PP->pList;
	m_strFtp=PP->strFtp;
	m_strName=PP->strName;
	m_strPwd=PP->strPwd;

	CString strSourceName;
	CString strDestName;
	CFileDialog dlg(TRUE,"","*.*");       //�����ı��Ի���������
	if (dlg.DoModal()==SEARCH)
	{
		//��ô��ϴ��ı��ػ��ļ�·�����ļ���
		strSourceName=dlg.GetPathName();
		strDestName=dlg.GetFileName();

		//����Upload�����ϴ��ļ�
		if (Upload(m_strFtp,m_strName,m_strPwd,strSourceName,strDestName))
			AfxMessageBox("�ϴ��ɹ���",MB_OK|MB_ICONINFORMATION);
		else
			AfxMessageBox("�ϴ�ʧ�ܣ�",MB_OK|MB_ICONSTOP);
	}  else  {
		//�ļ�ѡ���д���
		AfxMessageBox("��ѡ���ļ���",MB_OK|MB_ICONSTOP);
	}

	return 0;
}



#endif