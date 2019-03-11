#if !defined(AFX_LSOCKET_H__350EEA52_B196_422F_B01A_9926F028B8BE__INCLUDED_)
#define AFX_LSOCKET_H__350EEA52_B196_422F_B01A_9926F028B8BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LSocket.h : header file
//
class CMyDlg;//自写，对话框类定义



/////////////////////////////////////////////////////////////////////////////
// CLSocket command target
//用于监听客户机段链接请求的侦听套接字类定义
class CLSocket : public CSocket
{
// Attributes
	DECLARE_DYNAMIC(CLSocket);//自写，动态类声明
public:

// Operations
public:
	CLSocket(CMyDlg* pDlg);
	virtual ~CLSocket();

// Overrides
public:
	CMyDlg * m_pDlg;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLSocket)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CLSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	virtual void OnAccept(int nErrorCode);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LSOCKET_H__350EEA52_B196_422F_B01A_9926F028B8BE__INCLUDED_)
