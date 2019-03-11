// 聊天客户机Dlg.h : header file
//

#if !defined(AFX_DLG_H__F9759BF8_6BED_4BB5_8E46_F357DA83A44F__INCLUDED_)
#define AFX_DLG_H__F9759BF8_6BED_4BB5_8E46_F357DA83A44F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog
#include "CSocket.h"

typedef struct{
	CListBox* pList;
	CString strFtp;
	CString strName;
	CString	strPwd;
}FTP;

class CMyDlg : public CDialog
{
// Construction
public:
	void SendMsg(CString& strText,bool st);
	void ReceiveMsg();
	void OnReceive();
	CArchive* m_pArchiveIn;
	CArchive* m_pArchiveOut;
	CSocketFile* m_pFile;
	CCSocket* m_pSocket;
	CMyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
	CButton	m_btnUpload;
	CListBox	m_listFile;
	CButton	m_btnDownload;
	CButton	m_btnQuery;
	CEdit	m_editPwd;
	CEdit	m_editName;
	CEdit	m_editFtp;
	CListBox	m_listMsg;
	CButton	m_Send;
	CButton	m_btnClose;
	CButton	m_btnConn;
	CString	m_strCName;
	CString	m_strSName;
	CString	m_strMsg;
	UINT	m_nPort;
	CString	m_strFtp;
	CString	m_strPwd;
	CString	m_strName;
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
	afx_msg void OnSend();
	afx_msg void OnButtonConn();
	afx_msg void OnButtonClose();
	afx_msg void OnDestroy();
	afx_msg void OnQuery();
	afx_msg void OnDownload();
	afx_msg void OnUpload();
	afx_msg void OnSelchangeListFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_H__F9759BF8_6BED_4BB5_8E46_F357DA83A44F__INCLUDED_)
