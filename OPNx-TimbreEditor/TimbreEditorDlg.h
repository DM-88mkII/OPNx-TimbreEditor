#pragma once



#include <xaudio2.h>
#include <mmsystem.h>

#include "ModuleTab.h"
#include "SettingTab.h"

#pragma comment(lib, "xaudio2.lib")
#pragma comment(lib, "winmm.lib")



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
	IXAudio2* m_pIXAudio2;
	IXAudio2MasteringVoice* m_pIXAudio2MasteringVoice;
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSelchangeTabcontrol(NMHDR* pNMHDR, LRESULT* pResult);
	
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
public:
	IXAudio2* GetXAudio2();
	CSettingTab& GetSettingTab();
};
