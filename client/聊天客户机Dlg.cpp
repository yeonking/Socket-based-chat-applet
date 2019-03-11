// ����ͻ���Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "����ͻ���.h"
#include "����ͻ���Dlg.h"
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
	m_strCName="�ͻ�";
	m_nPort=8000;
	m_strSName=_T("localhost");
	GetDlgItem(IDC_EDIT_MSG)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CLOSE)->EnableWindow(FALSE);
	m_strFtp=_T("xxx");    // ��ʼ������������
	m_strName=_T("");     // ��ʼ����¼�û���
	m_strPwd=_T("");      //  ��ʼ����¼����
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
	m_pSocket=new CCSocket(this);//�����׽��ֶ���
	if(!m_pSocket->Create())//�����ײ��׽���
	{
		delete m_pSocket;
		m_pSocket=NULL;
		AfxMessageBox("�׽��ִ�������!");
		return;
	}
	if(!m_pSocket->Connect(m_strSName,m_nPort))
	{
		delete m_pSocket;
		m_pSocket=NULL;
		AfxMessageBox("�޷����ӷ���������!");
		return;
	}
	//����CSocketFile�����
	m_pFile=new CSocketFile(m_pSocket);
	m_pArchiveIn=new CArchive(m_pFile,CArchive::load);
	m_pArchiveOut=new CArchive(m_pFile,CArchive::store);

	UpdateData(TRUE);
	CString strTemp;
	strTemp=m_strCName+":����������";
	//����SendMsg,�������������Ϣ�������ÿͻ�������������
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
	strTemp=m_strCName+":�뿪������!";
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
	//����б��
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
//ʵ��ִ�н�����Ϣ�ĺ���
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
		strTemp="��������������!���ӹر�!";
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
//ʵ��ִ�з��͵ĺ���
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
		strTemp="DDDD:�뿪������!";
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
	UpdateData(TRUE);      // ����û��ĵ�ǰ���루�����������û����Ϳ��
	FTP* pp=new FTP;
	pp->pList=&m_listFile;
	pp->strFtp=m_strFtp;
	pp->strName=m_strName;
	pp->strPwd=m_strPwd;

	while(m_listFile.GetCount()!=0) m_listFile.DeleteString(0);  // ����б�������
	AfxBeginThread(mtQuery,pp);//������ѯ�߳�

}

void CMyDlg::OnDownload() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);      // ����û��ĵ�ǰ����
	FTP* pp=new FTP;
	pp->pList=&m_listFile;
	pp->strFtp=m_strFtp;
	pp->strName=m_strName;
	pp->strPwd=m_strPwd;

	AfxBeginThread(mtDownload,pp);//���������߳�

	//�������ذ�ť
	m_btnDownload.EnableWindow(FALSE);

	//�����ѯ���ϴ���ť
	m_btnUpload.EnableWindow(TRUE);
	m_btnQuery.EnableWindow(TRUE);

	//��������������ı��ͱ༭��ؼ�
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
	//��õ�ǰ����
	UpdateData(TRUE);

	//��������������ı���ؼ�
	m_editFtp.EnableWindow(FALSE);            //���������������ı���
	m_editName.EnableWindow(FALSE);          //��¼�ͻ��������ı���
	m_editPwd.EnableWindow(FALSE);            //���������ı���
	m_editFtp.EnableWindow(FALSE);
	m_editName.EnableWindow(FALSE);
	m_editPwd.EnableWindow(FALSE);

	//���ò�ѯ��ť
	m_btnQuery.EnableWindow(FALSE);

	FTP* pp=new FTP;
	pp->pList=&m_listFile;
	pp->strFtp=m_strFtp;
	pp->strName=m_strName;
	pp->strPwd=m_strPwd;

	AfxBeginThread(mtUpload,pp);//�����ϴ��߳�

	//�����ѯ��ť
	m_btnQuery.EnableWindow(TRUE);

	//��������������ı���ؼ�
	m_editFtp.EnableWindow(TRUE);
	m_editName.EnableWindow(TRUE);
	m_editPwd.EnableWindow(TRUE);
	m_editFtp.EnableWindow(TRUE);
	m_editName.EnableWindow(TRUE);
	m_editPwd.EnableWindow(TRUE);

}

//��ѯ�Ժ󣬵��û����б����ѡ����һ���ļ�ʱ��ִ�д˺�����
void CMyDlg::OnSelchangeListFile() 
{
	// TODO: Add your control notification handler code here
	// ��������������ı���ؼ�
	m_editFtp.EnableWindow(FALSE);          //���������������ı���
	m_editName.EnableWindow(FALSE);        //��¼�û��������ı��� 
	m_editPwd.EnableWindow(FALSE);          //���������ı���
	m_editFtp.EnableWindow(FALSE);
	m_editName.EnableWindow(FALSE);
	m_editPwd.EnableWindow(FALSE);

	//���ò�ѯ���ϴ���ť
	m_btnUpload.EnableWindow(FALSE);      //�ϴ���ť
	m_btnQuery.EnableWindow(FALSE);        //��ѯ��ť

	//�������ذ�ť
	m_btnDownload.EnableWindow(TRUE);
}

