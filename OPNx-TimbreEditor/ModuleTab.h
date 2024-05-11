#pragma once



#include "afxdialogex.h"
#include "TimbreTab.h"
#include "Timbre.h"
#include <memory>
#include <vector>
#include <format>



class CModuleTab : public CDialogEx
{
	DECLARE_DYNAMIC(CModuleTab)
	
	public:
		virtual ~CModuleTab();
		
		CModuleTab(CWnd* pParent = nullptr);
		
		#ifdef AFX_DESIGN_TIME
		enum { IDD = IDD_MODULE_TAB };
		#endif
	
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);
		
		DECLARE_MESSAGE_MAP()
	
	protected:
		CTabCtrl m_CTabCtrl;
		CTimbreTab m_CTimbreTab;
		std::vector<std::shared_ptr<CTimbre>> m_aCTimbre;
		int m_aaParam[5][15];
		int mx;
		int my;
		int m_iPrev;
		int m_Octaver;
		
		virtual BOOL OnInitDialog();
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		afx_msg void OnSelchangeTabcontrol(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnBnClickedModuleLoadButton();
		afx_msg void OnBnClickedModuleSaveButton();
		afx_msg void OnBnClickedModuleAddButton();
		afx_msg void OnBnClickedModuleDeleteButton();
		
		void SetTabName(CString Name);
		
		CWnd* GetParamWnd(int x, int y);
		IValue& GetParamValue(int x, int y);
		void DrawAllParam();
		
		void RedrawParam(int ax = 0, int ay = 0);
		void FocusNextTab();
		void FocusPrevTab();
		
		void FixParam();
		
		void Play(bool bShift, int Note);
		void Stop();
		
		bool ClipboardCopy(CString Text);
		CString ClipboardPaste();
		void Copy(bool bExt);
		void Paste(bool bExt);
		
		template<class... Args> void Log(std::wformat_string<Args...> fmt, Args&& ... args);
	
	public:
		void Cleanup();
};
