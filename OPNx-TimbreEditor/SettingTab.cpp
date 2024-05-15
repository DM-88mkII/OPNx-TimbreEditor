﻿


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
	DDX_Control(pDX, IDC_SETTING_COPY_PASTE_COMBO, m_CComboBoxFormatType);
	DDX_Control(pDX, IDC_SETTING_SWAP_COPY_PASTE_CHECK, m_CheckSwapCopyPaste);
	DDX_Control(pDX, IDC_SETTING_LATENCY_SLIDER, m_CSliderCtrlLatency);
	DDX_Control(pDX, IDC_SETTING_FILTER_COMBO, m_CComboBoxFilter);
	DDX_Control(pDX, IDC_SETTING_CUTOFF_SLIDER, m_CSliderCtrlCutoff);
	DDX_Control(pDX, IDC_SETTING_RESONANCE_SLIDER, m_CSliderCtrlResonance);
}



BEGIN_MESSAGE_MAP(CSettingTab, CDialogEx)
	ON_CBN_SELCHANGE(IDC_SETTING_COPY_PASTE_COMBO, &CSettingTab::OnCbnSelchangeSettingCopyPasteExtCombo)
	ON_BN_CLICKED(IDC_SETTING_SWAP_COPY_PASTE_CHECK, &CSettingTab::OnBnClickedSettingSwapCopyPasteCheck)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SETTING_LATENCY_SLIDER, &CSettingTab::OnNMCustomdrawSettingLatencySlider)
	ON_CBN_SELCHANGE(IDC_SETTING_FILTER_COMBO, &CSettingTab::OnCbnSelchangeSettingFilterCombo)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SETTING_CUTOFF_SLIDER, &CSettingTab::OnNMCustomdrawSettingCutoffSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SETTING_RESONANCE_SLIDER, &CSettingTab::OnNMCustomdrawSettingResonanceSlider)
END_MESSAGE_MAP()



BOOL CSettingTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();//call DoDataExchange()
	
	auto SetDropdownSize = [this](CComboBox& rCComboBox)
	{
		//rCComboBox.SetMinVisibleItems(rCComboBox.GetCount());//doesn't work
		
		CRect Rect;
		rCComboBox.GetDroppedControlRect(&Rect);
		Rect.bottom += 1000;
		rCComboBox.GetParent()->ScreenToClient(&Rect);
		rCComboBox.MoveWindow(&Rect);
	};
	
	m_CComboBoxFormatType.SetCurSel(theApp.GetValue(_T("FormatType"), (int)EFormatType::MUCOM));
//	m_CComboBoxFormatType.SetCurSel((int)EFormatType::MUCOM);
//	m_CComboBoxFormatType.SetCurSel((int)EFormatType::FMP);
//	m_CComboBoxFormatType.SetCurSel((int)EFormatType::PMD);
	SetDropdownSize(m_CComboBoxFormatType);
	
	m_CheckSwapCopyPaste.SetCheck(theApp.GetValue(_T("SwapCopyPaste"), BST_UNCHECKED));
	
	m_CSliderCtrlLatency.SetRange(1, 100);
	m_CSliderCtrlLatency.SetPos(theApp.GetValue(_T("Latency"), 1));
	
	m_CComboBoxFilter.SetCurSel(theApp.GetValue(_T("FilterMode"), (int)Filter::FilterMode::FILTER_MODE_LOWPASS));
	SetDropdownSize(m_CComboBoxFilter);
	
	m_CSliderCtrlCutoff.SetRange(1, 99);
	m_CSliderCtrlCutoff.SetPos(theApp.GetValue(_T("Cutoff"), 99));
	
	m_CSliderCtrlResonance.SetRange(1, 100);
	m_CSliderCtrlResonance.SetPos(theApp.GetValue(_T("Resonance"), 1));
	
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


void CSettingTab::OnCbnSelchangeSettingFilterCombo()
{
	theApp.SetValue(_T("FilterMode"), (int)GetFilterMode());
}


void CSettingTab::OnNMCustomdrawSettingCutoffSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	theApp.SetValue(_T("Cutoff"), (int)(GetCutoff() * 100.0));
	*pResult = 0;
}


void CSettingTab::OnNMCustomdrawSettingResonanceSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	theApp.SetValue(_T("Resonance"), (int)(GetResonance() * 100.0));
	*pResult = 0;
}



CSettingTab::EFormatType CSettingTab::GetFormatType()
{
	return (EFormatType)m_CComboBoxFormatType.GetCurSel();
}



bool CSettingTab::GetSwapCopyPaste()
{
	return (m_CheckSwapCopyPaste.GetCheck() == BST_CHECKED);
}



int CSettingTab::GetLatency()
{
	return m_CSliderCtrlLatency.GetPos();
}



Filter::FilterMode CSettingTab::GetFilterMode()
{
	return (Filter::FilterMode)m_CComboBoxFilter.GetCurSel();
}



double CSettingTab::GetCutoff()
{
	return m_CSliderCtrlCutoff.GetPos() / 100.0;
}



double CSettingTab::GetResonance()
{
	return m_CSliderCtrlResonance.GetPos() / 100.0;
}
