#pragma once

#include <vector>
using namespace std;

// CHighSet 对话框

class CHighSet : public CDialogEx
{
	DECLARE_DYNAMIC(CHighSet)

public:
	CHighSet(CWnd* pParent = nullptr);   // 标准构造函数
	CHighSet(double score[], int nums[], CWnd* pParent = nullptr);
	virtual ~CHighSet();

protected:
	int m_Nums[2];
	double m_Score[10];

public:
	void GetNums(int a[]);
	void GetScore(double a[]);

protected:
	bool CheckBox();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
