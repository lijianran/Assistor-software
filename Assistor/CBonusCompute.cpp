// CBonusCompute.cpp: 实现文件
//

#include "stdafx.h"
#include "Assistor.h"
#include "CBonusCompute.h"
#include "afxdialogex.h"


// CBonusCompute 对话框

IMPLEMENT_DYNAMIC(CBonusCompute, CDialogEx)

CBonusCompute::CBonusCompute(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BONUS, pParent)
{
	m_average = 7.0;
	m_first = 10.0;
	m_second = 5.0;
}

CBonusCompute::~CBonusCompute()
{
}

bool CBonusCompute::ReadFile()
{
	vector<string> titlestrings = { "班级",
	"语文教师","语文人平","语文一尖","语文二尖",
	"数学教师","数学人平","数学一尖","数学二尖",
	"英语教师","英语人平","英语一尖","英语二尖",
	"物理教师","物理人平","物理一尖","物理二尖",
	"化学教师","化学人平","化学一尖","化学二尖",
	"政治教师","政治人平","政治一尖","政治二尖",
	"历史教师","历史人平","历史一尖","历史二尖",
	"地理教师","地理人平","地理一尖","地理二尖",
	"生物教师","生物人平","生物一尖","生物二尖",};
	vector<string> titlestrings2 = { "语文",
		"数学","英语","物理","化学",
		"政治","历史","地理","生物"};


	ifstream infile, infile2;
	string line;
	infile.open(m_InfoPath, ios::in);
	infile2.open(m_NumbsPath, ios::in);

	if (infile.is_open() && infile2.is_open())
	{
		string line;
		vector<int> titileIndexs;
		getline(infile, line);
		while (!ProcessTitles(titlestrings, line, titileIndexs))
		{
			if (!infile.eof())
				getline(infile, line);
			else
				break;
		}

		if (titileIndexs.empty())//找不到标题
			::MessageBox(this->m_hWnd, _T("一分两率尖子表标题格式错误！"), _T("提示"), MB_OK);
		else
		{
			vector<int> titileIndexs1;
			getline(infile2, line);
			while (!ProcessTitles(titlestrings2, line, titileIndexs1))
			{
				if (!infile2.eof())
					getline(infile2, line);
				else
					break;
			}
			if (titileIndexs1.empty())//找不到标题
				::MessageBox(this->m_hWnd, _T("任课系数表标题格式错误！"), _T("提示"), MB_OK);
			else
			{/////////////////读数据////////////////////////
				while ((!infile.eof()) || (!infile2.eof()))
				{
					type m;
					int k = 0, l = 0;

					string field;
					vector<string> fields;
					getline(infile, line);
					istringstream data(line);
					while (getline(data, field, ','))
					{
						fields.push_back(field);
					}
					string field2;
					vector<string> fields2;
					getline(infile2, line);
					istringstream data2(line);
					while (getline(data2, field2, ','))
					{
						fields2.push_back(field2);
					}

					if (fields[0] == "全校人平")
					{
						for (int j = 2; j < 37; j += 4)
							Data.total_average.push_back(fields[titileIndexs[j]]);
						break;
					}

					m.clas = fields[titileIndexs[k++]];//班级

					m.name = fields[titileIndexs[k++]];
					m.average = fields[titileIndexs[k++] + 2];
					m.first = fields[titileIndexs[k++]];
					m.second = fields[titileIndexs[k++]];
					if (titileIndexs1[l] != -1)
						m.ratio = fields2[titileIndexs1[l++] + 1];
					Data.chinese.push_back(m);//语文

					m.name = fields[titileIndexs[k++]];
					m.average = fields[titileIndexs[k++] + 2];
					m.first = fields[titileIndexs[k++]];
					m.second = fields[titileIndexs[k++]];
					if (titileIndexs1[l] != -1)
						m.ratio = fields2[titileIndexs1[l++] + 1];
					Data.math.push_back(m);//数学


					m.name = fields[titileIndexs[k++]];
					m.average = fields[titileIndexs[k++] + 2];
					m.first = fields[titileIndexs[k++]];
					m.second = fields[titileIndexs[k++]];
					if (titileIndexs1[l] != -1)
						m.ratio = fields2[titileIndexs1[l++] + 1];
					Data.english.push_back(m);//英语

					m.name = fields[titileIndexs[k++]];
					m.average = fields[titileIndexs[k++] + 2];
					m.first = fields[titileIndexs[k++]];
					m.second = fields[titileIndexs[k++]];
					if (titileIndexs1[l] != -1)
						m.ratio = fields2[titileIndexs1[l++] + 1];
					Data.physics.push_back(m);//物理

					m.name = fields[titileIndexs[k++]];
					m.average = fields[titileIndexs[k++]];
					m.first = fields[titileIndexs[k++]];
					m.second = fields[titileIndexs[k++]];
					if (titileIndexs1[l] != -1)
						m.ratio = fields2[titileIndexs1[l++] + 1];
					Data.chemistry.push_back(m);//化学

					m.name = fields[titileIndexs[k++]];
					m.average = fields[titileIndexs[k++]];
					m.first = fields[titileIndexs[k++]];
					m.second = fields[titileIndexs[k++]];
					if (titileIndexs1[l] != -1)
						m.ratio = fields2[titileIndexs1[l++] + 1];
					Data.political.push_back(m);//政治

					m.name = fields[titileIndexs[k++]];
					m.average = fields[titileIndexs[k++]];
					m.first = fields[titileIndexs[k++]];
					m.second = fields[titileIndexs[k++]];
					if (titileIndexs1[l] != -1)
						m.ratio = fields2[titileIndexs1[l++] + 1];
					Data.history.push_back(m);//历史

					m.name = fields[titileIndexs[k++]];
					m.average = fields[titileIndexs[k++]];
					m.first = fields[titileIndexs[k++]];
					m.second = fields[titileIndexs[k++]];
					if (titileIndexs1[l] != -1)
						m.ratio = fields2[titileIndexs1[l++] + 1];
					Data.geography.push_back(m);//地理

					m.name = fields[titileIndexs[k++]];
					m.average = fields[titileIndexs[k++]];
					m.first = fields[titileIndexs[k++]];
					m.second = fields[titileIndexs[k++]];
					if (titileIndexs1[l] != -1)
						m.ratio = fields2[titileIndexs1[l++] + 1];
					Data.organism.push_back(m);//生物

				}
			}
		}
		infile.close();
		infile2.close();
	}
	else
	{
		::MessageBox(this->m_hWnd, _T("文件打开失败！"), _T("提示"), MB_OK);
		return false;
	}
	return true;
}

