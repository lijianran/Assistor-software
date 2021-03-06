// CScoreCompute.cpp: 实现文件
//

#include "stdafx.h"
#include "Assistor.h"
#include "CScoreCompute.h"
#include "afxdialogex.h"


// CScoreCompute 对话框

IMPLEMENT_DYNAMIC(CScoreCompute, CDialogEx)

CScoreCompute::CScoreCompute(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SCORE, pParent)
{
	m_PassScore[0] = 78;
	m_PassScore[1] = 72;
	m_PassScore[2] = 72;
	m_PassScore[3] = 48;
	m_PassScore[4] = 30;
	m_PassScore[5] = 30;
	m_PassScore[6] = 30;
	m_PassScore[7] = 30;
	m_PassScore[8] = 30;
	m_PassScore[9] = 0;
	m_Nums[0] = 280;
	m_Nums[1] = 840;
	m_Total = 0;
	m_flag = true;
	m_flag_teacher = true;
}

CScoreCompute::~CScoreCompute()
{
}

bool doublesort(double a, double b)
{
	return (a > b);
}
bool totalsort(vector<double> a, vector<double> b)
{
	int m = int(a.size()) - 1;
	int n = int(b.size()) - 1;
	return (a[m] > b[n]);
}


bool CScoreCompute::ReadFile()
{
	vector<string> titlestrings = {"班级",
		"语文","数学","英语","物理","化学",
		"政治","历史","地理","生物","总分"
	};
	vector<string> titlestrings2 = { "班级","人数" };
	vector<string> titlestrings3 = { "班级",
		"语文","数学","英语","物理","化学",
		"政治","历史","地理","生物"
	};
	vector<string> titlestrings4 = { "语文分差",
		"数学分差","英语分差","物理分差" };

	//读成绩表
	ifstream infile1;
	infile1.open(m_ScorePath, ios::in);
	if (infile1.is_open())
	{
		string line;
		vector<int> titileIndexs;
		getline(infile1, line);
		//找标题
		while (!ProcessTitles(titlestrings, line, titileIndexs))
		{
			if (!infile1.eof())
				getline(infile1, line);
			else
				break;
		}

		if(titileIndexs.empty())//找不到标题
			::MessageBox(this->m_hWnd, _T("成绩表标题格式错误！"), _T("提示"), MB_OK);
		else//找到标题
		{
			//算总分
			for (int i = 1; i <= 9; i++)
			{
				if (titileIndexs[i] != -1)
				{
					m_PassScore[9] += m_PassScore[i - 1];
				}
			}

			//读数据
			while (!infile1.eof())
			{
				string field;
				vector<string> fields;
				getline(infile1, line);
				istringstream data(line);
				while (getline(data, field, ','))
				{
					fields.push_back(field);
				}
				if (fields.empty())
					continue;
				for (unsigned int i = 0; i < titlestrings.size(); i++)
				{
					if (titileIndexs[i] != -1)
					{
						m_FileDatas[i].push_back(stod(fields[titileIndexs[i]]));
					}
				}
				m_Total++;
			}
		}
		infile1.close();
	}
	else
	{
		::MessageBox(this->m_hWnd, _T("成绩表打开失败！"), _T("提示"), MB_OK);
		return false;
	}
	
	//读有效人数
	ifstream infile2;
	infile2.open(m_NumbsPath, ios::in);
	if (infile2.is_open())
	{
		string line;
		vector<int> titileIndexs;
		getline(infile2, line);
		//找标题
		while (!ProcessTitles(titlestrings2, line, titileIndexs))
		{
			if (!infile2.eof())
				getline(infile2, line);
			else
				break;
		}
		if (titileIndexs.empty())//找不到标题
			::MessageBox(this->m_hWnd, _T("人数表标题格式错误！"), _T("提示"), MB_OK);
		else
		{
			//读入数据
			while (!infile2.eof())
			{
				string field;
				vector<string> fields;
				getline(infile2, line);
				istringstream data(line);
				while (getline(data, field, ','))
				{
					fields.push_back(field);
				}

				if (fields.empty())
					continue;
				m_BeginClass = stod(fields[titileIndexs[0]]);
				m_EffectiveNums.push_back(stoi(fields[titileIndexs[1]]));
			}
			m_ClassNums = m_EffectiveNums.size();
			m_BeginClass = m_BeginClass - m_ClassNums + 1;
		}
		infile2.close();
	}
	else
	{
		::MessageBox(this->m_hWnd, _T("人数表打开失败！"), _T("提示"), MB_OK);
		return false;
	}

	//读教师信息
	if (!m_TeachPath.IsEmpty())
	{
		ifstream infile3;
		infile3.open(m_TeachPath, ios::in);
		if (infile3.is_open())
		{
			string line;
			vector<int> titileIndexs;
			getline(infile3, line);
			//找标题
			while (!ProcessTitles(titlestrings3, line, titileIndexs))
			{
				if (!infile3.eof())
					getline(infile3, line);
				else
					break;
			}

			if (titileIndexs.empty())
				::MessageBox(this->m_hWnd, _T("教师信息文件标题格式错误！"), _T("提示"), MB_OK);
			else
			{
				//教师名字
				while (!infile3.eof())
				{
					string field;
					vector<string> fields;
					getline(infile3, line);
					istringstream data(line);
					while (getline(data, field, ','))
					{
						fields.push_back(field);
					}
					if (fields.empty())
						continue;
					for (unsigned int i = 0; i < titlestrings3.size(); i++)
					{
						if (titileIndexs[i] != -1)
						{
							m_TeacherNames[i].push_back(fields[titileIndexs[i]]);
						}
					}
				}
			}
			infile3.close();
		}
		else
		{
			::MessageBox(this->m_hWnd, _T("教师信息表打开失败！"), _T("提示"), MB_OK);
			return false;
		}
	}
	else
		m_flag_teacher = false;

	//读分差表
	ifstream infile4;
	infile4.open(m_InfoPath, ios::in);
	if (infile4.is_open())
	{
		string line;
		vector<int> titileIndexs;
		getline(infile4, line);
		//找标题
		while (!ProcessTitles(titlestrings4, line, titileIndexs))
		{
			if (!infile4.eof())
				getline(infile4, line);
			else
				break;
		}

		if (titileIndexs.empty())
			::MessageBox(this->m_hWnd, _T("分差信息文件标题格式错误！"), _T("提示"), MB_OK);
		else
		{
			//分差信息
			while (!infile4.eof())
			{
				string field;
				vector<string> fields;
				getline(infile4, line);
				istringstream data(line);
				while (getline(data, field, ','))
				{
					fields.push_back(field);
				}
				if (fields.empty())
					continue;
				for (unsigned int i = 0; i < titlestrings4.size(); i++)
				{
					if (titileIndexs[i] != -1)
					{
						m_Fencha[i].push_back(stod(fields[titileIndexs[i]]));
					}
					else
					{
						m_Fencha[i].push_back(0);
					}
				}
			}
		}
		infile4.close();
	}
	else
		m_flag = false;

	return true;
}

