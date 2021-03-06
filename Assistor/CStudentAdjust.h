#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct stu
{
	double clas;
	string name;
	double score;
	string sex;
	string goal;
	vector<string> info;

	string sign;
};

// CStudentAdjust 对话框

class CStudentAdjust : public CDialogEx
{
	DECLARE_DYNAMIC(CStudentAdjust)


public:
	CStudentAdjust(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CStudentAdjust();

protected:
	CString m_InfoPath;//文件路径
	string m_Titles;
	vector<vector<stu>> m_FileDatas;
	int m_BeginClass;
	int m_Score;

protected:
	bool ReadFile();
	void ProcessFileDatas();
	void SaveFile();
	bool CheckBox();

	void sawpstudent(stu *stua, stu *stub);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADJUST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonLoadinfos();
	virtual BOOL OnInitDialog();
};
