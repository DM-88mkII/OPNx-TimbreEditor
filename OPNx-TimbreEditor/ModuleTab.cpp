﻿


#include "pch.h"
#include "afxdialogex.h"
#include "TimbreEditor.h"
#include "TimbreEditorDlg.h"
#include "ModuleTab.h"
#include "Intermediate.h"

#include <filesystem>
#include <iostream>
#include <fstream>



IMPLEMENT_DYNAMIC(CModuleTab, CDialogEx)



CModuleTab::~CModuleTab()
{
}



CModuleTab::CModuleTab(CWnd* pParent /*=nullptr*/)
:CDialogEx(IDD_MODULE_TAB, pParent)
,m_aaParam{
	{	IDC_TIMBRE_EN_STATIC,
		IDC_TIMBRE_FDE_STATIC,
		IDC_TIMBRE_ALG_STATIC,
		IDC_TIMBRE_FB_STATIC,
		IDC_TIMBRE_VOID0_STATIC,
		IDC_TIMBRE_VOID1_STATIC,
		IDC_TIMBRE_VOID2_STATIC,
		IDC_TIMBRE_VOID3_STATIC,
		IDC_TIMBRE_VOID4_STATIC,
		IDC_TIMBRE_VOID5_STATIC,
		IDC_TIMBRE_NUM_STATIC,
		IDC_TIMBRE_VOL_STATIC,
		IDC_TIMBRE_SE_STATIC,
		IDC_TIMBRE_KT_STATIC,
		IDC_TIMBRE_DT_STATIC,
	},
	{	IDC_TIMBRE_EN1_STATIC,
		IDC_TIMBRE_FDE1_STATIC,
		IDC_TIMBRE_AR1_STATIC,
		IDC_TIMBRE_DR1_STATIC,
		IDC_TIMBRE_SR1_STATIC,
		IDC_TIMBRE_RR1_STATIC,
		IDC_TIMBRE_SL1_STATIC,
		IDC_TIMBRE_TL1_STATIC,
		IDC_TIMBRE_KS1_STATIC,
		IDC_TIMBRE_MT1_STATIC,
		IDC_TIMBRE_DT1_STATIC,
		IDC_TIMBRE_SSG1_STATIC,
		IDC_TIMBRE_SE_FIX1_STATIC,
		IDC_TIMBRE_SE_KT1_STATIC,
		IDC_TIMBRE_SE_DT1_STATIC,
	},
	{	IDC_TIMBRE_EN2_STATIC,
		IDC_TIMBRE_FDE2_STATIC,
		IDC_TIMBRE_AR2_STATIC,
		IDC_TIMBRE_DR2_STATIC,
		IDC_TIMBRE_SR2_STATIC,
		IDC_TIMBRE_RR2_STATIC,
		IDC_TIMBRE_SL2_STATIC,
		IDC_TIMBRE_TL2_STATIC,
		IDC_TIMBRE_KS2_STATIC,
		IDC_TIMBRE_MT2_STATIC,
		IDC_TIMBRE_DT2_STATIC,
		IDC_TIMBRE_SSG2_STATIC,
		IDC_TIMBRE_SE_FIX2_STATIC,
		IDC_TIMBRE_SE_KT2_STATIC,
		IDC_TIMBRE_SE_DT2_STATIC,
	},
	{	IDC_TIMBRE_EN3_STATIC,
		IDC_TIMBRE_FDE3_STATIC,
		IDC_TIMBRE_AR3_STATIC,
		IDC_TIMBRE_DR3_STATIC,
		IDC_TIMBRE_SR3_STATIC,
		IDC_TIMBRE_RR3_STATIC,
		IDC_TIMBRE_SL3_STATIC,
		IDC_TIMBRE_TL3_STATIC,
		IDC_TIMBRE_KS3_STATIC,
		IDC_TIMBRE_MT3_STATIC,
		IDC_TIMBRE_DT3_STATIC,
		IDC_TIMBRE_SSG3_STATIC,
		IDC_TIMBRE_SE_FIX3_STATIC,
		IDC_TIMBRE_SE_KT3_STATIC,
		IDC_TIMBRE_SE_DT3_STATIC,
	},
	{	IDC_TIMBRE_EN4_STATIC,
		IDC_TIMBRE_FDE4_STATIC,
		IDC_TIMBRE_AR4_STATIC,
		IDC_TIMBRE_DR4_STATIC,
		IDC_TIMBRE_SR4_STATIC,
		IDC_TIMBRE_RR4_STATIC,
		IDC_TIMBRE_SL4_STATIC,
		IDC_TIMBRE_TL4_STATIC,
		IDC_TIMBRE_KS4_STATIC,
		IDC_TIMBRE_MT4_STATIC,
		IDC_TIMBRE_DT4_STATIC,
		IDC_TIMBRE_SSG4_STATIC,
		IDC_TIMBRE_SE_FIX4_STATIC,
		IDC_TIMBRE_SE_KT4_STATIC,
		IDC_TIMBRE_SE_DT4_STATIC,
	},
}
,mx(2)
,my(1)
,m_iPrev(-1)
,m_Octaver(5)
{
	m_CTimbreTab.SetCur(mx, my, false);
}



void CModuleTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MODULE_TAB, m_CTabCtrl);
}



BEGIN_MESSAGE_MAP(CModuleTab, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_MODULE_TAB, &CModuleTab::OnSelchangeTabcontrol)
	ON_BN_CLICKED(IDC_MODULE_LOAD_BUTTON, &CModuleTab::OnBnClickedModuleLoadButton)
	ON_BN_CLICKED(IDC_MODULE_SAVE_BUTTON, &CModuleTab::OnBnClickedModuleSaveButton)
	ON_BN_CLICKED(IDC_MODULE_ADD_BUTTON, &CModuleTab::OnBnClickedModuleAddButton)
	ON_BN_CLICKED(IDC_MODULE_DELETE_BUTTON, &CModuleTab::OnBnClickedModuleDeleteButton)
END_MESSAGE_MAP()



BOOL CModuleTab::OnInitDialog()
{
	CDialogEx::OnInitDialog();//call DoDataExchange()
	
	CRect Rect;
	m_CTabCtrl.GetItemRect(0, &Rect);
	m_CTimbreTab.Create(IDD_TIMBRE_TAB, this);
	m_CTimbreTab.SetWindowPos(NULL, Rect.left, Rect.bottom, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	m_CTimbreTab.ShowWindow(SW_SHOW);
	
	OnBnClickedModuleAddButton();
	
	return FALSE;
}



BOOL CModuleTab::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message){
		case WM_KEYDOWN:{
			auto bControl = (GetKeyState(VK_LCONTROL) < 0) | (GetKeyState(VK_RCONTROL) < 0);
			if (bControl){
				switch (pMsg->wParam){
					case VK_UP:{		return TRUE;	}
					case VK_DOWN:{		return TRUE;	}
					case VK_LEFT:{		FocusPrevTab();	return TRUE;	}
					case VK_RIGHT:{		FocusNextTab();	return TRUE;	}
				}
			} else {
				auto bShift = (GetKeyState(VK_LSHIFT) < 0) | (GetKeyState(VK_RSHIFT) < 0);
				switch (pMsg->wParam){
					case VK_HOME:{		m_Octaver += (m_Octaver < 10)? 1: 0;	Log(_T("o{}"), m_Octaver-1);	return TRUE;	}
					case VK_END:{		m_Octaver -= (m_Octaver >  0)? 1: 0;	Log(_T("o{}"), m_Octaver-1);	return TRUE;	}
					
					case VK_UP:{		RedrawParam(0, -1);	return TRUE;	}
					case VK_DOWN:{		RedrawParam(0, 1);	return TRUE;	}
					case VK_LEFT:{		RedrawParam(-1, 0);	return TRUE;	}
					case VK_RIGHT:{		RedrawParam(1, 0);	return TRUE;	}
					
					case '0':
					case VK_NUMPAD0:{	GetParamValue(mx, my).InputChar('0');	RedrawParam();	return TRUE;	}
					case '1':
					case VK_NUMPAD1:{	GetParamValue(mx, my).InputChar('1');	RedrawParam();	return TRUE;	}
					case '2':
					case VK_NUMPAD2:{	GetParamValue(mx, my).InputChar('2');	RedrawParam();	return TRUE;	}
					case '3':
					case VK_NUMPAD3:{	GetParamValue(mx, my).InputChar('3');	RedrawParam();	return TRUE;	}
					case '4':
					case VK_NUMPAD4:{	GetParamValue(mx, my).InputChar('4');	RedrawParam();	return TRUE;	}
					case '5':
					case VK_NUMPAD5:{	GetParamValue(mx, my).InputChar('5');	RedrawParam();	return TRUE;	}
					case '6':
					case VK_NUMPAD6:{	GetParamValue(mx, my).InputChar('6');	RedrawParam();	return TRUE;	}
					case '7':
					case VK_NUMPAD7:{	GetParamValue(mx, my).InputChar('7');	RedrawParam();	return TRUE;	}
					case '8':
					case VK_NUMPAD8:{	GetParamValue(mx, my).InputChar('8');	RedrawParam();	return TRUE;	}
					case '9':
					case VK_NUMPAD9:{	GetParamValue(mx, my).InputChar('9');	RedrawParam();	return TRUE;	}
					case VK_OEM_MINUS:
					case VK_SUBTRACT:{	GetParamValue(mx, my).InputChar('-');	RedrawParam();	return TRUE;	}
					case VK_SPACE:{		GetParamValue(mx, my).InputChar(' ');	RedrawParam();	return TRUE;	}
					
					case VK_BACK:{		GetParamValue(mx, my).InputBackSpace();	RedrawParam();	return TRUE;	}
					case VK_RETURN:{	GetParamValue(mx, my).InputEnter();		RedrawParam();	return TRUE;	}
					case VK_ESCAPE:{	GetParamValue(mx, my).InputCancel();	RedrawParam();	return TRUE;	}
					
					case VK_PRIOR:{		GetParamValue(mx, my).AddValue((bShift)? 10: 1);	RedrawParam();	return TRUE;	}
					case VK_NEXT:{		GetParamValue(mx, my).AddValue((bShift)? -10: -1);	RedrawParam();	return TRUE;	}
					
					case 'Z':{			Play(bShift, 0);	Log(_T("o{}c"), m_Octaver-1);	return TRUE;	}
					case 'S':{			Play(bShift, 1);	Log(_T("o{}c+"), m_Octaver-1);	return TRUE;	}
					case 'X':{			Play(bShift, 2);	Log(_T("o{}d"), m_Octaver-1);	return TRUE;	}
					case 'D':{			Play(bShift, 3);	Log(_T("o{}d+"), m_Octaver-1);	return TRUE;	}
					case 'C':{			Play(bShift, 4);	Log(_T("o{}e"), m_Octaver-1);	return TRUE;	}
					case 'V':{			Play(bShift, 5);	Log(_T("o{}f"), m_Octaver-1);	return TRUE;	}
					case 'G':{			Play(bShift, 6);	Log(_T("o{}f+"), m_Octaver-1);	return TRUE;	}
					case 'B':{			Play(bShift, 7);	Log(_T("o{}g"), m_Octaver-1);	return TRUE;	}
					case 'H':{			Play(bShift, 8);	Log(_T("o{}g+"), m_Octaver-1);	return TRUE;	}
					case 'N':{			Play(bShift, 9);	Log(_T("o{}a"), m_Octaver-1);	return TRUE;	}
					case 'J':{			Play(bShift, 10);	Log(_T("o{}a+"), m_Octaver-1);	return TRUE;	}
					case 'M':{			Play(bShift, 11);	Log(_T("o{}b"), m_Octaver-1);	return TRUE;	}
					case VK_OEM_COMMA:{	Play(bShift, 12);	Log(_T("o{}c"), m_Octaver);		return TRUE;	}
					
					// nop
					case VK_MULTIPLY:
					case VK_ADD:
					case VK_SEPARATOR:
					case VK_DECIMAL:
					case VK_DIVIDE:
					case VK_OEM_PLUS:
					case VK_OEM_PERIOD:
					case VK_OEM_1:
					case VK_OEM_2:
					case VK_OEM_3:
					case VK_OEM_4:
					case VK_OEM_5:
					case VK_OEM_6:
					case VK_OEM_7:
					case VK_OEM_8:
					case VK_OEM_102:
					case 'Q':
					case 'W':
					case 'E':
					case 'R':
					case 'T':
					case 'Y':
					case 'U':
					case 'I':
					case 'O':
					case 'P':
					case 'A':
					case 'F':
					case 'K':
					case 'L':
					case '.':
					{
						return TRUE;
					}
				}
			}
			break;
		}
		case WM_KEYUP:{
			{	// 
				switch (pMsg->wParam){
					case 'Z':
					case 'S':
					case 'X':
					case 'D':
					case 'C':
					case 'V':
					case 'G':
					case 'B':
					case 'H':
					case 'N':
					case 'J':
					case 'M':
					case VK_OEM_COMMA:
					{
						Stop();
						return TRUE;
					}
				}
			}
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}



afx_msg void CModuleTab::OnSelchangeTabcontrol(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (pResult != NULL) *pResult = 0;
	
	auto nItem = m_CTabCtrl.GetItemCount();
	if (nItem > 0){
		m_CTimbreTab.RedrawWindow();
		
		if (m_iPrev >= 0 && m_iPrev < nItem){
			auto& rValue = m_aCTimbre[m_iPrev]->GetValue(mx, my);
			if (rValue.IsEditing()){
				rValue.InputEnter();
				RedrawParam();
			}
		}
		
		{	// 
			auto iItem = m_CTabCtrl.GetCurSel();
			// todo
			m_iPrev = iItem;
		}
	}
	DrawAllParam();
	SetFocus();
}



void CModuleTab::OnBnClickedModuleLoadButton()
{
	CFileDialog FileDialog(true, _T("opn_timbre"), _T("*.opn_timbre"), OFN_FILEMUSTEXIST | OFN_EXTENSIONDIFFERENT);
	if (FileDialog.DoModal() == IDOK){
		SetTabName(FileDialog.GetFileTitle());
		
		{	// 
			nlohmann::json j;
			
			std::filesystem::path Path = (LPCTSTR)FileDialog.GetFileTitle();
			auto Extension = Path.extension();
			if (Extension.empty()) Path += ".opn_timbre";
			
			std::ifstream File;
			try {
				File.open(Path.c_str(), std::ios::in);
				File >> j;
				
				auto v = j.get<CIntermediate>();
				auto iItem = m_CTabCtrl.GetCurSel();
				m_aCTimbre[iItem]->SetIntermediate(v);
				DrawAllParam();
				Log(_T(""));
			}
			catch (...){
				Log(_T("Load Error"));
			}
			File.close();
		}
	}
	SetFocus();
}



void CModuleTab::OnBnClickedModuleSaveButton()
{
	CFileDialog FileDialog(false, _T("opn_timbre"), _T("*.opn_timbre"), OFN_OVERWRITEPROMPT | OFN_EXTENSIONDIFFERENT);
	if (FileDialog.DoModal() == IDOK){
		SetTabName(FileDialog.GetFileTitle());
		
		{	// 
			auto iItem = m_CTabCtrl.GetCurSel();
			auto v = m_aCTimbre[iItem]->GetIntermediate();
			nlohmann::json j = v;
			
			std::filesystem::path Path = (LPCTSTR)FileDialog.GetFileTitle();
			auto Extension = Path.extension();
			if (Extension.empty()) Path += ".opn_timbre";
			
			std::ofstream File;
			File.open(Path.c_str(), std::ios::out);
			File << j << std::endl;
			File.close();
		}
	}
	SetFocus();
}



void CModuleTab::OnBnClickedModuleAddButton()
{
	if (m_CTabCtrl.GetItemCount() > 0) FixParam();
	
	auto pCTimbreEditorDlg = (CTimbreEditorDlg*)GetTopLevelParent();
	
	auto iItem = m_CTabCtrl.GetCurSel()+1;
	m_aCTimbre.insert(m_aCTimbre.begin() + iItem, std::make_shared<CTimbre>(pCTimbreEditorDlg->GetXAudio2()));
	m_CTabCtrl.InsertItem(iItem, _T("Init"));
	
	m_CTabCtrl.SetCurFocus(iItem);
	OnSelchangeTabcontrol(NULL, NULL);
}



void CModuleTab::OnBnClickedModuleDeleteButton()
{
	auto nItem = m_CTabCtrl.GetItemCount();
	if (nItem > 1){
		FixParam();
		
		auto iItem = m_CTabCtrl.GetCurSel();
		m_aCTimbre.erase(m_aCTimbre.begin() + iItem);
		m_CTabCtrl.DeleteItem(iItem);
		iItem -= (iItem < (nItem-1))? 0: 1;
		
		m_CTabCtrl.SetCurFocus(iItem);
		OnSelchangeTabcontrol(NULL, NULL);
	}
}



void CModuleTab::SetTabName(CString Name)
{
	TCITEM Item;
	Item.mask = TCIF_TEXT;
	Item.cchTextMax = Name.GetLength()+1;
	Item.pszText = (LPWSTR)(LPCTSTR)Name;
	
	auto iItem = m_CTabCtrl.GetCurSel();
	m_CTabCtrl.SetItem(iItem, &Item);
	
	// For some reason, it needs to be redrawn.
	m_CTimbreTab.ShowWindow(SW_HIDE);
	m_CTimbreTab.ShowWindow(SW_SHOW);
	//m_CTimbreTab.RedrawWindow();	// This is not good enough.
}



CWnd* CModuleTab::GetParamWnd(int x, int y)
{
	return m_CTimbreTab.GetDlgItem(m_aaParam[y][x]);
}



IValue& CModuleTab::GetParamValue(int x, int y)
{
	auto iItem = m_CTabCtrl.GetCurSel();
	return m_aCTimbre[iItem]->GetValue(x, y);
}



void CModuleTab::DrawAllParam()
{
	for (int y = 0; y < 5; ++y){
		for (int x = 0; x < 15; ++x){
			auto pCWnd = GetParamWnd(x, y);
			if (pCWnd != nullptr){
				pCWnd->SetWindowText((LPCTSTR)GetParamValue(x, y).GetText());
			}
		}
	}
}



void CModuleTab::FocusNextTab()
{
	FixParam();
	
	auto nItem = m_CTabCtrl.GetItemCount();
	auto iItem = m_CTabCtrl.GetCurSel();
	++iItem;
	iItem = (iItem < nItem)? iItem: 0;
	m_CTabCtrl.SetCurFocus(iItem);
}



void CModuleTab::FocusPrevTab()
{
	FixParam();
	
	auto nItem = m_CTabCtrl.GetItemCount();
	auto iItem = m_CTabCtrl.GetCurSel();
	--iItem;
	iItem = (iItem < 0)? nItem-1: iItem;
	m_CTabCtrl.SetCurFocus(iItem);
}



void CModuleTab::RedrawParam(int ax, int ay)
{
	auto pCWndOld = GetParamWnd(mx, my);
	auto& rValueOld = GetParamValue(mx, my);
	
	if ((ax != 0 || ay != 0) && rValueOld.IsEditing()) rValueOld.InputEnter();
	
	mx += ax;
	mx = (mx <  0)?  0: mx;
	mx = (mx > 14)? 14: mx;
	
	my += ay;
	my = (my < 0)? 0: my;
	my = (my > 4)? 4: my;
	
	auto pCWndNew = GetParamWnd(mx, my);
	auto& rValueNew = GetParamValue(mx, my);
	
	m_CTimbreTab.SetCur(mx, my, rValueNew.IsEditing());
	
	if (pCWndOld != nullptr) pCWndOld->SetWindowText((LPCTSTR)rValueOld.GetText());
	if (pCWndNew != nullptr) pCWndNew->SetWindowText((LPCTSTR)rValueNew.GetText());
}



void CModuleTab::FixParam()
{
	auto& rValue = GetParamValue(mx, my);
	if (rValue.IsEditing()){
		rValue.InputEnter();
		RedrawParam();
	}
}



void CModuleTab::Play(bool bShift, int Note)
{
	if (bShift){
		for (auto CTimbre : m_aCTimbre) CTimbre->Play((m_Octaver * 12) + Note);
	} else {
		auto iItem = m_CTabCtrl.GetCurSel();
		m_aCTimbre[iItem]->Play((m_Octaver * 12) + Note);
	}
}



void CModuleTab::Stop()
{
	for (auto CTimbre : m_aCTimbre) CTimbre->Stop();
}



template<class... Args> void CModuleTab::Log(std::wformat_string<Args...> fmt, Args&& ... args)
{
	auto Log = GetDlgItem(IDC_MODULE_LOG);
	Log->SetWindowText((LPCTSTR)std::format(fmt, std::forward<Args>(args)...).c_str());
}



void CModuleTab::Cleanup()
{
	m_aCTimbre.clear();
}