


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
	DDX_Control(pDX, IDC_SETTING_COPY_PASTE_EXT_COMBO, m_CComboBox);
}



BEGIN_MESSAGE_MAP(CSettingTab, CDialogEx)
	ON_CBN_SELCHANGE(IDC_SETTING_COPY_PASTE_EXT_COMBO, &CSettingTab::OnCbnSelchangeSettingCopyPasteExtCombo)
END_MESSAGE_MAP()



BOOL CSettingTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();//call DoDataExchange()
	
	m_CComboBox.SetCurSel((int)ECopyPaste::MUCOM);
	
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



CSettingTab::ECopyPaste CSettingTab::GetCopyPasteType()
{
	return (ECopyPaste)m_CComboBox.GetCurSel();
}
