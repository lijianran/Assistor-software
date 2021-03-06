// CStudentClassify.cpp: 实现文件
//

#include "stdafx.h"
#include "Assistor.h"
#include "CStudentClassify.h"
#include "afxdialogex.h"

bool sortool(studentdata a, studentdata b)
{
	return (a.score > b.score);
}
// CStudentClassify 对话框

IMPLEMENT_DYNAMIC(CStudentClassify, CDialogEx)

CStudentClassify::CStudentClassify(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CLASSIFY, pParent)
{

}

CStudentClassify::~CStudentClassify()
{
}

bool CStudentClassify::ReadFile()
{
	vector<string> titlestrings = { "学籍号","班级","姓名","总分","性别"};
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

		if (titileIndexs.empty())//找不到标题
		{
			::MessageBox(this->m_hWnd, _T("标题格式错误！"), _T("提示"), MB_OK);
			return false;
		}
		else
		{
			for (unsigned int i = 0; i < titileIndexs.size(); i++)
			{
				if (titileIndexs[i] == -1)
				{
					::MessageBox(this->m_hWnd, _T("标题缺少必要信息！"), _T("提示"), MB_OK);
					return false;
				}
			}
		}

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

			if (fields[titileIndexs[4]] == "男")
			{
				m_FileBoyDatas.ids.push_back(fields[titileIndexs[0]]);
				m_FileBoyDatas.classes.push_back(fields[titileIndexs[1]]);
				m_FileBoyDatas.names.push_back(fields[titileIndexs[2]]);
				m_FileBoyDatas.scores.push_back(fields[titileIndexs[3]]);
				m_FileBoyDatas.sexes.push_back(fields[titileIndexs[4]]);
			}
			else
			{
				m_FileGirlDatas.ids.push_back(fields[titileIndexs[0]]);
				m_FileGirlDatas.classes.push_back(fields[titileIndexs[1]]);
				m_FileGirlDatas.names.push_back(fields[titileIndexs[2]]);
				m_FileGirlDatas.scores.push_back(fields[titileIndexs[3]]);
				m_FileGirlDatas.sexes.push_back(fields[titileIndexs[4]]);
			}
		}
		infile.close();
	}
	else
	{
		::MessageBox(this->m_hWnd, _T("学生信息表打开失败！"), _T("提示"), MB_OK);
		return false;
	}
	return true;
}

