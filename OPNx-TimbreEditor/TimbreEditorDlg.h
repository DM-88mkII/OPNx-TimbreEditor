#pragma once



#include "ModuleTab.h"
#include "SettingTab.h"



class CTimbreEditorDlg : public CDialogEx
{
	public:
		~CTimbreEditorDlg();
		
		CTimbreEditorDlg(CWnd* pParent = nullptr);
		
		#ifdef AFX_DESIGN_TIME
		enum { IDD = IDD_TIMBREEDITOR_DIALOG };
		#endif
	
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);
		
		DECLARE_MESSAGE_MAP()
	
	protected:
		HICON m_hIcon;
		CTabCtrl m_CTabCtrl;
		CModuleTab m_CModuleTab;
		CSettingTab m_CSettingTab;
		
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		afx_msg void OnSelchangeTabcontrol(NMHDR* pNMHDR, LRESULT* pResult);
		
		virtual BOOL OnInitDialog();
		afx_msg void OnPaint();
		afx_msg HCURSOR OnQueryDragIcon();
	
	public:
		CSettingTab& GetSettingTab();
};