void CBonusCompute::ProcessFileDatas()
{
	for (unsigned int i = 0; i < Data.chinese.size(); i++)
	{
		type m = Data.chinese[i];
		outresult out;
		if (m.name.empty())
			break;
		out.averagemoney = 100 + m_average * (stod(m.average) - stod(Data.total_average[0]));
		out.firstmoeny = 60 + m_first * (stod(m.first) - 10);
		out.secondmoney = 40 + m_second * (stod(m.second) - 20);
		out.totalmoney = (out.averagemoney + out.firstmoeny + out.secondmoney)*stod(m.ratio);
		out.clas = m.clas;
		out.name = m.name;
		out.course = "语文";
		results.push_back(out);
	}
	for (unsigned int i = 0; i < Data.math.size(); i++)
	{
		type m = Data.math[i];
		outresult out;
		if (m.name.empty())
			break;
		out.averagemoney = 100 + m_average * (stod(m.average) - stod(Data.total_average[1]));
		out.firstmoeny = 60 + m_first * (stod(m.first) - 10);
		out.secondmoney = 40 + m_second * (stod(m.second) - 20);
		out.totalmoney = (out.averagemoney + out.firstmoeny + out.secondmoney)*stod(m.ratio);
		out.clas = m.clas;
		out.name = m.name;
		out.course = "数学";
		results.push_back(out);
	}
	for (unsigned int i = 0; i < Data.english.size(); i++)
	{
		type m = Data.english[i];
		outresult out;
		if (m.name.empty())
			break;
		out.averagemoney = 100 + m_average * (stod(m.average) - stod(Data.total_average[2]));
		out.firstmoeny = 60 + m_first * (stod(m.first) - 10);
		out.secondmoney = 40 + m_second * (stod(m.second) - 20);
		out.totalmoney = (out.averagemoney + out.firstmoeny + out.secondmoney)*stod(m.ratio);
		out.clas = m.clas;
		out.name = m.name;
		out.course = "英语";
		results.push_back(out);
	}
	for (unsigned int i = 0; i < Data.physics.size(); i++)
	{
		type m = Data.physics[i];
		outresult out;
		if (m.name.empty())
			break;
		out.averagemoney = 100 + m_average * (stod(m.average) - stod(Data.total_average[3]));
		out.firstmoeny = 60 + m_first * (stod(m.first) - 10);
		out.secondmoney = 40 + m_second * (stod(m.second) - 20);
		out.totalmoney = (out.averagemoney + out.firstmoeny + out.secondmoney)*stod(m.ratio);
		out.clas = m.clas;
		out.name = m.name;
		out.course = "物理";
		results.push_back(out);
	}
	for (unsigned int i = 0; i < Data.chemistry.size(); i++)
	{
		type m = Data.chemistry[i];
		outresult out;
		if (m.name.empty())
			break;
		out.averagemoney = 100 + m_average * (stod(m.average) - stod(Data.total_average[4]));
		out.firstmoeny = 60 + m_first * (stod(m.first) - 10);
		out.secondmoney = 40 + m_second * (stod(m.second) - 20);
		out.totalmoney = (out.averagemoney + out.firstmoeny + out.secondmoney)*stod(m.ratio);
		out.clas = m.clas;
		out.name = m.name;
		out.course = "化学";
		results.push_back(out);
	}
	for (unsigned int i = 0; i < Data.political.size(); i++)
	{
		type m = Data.political[i];
		outresult out;
		if (m.name.empty())
			break;
		out.averagemoney = 100 + m_average * (stod(m.average) - stod(Data.total_average[5]));
		out.firstmoeny = 60 + m_first * (stod(m.first) - 10);
		out.secondmoney = 40 + m_second * (stod(m.second) - 20);
		out.totalmoney = (out.averagemoney + out.firstmoeny + out.secondmoney)*stod(m.ratio);
		out.clas = m.clas;
		out.name = m.name;
		out.course = "政治";
		results.push_back(out);
	}
	for (unsigned int i = 0; i < Data.history.size(); i++)
	{
		type m = Data.history[i];
		outresult out;
		if (m.name.empty())
			break;
		out.averagemoney = 100 + m_average * (stod(m.average) - stod(Data.total_average[6]));
		out.firstmoeny = 60 + m_first * (stod(m.first) - 10);
		out.secondmoney = 40 + m_second * (stod(m.second) - 20);
		out.totalmoney = (out.averagemoney + out.firstmoeny + out.secondmoney)*stod(m.ratio);
		out.clas = m.clas;
		out.name = m.name;
		out.course = "历史";
		results.push_back(out);
	}
	for (unsigned int i = 0; i < Data.geography.size(); i++)
	{
		type m = Data.geography[i];
		outresult out;
		if (m.name.empty())
			break;
		out.averagemoney = 100 + m_average * (stod(m.average) - stod(Data.total_average[7]));
		out.firstmoeny = 60 + m_first * (stod(m.first) - 10);
		out.secondmoney = 40 + m_second * (stod(m.second) - 20);
		out.totalmoney = (out.averagemoney + out.firstmoeny + out.secondmoney)*stod(m.ratio);
		out.clas = m.clas;
		out.name = m.name;
		out.course = "地理";
		results.push_back(out);
	}
	for (unsigned int i = 0; i < Data.organism.size(); i++)
	{
		type m = Data.organism[i];
		outresult out;
		if (m.name.empty())
			break;
		out.averagemoney = 100 + m_average * (stod(m.average) - stod(Data.total_average[8]));
		out.firstmoeny = 60 + m_first * (stod(m.first) - 10);
		out.secondmoney = 40 + m_second * (stod(m.second) - 20);
		out.totalmoney = (out.averagemoney + out.firstmoeny + out.secondmoney)*stod(m.ratio);
		out.clas = m.clas;
		out.name = m.name;
		out.course = "生物";
		results.push_back(out);
	}
}

