// Msg.cpp: implementation of the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "����ͻ���.h"
#include "Msg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsg::CMsg()
{
	m_strBuf=_T("");
	m_bClose=FALSE;
}

CMsg::~CMsg()
{
}

void CMsg::Serialize(CArchive &ar)
{
		if(ar.IsStoring())//���������ͷ�������
	{
		ar<<(WORD)m_bClose;
		ar<<m_strBuf;
	}else{//������룬�ͽ�������
		WORD wd;
		ar>>wd;
		m_bClose=(BOOL)wd;
		ar>>m_strBuf;
	}
}
IMPLEMENT_DYNAMIC(CMsg,CObject)
