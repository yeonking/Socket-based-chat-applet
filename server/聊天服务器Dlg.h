// 聊天服务器Dlg.h : header file
//

#if !defined(AFX_DLG_H__282DD43B_F5C0_4026_9EAF_78749E37C24C__INCLUDED_)
#define AFX_DLG_H__282DD43B_F5C0_4026_9EAF_78749E37C24C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

#include "CSocket.h"
#include "LSocket.h"
class CMsg;
typedef struct {
	CLSocket* n_pLsocket;
	CCSocket* n_pSocket;
	CPtrList* n_connList;
	CStatic* m_staNum;
}CHAT;


class CMyDlg : public CDialog
{
// Construction
public:
	void backClients(CMsg* pMsg);//向聊天室所有客户及转发消息
	void OnReceive(CCSocket* pSocket);//获取客户机的发送消息
	void OnAccept();//接受请求连接
	CPtrList m_connList;//侦听套接字
	CLSocket* m_pLSocket;//连接列表
	CMyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
	CListBox	m_listMsg;
	CButton	m_btnClose;
	CButton	m_btnListen;
	CStatic	m_staNum;
	UINT	m_nPort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonListen();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_H__282DD43B_F5C0_4026_9EAF_78749E37C24C__INCLUDED_)
