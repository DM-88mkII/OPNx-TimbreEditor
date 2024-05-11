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
		
		virtual BOOL OnInitDialog();
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		afx_msg void OnCbnSelchangeSettingCopyPasteExtCombo();
	
	public:
		enum ECopyPaste
		{
			MUCOM,
			FMP,
		};
		ECopyPaste GetCopyPasteType();
};
