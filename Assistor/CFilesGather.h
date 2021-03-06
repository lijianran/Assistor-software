#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// CFilesGather 对话框

class CFilesGather : public CDialogEx
{
	DECLARE_DYNAMIC(CFilesGather)

public:
	CFilesGather(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFilesGather();

protected:
	vector<CString> m_FilePaths;
	CString m_ModelFilePath;
	vector<string> titlestrings;
	vector<vector<string>> m_Datas;

protected:
	bool ReadFile();
	void ProcessFileDatas();
	void SaveFile();
	bool CheckBox();
	void GetFileList(char* szPath);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GATHER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonSelect();
	virtual BOOL OnInitDialog();
protected:
	CListCtrl m_ListShow;
public:
	afx_msg void OnBnClickedButtonImport();
};
