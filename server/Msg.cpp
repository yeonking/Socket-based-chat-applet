// Msg.cpp: implementation of the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "聊天服务器.h"
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
	m_strText=_T("");//初始化成员变量
	m_bClose=FALSE;
}

CMsg::~CMsg()
{

}

void CMsg::Serialize(CArchive &ar)
{
	if(ar.IsStoring())//如果是输出，则发送数据
	{
		ar<<(WORD)m_bClose;
		ar<<m_strText;
	}
	else{//如果是输入，则接受
		WORD wd;
		ar>>wd;
		m_bClose=(BOOL)wd;
		ar>>m_strText;
	}
}
IMPLEMENT_DYNAMIC(CMsg,CObject)