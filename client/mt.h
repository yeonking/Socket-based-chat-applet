#ifndef __MT_H__
#define __MT_H__

#include "stdafx.h"
#include "聊天客户机.h"
#include "聊天客户机Dlg.h"
#include "CSocket.h"
#include "Msg.h"
#include "Afxinet.h"

UINT mtQuery(LPVOID pParam)
{
	AfxMessageBox("启动查询线程QwQ");
	if (pParam==NULL) AfxEndThread(NULL);
	//获取函数调用的参数，函数调用的入口参数
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

	CInternetSession* pSession;     //定义会话对象指针变量
	CFtpConnection* pConnection;   //定义连接对象指针变量
	CFtpFileFind* pFileFind;          //定义文件查询对象指针变量
	CString strFileName;
	BOOL bContinue;

	pConnection=NULL;      //初始化
	pFileFind=NULL;

	while(m_pList->GetCount()!=0) m_pList->DeleteString(0);  // 清除列表框的内容

	pSession=new CInternetSession(          // 创建Internet会话类对象
			AfxGetAppName(),1,PRE_CONFIG_INTERNET_ACCESS);
	try 
	{  // 试图建立与指定FTP服务器的连接
		pConnection=
			pSession->GetFtpConnection(m_strFtp,m_strName,m_strPwd);
	}  catch (CInternetException* e)  {   
		e->Delete();                          // 无法建立连接，进行错误处理
		pConnection=NULL;
	}

	if (pConnection!=NULL)
	{
		// 创建CFtpFileFind对象，向构造函数传递CFtpConnection对象的指针
		pFileFind=new CFtpFileFind(pConnection);
		bContinue=pFileFind->FindFile("*");  // 查找服务器上当前目录的任意文件
		if (!bContinue)   // 如果一个文件都找不到，结束查找
		{
			pFileFind->Close();
			pFileFind=NULL;
		}

		while (bContinue)  // 找到了第一个文件，继续找其它的文件
		{
			strFileName=pFileFind->GetFileName();  // 获得找到的文件的文件名
			// 如果找到的是否目录，将目录名放在括弧中
			if (pFileFind->IsDirectory())  strFileName="["+strFileName+"]";
			// 将找到的文件或目录名显示在列表框中。
			m_pList->AddString(strFileName);
			bContinue=pFileFind->FindNextFile();    // 查找下一个文件
		}

		if (pFileFind!=NULL)
		{
			pFileFind->Close();   // 结束查询
			pFileFind=NULL;
		}
	}
	delete pFileFind;              // 删除文件查询对象
	if (pConnection!=NULL)
	{
		pConnection->Close();
		delete pConnection;      // 删除FTP连接对象
	}
	delete pSession;             // 删除Internet 会话对象 
	return 0;
}

BOOL Download(CString strFtp,CString strName,CString strPwd,CString strSName, CString strDName)
{
	CInternetSession* pSession;      //定义会话对象变量指针
	CFtpConnection* pConnection;    //定义连接对象变量指针

	pConnection=NULL;

	//创建Internet会话对象
	pSession=new CInternetSession( AfxGetAppName(), 1,
	PRE_CONFIG_INTERNET_ACCESS);

	try
	{
		//建立FTP连接
		pConnection=pSession->GetFtpConnection(strFtp,
				strName, strPwd);
	}
	catch (CInternetException* e)
	{
		//错误处理
		e->Delete();
		pConnection=NULL;
		return FALSE;
	}

	if (pConnection!=NULL)
	{
		//下载文件
		if (!pConnection->GetFile(strSName,strDName))
		{
			//下载文件错误
			pConnection->Close();
			delete pConnection;
			delete pSession;
			return FALSE;
		}
	}

	//清除对象
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
	AfxMessageBox("启动下载线程QwQ");
	if (pParam==NULL) AfxEndThread(NULL);
	//获取函数调用的参数，函数调用的入口参数
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

	//获得用户在列表框中的选择
	m_pList->GetText(nSel,strSourceName);

	if (strSourceName.GetAt(0)!='[' )
	{
		//选择的是文件
		CString strDestName;
		CFileDialog dlg(FALSE,"","*.*");   //定义了一个文件对话框对象变量
		if (dlg.DoModal()==SEARCH)        //激活文件对话框
		{
			//获得下载文件在本地机上存储的路径和名称
			strDestName=dlg.GetPathName();

			//调用函数下载文件
			if (Download(m_strFtp,m_strName,m_strPwd,strSourceName,strDestName))
				AfxMessageBox("下载成功！",MB_OK|MB_ICONINFORMATION);
			else{
				AfxMessageBox("下载失败！",MB_OK|MB_ICONSTOP);
				return FALSE;
			}
		}  else  {
			AfxMessageBox("请写入文件名！",MB_OK|MB_ICONSTOP);
			return FALSE;
		}
	}  else  {
		//选择的是目录
		AfxMessageBox("不能下载目录!\n请重选!",MB_OK|MB_ICONSTOP);
		return FALSE;
	}

	return 0;
}

BOOL Upload(CString strFtp,CString strName,CString strPwd,CString strSName, CString strDName)
{
	CInternetSession* pSession;
	CFtpConnection* pConnection;

	pConnection=NULL;

	//创建Internet会话
	pSession=new CInternetSession(	AfxGetAppName(), 1,
	PRE_CONFIG_INTERNET_ACCESS);

	try
	{
		//建立FTP连接
		pConnection=pSession->GetFtpConnection(strFtp,
		strName, strPwd);
	}
	catch (CInternetException* e)
	{
		//错误处理
		e->Delete();
		pConnection=NULL;
		return FALSE;
	}

	if (pConnection!=NULL)
	{
		//上传文件
		if (!pConnection->PutFile(strSName,strDName))
		{
			//上传文件错误
			pConnection->Close();
			delete pConnection;
			delete pSession;
			return FALSE;
		}
	}

	//清除对象
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
	AfxMessageBox("启动上传线程QwQ");
	if (pParam==NULL) AfxEndThread(NULL);
	//获取函数调用的参数，函数调用的入口参数
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
	CFileDialog dlg(TRUE,"","*.*");       //定义文本对话框对象变量
	if (dlg.DoModal()==SEARCH)
	{
		//获得待上传的本地机文件路径和文件名
		strSourceName=dlg.GetPathName();
		strDestName=dlg.GetFileName();

		//调用Upload函数上传文件
		if (Upload(m_strFtp,m_strName,m_strPwd,strSourceName,strDestName))
			AfxMessageBox("上传成功！",MB_OK|MB_ICONINFORMATION);
		else
			AfxMessageBox("上传失败！",MB_OK|MB_ICONSTOP);
	}  else  {
		//文件选择有错误
		AfxMessageBox("请选择文件！",MB_OK|MB_ICONSTOP);
	}

	return 0;
}



#endif