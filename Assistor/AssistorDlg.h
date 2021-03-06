
// AssistorDlg.h: 头文件
//

#pragma once

#include "CScoreCompute.h"
#include "CBonusCompute.h"
#include "CStudentClassify.h"
#include "CClassSort.h"
#include "CStudentAdjust.h"
#include "CFilesGather.h"
#include "CTeacherClassfy.h"

// CAssistorDlg 对话框
class CAssistorDlg : public CDialogEx
{
// 构造
public:
	CAssistorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ASSISTOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CFont newFont;


	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonBonus();
	afx_msg void OnBnClickedButtonScore();
	afx_msg void OnBnClickedButtonClassify();
	afx_msg void OnBnClickedButtonSort();
	afx_msg void OnBnClickedButtonAdjust();
	afx_msg void OnBnClickedButtonGather();
	afx_msg void OnBnClickedButtonTeacher();
protected:
	CStatic m_Title;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
protected:
	CStatic m_MyName;
};