void CStudentClassify::ProcessFileDatas()
{
	//分男女
	for (unsigned int i = 0; i < m_FileGirlDatas.ids.size(); i++)
	{
		studentdata girl;
		girl.id = m_FileGirlDatas.ids[i];
		girl.clas = m_FileGirlDatas.classes[i];
		girl.name = m_FileGirlDatas.names[i];
		if (m_FileGirlDatas.scores[i].size() == 0)
			girl.score = 0;
		else
			girl.score = stod(m_FileGirlDatas.scores[i]);

		girl.sex = m_FileGirlDatas.sexes[i];
		m_Girls.push_back(girl);
	}
	sort(m_Girls.begin(), m_Girls.end(), sortool);

	for (unsigned int i = 0; i < m_FileBoyDatas.ids.size(); i++)
	{
		studentdata boy;
		boy.id = m_FileBoyDatas.ids[i];
		boy.clas = m_FileBoyDatas.classes[i];
		boy.name = m_FileBoyDatas.names[i];
		if (m_FileBoyDatas.scores[i].size() == 0)
			boy.score = 0;
		else
			boy.score = stod(m_FileBoyDatas.scores[i]);
		boy.sex = m_FileBoyDatas.sexes[i];
		m_Boys.push_back(boy);
	}
	sort(m_Boys.begin(), m_Boys.end(), sortool);
	//分班级
	vector<vector<studentdata>> boygroups;
	vector<vector<studentdata>> girlgroups;
	vector<studentdata> restudents;
	int boygroupsnumb = m_Boys.size() / m_ClassNums;
	int girlgroupsnumb = m_Girls.size() / m_ClassNums;

	for (int j = 0; j < boygroupsnumb; j++)
	{
		vector<studentdata> group;
		if (j % 2 == 0)
		{
			for (int i = j * m_ClassNums; i < (j + 1)*m_ClassNums; i++)
			{
				group.push_back(m_Boys[i]);
			}
		}
		else
		{
			for (int i = (j + 1) * m_ClassNums - 1; i >= j * m_ClassNums; i--)
			{
				group.push_back(m_Boys[i]);
			}
		}
		boygroups.push_back(group);
	}

	for (int j = 0; j < girlgroupsnumb; j++)
	{
		vector<studentdata> group;
		if (j % 2 != 0)
		{
			for (int i = j * m_ClassNums; i < (j + 1)*m_ClassNums; i++)
			{
				group.push_back(m_Girls[i]);
			}
		}
		else
		{
			for (int i = (j + 1) * m_ClassNums - 1; i >= j * m_ClassNums; i--)
			{
				group.push_back(m_Girls[i]);
			}
		}
		girlgroups.push_back(group);
	}

	for (int j = 0; j < m_ClassNums; j++)
	{
		vector<studentdata> oneclass;
		for (unsigned int i = 0; i < boygroups.size(); i++)
		{
			oneclass.push_back(boygroups[i][j]);
		}
		for (unsigned int i = 0; i < girlgroups.size(); i++)
		{
			oneclass.push_back(girlgroups[i][j]);
		}
		m_Classes.push_back(oneclass);
	}
	int totalnumb = m_Boys.size() + m_Girls.size();
	int restboy = m_Boys.size() - boygroupsnumb * m_ClassNums;
	int restgirl = m_Girls.size() - girlgroupsnumb * m_ClassNums;

	for (int i = 0; i < restboy; i++)
		restudents.push_back(m_Boys[m_Boys.size() - i - 1]);
	for (int i = 0; i < restgirl; i++)
		restudents.push_back(m_Girls[m_Girls.size() - i - 1]);

	for (unsigned int i = 0, j = 0; i < restudents.size(); i++, j++)
	{
		m_Classes[j].push_back(restudents[i]);
		if (j == m_ClassNums - 1)
			j = -1;
	}
}

void CStudentClassify::SaveFile()
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
		int grade = stoi(m_Classes[0][0].clas) / 100 + 1;
		grade *= 100;
		if (outfile1.is_open())
		{
			outfile1 << "学籍号,原班级,姓名,总分,性别,新班级" << endl;
			for (int i = 0; i < m_ClassNums; i++)
			{
				vector<studentdata> oneclass=m_Classes[i];
				for (unsigned int j = 0; j < oneclass.size(); j++)
				{
					studentdata m = oneclass[j];
					outfile1 << m.id << ','
						<< m.clas << ','
						<< m.name << ','
						<< m.score << ','
						<< m.sex << ','
						<< i + 1 + grade << ','
						<< endl;
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

bool CStudentClassify::CheckBox()
{
	m_ClassNums = GetDlgItemInt(IDC_EDIT_NUMS);
	
	if (m_InfoPath.IsEmpty())
	{
		::MessageBox(this->m_hWnd, _T("请导入学生信息表！"), _T("提示"), MB_OK);
		return false;
	}

	if (m_ClassNums == 0)
	{
		::MessageBox(this->m_hWnd, _T("请输入分班数目！"), _T("提示"), MB_OK);
		return false;
	}
	else if (m_ClassNums > 99)
	{
		::MessageBox(this->m_hWnd, _T("分班数目超过两位数！"), _T("提示"), MB_OK);
		return false;
	}
	else
		return true;
}

void CStudentClassify::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStudentClassify, CDialogEx)
	ON_BN_CLICKED(IDOK, &CStudentClassify::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CStudentClassify::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_LOADINFOMATION, &CStudentClassify::OnBnClickedButtonLoadinfomation)
END_MESSAGE_MAP()


// CStudentClassify 消息处理程序


void CStudentClassify::OnBnClickedOk()
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


void CStudentClassify::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CStudentClassify::OnBnClickedButtonLoadinfomation()
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
