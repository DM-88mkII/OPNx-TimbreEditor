#pragma once



#include "afxdialogex.h"



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
		CComboBox m_CComboBox;
		CButton m_Check;
		CSliderCtrl m_CSliderCtrl;
		
		virtual BOOL OnInitDialog();
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		afx_msg void OnCbnSelchangeSettingCopyPasteExtCombo();
		afx_msg void OnBnClickedSettingSwapCopyPasteCheck();
		afx_msg void OnNMCustomdrawSettingLatencySlider(NMHDR* pNMHDR, LRESULT* pResult);
	
	public:
		enum EFormatType
		{
			MUCOM,
			FMP,
			PMD,
			MAmidiMemo,
		};
		EFormatType GetFormatType();
		bool GetSwapCopyPaste();
		int GetLatency();
};
