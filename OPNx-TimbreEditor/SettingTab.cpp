


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
	DDX_Control(pDX, IDC_SETTING_COPY_FORMAT_COMBO, m_CComboBoxFormatType);
	DDX_Control(pDX, IDC_SETTING_SWAP_COPY_FORMAT_CHECK, m_CButtonSwapCopyFormat);
	DDX_Control(pDX, IDC_SETTING_AUTO_COPY_FORMAT_CHECK, m_CButtonAutoCopyFormat);
	DDX_Control(pDX, IDC_SETTING_LATENCY_SLIDER, m_CSliderCtrlLatency);
	DDX_Control(pDX, IDC_SETTING_FILTER_COMBO, m_CComboBoxFilter);
	DDX_Control(pDX, IDC_SETTING_CUTOFF_SLIDER, m_CSliderCtrlCutoff);
	DDX_Control(pDX, IDC_SETTING_RESONANCE_SLIDER, m_CSliderCtrlResonance);
	DDX_Control(pDX, IDC_SETTING_DC_CUT_CHECK, m_CButtonDCCut);
	DDX_Control(pDX, IDC_SETTING_DC_CUT_RATE_SLIDER, m_CSliderCtrlDCCutRate);
	DDX_Control(pDX, IDC_SETTING_SYNTHESIZE_FREQ_COMBO, m_CComboBoxSynthesizeFreq);
}



BEGIN_MESSAGE_MAP(CSettingTab, CDialogEx)
	ON_CBN_SELCHANGE(IDC_SETTING_COPY_FORMAT_COMBO, &CSettingTab::OnCbnSelchangeSettingCopyFormatExtCombo)
	ON_BN_CLICKED(IDC_SETTING_SWAP_COPY_FORMAT_CHECK, &CSettingTab::OnBnClickedSettingSwapCopyFormatCheck)
	ON_BN_CLICKED(IDC_SETTING_AUTO_COPY_FORMAT_CHECK, &CSettingTab::OnBnClickedSrttingAutoCopyFormatCheck)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SETTING_LATENCY_SLIDER, &CSettingTab::OnNMCustomdrawSettingLatencySlider)
	ON_CBN_SELCHANGE(IDC_SETTING_FILTER_COMBO, &CSettingTab::OnCbnSelchangeSettingFilterCombo)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SETTING_CUTOFF_SLIDER, &CSettingTab::OnNMCustomdrawSettingCutoffSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SETTING_RESONANCE_SLIDER, &CSettingTab::OnNMCustomdrawSettingResonanceSlider)
	ON_BN_CLICKED(IDC_SETTING_DC_CUT_CHECK, &CSettingTab::OnBnClickedSettingDcCutCheck)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SETTING_DC_CUT_RATE_SLIDER, &CSettingTab::OnNMCustomdrawSettingDcCutRateSlider)
	ON_CBN_SELCHANGE(IDC_SETTING_SYNTHESIZE_FREQ_COMBO, &CSettingTab::OnCbnSelchangeSettingSynthesizeFreqCombo)
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
	SetDropdownSize(m_CComboBoxFormatType);
	
	m_CButtonSwapCopyFormat.SetCheck(theApp.GetValue(_T("SwapCopyFormat"), BST_UNCHECKED));
	
	m_CButtonAutoCopyFormat.SetCheck(theApp.GetValue(_T("AutoCopyFormat"), BST_UNCHECKED));
	
	m_CSliderCtrlLatency.SetRange(1, 100);
	m_CSliderCtrlLatency.SetPos(theApp.GetValue(_T("Latency"), 1));
	
	m_CComboBoxFilter.SetCurSel(theApp.GetValue(_T("FilterMode"), (int)Filter::FilterMode::FILTER_MODE_LOWPASS));
	SetDropdownSize(m_CComboBoxFilter);
	
	m_CSliderCtrlCutoff.SetRange(1, 99);
	m_CSliderCtrlCutoff.SetPos(theApp.GetValue(_T("Cutoff"), 99));
	
	m_CSliderCtrlResonance.SetRange(1, 100);
	m_CSliderCtrlResonance.SetPos(theApp.GetValue(_T("Resonance"), 1));
	
	m_CButtonDCCut.SetCheck(theApp.GetValue(_T("DCCut"), BST_UNCHECKED));
	
	m_CSliderCtrlDCCutRate.SetRange(0, 9);
	m_CSliderCtrlDCCutRate.SetPos(theApp.GetValue(_T("DCCutRate"), 5));
	
	m_CComboBoxSynthesizeFreq.SetCurSel(theApp.GetValue(_T("SynthesizeFreq"), (int)ESynthesizeFreq::Hz55555));
	SetDropdownSize(m_CComboBoxSynthesizeFreq);
	
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



void CSettingTab::OnCbnSelchangeSettingCopyFormatExtCombo()
{
	theApp.SetValue(_T("FormatType"), (int)GetFormatType());
}



void CSettingTab::OnBnClickedSettingSwapCopyFormatCheck()
{
	theApp.SetValue(_T("SwapCopyFormat"), (IsSwapCopyFormat())? BST_CHECKED: BST_UNCHECKED);
}



void CSettingTab::OnBnClickedSrttingAutoCopyFormatCheck()
{
	theApp.SetValue(_T("AutoCopyFormat"), (IsAutoCopyFormat())? BST_CHECKED: BST_UNCHECKED);
}



void CSettingTab::OnCbnSelchangeSettingSynthesizeFreqCombo()
{
	theApp.SetValue(_T("SynthesizeFreq"), (int)GetSynthesizeFreq());
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



void CSettingTab::OnBnClickedSettingDcCutCheck()
{
	theApp.SetValue(_T("DCCut"), (IsDCCut())? BST_CHECKED: BST_UNCHECKED);
}



void CSettingTab::OnNMCustomdrawSettingDcCutRateSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	theApp.SetValue(_T("DCCutRate"), (int)((GetDCCutRate() - 0.99) * 1000.0));
	*pResult = 0;
}



CSettingTab::EFormatType CSettingTab::GetFormatType()
{
	return (EFormatType)m_CComboBoxFormatType.GetCurSel();
}



void CSettingTab::SetFormatType(EFormatType EFormatType)
{
	m_CComboBoxFormatType.SetCurSel((int)EFormatType);
}



bool CSettingTab::IsSwapCopyFormat()
{
	return (m_CButtonSwapCopyFormat.GetCheck() == BST_CHECKED);
}



bool CSettingTab::IsAutoCopyFormat()
{
	return (m_CButtonAutoCopyFormat.GetCheck() == BST_CHECKED);
}



CSettingTab::ESynthesizeFreq CSettingTab::GetSynthesizeFreq()
{
	return (CSettingTab::ESynthesizeFreq)m_CComboBoxSynthesizeFreq.GetCurSel();
}



int CSettingTab::GetSynthesizeFreq(ESynthesizeFreq ESynthesizeFreq)
{
	switch (ESynthesizeFreq){
		case CSettingTab::Hz55555: return 55555;
		case CSettingTab::Hz55466: return 55466;
	}
	return 55555;
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



bool CSettingTab::IsDCCut()
{
	return (m_CButtonDCCut.GetCheck() == BST_CHECKED);
}



double CSettingTab::GetDCCutRate()
{
	return (m_CSliderCtrlDCCutRate.GetPos() / 1000.0) + 0.99;
}
