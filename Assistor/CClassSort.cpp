// CClassSort.cpp: 实现文件
//

#include "stdafx.h"
#include "Assistor.h"
#include "CClassSort.h"
#include "afxdialogex.h"

bool classort(studentinfo a, studentinfo b)
{
	return (a.clas < b.clas);
}
bool scoresort(studentinfo a, studentinfo b)
{
	return (a.score > b.score);
}

// CClassSort 对话框

IMPLEMENT_DYNAMIC(CClassSort, CDialogEx)

CClassSort::CClassSort(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SORT, pParent)
{
	m_TotalFlag = true;
}

CClassSort::~CClassSort()
{
	//delete m_ClassDatas;
	//delete m_Numbs;
	//delete m_Index;
}

bool CClassSort::ReadFile()
{
	vector<string> titlestrings = { "班级","总分" };
	ifstream infile;
	infile.open(m_InfoPath, ios::in);
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
		m_Titles = line;

		if (titileIndexs.empty())//找不到标题
		{
			::MessageBox(this->m_hWnd, _T("标题格式错误！"), _T("提示"), MB_OK);
			return false;
		}
		else
		{
			if (titileIndexs[0] == -1)
			{
				::MessageBox(this->m_hWnd, _T("缺少班级信息！"), _T("提示"), MB_OK);
				return false;
			}
			if (titileIndexs[1] == -1)
			{
				m_TotalFlag = false;
			}
		}

		while (!infile.eof())//读数据
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

			studentinfo student;
			for (unsigned int i = 0; i < fields.size(); i++)
			{
				if (i == titileIndexs[0])
					student.clas = stod(fields[i]);
				if (i == titileIndexs[1])
					student.score = stod(fields[i]);
				student.info.push_back(fields[i]);
			}
			m_FileDatas.push_back(student);
		}
		infile.close();
	}
	else
	{
		::MessageBox(this->m_hWnd, _T("分班信息表打开失败！"), _T("提示"), MB_OK);
		return false;
	}

	return true;
}

void CClassSort::ProcessFileDatas()
{
	sort(m_FileDatas.begin(), m_FileDatas.end(), classort);	//按班级排序
	m_BeginClass = int(m_FileDatas[0].clas - 1);//年级
	m_ClassNumbs = int(m_FileDatas.back().clas - m_BeginClass);//班级数

	m_ClassDatas = new vector<studentinfo>[m_ClassNumbs];
	m_Numbs = new int[m_ClassNumbs];
	for (int i = 0; i < m_ClassNumbs; i++)
		m_Numbs[i] = 0;

	for (unsigned int i = 0; i < m_FileDatas.size(); i++)
	{
		int k = int(m_FileDatas[i].clas - m_BeginClass - 1);
		m_Numbs[k]++;
		m_ClassDatas[k].push_back(m_FileDatas[i]);
	}


	//按总分排序
	if (m_TotalFlag)
	{
		m_Index = new vector<int>[m_ClassNumbs];

		for (int j = 0; j < m_ClassNumbs; j++)
		{
			sort(m_ClassDatas[j].begin(), m_ClassDatas[j].end(), scoresort);
			// 初始化索引向量
			vector<size_t> idex(m_Numbs[j]);
			//使用iota对向量赋0~？的连续值
			std::iota(idex.begin(), idex.end(), 0);

			for (int i = 0; i < m_Numbs[j]; i++)
			{
				if (i != 0 && m_ClassDatas[j][i].score == m_ClassDatas[j][i - 1].score)
					m_Index[j].push_back(m_Index[j][i - 1]);
				else
					m_Index[j].push_back(i + 1);
			}
		}
	}

}

void CClassSort::SaveFile()
{
	::MessageBox(this->m_hWnd, _T("计算完成，请选择文件夹进行保存！"), _T("提示"), MB_OK);

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
			if (m_TotalFlag)
			{
				outfile1 << "序号,班名," << m_Titles;
				for (int j = 0; j < m_ClassNumbs; j++)
				{
					for (int i = 0; i < m_Numbs[j]; i++)
					{
						outfile1 << endl << i + 1 << ',' << m_Index[j][i] << ',';
						for (unsigned int k = 0; k < m_ClassDatas[j][i].info.size(); k++)
							outfile1 << m_ClassDatas[j][i].info[k] << ',';
					}

				}
			}
			else
			{
				outfile1 << "序号," << m_Titles;
				for (int j = 0; j < m_ClassNumbs; j++)
				{
					for (int i = 0; i < m_Numbs[j]; i++)
					{
						outfile1 << endl << i + 1 << ',';
						for (unsigned int k = 0; k < m_ClassDatas[j][i].info.size(); k++)
							outfile1 << m_ClassDatas[j][i].info[k] << ',';
					}

				}
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

bool CClassSort::CheckBox()
{
	if (m_InfoPath.IsEmpty())
	{
		::MessageBox(this->m_hWnd, _T("请导入分班信息表！"), _T("提示"), MB_OK);
		return false;
	}
	return true;
}


void CClassSort::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CClassSort, CDialogEx)
	ON_BN_CLICKED(IDOK, &CClassSort::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CClassSort::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_LOADINFOS, &CClassSort::OnBnClickedButtonLoadinfos)
END_MESSAGE_MAP()


// CClassSort 消息处理程序


void CClassSort::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (CheckBox())
	{
		if (ReadFile())
		{
			ProcessFileDatas();
			SaveFile();
			CDialogEx::OnOK();
		}
	}
}


void CClassSort::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CClassSort::OnBnClickedButtonLoadinfos()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog findFileDlg(
		TRUE,  // TRUE是创建打开文件对话框，FALSE则创建的是保存文件对话框
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
		m_InfoPath = findFileDlg.GetPathName();  // 取出文件路径
		SetDlgItemText(IDC_INFOMATION, m_InfoPath);
	}
}
