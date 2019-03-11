// 聊天客户机Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "聊天客户机.h"
#include "聊天客户机Dlg.h"
#include "CSocket.h"
#include "Msg.h"
#include "Afxinet.h"
#include "mt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
	m_strCName = _T("");
	m_strSName = _T("");
	m_strMsg = _T("");
	m_nPort = 0;
	m_strFtp = _T("");
	m_strPwd = _T("");
	m_strName = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pSocket=NULL;
	m_pFile=NULL;
	m_pArchiveIn=NULL;
	m_pArchiveOut=NULL;
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	DDX_Control(pDX, IDC_UPLOAD, m_btnUpload);
	DDX_Control(pDX, IDC_LIST_FILE, m_listFile);
	DDX_Control(pDX, IDC_DOWNLOAD, m_btnDownload);
	DDX_Control(pDX, SEARCH, m_btnQuery);
	DDX_Control(pDX, IDC_EDIT_PWD, m_editPwd);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_FTP, m_editFtp);
	DDX_Control(pDX, IDC_LIST_MSG, m_listMsg);
	DDX_Control(pDX, IDOK, m_Send);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_btnClose);
	DDX_Control(pDX, IDC_BUTTON_CONN, m_btnConn);
	DDX_Text(pDX, IDC_EDIT_CNAME, m_strCName);
	DDX_Text(pDX, IDC_EDIT_SNAME, m_strSName);
	DDX_Text(pDX, IDC_EDIT_MSG, m_strMsg);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	DDX_Text(pDX, IDC_EDIT_FTP, m_strFtp);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, OnSend)
	ON_BN_CLICKED(IDC_BUTTON_CONN, OnButtonConn)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_WM_DESTROY()
	ON_BN_CLICKED(SEARCH, OnQuery)
	ON_BN_CLICKED(IDC_DOWNLOAD, OnDownload)
	ON_BN_CLICKED(IDC_UPLOAD, OnUpload)
	ON_LBN_SELCHANGE(IDC_LIST_FILE, OnSelchangeListFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_strCName="客户";
	m_nPort=8000;
	m_strSName=_T("localhost");
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	m_strFtp=_T("xxx");    // 初始化服务器域名
	m_strName=_T("");     // 初始化登录用户名
	m_strPwd=_T("");      //  初始化登录口令
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(!m_strMsg.IsEmpty())
	{
		this->SendMsg(m_strCName+":"+m_strMsg,FALSE);
		m_strMsg=_T("");
		UpdateData(FALSE);
	}
}

void CMyDlg::OnButtonConn() 
{
	// TODO: Add your control notification handler code here
	m_pSocket=new CCSocket(this);//创建套接字对象
	if(!m_pSocket->Create())//创建底层套接字
	{
		delete m_pSocket;
		m_pSocket=NULL;
		AfxMessageBox("套接字创建错误!");
		return;
	}
	if(!m_pSocket->Connect(m_strSName,m_nPort))
	{
		delete m_pSocket;
		m_pSocket=NULL;
		AfxMessageBox("无法连接服务器错误!");
		return;
	}
	//创建CSocketFile类对象
	m_pFile=new CSocketFile(m_pSocket);
	m_pArchiveIn=new CArchive(m_pFile,CArchive::load);
	m_pArchiveOut=new CArchive(m_pFile,CArchive::store);

	UpdateData(TRUE);
	CString strTemp;
	strTemp=m_strCName+":进入聊天室";
	//调用SendMsg,想服务器发送消息，表明该客户及进入聊天室
	SendMsg(strTemp,FALSE);
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(TRUE);

	GetDlgItem(IDC_EDIT_CNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CONN)->EnableWindow(FALSE);
}

void CMyDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	CString strTemp;
	strTemp=m_strCName+":离开聊天室!";
	SendMsg(strTemp,TRUE);
	
	delete m_pArchiveOut;
	m_pArchiveOut=NULL;
	delete m_pArchiveIn;
	m_pArchiveIn=NULL;
	delete m_pFile;
	m_pFile=NULL;
	m_pSocket->Close();
	delete m_pSocket;
	m_pSocket=NULL;
	//清除列表框
	while(m_listMsg.GetCount()!=0)
		m_listMsg.DeleteString(0);
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	
	GetDlgItem(IDC_EDIT_CNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CONN)->EnableWindow(TRUE);
}

void CMyDlg::OnReceive()
{
	do
	{
		ReceiveMsg();
		if(m_pSocket==NULL) return;
	} while(!m_pArchiveIn->IsBufferEmpty());

}
//实际执行接收消息的函数
void CMyDlg::ReceiveMsg()
{
	CMsg msg;
	TRY
	{
		msg.Serialize(*m_pArchiveIn);
		m_listMsg.AddString(msg.m_strBuf);
	}
	CATCH(CFileException,e)
	{
		CString strTemp;
		strTemp="服务器重置连接!连接关闭!";
		m_listMsg.AddString(strTemp);
		msg.m_bClose=TRUE;
		m_pArchiveOut->Abort();
		delete m_pArchiveIn;
		m_pArchiveIn=NULL;
		delete m_pArchiveOut;
		m_pArchiveOut=NULL;
		delete m_pFile;
		m_pFile=NULL;
		delete m_pSocket;
		m_pSocket=NULL;
	}
	END_CATCH
}
//实际执行发送的函数
void CMyDlg::SendMsg(CString &strText, bool st)
{
	if(m_pArchiveOut!=NULL)
	{
		CMsg msg;
		msg.m_strBuf=strText;
		msg.m_bClose=st;
		msg.Serialize(*m_pArchiveOut);
		m_pArchiveOut->Flush();
	}
}

void CMyDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if((m_pSocket!=NULL)&&(m_pFile!=NULL)&&(m_pArchiveOut!=NULL))
	{
		CMsg msg;
		CString strTemp;
		strTemp="DDDD:离开聊天室!";
		msg.m_bClose=TRUE;
		msg.m_strBuf=m_strCName+strTemp;
		msg.Serialize(*m_pArchiveOut);
		m_pArchiveOut->Flush();
	}
	delete m_pArchiveOut;
	m_pArchiveOut=NULL;
	delete m_pArchiveIn;
	m_pArchiveIn=NULL;
	delete m_pFile;
	m_pFile=NULL;
	if(m_pSocket!=NULL)
	{
		BYTE Buffer[50];
		m_pSocket->ShutDown();
		while(m_pSocket->Receive(Buffer,50)>0);
	}
	delete m_pSocket;
	m_pSocket=NULL;
}

void CMyDlg::OnQuery() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);      // 获得用户的当前输入（服务器名，用户名和口令）
	FTP* pp=new FTP;
	pp->pList=&m_listFile;
	pp->strFtp=m_strFtp;
	pp->strName=m_strName;
	pp->strPwd=m_strPwd;

	while(m_listFile.GetCount()!=0) m_listFile.DeleteString(0);  // 清除列表框的内容
	AfxBeginThread(mtQuery,pp);//启动查询线程

}

void CMyDlg::OnDownload() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);      // 获得用户的当前输入
	FTP* pp=new FTP;
	pp->pList=&m_listFile;
	pp->strFtp=m_strFtp;
	pp->strName=m_strName;
	pp->strPwd=m_strPwd;

	AfxBeginThread(mtDownload,pp);//启动下载线程

	//禁用下载按钮
	m_btnDownload.EnableWindow(FALSE);

	//激活查询和上传按钮
	m_btnUpload.EnableWindow(TRUE);
	m_btnQuery.EnableWindow(TRUE);

	//激活用来输入的文本和编辑框控件
	m_editFtp.EnableWindow(TRUE);
	m_editName.EnableWindow(TRUE);
	m_editPwd.EnableWindow(TRUE);
	m_editFtp.EnableWindow(TRUE);
	m_editName.EnableWindow(TRUE);
	m_editPwd.EnableWindow(TRUE);

}

void CMyDlg::OnUpload() 
{
	// TODO: Add your control notification handler code here
	//获得当前输入
	UpdateData(TRUE);

	//禁用用于输入的文本框控件
	m_editFtp.EnableWindow(FALSE);            //服务器域名输入文本框
	m_editName.EnableWindow(FALSE);          //登录客户名输入文本框
	m_editPwd.EnableWindow(FALSE);            //口令输入文本框
	m_editFtp.EnableWindow(FALSE);
	m_editName.EnableWindow(FALSE);
	m_editPwd.EnableWindow(FALSE);

	//禁用查询按钮
	m_btnQuery.EnableWindow(FALSE);

	FTP* pp=new FTP;
	pp->pList=&m_listFile;
	pp->strFtp=m_strFtp;
	pp->strName=m_strName;
	pp->strPwd=m_strPwd;

	AfxBeginThread(mtUpload,pp);//启动上传线程

	//激活查询按钮
	m_btnQuery.EnableWindow(TRUE);

	//激活用于输入的文本框控件
	m_editFtp.EnableWindow(TRUE);
	m_editName.EnableWindow(TRUE);
	m_editPwd.EnableWindow(TRUE);
	m_editFtp.EnableWindow(TRUE);
	m_editName.EnableWindow(TRUE);
	m_editPwd.EnableWindow(TRUE);

}

//查询以后，当用户在列表框中选择了一个文件时，执行此函数。
void CMyDlg::OnSelchangeListFile() 
{
	// TODO: Add your control notification handler code here
	// 禁用用来输入的文本框控件
	m_editFtp.EnableWindow(FALSE);          //服务器域名输入文本框
	m_editName.EnableWindow(FALSE);        //登录用户名输入文本框 
	m_editPwd.EnableWindow(FALSE);          //口令输入文本框
	m_editFtp.EnableWindow(FALSE);
	m_editName.EnableWindow(FALSE);
	m_editPwd.EnableWindow(FALSE);

	//禁用查询和上传按钮
	m_btnUpload.EnableWindow(FALSE);      //上传按钮
	m_btnQuery.EnableWindow(FALSE);        //查询按钮

	//激活下载按钮
	m_btnDownload.EnableWindow(TRUE);
}