void CScoreCompute::ProcessFileDatas()
{
	//按班级存数据
	m_ClassDatas = new vector<vector<double>>[m_ClassNums];

	for (unsigned int i = 0; i < m_FileDatas[0].size(); i++)
	{
		vector<double> temp;
		for (int j = 0; j < 11; j++)
		{
			if (m_FileDatas[j].size() == 0)
				temp.push_back(0);
			else
				temp.push_back(m_FileDatas[j][i]);
		}
		int k = int(m_FileDatas[0][i] - m_BeginClass);
		m_ClassDatas[k].push_back(temp);
	}

	//计算分数线
	vector<double> ExcellentResult;
	vector<double> Excellent2Result;

	double total_one;
	double total_two;


	vector<double> datas;
	for (unsigned int i = 0; i < m_FileDatas[0].size(); i++)
	{
		datas.push_back(m_FileDatas[10][i]);
	}
	sort(datas.begin(), datas.end(), doublesort);
	total_one = datas[m_Nums[0] * 2 - 1];
	total_two = datas[m_Nums[1] * 2 - 1];

	vector<double> ExcellentStudent[11];
	vector<double> Excellent2Student[11];

	for (unsigned int i = 0; i < m_FileDatas[0].size(); i++)
	{

		if (m_FileDatas[10][i] >= total_one)
		{
			for (int j = 0; j < 11; j++)
			{
				if (m_FileDatas[j].size() == 0)
					continue;
				ExcellentStudent[j].push_back(m_FileDatas[j][i]);
				Excellent2Student[j].push_back(m_FileDatas[j][i]);
			}
		}
		else if (m_FileDatas[10][i] >= total_two)
		{
			for (int j = 0; j < 11; j++)
			{
				if (m_FileDatas[j].size() == 0)
					continue;
				Excellent2Student[j].push_back(m_FileDatas[j][i]);
			}
		}
	}

	for (int i = 1; i < 11; i++)
	{
		if (m_FileDatas[i].size() == 0)
		{
			ExcellentResult.push_back(1);
		}
		else
		{
			datas = ExcellentStudent[i];
			sort(datas.begin(), datas.end(), doublesort);
			ExcellentResult.push_back(datas[m_Nums[0] - 1]);
		}
	}
	for (int i = 1; i < 11; i++)
	{
		if (m_FileDatas[i].size() == 0)
		{
			Excellent2Result.push_back(1);
		}
		else
		{
			datas = Excellent2Student[i];
			sort(datas.begin(), datas.end(), doublesort);
			Excellent2Result.push_back(datas[m_Nums[1] - 1]);
		}
	}

	//计算数据
	double totalscore[10] = { 0 };
	for (int i = 0; i < m_ClassNums; i++)
	{
		outype out = { { 0 },{ 0 },{ 0 },{ 0 } };

		vector<vector<double>> oneclass = m_ClassDatas[i];
		//算人头
		for (unsigned int j = 0; j < oneclass.size(); j++)
		{
			vector<double> onestudent = oneclass[j];
			for (unsigned int k = 1; k < onestudent.size(); k++)
			{
				if (onestudent[k] >= m_PassScore[k-1])
					out.PassNums[k-1]++;
				if (onestudent[10] >= total_one && onestudent[k] >= ExcellentResult[k - 1])
					out.ExcellentNums[k-1]++;
				if (onestudent[10] >= total_two && onestudent[k] >= Excellent2Result[k - 1])
					out.Excellent2Nums[k-1]++;
			}
		}
		for (int j = 0; j < 10; j++)
			out.Excellent2Nums[j] -= out.ExcellentNums[j];
		//算平均分
		sort(oneclass.begin(), oneclass.end(), totalsort);
		if (oneclass.size() >= unsigned int(m_EffectiveNums[i]))
		{
			for (int j = 0; j < m_EffectiveNums[i]; j++)
			{
				vector<double> onestudent = oneclass[j];
				for (unsigned int k = 1; k < onestudent.size(); k++)
				{
					out.AverageResult[k - 1] += onestudent[k];
				}
			}
		}
		else
		{
			for (unsigned int j = 0; j < oneclass.size(); j++)
			{
				vector<double> onestudent = oneclass[j];
				for (unsigned int k = 1; k < onestudent.size(); k++)
				{
					out.AverageResult[k - 1] += onestudent[k];
				}
			}
		}
		double average = 0;
		for (int j = 0; j < 10; j++)
		{
			out.AverageResult[j] /= m_EffectiveNums[i];
			out.AverageResult[j] = round(out.AverageResult[j]);
			//各科全校总分
			totalscore[j] += out.AverageResult[j];
		}

		//分差信息
		if (m_flag)
		{
			for (int j = 0; j < 4; j++)
			{
				out.AverageResult[j] -= m_Fencha[j][i];
			}
		}

		m_OutDatas.push_back(out);
	}

	//各科全校人平
	for (int k = 0; k < 10; k++)
	{
		m_TotalScore.push_back(round(round(totalscore[k]) / m_ClassNums));
	}

	//计算排名
	vector<double> ch[40];//辅助排名
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < m_ClassNums; j++)
		{
			ch[i * 4].push_back(m_OutDatas[j].AverageResult[i]);
			ch[i * 4 + 1].push_back(m_OutDatas[j].PassNums[i]);
			ch[i * 4 + 2].push_back(m_OutDatas[j].ExcellentNums[i]);
			ch[i * 4 + 3].push_back(m_OutDatas[j].Excellent2Nums[i]);
		}
	}

	for (int i = 0; i < 40; i++)
		m_Index[i] = new int[m_ClassNums];

	for (int j = 0; j < 40; j++)
	{
		// 初始化索引向量
		vector<size_t> idex(m_ClassNums);
		//使用iota对向量赋0~？的连续值
		std::iota(idex.begin(), idex.end(), 0);

		vector<double> inx = ch[j];
		// 通过比较v的值对索引idx进行排序
		sort(idex.begin(), idex.end(),
			[&inx](size_t i1, size_t i2) {return inx[i1] > inx[i2]; });
		for (int i = 0; i < m_ClassNums; i++)
		{
			if (i != 0 && inx[idex[i]] == inx[idex[i - 1]])
			{
				m_Index[j][idex[i]] = m_Index[j][idex[i - 1]];
			}
			else
				m_Index[j][idex[i]] = i + 1;
		}
	}

	//综合排名计算

	vector<int> zonghe[10];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < m_ClassNums; j++)
		{
			int m = m_Index[i * 4][j] + m_Index[i * 4 + 1][j] + m_Index[i * 4 + 2][j];
			zonghe[i].push_back(m);
		}
	}

	for (int i = 0; i < 10; i++)
		zongheIndex[i] = new int[m_ClassNums];

	for (int j = 0; j < 10; j++)
	{
		// 初始化索引向量
		vector<size_t> idex(m_ClassNums);
		//使用iota对向量赋0~？的连续值
		std::iota(idex.begin(), idex.end(), 0);

		vector<int> inx = zonghe[j];
		// 通过比较v的值对索引idx进行排序
		sort(idex.begin(), idex.end(),
			[&inx](size_t i1, size_t i2) {return inx[i1] < inx[i2]; });
		for (int i = 0; i < m_ClassNums; i++)
		{
			if (i != 0 && inx[idex[i]] == inx[idex[i - 1]])
			{
				zongheIndex[j][idex[i]] = zongheIndex[j][idex[i - 1]];
			}
			else
				zongheIndex[j][idex[i]] = i + 1;
		}
	}

}

