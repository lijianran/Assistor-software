// CFilesGather.cpp: 实现文件
//

#include "stdafx.h"
#include "Assistor.h"
#include "CFilesGather.h"
#include "afxdialogex.h"




// CFilesGather 对话框

IMPLEMENT_DYNAMIC(CFilesGather, CDialogEx)

CFilesGather::CFilesGather(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GATHER, pParent)
{

}

CFilesGather::~CFilesGather()
{
}

bool CFilesGather::ReadFile()
{
	ifstream infile;
	infile.open(m_ModelFilePath, ios::in);
	if (infile.is_open())
	{
		string line;
		string field;
		getline(infile, line);
		istringstream data(line);
		while (getline(data, field, ','))
		{
			if (field == "")
				break;
			titlestrings.push_back(field);
		}
		infile.close();
	}
	else
	{
		::MessageBox(this->m_hWnd, _T("模板标题读入失败！"), _T("提示"), MB_OK);
		return false;
	}

	int filenums = int(m_FilePaths.size());
	for (int i = 0; i < filenums; i++)
	{
		CString onefile = m_FilePaths[i];
		infile.open(onefile, ios::in);
		if (infile.is_open())
		{
			string line;
			vector<int> titileIndexs;
			getline(infile, line);
			//找标题
			while (!ProcessTitles(titlestrings, line, titileIndexs))
			{
				if (!infile.eof())
					getline(infile, line);
				else
					break;
			}

			bool flag = true;
			if (titileIndexs.empty())//找不到标题
			{
				flag = false;
				CString num;
				num.Format(_T("%d"), i + 1);
				::MessageBox(this->m_hWnd, num+_T("号文件标题格式错误！"), _T("提示"), MB_OK);
				continue;
			}
			else
			{
				for (unsigned int i = 0; i < titileIndexs.size(); i++)
				{
					if (titileIndexs[i] == -1)
					{
						flag = false;
						CString num;
						num.Format(_T("%d"), i + 1);
						::MessageBox(this->m_hWnd,num+_T("号文件缺少需要信息！"), _T("提示"), MB_OK);
					}
				}
			}
			if (!flag)
				return false;

			//读数据
			while (!infile.eof())
			{
				string field;
				vector<string> fields;
				getline(infile, line);
				istringstream data(line);
				while (getline(data, field, ','))
				{
					fields.push_back(field);
				}
				if (fields.empty())
					break;

				vector<string> datas;
				for (unsigned int i = 0; i < titileIndexs.size(); i++)
				{
					if (titileIndexs[i] >= int(fields.size()))
						datas.push_back("");
					else
						datas.push_back(fields[titileIndexs[i]]);
				}
				m_Datas.push_back(datas);
			}
			infile.close();
		}
		else
		{
			CString num;
			num.Format(_T("%d"), i + 1);
			::MessageBox(this->m_hWnd, num + _T("号文件打开失败！"), _T("提示"), MB_OK);
			return false;
		}
	}

	return true;
}

void CFilesGather::ProcessFileDatas()
{

}

void CFilesGather::SaveFile()
{
	::MessageBox(this->m_hWnd, _T("汇总完成，请选择文件夹进行保存！"), _T("提示"), MB_OK);

	CString SavePath;
	CFileDialog findFileDlg(
		FALSE,  // TRUE是创建打开文件对话框，FALSE则创建的是保存文件对话框
		_T(".csv"),  // 默认的打开文件的类型
		NULL,  // 默认打开的文件名
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,  // 打开只读文件
		_T("文件(*.csv)|*.csv|")  // 所有可以打开的文件类型
	);

	// findFileDlg.GetOFN().lpstrInitialDir=strFile.c_str();// 默认目录
	if (IDOK == findFileDlg.DoModal())
	{
		//char tempBuff[1024];
		//int index = 0, startPos = 0, playTime, iSum, findFlag = 0, iChn = 0;
		SavePath = findFileDlg.GetPathName();  // 取出文件路径

		ofstream outfile1;
		outfile1.open(SavePath, ios::out | ios::trunc);

		if (outfile1.is_open())
		{
			for (unsigned int i = 0; i < titlestrings.size(); i++)
				outfile1 << titlestrings[i] << ",";
			outfile1 << endl;
			for (unsigned int i = 0; i < m_Datas.size(); i++)
			{
				vector<string> datas = m_Datas[i];
				for (unsigned int j = 0; j < datas.size(); j++)
				{
					outfile1 << datas[j] << ",";
				}
				outfile1 << endl;
			}
			outfile1.close();
			::MessageBox(this->m_hWnd, _T("保存完毕，点击确定回到主菜单！"), _T("提示"), MB_OK);
		}
		else
			::MessageBox(this->m_hWnd, _T("保存失败，点击确定回到主菜单！"), _T("提示"), MB_OK);
	}
	else
		::MessageBox(this->m_hWnd, _T("取消保存！"), _T("提示"), MB_OK);
}

