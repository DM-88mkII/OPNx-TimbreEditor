


#include "pch.h"
#include "framework.h"
#include "TimbreEditor.h"
#include "TimbreEditorDlg.h"
#include "afxdialogex.h"
#include "Value.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



CTimbreEditorDlg::~CTimbreEditorDlg()
{
}



CTimbreEditorDlg::CTimbreEditorDlg(CWnd* pParent /*=nullptr*/)
:CDialogEx(IDD_TIMBREEDITOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}



void CTimbreEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MASTER_TAB, m_CTabCtrl);
}



BEGIN_MESSAGE_MAP(CTimbreEditorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_MASTER_TAB, &CTimbreEditorDlg::OnSelchangeTabcontrol)
END_MESSAGE_MAP()



BOOL CTimbreEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();//call DoDataExchange()
	
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	
	m_CTabCtrl.InsertItem(0, _T("Module"));
	m_CTabCtrl.InsertItem(1, _T("Setting"));
	
	m_CModuleTab.Create(IDD_MODULE_TAB, this);
	m_CSettingTab.Create(IDD_SETTING_TAB, this);
	
	CRect Rect;
	m_CTabCtrl.GetItemRect(0, &Rect);
	m_CModuleTab.SetWindowPos(NULL, Rect.left, Rect.bottom, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	m_CSettingTab.SetWindowPos(NULL, Rect.left, Rect.bottom, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	
	m_CTabCtrl.SetCurFocus(0);
	OnSelchangeTabcontrol(NULL, NULL);
	
	m_CModuleTab.SetFocus();
	
	return FALSE;
}



void CTimbreEditorDlg::OnPaint()
{
	if (IsIconic()){
		CPaintDC dc(this);
		
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int mx = (rect.Width() - cxIcon + 1) / 2;
		int my = (rect.Height() - cyIcon + 1) / 2;
		
		dc.DrawIcon(mx, my, m_hIcon);
	} else {
		CDialogEx::OnPaint();
	}
}



HCURSOR CTimbreEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CTimbreEditorDlg::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message){
		case WM_KEYDOWN:{
			switch (pMsg->wParam){
				case VK_RETURN:{	return TRUE;	}
				case VK_ESCAPE:{	return TRUE;	}
			}
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}



afx_msg void CTimbreEditorDlg::OnSelchangeTabcontrol(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (pResult != NULL) *pResult = 0;
	
	auto iItem = m_CTabCtrl.GetCurSel();
	m_CModuleTab.ShowWindow((iItem == 0)? SW_SHOW: SW_HIDE);
	m_CSettingTab.ShowWindow((iItem == 1)? SW_SHOW: SW_HIDE);
	
	switch (iItem){
		case 0:{
			m_CModuleTab.SetFocus();
			break;
		}
		case 1:{
			m_CSettingTab.SetFocus();
			m_CModuleTab.FixParam();
			m_CModuleTab.RotateCancel();
			break;
		}
	}
}



CSettingTab& CTimbreEditorDlg::GetSettingTab()
{
	return m_CSettingTab;
}
