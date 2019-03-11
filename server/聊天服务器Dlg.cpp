// 聊天服务器Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "聊天服务器.h"
#include "聊天服务器Dlg.h"
#include "Msg.h"
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
	m_nPort = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	DDX_Control(pDX, IDC_LIST_MSG, m_listMsg);
	DDX_Control(pDX, IDOK, m_btnClose);
	DDX_Control(pDX, IDC_BUTTON_LISTEN, m_btnListen);
	DDX_Control(pDX, IDC_STATIC_NUM, m_staNum);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LISTEN, OnButtonListen)
	ON_BN_CLICKED(IDOK, OnClose)
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
	m_nPort=8000;
	UpdateData(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
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

//单机监听按钮的操作
void CMyDlg::OnButtonListen() 
{

	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//创建侦听套接字对象
	m_pLSocket=new CLSocket(this);
	//创建监听套接字的底层套接字，在用户指定的端口上侦听
	if(!m_pLSocket->Create(m_nPort))
	{
		delete m_pLSocket;
		m_pLSocket=NULL;
		AfxMessageBox("创建监听套接字错误");
		return;
	}
	CHAT* pp=new CHAT;
	pp->n_pLsocket=m_pLSocket;
	pp->n_pSocket=NULL;
	pp->n_connList=NULL;
	pp->m_staNum=NULL;
	AfxBeginThread(mtButtonListen,pp);//创建监听线程
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);

}

//停止按钮的操作
void CMyDlg::OnClose() 
{
	// TODO: Add your control notification handler code here
	CMsg msg;
	msg.m_strText="服务器终止服务!";
	delete m_pLSocket;  //删除监听套接字
	m_pLSocket=NULL;
	while(!m_connList.IsEmpty())
	{
		//向每个客户发送“服务器终止服务”的消息
		//并逐个删除已建立的连接
		CCSocket* pSocket=(CCSocket*)m_connList.RemoveHead();
		pSocket->SendMessage(&msg);
		delete pSocket;
	}
	//清除列表框
	while(m_listMsg.GetCount()!=0)
		m_listMsg.DeleteString(0);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_LISTEN)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
}

//接受连接请求
void CMyDlg::OnAccept()
{
	//创建用于与客户端连接并交换数据的套接字对象
	CCSocket* pSocket=new CCSocket(this);
	CHAT* pp=new CHAT;
	pp->n_pLsocket=m_pLSocket;
	pp->n_pSocket=pSocket;
	pp->n_connList=&m_connList;
	pp->m_staNum=&m_staNum;
	AfxBeginThread(mtAccept,pp);//创建连接线程
}

//获取客户机的发送消息
void CMyDlg::OnReceive(CCSocket *pSocket)
{
	static CMsg msg;
	do{
		//接收客户机发来的消息
		pSocket->ReceiveMessage(&msg);
		//显示在对话框中
		m_listMsg.AddString(msg.m_strText);
		//向所有客户机返回该客户发来的消息
		backClients(&msg);

		//如有客户关闭，将其从接连列表中删除
		if(msg.m_bClose)
		{
			pSocket->Close();
			POSITION pos,temp;
			for(pos=m_connList.GetHeadPosition();pos!=NULL;)
			{
				//对于关闭的客户机，将消息列表中已建立的链接删除
				temp=pos;
				CCSocket* pSock=(CCSocket*)m_connList.GetNext(pos);
				//匹配成功
				if(pSock==pSocket)
				{
					m_connList.RemoveAt(temp);
					CString strTemp;
					strTemp.Format("在线人数: %d",m_connList.GetCount());
					m_staNum.SetWindowText(strTemp);
					break;
				}
			}
			delete pSocket;
			break;
		}
	}while (!pSocket->m_pArchiveIn->IsBufferEmpty());
}

//当服务器收到某个客户发来的消息好，将他转发给所有客户机
void CMyDlg::backClients(CMsg *pMsg)
{
	for(POSITION pos=m_connList.GetHeadPosition();pos!=NULL;)
	{
		//获得连接列表的成员
		CCSocket* pSocket=(CCSocket*)m_connList.GetNext(pos);
		pSocket->SendMessage(pMsg);
	}
}
