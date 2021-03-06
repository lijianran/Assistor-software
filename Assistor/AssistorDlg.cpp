
// AssistorDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Assistor.h"
#include "AssistorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAssistorDlg 对话框



CAssistorDlg::CAssistorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ASSISTOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAssistorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_MAINTITLE, m_Title);
	DDX_Control(pDX, IDC_STATIC_MYNAME, m_MyName);
}

BEGIN_MESSAGE_MAP(CAssistorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CAssistorDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_BONUS, &CAssistorDlg::OnBnClickedButtonBonus)
	ON_BN_CLICKED(IDC_BUTTON_SCORE, &CAssistorDlg::OnBnClickedButtonScore)
	ON_BN_CLICKED(IDC_BUTTON_CLASSIFY, &CAssistorDlg::OnBnClickedButtonClassify)
	ON_BN_CLICKED(IDC_BUTTON_SORT, &CAssistorDlg::OnBnClickedButtonSort)
	ON_BN_CLICKED(IDC_BUTTON_ADJUST, &CAssistorDlg::OnBnClickedButtonAdjust)
	ON_BN_CLICKED(IDC_BUTTON_GATHER, &CAssistorDlg::OnBnClickedButtonGather)
	ON_BN_CLICKED(IDC_BUTTON_TEACHER, &CAssistorDlg::OnBnClickedButtonTeacher)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAssistorDlg 消息处理程序

BOOL CAssistorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAssistorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAssistorDlg::OnPaint()
{

	//CRect rect;
	//CPaintDC dc(this);
	//GetClientRect(rect);
	//dc.FillSolidRect(rect, RGB(146, 0, 7)); //设置为绿色背景

	//newFont.CreatePointFont(200, L"黑体");
	//m_Title.SetFont(&newFont);
	//newFont.CreatePointFont(120, L"黑体");
	//m_MyName.SetFont(&newFont);

	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAssistorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAssistorDlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	if ((::MessageBox(this->m_hWnd, _T("确定退出系统吗？"), _T("提示"), MB_OKCANCEL)) == IDOK)
		CDialogEx::OnCancel();

}


void CAssistorDlg::OnBnClickedButtonScore()
{
	// TODO: 在此添加控件通知处理程序代码
	CScoreCompute calculator;
	if (calculator.DoModal() == IDOK)
	{

	}
}


void CAssistorDlg::OnBnClickedButtonBonus()
{
	// TODO: 在此添加控件通知处理程序代码
	CBonusCompute calculator;
	if (calculator.DoModal() == IDOK)
	{

	}

}


void CAssistorDlg::OnBnClickedButtonClassify()
{
	// TODO: 在此添加控件通知处理程序代码
	CStudentClassify classify;
	if (classify.DoModal() == IDOK)
	{

	}
}


void CAssistorDlg::OnBnClickedButtonSort()
{
	// TODO: 在此添加控件通知处理程序代码
	CClassSort classort;
	if (classort.DoModal() == IDOK)
	{

	}
}


void CAssistorDlg::OnBnClickedButtonAdjust()
{
	// TODO: 在此添加控件通知处理程序代码
	CStudentAdjust adjust;
	if (adjust.DoModal() == IDOK)
	{

	}
}


void CAssistorDlg::OnBnClickedButtonGather()
{
	// TODO: 在此添加控件通知处理程序代码
	CFilesGather gather;
	if (gather.DoModal() == IDOK)
	{

	}
}


void CAssistorDlg::OnBnClickedButtonTeacher()
{
	// TODO: 在此添加控件通知处理程序代码
	CTeacherClassfy classfy;
	if (classfy.DoModal() == IDOK)
	{

	}
}


HBRUSH CAssistorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性


	//if (IDC_STATIC_MAINTITLE == pWnd->GetDlgCtrlID())//判断发出消息的空间是否是该静态文本框
	//{
	//	pDC->SetTextColor(RGB(0, 0, 0));//设置文本颜色为白色
	//	pDC->SetBkMode(OPAQUE);//设置文本背景模式为透明
	//	pDC->SetBkColor(RGB(146, 0, 7));//设置文本背景为黑色
	//	hbr = CreateSolidBrush(RGB(146, 0, 7));//控件的背景色为黑色
	//}
	//if (IDC_STATIC_MYNAME == pWnd->GetDlgCtrlID())//判断发出消息的空间是否是该静态文本框
	//{
	//	pDC->SetTextColor(RGB(0, 0, 0));//设置文本颜色为白色
	//	pDC->SetBkMode(OPAQUE);//设置文本背景模式为透明
	//	pDC->SetBkColor(RGB(146, 0, 7));//设置文本背景为黑色
	//	hbr = CreateSolidBrush(RGB(146, 0, 7));//控件的背景色为黑色
	//}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