void CScoreCompute::SaveFile()
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
			if (!m_flag)//无分差表导入
			{
				if (!m_flag_teacher)
				{
					outfile1 << "班级,"
						<< "语文人平,排名,语文及格,排名,语文一尖,排名,综合排名,语文二尖,排名,"
						<< "数学人平,排名,数学及格,排名,数学一尖,排名,综合排名,数学二尖,排名,"
						<< "英语人平,排名,英语及格,排名,英语一尖,排名,综合排名,英语二尖,排名,"
						<< "物理人平,排名,物理及格,排名,物理一尖,排名,综合排名,物理二尖,排名,"
						<< "化学人平,排名,化学及格,排名,化学一尖,排名,综合排名,化学二尖,排名,"
						<< "政治人平,排名,政治及格,排名,政治一尖,排名,综合排名,政治二尖,排名,"
						<< "历史人平,排名,历史及格,排名,历史一尖,排名,综合排名,历史二尖,排名,"
						<< "地理人平,排名,地理及格,排名,地理一尖,排名,综合排名,地理二尖,排名,"
						<< "生物人平,排名,生物及格,排名,生物一尖,排名,综合排名,生物二尖,排名,"
						<< "总分人平,排名,总分及格,排名,总分一尖,排名,综合排名,总分二尖,排名,"
						<< endl;
					for (unsigned int i = 0; i < m_OutDatas.size(); i++)
					{
						int classname = int(m_BeginClass + i);
						outype m = m_OutDatas[i];
						//outfile1 << m_TeacherNames[0][i];
						outfile1 << classname << ',';
						for (int j = 0; j < 9; j++)
						{
							outfile1 << m.AverageResult[j] << ','
								<< m_Index[j * 4][i] << ','
								<< m.PassNums[j] << ','
								<< m_Index[j * 4 + 1][i] << ','
								<< m.ExcellentNums[j] << ','
								<< m_Index[j * 4 + 2][i] << ','
								<< zongheIndex[j][i] << ','
								<< m.Excellent2Nums[j] << ','
								<< m_Index[j * 4 + 3][i] << ',';
						}
						int j = 9;
						outfile1
							<< m.AverageResult[j] << ','
							<< m_Index[j * 4][i] << ','
							<< m.PassNums[j] << ','
							<< m_Index[j * 4 + 1][i] << ','
							<< m.ExcellentNums[j] << ','
							<< m_Index[j * 4 + 2][i] << ','
							<< zongheIndex[j][i] << ','
							<< m.Excellent2Nums[j] << ','
							<< m_Index[j * 4 + 3][i] << ',';
						outfile1 << endl;
					}
					outfile1 << "全校人平" << ',';
					for (int i = 0; i < 10; i++)
						outfile1 << m_TotalScore[i] << ','
						<< "" << ',' << "" << ',' << "" << ',' << "" << ','
						<< "" << ',' << "" << ',' << "" << ',' << "" << ',';
					outfile1.close();
					::MessageBox(this->m_hWnd, _T("保存完毕，点击确定回到主菜单！"), _T("提示"), MB_OK);

				}
				else
				{
					outfile1 << "班级,"
						<< "语文教师,语文人平,排名,语文及格,排名,语文一尖,排名,综合排名,语文二尖,排名,"
						<< "数学教师,数学人平,排名,数学及格,排名,数学一尖,排名,综合排名,数学二尖,排名,"
						<< "英语教师,英语人平,排名,英语及格,排名,英语一尖,排名,综合排名,英语二尖,排名,"
						<< "物理教师,物理人平,排名,物理及格,排名,物理一尖,排名,综合排名,物理二尖,排名,"
						<< "化学教师,化学人平,排名,化学及格,排名,化学一尖,排名,综合排名,化学二尖,排名,"
						<< "政治教师,政治人平,排名,政治及格,排名,政治一尖,排名,综合排名,政治二尖,排名,"
						<< "历史教师,历史人平,排名,历史及格,排名,历史一尖,排名,综合排名,历史二尖,排名,"
						<< "地理教师,地理人平,排名,地理及格,排名,地理一尖,排名,综合排名,地理二尖,排名,"
						<< "生物教师,生物人平,排名,生物及格,排名,生物一尖,排名,综合排名,生物二尖,排名,"
						<< "总分人平,排名,总分及格,排名,总分一尖,排名,综合排名,总分二尖,排名,"
						<< endl;
					for (unsigned int i = 0; i < m_OutDatas.size(); i++)
					{
						int classname = int(m_BeginClass + i);
						outype m = m_OutDatas[i];
						//outfile1 << m_TeacherNames[0][i];
						outfile1 << classname << ',';
						for (int j = 0; j < 9; j++)
						{
							outfile1 << m_TeacherNames[j + 1][i] << ','
								<< m.AverageResult[j] << ','
								<< m_Index[j * 4][i] << ','
								<< m.PassNums[j] << ','
								<< m_Index[j * 4 + 1][i] << ','
								<< m.ExcellentNums[j] << ','
								<< m_Index[j * 4 + 2][i] << ','
								<< zongheIndex[j][i] << ','
								<< m.Excellent2Nums[j] << ','
								<< m_Index[j * 4 + 3][i] << ',';
						}
						int j = 9;
						outfile1
							<< m.AverageResult[j] << ','
							<< m_Index[j * 4][i] << ','
							<< m.PassNums[j] << ','
							<< m_Index[j * 4 + 1][i] << ','
							<< m.ExcellentNums[j] << ','
							<< m_Index[j * 4 + 2][i] << ','
							<< zongheIndex[j][i] << ','
							<< m.Excellent2Nums[j] << ','
							<< m_Index[j * 4 + 3][i] << ',';
						outfile1 << endl;
					}
					outfile1 << "全校人平" << ',';
					for (int i = 0; i < 10; i++)
						outfile1 << "" << ',' << m_TotalScore[i] << ','
						<< "" << ',' << "" << ',' << "" << ',' << "" << ','
						<< "" << ',' << "" << ',' << "" << ',' << "" << ',';
					outfile1.close();
					::MessageBox(this->m_hWnd, _T("保存完毕，点击确定回到主菜单！"), _T("提示"), MB_OK);

				}
			}
			else//有分差表导入
			{
				if (!m_flag_teacher)
				{
					outfile1 << "班级,"
						<< "语文人平,分差,最终人平,排名,语文及格,排名,语文一尖,排名,综合排名,语文二尖,排名,"
						<< "数学人平,分差,最终人平,排名,数学及格,排名,数学一尖,排名,综合排名,数学二尖,排名,"
						<< "英语人平,分差,最终人平,排名,英语及格,排名,英语一尖,排名,综合排名,英语二尖,排名,"
						<< "物理人平,分差,最终人平,排名,物理及格,排名,物理一尖,排名,综合排名,物理二尖,排名,"
						<< "化学人平,排名,化学及格,排名,化学一尖,排名,综合排名,化学二尖,排名,"
						<< "政治人平,排名,政治及格,排名,政治一尖,排名,综合排名,政治二尖,排名,"
						<< "历史人平,排名,历史及格,排名,历史一尖,排名,综合排名,历史二尖,排名,"
						<< "地理人平,排名,地理及格,排名,地理一尖,排名,综合排名,地理二尖,排名,"
						<< "生物人平,排名,生物及格,排名,生物一尖,排名,综合排名,生物二尖,排名,"
						<< "总分人平,排名,总分及格,排名,总分一尖,排名,综合排名,总分二尖,排名,"
						<< endl;
					for (unsigned int i = 0; i < m_OutDatas.size(); i++)
					{
						int classname = int(m_BeginClass + i);
						outype m = m_OutDatas[i];
						//outfile1 << m_TeacherNames[0][i];
						outfile1 << classname << ',';

						for (int j = 0; j < 4; j++)
						{
							outfile1 << m.AverageResult[j] + m_Fencha[j][i] << ','
								<< m_Fencha[j][i] << ","
								<< m.AverageResult[j] << ","
								<< m_Index[j * 4][i] << ','
								<< m.PassNums[j] << ','
								<< m_Index[j * 4 + 1][i] << ','
								<< m.ExcellentNums[j] << ','
								<< m_Index[j * 4 + 2][i] << ','
								<< zongheIndex[j][i] << ','
								<< m.Excellent2Nums[j] << ','
								<< m_Index[j * 4 + 3][i] << ',';
						}
						for (int j = 4; j < 9; j++)
						{
							outfile1 << m.AverageResult[j] << ","
								<< m_Index[j * 4][i] << ','
								<< m.PassNums[j] << ','
								<< m_Index[j * 4 + 1][i] << ','
								<< m.ExcellentNums[j] << ','
								<< m_Index[j * 4 + 2][i] << ','
								<< zongheIndex[j][i] << ','
								<< m.Excellent2Nums[j] << ','
								<< m_Index[j * 4 + 3][i] << ',';
						}
						int j = 9;
						outfile1
							<< m.AverageResult[j] << ','
							<< m_Index[j * 4][i] << ','
							<< m.PassNums[j] << ','
							<< m_Index[j * 4 + 1][i] << ','
							<< m.ExcellentNums[j] << ','
							<< m_Index[j * 4 + 2][i] << ','
							<< zongheIndex[j][i] << ','
							<< m.Excellent2Nums[j] << ','
							<< m_Index[j * 4 + 3][i] << ',';
						outfile1 << endl;
					}
					outfile1 << "全校人平" << ',';
					for (int i = 0; i < 4; i++)
						outfile1 << m_TotalScore[i] << ','
						<< "" << ',' << "" << ',' << "" << ',' << "" << ','
						<< "" << ',' << "" << ',' << "" << ',' << "" << ','
						<< "" << ',' << "" << ',';
					for (int i = 4; i < 9; i++)
						outfile1  << m_TotalScore[i] << ','
						<< "" << ',' << "" << ',' << "" << ',' << "" << ','
						<< "" << ',' << "" << ',' << "" << ',' << "" << ',';
					outfile1 << m_TotalScore[9] << ',';

					outfile1.close();
					::MessageBox(this->m_hWnd, _T("保存完毕，点击确定回到主菜单！"), _T("提示"), MB_OK);

				}
				else
				{
					outfile1 << "班级,"
						<< "语文教师,语文人平,分差,最终人平,排名,语文及格,排名,语文一尖,排名,综合排名,语文二尖,排名,"
						<< "数学教师,数学人平,分差,最终人平,排名,数学及格,排名,数学一尖,排名,综合排名,数学二尖,排名,"
						<< "英语教师,英语人平,分差,最终人平,排名,英语及格,排名,英语一尖,排名,综合排名,英语二尖,排名,"
						<< "物理教师,物理人平,分差,最终人平,排名,物理及格,排名,物理一尖,排名,综合排名,物理二尖,排名,"
						<< "化学教师,化学人平,排名,化学及格,排名,化学一尖,排名,综合排名,化学二尖,排名,"
						<< "政治教师,政治人平,排名,政治及格,排名,政治一尖,排名,综合排名,政治二尖,排名,"
						<< "历史教师,历史人平,排名,历史及格,排名,历史一尖,排名,综合排名,历史二尖,排名,"
						<< "地理教师,地理人平,排名,地理及格,排名,地理一尖,排名,综合排名,地理二尖,排名,"
						<< "生物教师,生物人平,排名,生物及格,排名,生物一尖,排名,综合排名,生物二尖,排名,"
						<< "总分人平,排名,总分及格,排名,总分一尖,排名,综合排名,总分二尖,排名,"
						<< endl;
					for (unsigned int i = 0; i < m_OutDatas.size(); i++)
					{
						int classname = int(m_BeginClass + i);
						outype m = m_OutDatas[i];
						//outfile1 << m_TeacherNames[0][i];
						outfile1 << classname << ',';

						for (int j = 0; j < 4; j++)
						{
							outfile1 << m_TeacherNames[j + 1][i] << ','
								<< m.AverageResult[j] + m_Fencha[j][i] << ','
								<< m_Fencha[j][i] << ","
								<< m.AverageResult[j] << ","
								<< m_Index[j * 4][i] << ','
								<< m.PassNums[j] << ','
								<< m_Index[j * 4 + 1][i] << ','
								<< m.ExcellentNums[j] << ','
								<< m_Index[j * 4 + 2][i] << ','
								<< zongheIndex[j][i] << ','
								<< m.Excellent2Nums[j] << ','
								<< m_Index[j * 4 + 3][i] << ',';
						}
						for (int j = 4; j < 9; j++)
						{
							outfile1 << m_TeacherNames[j + 1][i] << ','
								<< m.AverageResult[j] << ","
								<< m_Index[j * 4][i] << ','
								<< m.PassNums[j] << ','
								<< m_Index[j * 4 + 1][i] << ','
								<< m.ExcellentNums[j] << ','
								<< m_Index[j * 4 + 2][i] << ','
								<< zongheIndex[j][i] << ','
								<< m.Excellent2Nums[j] << ','
								<< m_Index[j * 4 + 3][i] << ',';
						}
						int j = 9;
						outfile1
							<< m.AverageResult[j] << ','
							<< m_Index[j * 4][i] << ','
							<< m.PassNums[j] << ','
							<< m_Index[j * 4 + 1][i] << ','
							<< m.ExcellentNums[j] << ','
							<< m_Index[j * 4 + 2][i] << ','
							<< zongheIndex[j][i] << ','
							<< m.Excellent2Nums[j] << ','
							<< m_Index[j * 4 + 3][i] << ',';
						outfile1 << endl;
					}
					outfile1 << "全校人平" << ',';
					for (int i = 0; i < 4; i++)
						outfile1 << "" << ',' << m_TotalScore[i] << ','
						<< "" << ',' << "" << ',' << "" << ',' << "" << ','
						<< "" << ',' << "" << ',' << "" << ',' << "" << ','
						<< "" << ',' << "" << ',';
					for (int i = 4; i < 9; i++)
						outfile1 << "" << ',' << m_TotalScore[i] << ','
						<< "" << ',' << "" << ',' << "" << ',' << "" << ','
						<< "" << ',' << "" << ',' << "" << ',' << "" << ',';
					outfile1 << m_TotalScore[9] << ',';

					outfile1.close();
					::MessageBox(this->m_hWnd, _T("保存完毕，点击确定回到主菜单！"), _T("提示"), MB_OK);
				}
			}
		}
		else
			::MessageBox(this->m_hWnd, _T("保存失败，点击确定回到主菜单！"), _T("提示"), MB_OK);
	}
	else
		::MessageBox(this->m_hWnd, _T("取消保存！"), _T("提示"), MB_OK);
}

