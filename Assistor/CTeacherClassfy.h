#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct teacherdatas
{
	vector<string> ids;
	vector<string> classes;
	vector<string> names;
	vector<string> scores;
	vector<string> sexes;

};
struct teacher
{
	string name;
	int rank;
};

// CTeacherClassfy 对话框

class CTeacherClassfy : public CDialogEx
{
	DECLARE_DYNAMIC(CTeacherClassfy)

public:
	CTeacherClassfy(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTeacherClassfy();

protected:
	CString m_InfoPath;//文件路径
	CString m_MasterPath;

	vector<int> titileIndexs;

	vector<vector<teacher>> m_Datas;
	int classnum;
	vector<string> *m_Masters;
	vector<string> m_Names;
	vector<string> m_MasterNames;
	vector<teacher> *m_Class;

protected:
	bool ReadFile();
	void ProcessFileDatas();
	void SaveFile();
	bool CheckBox();



// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TEACHER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonLoadmaster();
};
