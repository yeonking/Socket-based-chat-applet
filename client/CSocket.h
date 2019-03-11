#if !defined(AFX_CSOCKET_H__79D8F5D5_20EB_4AD7_BF73_E7CF184B8106__INCLUDED_)
#define AFX_CSOCKET_H__79D8F5D5_20EB_4AD7_BF73_E7CF184B8106__INCLUDED_

//#include "聊天客户机Dlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCSocket command target

class CMyDlg;

class CCSocket : public CSocket
{
	DECLARE_DYNAMIC(CCSocket);
// Attributes
public:

// Operations
public:
	CCSocket(CMyDlg* pDlg);
	virtual ~CCSocket();

// Overrides
public:
	CMyDlg* m_pDlg;
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

#endif // !defined(AFX_CSOCKET_H__79D8F5D5_20EB_4AD7_BF73_E7CF184B8106__INCLUDED_)
