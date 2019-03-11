#if !defined(AFX_CSOCKET_H__46EDE681_75C6_4E90_B701_6252C89BF27F__INCLUDED_)
#define AFX_CSOCKET_H__46EDE681_75C6_4E90_B701_6252C89BF27F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSocket.h : header file
//

class CMyDlg;
class CMsg;

/////////////////////////////////////////////////////////////////////////////
// CCSocket command target

class CCSocket : public CSocket
{
	DECLARE_DYNAMIC(CCSocket);//自写，动态类声明
// Attributes
public:

// Operations
public:
	CCSocket(CMyDlg* pDlg);
	virtual ~CCSocket();

// Overrides
public:	
	void ReceiveMessage(CMsg *pMsg);
	void SendMessage(CMsg* pMsg);
	void Initialize();
	CArchive* m_pArchiveIn;
	CArchive* m_pArchiveOut;
	CSocketFile* m_pFile;
	CMyDlg * m_pDlg;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSocket)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CCSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	virtual void OnReceive(int nErrorCode);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSOCKET_H__46EDE681_75C6_4E90_B701_6252C89BF27F__INCLUDED_)
