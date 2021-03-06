#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct type
{
	string clas;
	string name;
	string average;
	string first;
	string second;
	string ratio;
};
struct datas
{
	vector<type> chinese;
	vector<type> math;
	vector<type> english;
	vector<type> physics;
	vector<type> chemistry;
	vector<type> political;
	vector<type> history;
	vector<type> geography;
	vector<type> organism;
	vector<string> total_average;
};
struct outresult
{
	string clas;
	string course;
	string name;
	double averagemoney;
	double firstmoeny;
	double secondmoney;
	double totalmoney;
};
struct goal
{
	string name;
	double money;
};
// CBonusCompute 对话框

class CBonusCompute : public CDialogEx
{
	DECLARE_DYNAMIC(CBonusCompute)

public:
	CBonusCompute(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CBonusCompute();

protected:
	CString m_InfoPath, m_NumbsPath;//文件路径
	datas Data;
	vector<outresult> results;
	double m_average;
	double m_first;
	double m_second;
	

protected:
	bool ReadFile();
	void ProcessFileDatas();
	void SaveFile();
	bool CheckBox();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BONUS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLoadinfos();
	afx_msg void OnBnClickedButtonLoadnumber();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
