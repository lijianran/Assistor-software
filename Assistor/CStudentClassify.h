#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct filedatas
{
	vector<string> ids;
	vector<string> classes;
	vector<string> names;
	vector<string> scores;
	vector<string> sexes;

};
struct studentdata
{
	string id;
	string clas;
	string name;
	double score;
	string sex;

};

// CStudentClassify 对话框

class CStudentClassify : public CDialogEx
{
	DECLARE_DYNAMIC(CStudentClassify)


public:
	CStudentClassify(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CStudentClassify();


protected:
	CString m_InfoPath;//文件路径
	filedatas m_FileBoyDatas;
	filedatas m_FileGirlDatas;
	vector<studentdata> m_Boys;
	vector<studentdata> m_Girls;
	int m_ClassNums;

	vector<vector<studentdata>> m_Classes;

protected:
	bool ReadFile();
	void ProcessFileDatas();
	void SaveFile();
	bool CheckBox();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CLASSIFY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonLoadinfomation();
};