void CBonusCompute::SaveFile()
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
			outfile1 << "班级,科目,姓名,金额" << endl;
			for (unsigned int i = 0; i < results.size(); i++)
			{
				outresult m = results[i];
				outfile1 << m.clas << ','
					<< m.course << ','
					<< m.name << ','
					<< m.totalmoney << ','
					<< endl;
			}
		}
		else
		{
			::MessageBox(this->m_hWnd, _T("保存失败，点击确定回到主菜单！"), _T("提示"), MB_OK);
			return;
		}

		vector<goal> result2;
		for (unsigned int i = 0; i < results.size(); i++)
		{
			int key = 0;
			outresult m = results[i];
			for (unsigned int j = 0; j < result2.size(); j++)
			{
				goal n = result2[j];
				if (m.name == n.name)
				{
					if (n.money < 0)
						result2[j].money = 0;
					result2[j].money += m.totalmoney;
					key++;
				}

			}
			if (key == 0)
			{
				goal k;
				k.name = m.name;
				k.money = m.totalmoney;
				result2.push_back(k);
			}

		}
		outfile1 << endl << "姓名,金额" << endl;
		for (unsigned int i = 0; i < result2.size(); i++)
		{

			goal m = result2[i];
			outfile1 << m.name << ','
				<< m.money << ','
				<< endl;
		}
		outfile1.close();
		::MessageBox(this->m_hWnd, _T("保存完毕，点击确定回到主菜单！"), _T("提示"), MB_OK);
	}
	else
		::MessageBox(this->m_hWnd, _T("取消保存！"), _T("提示"), MB_OK);
}

