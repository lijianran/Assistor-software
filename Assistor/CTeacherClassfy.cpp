// CTeacherClassfy.cpp: 实现文件
//

#include "stdafx.h"
#include "Assistor.h"
#include "CTeacherClassfy.h"
#include "afxdialogex.h"


// CTeacherClassfy 对话框

IMPLEMENT_DYNAMIC(CTeacherClassfy, CDialogEx)

CTeacherClassfy::CTeacherClassfy(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TEACHER, pParent)
{

}

CTeacherClassfy::~CTeacherClassfy()
{
}

bool CTeacherClassfy::ReadFile()
{
	vector<string> titlestrings = { "语文教师","数学教师","英语教师",
		"物理教师","化学教师","政治教师","历史教师","地理教师","生物教师" };
	ifstream infile;
	infile.open(m_InfoPath, ios::in);
	if (infile.is_open())
	{
		string line;
		//vector<int> titileIndexs;
		getline(infile, line);
		//找标题
		while (!ProcessTitles(titlestrings, line, titileIndexs))
		{
			if (!infile.eof())
				getline(infile, line);
			else
				break;
		}

		int coursenum = 0;
		if (titileIndexs.empty())//找不到标题
		{
			::MessageBox(this->m_hWnd, _T("标题格式错误！"), _T("提示"), MB_OK);
			return false;
		}
		else
		{
			for (unsigned int i = 0; i < titileIndexs.size(); i++)
			{
				if (titileIndexs[i] != -1)
				{
					coursenum++;
				}
			}
		}

		vector<teacher> *teachers = new vector<teacher>[coursenum];

		while (!infile.eof())
		{
			string field;
			vector<string> fields;
			getline(infile, line);
			istringstream data(line);
			while (getline(data, field, ','))
			{
				if (field.empty())
					continue;
				fields.push_back(field);
			}
			if (fields.empty())
				break;
			if (fields[0].empty())
				break;


			for (unsigned int i = 0, n = 0; i < titileIndexs.size(); i++)
			{
				teacher temp;
				if (titileIndexs[i] != -1)
				{
					temp.name = fields[titileIndexs[i]];
					int rank = stoi(fields[titileIndexs[i] + 1]);
					if (rank == 1)
						temp.rank = 2;
					if (rank == 2)
						temp.rank = 1;
					if (rank == 3)
						temp.rank = -1;
					if (rank == 4)
						temp.rank = -2;

					teachers[n++].push_back(temp);
				}
			}

		}
		for (int i = 0; i < coursenum; i++)
		{
			m_Datas.push_back(teachers[i]);
		}
		infile.close();
	}
	else
	{
		::MessageBox(this->m_hWnd, _T("教师信息表打开失败！"), _T("提示"), MB_OK);
		return false;
	}

	infile.open(m_MasterPath, ios::in);
	if (infile.is_open())
	{
		m_Masters = new vector<string>[m_Datas.size()];

		int n = 0;
		string line;
		while (!infile.eof())
		{
			string field;
			vector<string> fields;
			getline(infile, line);
			istringstream data(line);
			while (getline(data, field, ','))
			{
				if (field.empty())
					continue;
				fields.push_back(field);
			}
			if (fields.empty())
				break;

			for (unsigned int i = 1; i < fields.size(); i++)
			{
				m_Masters[n].push_back(fields[i]);
				m_MasterNames.push_back(fields[i]);
				m_Names.push_back(fields[i]);
			}
			n++;
		}
		infile.close();
	}
	else
	{
		::MessageBox(this->m_hWnd, _T("班主任表打开失败！"), _T("提示"), MB_OK);
		return false;
	}	
	return true;
}

