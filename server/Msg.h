// Msg.h: interface for the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSG_H__3963015E_CA6C_4EFA_AA24_F916A34FFC83__INCLUDED_)
#define AFX_MSG_H__3963015E_CA6C_4EFA_AA24_F916A34FFC83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMsg : public CObject  
{
	DECLARE_DYNCREATE(CMsg);
public:
	virtual void Serialize(CArchive& ar);
	BOOL m_bClose;
	CString m_strText;
	CMsg();
	virtual ~CMsg();

};

#endif // !defined(AFX_MSG_H__3963015E_CA6C_4EFA_AA24_F916A34FFC83__INCLUDED_)
