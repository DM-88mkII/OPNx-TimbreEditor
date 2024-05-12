


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
}



BEGIN_MESSAGE_MAP(CSettingTab, CDialogEx)
	ON_CBN_SELCHANGE(IDC_SETTING_COPY_PASTE_COMBO, &CSettingTab::OnCbnSelchangeSettingCopyPasteExtCombo)
END_MESSAGE_MAP()



BOOL CSettingTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();//call DoDataExchange()
	
	m_CComboBox.SetCurSel((int)EFormatType::MUCOM);
//	m_CComboBox.SetCurSel((int)EFormatType::FMP);
//	m_CComboBox.SetCurSel((int)EFormatType::PMD);
	
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
	
}



CSettingTab::EFormatType CSettingTab::GetFormatType()
{
	return (EFormatType)m_CComboBox.GetCurSel();
}
