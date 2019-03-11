// Msg.h: interface for the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSG_H__4F6DF4E8_3723_4523_91B6_FB44A65D51C9__INCLUDED_)
#define AFX_MSG_H__4F6DF4E8_3723_4523_91B6_FB44A65D51C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMsg : public CObject  
{
	DECLARE_DYNCREATE(CMsg);
public:
	BOOL m_bClose;
	CString m_strBuf;
	virtual void Serialize(CArchive& ar);
	CMsg();
	virtual ~CMsg();
};

#endif // !defined(AFX_MSG_H__4F6DF4E8_3723_4523_91B6_FB44A65D51C9__INCLUDED_)
