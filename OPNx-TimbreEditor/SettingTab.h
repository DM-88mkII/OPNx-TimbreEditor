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
		CButton m_CButtonSwapCopyFormat;
		CButton m_CButtonAutoCopyFormat;
		CComboBox m_CComboBoxSynthesizeFreq;
		CSliderCtrl m_CSliderCtrlLatency;
		CComboBox m_CComboBoxFilter;
		CSliderCtrl m_CSliderCtrlCutoff;
		CSliderCtrl m_CSliderCtrlResonance;
		CButton m_CButtonDCCut;
		CSliderCtrl m_CSliderCtrlDCCutRate;
		CButton m_CButtonSwapPreview;
		CSliderCtrl m_CSliderCtrlVolume;
		CButton m_CButtonSLTLLink;
		
		virtual BOOL OnInitDialog();
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		afx_msg void OnCbnSelchangeSettingCopyFormatExtCombo();
		afx_msg void OnBnClickedSettingSwapCopyFormatCheck();
		afx_msg void OnBnClickedSrttingAutoCopyFormatCheck();
		afx_msg void OnCbnSelchangeSettingSynthesizeFreqCombo();
		afx_msg void OnNMCustomdrawSettingLatencySlider(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnCbnSelchangeSettingFilterCombo();
		afx_msg void OnNMCustomdrawSettingCutoffSlider(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnNMCustomdrawSettingResonanceSlider(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnBnClickedSettingDcCutCheck();
		afx_msg void OnNMCustomdrawSettingDcCutRateSlider(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnBnClickedSettingSwapPreviewCheck();
		afx_msg void OnNMCustomdrawSettingVolumeSlider(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnBnClickedSettingSLTLLink();
		
		template<class... Args> void Log(std::wformat_string<Args...> fmt, Args&& ... args);
	
	public:
		enum EFormatType
		{
			Mucom,
			PmdOPN,
			PmdOPM,
			Fmp,
			FmpA,
			Fmp7F,
			Fmp7FA,
			Fmp7FC,
			Mml2VgmF,
			Mml2VgmN,
			Mml2VgmM,
			mucomDotNET,
			MAmidiMemoMOPN,
			MAmidiMemoMOPM,
			ZMusicV,
			ZMusicAt,
			NagDrv,
			NrtDrv,
			MmlDrv,
			MmlGui,
			Muap98,
			V3MmlOPN,
			V3MmlOPNA,
			V3MmlOPM,
			N88Basic,
			Num,
		};
		enum ESynthesizeFreq
		{
			Hz55555,
			Hz55466,
		};
		EFormatType GetFormatType();
		void SetFormatType(EFormatType EFormatType);
		bool IsSwapCopyFormat();
		bool IsAutoCopyFormat();
		ESynthesizeFreq GetSynthesizeFreq();
		int GetSynthesizeFreq(ESynthesizeFreq ESynthesizeFreq);
		int GetLatency();
		Filter::FilterMode GetFilterMode();
		double GetCutoff();
		double GetResonance();
		bool IsDCCut();
		double GetDCCutRate();
		bool IsSwapPreview();
		double GetVolume();
		void SetVolume(double Volume);
		bool IsSLTLLink();
};