bool CFilesGather::CheckBox()
{
	if (m_FilePaths.empty())
	{
		::MessageBox(this->m_hWnd, _T("请选择文件夹！"), _T("提示"), MB_OK);
		return false;
	}
	if (m_ModelFilePath.IsEmpty())
	{
		::MessageBox(this->m_hWnd, _T("请导入模板文件！"), _T("提示"), MB_OK);
		return false;
	}
	return true;
}

void CFilesGather::GetFileList(char * szPath)
{
	m_FilePaths.clear();
	m_ModelFilePath = "";
	m_ListShow.DeleteAllItems();

	CFileFind finder;
	//建立CString对象，设置检索匹配字符串
	CString strWildcard(szPath);
	strWildcard += _T("\\*.*");

	//文件内部检索
	BOOL bWorking = finder.FindFile(strWildcard);
	int i; //用于定位字符，作为下标
	int index = 0;    //用于列表索引

	CString fontName, filepath, filename, lastType/*, filesize*/;//存储切割结果
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		filename = finder.GetFileName();
		//imageSize = finder.GetLength();//假设文件夹里面全是图片，获取图片文件长度
		if (filename != _T(".") && filename != _T(".."))
		{
			filepath = finder.GetFilePath();
			for (i = 0; i < filename.GetLength(); i++)
			{
				if (filename[i] == '.')
				{
					fontName = filename.Mid(0, i);
					lastType = filename.Mid(i + 1, filename.GetLength());

					if (lastType != "csv")
						continue;
					else
						m_FilePaths.push_back(filepath);

					CString nums;
					nums.Format(_T("%d"), index + 1);
					m_ListShow.InsertItem(index, nums);
					m_ListShow.SetItemText(index, 1, fontName);
					m_ListShow.SetItemText(index, 2, lastType);
					m_ListShow.SetItemText(index, 3, filepath);
				}
			}
			index++;
		}
	}
	finder.Close();
}

void CFilesGather::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FILES, m_ListShow);
}


BEGIN_MESSAGE_MAP(CFilesGather, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFilesGather::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CFilesGather::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_SELECT, &CFilesGather::OnBnClickedButtonSelect)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CFilesGather::OnBnClickedButtonImport)
END_MESSAGE_MAP()


// CFilesGather 消息处理程序


void CFilesGather::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (CheckBox())
	{
		if (ReadFile())
		{
			//ProcessFileDatas();
			SaveFile();
			CDialogEx::OnOK();
		}
	}
}


void CFilesGather::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CFilesGather::OnBnClickedButtonSelect()
{
	// TODO: 在此添加控件通知处理程序代码	
	UpdateData(TRUE);
	// 呼出文件夹
	BROWSEINFO  bi = { 0 };
	ITEMIDLIST *pidl;
	TCHAR       szPath[MAX_PATH];


	bi.hwndOwner = m_hWnd;
	bi.pszDisplayName = szPath;
	bi.lpszTitle = TEXT("选择要处理的文件所在文件夹：");
	bi.ulFlags = BIF_RETURNONLYFSDIRS;


	if (pidl = SHBrowseForFolder(&bi))
	{
		SHGetPathFromIDList(pidl, szPath);
		//return ;
	}
	if (NULL == pidl)    // 如果没有选择文件路径，
	{
		return;
	}
	//m_StrSmaliPath = szPath;     // szPath即是文件夹的路径

	GetFileList(ConvertLPWSTRToLPSTR(szPath));

	UpdateData(FALSE);
}


void CFilesGather::OnBnClickedButtonImport()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_FilePaths.empty())
	{
		::MessageBox(this->m_hWnd, _T("请先选择文件夹！"), _T("提示"), MB_OK);
		return;
	}
	if (!m_ModelFilePath.IsEmpty())
	{
		CListCtrl *pList = (CListCtrl *)GetDlgItem(IDC_LIST_FILES);
		pList->DeleteItem(0);
	}


	CFileDialog findFileDlg(
		TRUE,  // TRUE是创建打开文件对话框，FALSE则创建的是保存文件对话框
		_T(".csv"),  // 默认的打开文件的类型
		NULL,  // 默认打开的文件名
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,  // 打开只读文件
		_T("文件(*.csv)|*.csv|")  // 所有可以打开的文件类型
	);

	if (IDOK == findFileDlg.DoModal())
	{
		m_ModelFilePath = findFileDlg.GetPathName();  // 取出文件路径

		m_ListShow.InsertItem(0, _T("0"));
		m_ListShow.SetItemText(0, 1, _T("模板文件"));
		m_ListShow.SetItemText(0, 2, _T("csv"));
		m_ListShow.SetItemText(0, 3, m_ModelFilePath);
	}

}


BOOL CFilesGather::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_ListShow.DeleteAllItems();
	m_ListShow.InsertColumn(0, _T("序号"), LVCFMT_CENTER, 50);
	m_ListShow.InsertColumn(1, _T("文件名"), LVCFMT_CENTER, 200);
	m_ListShow.InsertColumn(2, _T("文件类型"), LVCFMT_CENTER, 100);
	m_ListShow.InsertColumn(3, _T("存放路径"), LVCFMT_LEFT, 500);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

