// CHighSet.cpp: 实现文件
//

#include "stdafx.h"
#include "Assistor.h"
#include "CHighSet.h"
#include "afxdialogex.h"


// CHighSet 对话框

IMPLEMENT_DYNAMIC(CHighSet, CDialogEx)

CHighSet::CHighSet(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETTING, pParent)
{

}

CHighSet::CHighSet(double score[], int nums[], CWnd* pParent)
	: CDialogEx(IDD_DIALOG_SETTING, pParent)
{

	m_Nums[0] = nums[0];
	m_Nums[1] = nums[1] - nums[0];
	m_Score[0] = score[0];
	m_Score[1] = score[1];
	m_Score[2] = score[2];
	m_Score[3] = score[3];
	m_Score[4] = score[4];
	m_Score[5] = score[5];
	m_Score[6] = score[6];
	m_Score[7] = score[7];
	m_Score[8] = score[8];

	m_Score[9] = 0;
	for (int i = 0; i < 9; i++)
		m_Score[9] += m_Score[i];

}

CHighSet::~CHighSet()
{
}

void CHighSet::GetNums(int a[])
{
	a[0] = m_Nums[0];
	a[1] = m_Nums[1];
}

void CHighSet::GetScore(double a[])
{
	for (int i = 0; i < 10; i++)
		a[i] = m_Score[i];
}

bool CHighSet::CheckBox()
{
	int nEdit[11] = { 0 };

	nEdit[0] = GetDlgItemInt(IDC_EDIT1);
	nEdit[1] = GetDlgItemInt(IDC_EDIT2);
	nEdit[2] = GetDlgItemInt(IDC_EDIT3);
	nEdit[3] = GetDlgItemInt(IDC_EDIT4);
	nEdit[4] = GetDlgItemInt(IDC_EDIT5);
	nEdit[5] = GetDlgItemInt(IDC_EDIT6);
	nEdit[6] = GetDlgItemInt(IDC_EDIT7);
	nEdit[7] = GetDlgItemInt(IDC_EDIT8);
	nEdit[8] = GetDlgItemInt(IDC_EDIT9);
	nEdit[9] = GetDlgItemInt(IDC_EDIT_FIRST);
	nEdit[10] = GetDlgItemInt(IDC_EDIT_SECOND);

	//if (nEdit[9] >= nEdit[10])
	//{
	//	::MessageBox(this->m_hWnd, _T("一尖人数大于二尖人数！"), _T("提示"), MB_OK);
	//	return false;
	//}
	m_Nums[0] = nEdit[9];
	m_Nums[1] = nEdit[9] + nEdit[10];


	for (int i = 0; i < 9; i++)
	{
		if (nEdit[i] > 999)
		{
			::MessageBox(this->m_hWnd, _T("单科卷面总分超过四位数！"), _T("提示"), MB_OK);
			return false;
		}
		if (nEdit[i] < 10)
		{
			::MessageBox(this->m_hWnd, _T("单科卷面总分少于两位数！"), _T("提示"), MB_OK);
			return false;
		}
	}
	int totalnums = 0;
	for (int i = 0; i < 9; i++)
	{
		m_Score[i] = nEdit[i] * 0.6;
		totalnums += nEdit[i];
	}
	m_Score[9] = totalnums * 0.6;
	CString total;
	total.Format(_T("%d"), totalnums);
	SetDlgItemText(IDC_EDIT10, total);

	return true;
}

void CHighSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHighSet, CDialogEx)
	ON_BN_CLICKED(IDOK, &CHighSet::OnBnClickedOk)
END_MESSAGE_MAP()


// CHighSet 消息处理程序


BOOL CHighSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	int scorenums[10];
	CString score[10];
	for (int i = 0; i < 10; i++)
		scorenums[i] = int(m_Score[i] / 0.6);
	for (int i = 0; i < 10; i++)
		score[i].Format(_T("%d"), scorenums[i]);
	SetDlgItemText(IDC_EDIT1, score[0]);
	SetDlgItemText(IDC_EDIT2, score[1]);
	SetDlgItemText(IDC_EDIT3, score[2]);
	SetDlgItemText(IDC_EDIT4, score[3]);
	SetDlgItemText(IDC_EDIT5, score[4]);
	SetDlgItemText(IDC_EDIT6, score[5]);
	SetDlgItemText(IDC_EDIT7, score[6]);
	SetDlgItemText(IDC_EDIT8, score[7]);
	SetDlgItemText(IDC_EDIT9, score[8]);
	SetDlgItemText(IDC_EDIT10, score[9]);

	CString first, second;
	first.Format(_T("%d"), m_Nums[0]);
	second.Format(_T("%d"), m_Nums[1]);
	SetDlgItemText(IDC_EDIT_FIRST, first);
	SetDlgItemText(IDC_EDIT_SECOND, second);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CHighSet::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	if (CheckBox())
	{
		::MessageBox(this->m_hWnd, _T("修改成功！"), _T("提示"), MB_OK);
		CDialogEx::OnOK();

	}
}
