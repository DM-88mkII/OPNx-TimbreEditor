#pragma once



#include "afxdialogex.h"
#include "martin-finke/Filter.h"



class CSettingTab : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingTab)
	
	public:
		virtual ~CSettingTab();
		
		CSettingTab(CWnd* pParent = nullptr);
		
		#ifdef AFX_DESIGN_TIME
		enum { IDD = IDD_SETTING_TAB };
		#endif
	
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);
		
		DECLARE_MESSAGE_MAP()
	
	protected:
		CComboBox m_CComboBoxFormatType;
		CButton m_CheckSwapCopyPaste;
		CSliderCtrl m_CSliderCtrlLatency;
		CComboBox m_CComboBoxFilter;
		CSliderCtrl m_CSliderCtrlCutoff;
		CSliderCtrl m_CSliderCtrlResonance;
		CButton m_CButtonDCCut;
		CSliderCtrl m_CSliderCtrlDCCutRate;
		CComboBox m_CComboBoxSynthesizeFreq;
		
		virtual BOOL OnInitDialog();
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		afx_msg void OnCbnSelchangeSettingCopyPasteExtCombo();
		afx_msg void OnBnClickedSettingSwapCopyPasteCheck();
		afx_msg void OnNMCustomdrawSettingLatencySlider(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnCbnSelchangeSettingFilterCombo();
		afx_msg void OnNMCustomdrawSettingCutoffSlider(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnNMCustomdrawSettingResonanceSlider(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnBnClickedSettingDcCutCheck();
		afx_msg void OnNMCustomdrawSettingDcCutRateSlider(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnCbnSelchangeSettingSynthesizeFreqCombo();
	
	public:
		enum EFormatType
		{
			MUCOM,
			FMP,
			PMD,
			MAmidiMemo,
		};
		enum ESynthesizeFreq
		{
			Hz55555,
			Hz55466,
		};
		EFormatType GetFormatType();
		bool GetSwapCopyPaste();
		int GetLatency();
		Filter::FilterMode GetFilterMode();
		double GetCutoff();
		double GetResonance();
		bool IsDCCut();
		double GetDCCutRate();
		ESynthesizeFreq GetSynthesizeFreq();
		int GetSynthesizeFreq(ESynthesizeFreq ESynthesizeFreq);
};