bool CBonusCompute::CheckBox()
{
	if (m_InfoPath.IsEmpty())
	{
		::MessageBox(this->m_hWnd, _T("请导入一分两率尖子表！"), _T("提示"), MB_OK);
		return false;
	}
	if (m_NumbsPath.IsEmpty())
	{
		::MessageBox(this->m_hWnd, _T("请导入任课系数表！"), _T("提示"), MB_OK);
		return false;
	}
	CString par[3];
	GetDlgItemText(IDC_EDIT_AVERAGEPAR, par[0]);
	GetDlgItemText(IDC_EDIT_FIRSTPAR, par[1]);
	GetDlgItemText(IDC_EDIT_SECONDPAR, par[2]);
	if (par[0].IsEmpty())
	{
		::MessageBox(this->m_hWnd, _T("请输入人平分系数！"), _T("提示"), MB_OK);
		return false;
	}
	if (par[1].IsEmpty())
	{
		::MessageBox(this->m_hWnd, _T("请输入一尖系数！"), _T("提示"), MB_OK);
		return false;
	}
	if (par[2].IsEmpty())
	{
		::MessageBox(this->m_hWnd, _T("请输入二尖系数！"), _T("提示"), MB_OK);
		return false;
	}
	m_average = _ttof(par[0]);
	m_first = _ttof(par[1]);
	m_second = _ttof(par[2]);

	return true;
}


void CBonusCompute::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBonusCompute, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOADINFOS, &CBonusCompute::OnBnClickedButtonLoadinfos)
	ON_BN_CLICKED(IDC_BUTTON_LOADNUMBER, &CBonusCompute::OnBnClickedButtonLoadnumber)
	ON_BN_CLICKED(IDOK, &CBonusCompute::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CBonusCompute::OnBnClickedCancel)
END_MESSAGE_MAP()


// CBonusCompute 消息处理程序


void CBonusCompute::OnBnClickedButtonLoadinfos()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog findFileDlg(
		TRUE,  // TRUE是创建打开文件对话框，FALSE则创建的是保存文件对话框
		_T(".csv"),  // 默认的打开文件的类型
		NULL,  // 默认打开的文件名
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,  // 打开只读文件
		_T("文件(*.csv)|*.csv|")  // 所有可以打开的文件类型
	);

	//findFileDlg.GetOFN().lpstrInitialDir = strFile/*.c_str()*/;// 默认目录
	
	if (IDOK == findFileDlg.DoModal())
	{
		//char tempBuff[1024];
		//int index = 0, startPos = 0, playTime, iSum, findFlag = 0, iChn = 0;
		m_InfoPath = findFileDlg.GetPathName();  // 取出文件路径
		SetDlgItemText(IDC_SCOREPATH, m_InfoPath);
	}


}


void CBonusCompute::OnBnClickedButtonLoadnumber()
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
		m_NumbsPath = findFileDlg.GetPathName();  // 取出文件路径
		SetDlgItemText(IDC_NUMBERPATH, m_NumbsPath);
	}

}


void CBonusCompute::OnBnClickedOk()
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


void CBonusCompute::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL CBonusCompute::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CString par[3];
	par[0].Format(_T("%f"), m_average);
	par[1].Format(_T("%f"), m_first);
	par[2].Format(_T("%f"), m_second);
	SetDlgItemText(IDC_EDIT_AVERAGEPAR, par[0]);
	SetDlgItemText(IDC_EDIT_FIRSTPAR, par[1]);
	SetDlgItemText(IDC_EDIT_SECONDPAR, par[2]);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