bool CScoreCompute::CheckBox()
{
	if (m_ScorePath.IsEmpty())
	{
		::MessageBox(this->m_hWnd, _T("请导入成绩表！"), _T("提示"), MB_OK);
		return false;
	}
	if (m_NumbsPath.IsEmpty())
	{
		::MessageBox(this->m_hWnd, _T("请导入人数表！"), _T("提示"), MB_OK);
		return false;
	}
	return true;
}



double CScoreCompute::round(double x)
{
	x *= 10;
	x += 0.5;
	double b = floor(x);
	b /= 10;
	return b;
}

void CScoreCompute::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CScoreCompute, CDialogEx)
	ON_BN_CLICKED(IDOK, &CScoreCompute::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CScoreCompute::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_LOADSCORE, &CScoreCompute::OnBnClickedButtonLoadscore)
	ON_BN_CLICKED(IDC_BUTTON_LOADNUMBER, &CScoreCompute::OnBnClickedButtonLoadnumber)
	ON_BN_CLICKED(IDC_BUTTON_SET, &CScoreCompute::OnBnClickedButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_LOADINFO, &CScoreCompute::OnBnClickedButtonLoadinfo)
	ON_BN_CLICKED(IDC_BUTTON_LOADTRACHER, &CScoreCompute::OnBnClickedButtonLoadtracher)