void CTeacherClassfy::ProcessFileDatas()
{
	classnum = int(m_Datas[0].size());
	m_Class = new vector<teacher>[classnum];

	for (int i = 0; i < classnum; i++)//分班
	{
		int balance = 0;
		int num = -1;
		for (unsigned int j = 0; j < m_Datas.size(); j++)//找班主任
		{
			if (m_Masters[j].size() != 0)
			{
				num = j;
				break;
			}
		}

		string name;
		if (num != -1)
		{
			name = m_Masters[num][0];
			m_Masters[num].erase(m_Masters[num].begin());
			for (unsigned int j = 0; j < m_Names.size(); j++)
			{
				if (m_Names[j] == name)
					m_Names.erase(m_Names.begin() + j);
			}
		}

		for (unsigned int j = 0; j < m_Datas.size(); j++)
		{
			vector<teacher> teachers = m_Datas[j];

			if (j == num)//班主任
			{
				for (unsigned int k = 0; k < teachers.size(); k++)
				{
					if (teachers[k].name == name)
					{
						balance += teachers[k].rank;
						m_Class[i].push_back(teachers[k]);
						m_Datas[j].erase(m_Datas[j].begin() + k);
						break;
					}

				}
			}
			else//其他老师
			{
				bool flag = false;
				for (unsigned int k = 0; k < teachers.size(); k++)
				{
					vector<string>::iterator it;
					it = find(m_Names.begin(), m_Names.end(), teachers[k].name);
					if (it != m_Names.end())
					{
						//要做班主任
						for (unsigned int l = 0; l < teachers.size(); l++)
						{
							if (l != k && teachers[l].name == teachers[k].name)
							{
								int m = balance + teachers[k].rank;
								if ((m >= -2 && m <= 2) || balance == 0)
								{
									balance += teachers[k].rank;
									m_Class[i].push_back(teachers[k]);
									m_Datas[j].erase(m_Datas[j].begin() + k);
									flag = true;
									break;
								}

							}
						}
						if (flag)
							break;
					}
					else
					{
						//不是班主任
						int m = balance + teachers[k].rank;
						if ((m >= -2 && m <= 2) || balance == 0)
						{
							balance += teachers[k].rank;
							m_Class[i].push_back(teachers[k]);
							m_Datas[j].erase(m_Datas[j].begin() + k);
							flag = true;
							break;
						}

					}
				}
				if (!flag)
				{
					teacher tem;
					tem.name = "";
					tem.rank = 0;
					m_Class[i].push_back(tem);
				}

			}

		}

	}
}

void CTeacherClassfy::SaveFile()
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
		SavePath = findFileDlg.GetPathName();  // 取出文件路径

		ofstream outfile1;
		outfile1.open(SavePath, ios::out | ios::trunc);
		if (outfile1.is_open())
		{
			vector<string> titlestrings = { "语文教师","数学教师","英语教师",
			"物理教师","化学教师","政治教师","历史教师","地理教师","生物教师" };

			outfile1 << "序号,班主任,";
			for (int i = 0; i < 9; i++)
			{
				if (titileIndexs[i] != -1)
					outfile1 << titlestrings[i] << ",";
			}
			outfile1 << "水平" << endl;

			for (int i = 0; i < classnum; i++)
			{
				vector<teacher> temp = m_Class[i];
				int rank = 0;
				if(i==int(m_MasterNames.size()))
					outfile1 << i + 1 << "," << ",";
				else
					outfile1 << i + 1 << "," << m_MasterNames[i] << ",";
				for (unsigned int j = 0; j < temp.size(); j++)
				{
					rank += temp[j].rank;
					outfile1 << temp[j].name << ",";
				}
				outfile1 << rank << endl;
			}

			outfile1 << endl;
			for (unsigned int i = 1; i < m_Datas.size(); i++)
			{
				vector<teacher> temp = m_Datas[i];
				for (unsigned int j = 0; j < temp.size(); j++)
				{
					outfile1 << temp[j].name << ",";
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

bool CTeacherClassfy::CheckBox()
{
	if (m_InfoPath.IsEmpty())
	{
		::MessageBox(this->m_hWnd, _T("请导入教师信息表！"), _T("提示"), MB_OK);
		return false;
	}
	if (m_MasterPath.IsEmpty())
	{
		::MessageBox(this->m_hWnd, _T("请导入班主任表！"), _T("提示"), MB_OK);
		return false;
	}
	return true;
}

void CTeacherClassfy::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTeacherClassfy, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CTeacherClassfy::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDOK, &CTeacherClassfy::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTeacherClassfy::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_LOADMASTER, &CTeacherClassfy::OnBnClickedButtonLoadmaster)
END_MESSAGE_MAP()


// CTeacherClassfy 消息处理程序


void CTeacherClassfy::OnBnClickedButtonLoad()
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


void CTeacherClassfy::OnBnClickedButtonLoadmaster()
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
		m_MasterPath = findFileDlg.GetPathName();  // 取出文件路径
		SetDlgItemText(IDC_MASTER, m_MasterPath);
	}
}


void CTeacherClassfy::OnBnClickedOk()
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


void CTeacherClassfy::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

