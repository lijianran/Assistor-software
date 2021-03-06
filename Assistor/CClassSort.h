#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct studentinfo
{
	double clas;
	double score;
	vector<string> info;
};

// CClassSort 对话框

class CClassSort : public CDialogEx
{
	DECLARE_DYNAMIC(CClassSort)

public:
	CClassSort(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CClassSort();

protected:
	CString m_InfoPath;//文件路径
	string m_Titles;
	vector<studentinfo> m_FileDatas;
	bool m_TotalFlag;
	int m_BeginClass;
	int m_ClassNumbs;
	vector<studentinfo> *m_ClassDatas;
	int *m_Numbs;
	vector<int> *m_Index;


protected:
	bool ReadFile();
	void ProcessFileDatas();
	void SaveFile();
	bool CheckBox();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonLoadinfos();
};
