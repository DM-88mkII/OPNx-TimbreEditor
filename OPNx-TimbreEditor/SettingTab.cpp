


#include "pch.h"
#include "TimbreEditor.h"
#include "afxdialogex.h"
#include "SettingTab.h"



IMPLEMENT_DYNAMIC(CSettingTab, CDialogEx)



CSettingTab::~CSettingTab()
{
}



CSettingTab::CSettingTab(CWnd* pParent /*=nullptr*/)
:CDialogEx(IDD_SETTING_TAB, pParent)
{
}



void CSettingTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SETTING_COPY_PASTE_COMBO, m_CComboBox);
	DDX_Control(pDX, IDC_SETTING_SWAP_COPY_PASTE_CHECK, m_Check);
	DDX_Control(pDX, IDC_SETTING_LATENCY_SLIDER, m_CSliderCtrl);
}



BEGIN_MESSAGE_MAP(CSettingTab, CDialogEx)
	ON_CBN_SELCHANGE(IDC_SETTING_COPY_PASTE_COMBO, &CSettingTab::OnCbnSelchangeSettingCopyPasteExtCombo)
	ON_BN_CLICKED(IDC_SETTING_SWAP_COPY_PASTE_CHECK, &CSettingTab::OnBnClickedSettingSwapCopyPasteCheck)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SETTING_LATENCY_SLIDER, &CSettingTab::OnNMCustomdrawSettingLatencySlider)
END_MESSAGE_MAP()



BOOL CSettingTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();//call DoDataExchange()
	
	m_CComboBox.SetCurSel(theApp.GetValue(_T("FormatType"), (int)EFormatType::MUCOM));
//	m_CComboBox.SetCurSel((int)EFormatType::MUCOM);
//	m_CComboBox.SetCurSel((int)EFormatType::FMP);
//	m_CComboBox.SetCurSel((int)EFormatType::PMD);
	
	m_Check.SetCheck(theApp.GetValue(_T("SwapCopyPaste"), BST_UNCHECKED));
	
	m_CSliderCtrl.SetRange(1, 100);
	m_CSliderCtrl.SetPos(theApp.GetValue(_T("Latency"), 1));
	
	return FALSE;
}



BOOL CSettingTab::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message){
		case WM_KEYDOWN:{
			switch (pMsg->wParam){
				case VK_RETURN:
				case VK_ESCAPE:
				{
					return TRUE;
				}
			}
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}



void CSettingTab::OnCbnSelchangeSettingCopyPasteExtCombo()
{
	theApp.SetValue(_T("FormatType"), (int)GetFormatType());
}



void CSettingTab::OnBnClickedSettingSwapCopyPasteCheck()
{
	theApp.SetValue(_T("SwapCopyPaste"), (GetSwapCopyPaste())? BST_CHECKED: BST_UNCHECKED);
}



void CSettingTab::OnNMCustomdrawSettingLatencySlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	theApp.SetValue(_T("Latency"), GetLatency());
	*pResult = 0;
}



CSettingTab::EFormatType CSettingTab::GetFormatType()
{
	return (EFormatType)m_CComboBox.GetCurSel();
}



bool CSettingTab::GetSwapCopyPaste()
{
	return (m_Check.GetCheck() == BST_CHECKED);
}



int CSettingTab::GetLatency()
{
	return m_CSliderCtrl.GetPos();
}
