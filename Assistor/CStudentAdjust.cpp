// CStudentAdjust.cpp: 实现文件
//

#include "stdafx.h"
#include "Assistor.h"
#include "CStudentAdjust.h"
#include "afxdialogex.h"


// CStudentAdjust 对话框

IMPLEMENT_DYNAMIC(CStudentAdjust, CDialogEx)

CStudentAdjust::CStudentAdjust(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADJUST, pParent)
{
	m_Score = 5;
}

CStudentAdjust::~CStudentAdjust()
{
}

bool CStudentAdjust::ReadFile()
{
	vector<string> titlestrings = { "姓名","总分","性别","新班级","目标班级" };
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
			for (unsigned int i = 0; i < titileIndexs.size(); i++)
			{
				if (titileIndexs[i] == -1)
				{
					::MessageBox(this->m_hWnd, _T("标题缺少必要信息！"), _T("提示"), MB_OK);
					return false;
				}
			}
		}

		vector<stu> oneclass;
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
			{
				m_FileDatas.push_back(oneclass);
				break;
			}

			stu student;
			for (unsigned int i = 0; i < fields.size(); i++)
			{
				if (i == titileIndexs[0])//姓名
					student.name = fields[i];
				if (i == titileIndexs[1])//总分
					student.score = stod(fields[i]);
				if (i == titileIndexs[2])//性别
					student.sex = fields[i];
				if (i == titileIndexs[3])//新班级
					student.clas = stod(fields[i]);
				if (i == titileIndexs[4])//目标班级
				{
					student.goal = fields[i];
					student.sign = "待调整";
				}

				student.info.push_back(fields[i]);
			}
			if (oneclass.empty())
			{
				oneclass.push_back(student);
				continue;
			}
			if (oneclass.back().clas == student.clas)
				oneclass.push_back(student);
			else
			{
				m_FileDatas.push_back(oneclass);
				oneclass.clear();
				oneclass.push_back(student);
			}
		}
		m_BeginClass = int(m_FileDatas[0][0].clas / 100);
		infile.close();
	}
	else
	{
		::MessageBox(this->m_hWnd, _T("分班信息表打开失败！"), _T("提示"), MB_OK);
		return false;
	}

	return true;
}

void CStudentAdjust::ProcessFileDatas()
{
	for (unsigned int i = 0; i < m_FileDatas.size(); i++)
	{
		int studentnumbs = int(m_FileDatas[i].size());
		for (int j = 0; j < studentnumbs; j++)
		{
			stu *studentone = &m_FileDatas[i][j];
			if (studentone->goal.empty())
				continue;

			int goal = stoi(studentone->goal) - m_BeginClass * 100 - 1;
			if (goal < 0 || goal > 100)
			{
				studentone->sign = "调整失败";
				continue;
			}
			if (goal == i)
			{
				studentone->sign = "成功";
				continue;
			}

			bool flag = false;
			//相同分优先
			for (unsigned int k = 0; k < m_FileDatas[goal].size(); k++)
			{
				stu *studenttwo = &m_FileDatas[goal][k];
				if (!studenttwo->goal.empty())
					continue;

				if (studenttwo->score == studentone->score)
				{
					sawpstudent(studentone, studenttwo);
					flag = true;
					break;
				}
			}
			if (flag)
				continue;
			else
				studentone->sign = "调整失败";
			//相隔5分,考虑性别
			for (unsigned int k = 0; k < m_FileDatas[goal].size(); k++)
			{
				stu *studenttwo = &m_FileDatas[goal][k];
				if (!studenttwo->goal.empty())
					continue;

				if (studenttwo->sex != studentone->sex)
					continue;

				if (studenttwo->score <= studentone->score + m_Score 
					&& studenttwo->score >= studentone->score - m_Score)
				{
					sawpstudent(studentone, studenttwo);
					flag = true;
					break;
				}
			}
			if (flag)
				continue;
			else
				studentone->sign = "调整失败";

			//不考虑性别
			for (unsigned int k = 0; k < m_FileDatas[goal].size(); k++)
			{
				stu *studenttwo = &m_FileDatas[goal][k];
				if (!studenttwo->goal.empty())
					continue;

				if (studenttwo->score <= studentone->score + m_Score 
					&& studenttwo->score >= studentone->score - m_Score)
				{
					sawpstudent(studentone, studenttwo);
					flag = true;
					break;
				}
			}
			if (flag)
				continue;
			else
				studentone->sign = "调整失败";

		}
	}
}

void CStudentAdjust::SaveFile()
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
			
			outfile1 << m_Titles << ",调整后班级,备注" << endl;
			for (unsigned int j = 0; j < m_FileDatas.size(); j++)
			{
				for (unsigned int i = 0; i < m_FileDatas[j].size(); i++)
				{
					for (unsigned int k = 0; k < m_FileDatas[j][i].info.size(); k++)
						outfile1 << m_FileDatas[j][i].info[k] << ',';
					if (m_FileDatas[j][i].goal.empty())
						outfile1 << ",";
					outfile1 << m_BeginClass * 100 + j + 1 << ",";
					outfile1 << m_FileDatas[j][i].sign << endl;
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

bool CStudentAdjust::CheckBox()
{
	m_Score = GetDlgItemInt(IDC_EDIT_NUMS);

	if (m_InfoPath.IsEmpty())
	{
		::MessageBox(this->m_hWnd, _T("请导入分班信息表！"), _T("提示"), MB_OK);
		return false;
	}

	if (m_Score > 9)
	{
		::MessageBox(this->m_hWnd, _T("区间超过20分！"), _T("提示"), MB_OK);
		return false;
	}
	if (m_Score < 1)
	{
		::MessageBox(this->m_hWnd, _T("区间不能为0！"), _T("提示"), MB_OK);
		return false;
	}

	return true;
}


void CStudentAdjust::sawpstudent(stu * stua, stu * stub)
{
	stua->sign = "换出";
	stub->sign = "成功";
	stu temp;
	temp.clas = stua->clas;
	temp.goal = stua->goal;
	temp.info.assign(stua->info.begin(), stua->info.end());
	temp.name = stua->name;
	temp.score = stua->score;
	temp.sex = stua->sex;

	stua->clas = stub->clas;
	stua->goal = stub->goal;
	stua->info.assign(stub->info.begin(), stub->info.end());
	stua->name = stub->name;
	stua->score = stub->score;
	stua->sex = stub->sex;

	stub->clas = temp.clas;
	stub->goal = temp.goal;
	stub->info.assign(temp.info.begin(), temp.info.end());
	stub->name = temp.name;
	stub->score = temp.score;
	stub->sex = temp.sex;
}


void CStudentAdjust::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStudentAdjust, CDialogEx)
	ON_BN_CLICKED(IDOK, &CStudentAdjust::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CStudentAdjust::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_LOADINFOS, &CStudentAdjust::OnBnClickedButtonLoadinfos)
END_MESSAGE_MAP()


// CStudentAdjust 消息处理程序


void CStudentAdjust::OnBnClickedOk()
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


void CStudentAdjust::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CStudentAdjust::OnBnClickedButtonLoadinfos()
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


BOOL CStudentAdjust::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CString score;
	score.Format(_T("%d"), m_Score);
	SetDlgItemText(IDC_EDIT_NUMS, score);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
