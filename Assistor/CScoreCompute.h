#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include "CHighSet.h"
#include "Tools.h"
using namespace std;

struct outype
{
	double AverageResult[10];
	int ExcellentNums[10];
	int Excellent2Nums[10];
	int PassNums[10];
};

// CScoreCompute 对话框

class CScoreCompute : public CDialogEx
{
	DECLARE_DYNAMIC(CScoreCompute)

public:
	CScoreCompute(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CScoreCompute();


protected:
	CString m_ScorePath, m_NumbsPath, m_TeachPath,m_InfoPath;//文件路径
	vector<double> m_FileDatas[11];//成绩表信息
	int m_Total;//总人数
	int m_ClassNums;//班级个数
	double m_BeginClass;//开始班级701或801或901
	vector<int> m_EffectiveNums;//有效人数表信息
	vector<string> m_TeacherNames[10];//教师姓名
	vector<double> m_Fencha[4];//分差数据
	bool m_flag;
	bool m_flag_teacher;

	vector<vector<double>> *m_ClassDatas;//班级信息

	vector<outype> m_OutDatas;//输出的数据
	vector<double> m_TotalScore;//各科全校人平
	int *m_Index[40];//排名信息
	int *zongheIndex[10];//综合排名信息

	double m_PassScore[10];//及格分数线
	int m_Nums[2];//一尖二尖

protected:
	bool ReadFile();
	void ProcessFileDatas();
	void SaveFile();
	bool CheckBox();
	double round(double x);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SCORE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonLoadscore();
	afx_msg void OnBnClickedButtonLoadnumber();
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnBnClickedButtonLoadinfo();
	afx_msg void OnBnClickedButtonLoadtracher();
};