END_MESSAGE_MAP()


// CScoreCompute 消息处理程序


void CScoreCompute::OnBnClickedOk()
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


void CScoreCompute::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CScoreCompute::OnBnClickedButtonLoadscore()
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
		m_ScorePath = findFileDlg.GetPathName();  // 取出文件路径
		
		SetDlgItemText(IDC_SCOREPATH, m_ScorePath);
	}
}


void CScoreCompute::OnBnClickedButtonLoadnumber()
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


void CScoreCompute::OnBnClickedButtonLoadtracher()
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
		m_TeachPath = findFileDlg.GetPathName();  // 取出文件路径
		SetDlgItemText(IDC_TEACHER, m_TeachPath);
	}

}


void CScoreCompute::OnBnClickedButtonLoadinfo()
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
		SetDlgItemText(IDC_INFOPATH, m_InfoPath);
	}

}


void CScoreCompute::OnBnClickedButtonSet()
{
	// TODO: 在此添加控件通知处理程序代码
	double score[10];
	for (int i = 0; i < 10; i++)
		score[i] = m_PassScore[i];
	int nums[2];
	nums[0] = m_Nums[0];
	nums[1] = m_Nums[1];

	CHighSet set(score, nums);
	if (set.DoModal() == IDOK)
	{
		set.GetScore(m_PassScore);
		set.GetNums(m_Nums);
	}
}

