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
	{	// 
		if (m_pIXAudio2SourceVoice != nullptr){
			m_pIXAudio2SourceVoice->Stop();
			m_pIXAudio2SourceVoice->DestroyVoice();
		}
		CloseHandle(m_Event);
	}
	
	{	// 
		if (m_pIXAudio2MasteringVoice) m_pIXAudio2MasteringVoice->DestroyVoice();
		if (m_pIXAudio2) m_pIXAudio2->Release();
		CoUninitialize();
	}
}



CModuleTab::CModuleTab(CWnd* pParent /*=nullptr*/)
:CDialogEx(IDD_MODULE_TAB, pParent)
,m_aaParam{
	{	IDC_TIMBRE_EN_STATIC,
		IDC_TIMBRE_FDE_STATIC,
		IDC_TIMBRE_ALG_STATIC,
		IDC_TIMBRE_FB_STATIC,
		IDC_TIMBRE_NUM_STATIC,
		IDC_TIMBRE_KML_STATIC,
		IDC_TIMBRE_KMH_STATIC,
		IDC_TIMBRE_VOID2_STATIC,
		IDC_TIMBRE_VOID3_STATIC,
		IDC_TIMBRE_VOID4_STATIC,
		IDC_TIMBRE_VOID5_STATIC,
		IDC_TIMBRE_VOID6_STATIC,
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
		IDC_TIMBRE_SE_FDT1_STATIC,
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
		IDC_TIMBRE_SE_FDT2_STATIC,
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
		IDC_TIMBRE_SE_FDT3_STATIC,
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
		IDC_TIMBRE_SE_FDT4_STATIC,
	},
}
,mx(2)
,my(1)
,m_iPrev(-1)
,m_Octave(5)
,m_pIXAudio2(nullptr)
,m_pIXAudio2MasteringVoice(nullptr)
,m_Event(CreateEvent(NULL, FALSE, FALSE, NULL))
,m_Format{0}
,m_pIXAudio2SourceVoice(nullptr)
,m_Buffer{0}
,m_iQueue(0)
{
	m_CTimbreTab.SetCur(mx, my, false);
	
	{	// 
		HRESULT ret;
		ret = CoInitializeEx(NULL, COINIT_MULTITHREADED);
		if (FAILED(ret)) OutputDebugStringA("CoInitializeEx.Error\n");
		ret = XAudio2Create(&m_pIXAudio2);
		if (FAILED(ret)) OutputDebugStringA("XAudio2Create.Error\n");
		ret = m_pIXAudio2->CreateMasteringVoice(&m_pIXAudio2MasteringVoice);
		if (FAILED(ret)) OutputDebugStringA("CreateMasteringVoice.Error\n");
	}
	
	{	// 
		auto SynthesizeFreq = theApp.GetValue(_T("SynthesizeFreq"), 0);
		auto& rCSettingTab = GetSettingTab();
		
		m_Format.wFormatTag = WAVE_FORMAT_PCM;
		m_Format.nChannels = 1;
		m_Format.nSamplesPerSec = rCSettingTab.GetSynthesizeFreq((CSettingTab::ESynthesizeFreq)SynthesizeFreq);
		m_Format.wBitsPerSample = sizeof(m_aaQueue[0][0]) * 8;
		m_Format.cbSize = 0;
		m_Format.nBlockAlign = (m_Format.wBitsPerSample * m_Format.nChannels) / 8;
		m_Format.nAvgBytesPerSec = m_Format.nSamplesPerSec * m_Format.nBlockAlign;
		
		{	// 
			auto Latency = theApp.GetValue(_T("Latency"), 1);
			auto Size = ((m_Format.nSamplesPerSec * /*ms*/Latency) / /*ms*/1000) * /*ch*/m_Format.nChannels;
			m_aaQueue[0].resize(Size);
			m_aaQueue[1].resize(Size);
			m_aOutput.resize(Size * m_Format.nChannels);
		}
		
		HRESULT ret;
		ret = m_pIXAudio2->CreateSourceVoice(&m_pIXAudio2SourceVoice, &m_Format, 0, XAUDIO2_DEFAULT_FREQ_RATIO, this);
		if (FAILED(ret)){
			OutputDebugStringA("CreateSourceVoice.Error\n");
			m_pIXAudio2SourceVoice = nullptr;
			return;
		}
		
		ret = m_pIXAudio2SourceVoice->Start();
		if (FAILED(ret)) OutputDebugStringA("Start.Error\n");
		
		SubmitSourceBuffer();
	}
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
			auto bShift = (GetKeyState(VK_LSHIFT) < 0) | (GetKeyState(VK_RSHIFT) < 0);
			auto bControl = (GetKeyState(VK_LCONTROL) < 0) | (GetKeyState(VK_RCONTROL) < 0);
			if (bControl){
				switch (pMsg->wParam){
					case VK_UP:{		return TRUE;	}
					case VK_DOWN:{		return TRUE;	}
					case VK_LEFT:{		FocusPrevTab();	return TRUE;	}
					case VK_RIGHT:{		FocusNextTab();	return TRUE;	}
					
					case 'C':{			Copy(bShift);	return TRUE;	}
					case 'V':{			Paste();		return TRUE;	}
					case 'Z':{			Undo();			return TRUE;	}
					
					case 'O':{			OnBnClickedModuleLoadButton();	return TRUE;	}
					case 'S':{			OnBnClickedModuleSaveButton();	return TRUE;	}
					
					case 'R':{			Rotate();	return TRUE;	}
					
					case VK_INSERT:{	OnBnClickedModuleAddButton();	return TRUE;	}
					case VK_DELETE:{	OnBnClickedModuleDeleteButton();return TRUE;	}
				}
			} else {
				switch (pMsg->wParam){
					case VK_HOME:{		m_Octave += (m_Octave < 10)? 1: 0;	Log(_T("o{}"), m_Octave-1);	return TRUE;	}
					case VK_END:{		m_Octave -= (m_Octave >  0)? 1: 0;	Log(_T("o{}"), m_Octave-1);	return TRUE;	}
					
					case VK_INSERT:{	VolumeUp();		return TRUE;	}
					case VK_DELETE:{	VolumeDown();	return TRUE;	}
					
					case VK_UP:{		MoveCursor(0, -1);	return TRUE;	}
					case VK_DOWN:{		MoveCursor(0, 1);	return TRUE;	}
					case VK_LEFT:{		MoveCursor(-1, 0);	return TRUE;	}
					case VK_RIGHT:{		MoveCursor(1, 0);	return TRUE;	}
					
					case '0':
					case VK_NUMPAD0:{	if (!m_bRotate){	GetParamValue(mx, my).InputChar('0');	RedrawParam(mx, my);	}	return TRUE;	}
					case '1':
					case VK_NUMPAD1:{	if (!m_bRotate){	GetParamValue(mx, my).InputChar('1');	RedrawParam(mx, my);	}	return TRUE;	}
					case '2':
					case VK_NUMPAD2:{	if (!m_bRotate){	GetParamValue(mx, my).InputChar('2');	RedrawParam(mx, my);	}	return TRUE;	}
					case '3':
					case VK_NUMPAD3:{	if (!m_bRotate){	GetParamValue(mx, my).InputChar('3');	RedrawParam(mx, my);	}	return TRUE;	}
					case '4':
					case VK_NUMPAD4:{	if (!m_bRotate){	GetParamValue(mx, my).InputChar('4');	RedrawParam(mx, my);	}	return TRUE;	}
					case '5':
					case VK_NUMPAD5:{	if (!m_bRotate){	GetParamValue(mx, my).InputChar('5');	RedrawParam(mx, my);	}	return TRUE;	}
					case '6':
					case VK_NUMPAD6:{	if (!m_bRotate){	GetParamValue(mx, my).InputChar('6');	RedrawParam(mx, my);	}	return TRUE;	}
					case '7':
					case VK_NUMPAD7:{	if (!m_bRotate){	GetParamValue(mx, my).InputChar('7');	RedrawParam(mx, my);	}	return TRUE;	}
					case '8':
					case VK_NUMPAD8:{	if (!m_bRotate){	GetParamValue(mx, my).InputChar('8');	RedrawParam(mx, my);	}	return TRUE;	}
					case '9':
					case VK_NUMPAD9:{	if (!m_bRotate){	GetParamValue(mx, my).InputChar('9');	RedrawParam(mx, my);	}	return TRUE;	}
					case VK_OEM_MINUS:
					case VK_SUBTRACT:{	if (!m_bRotate){	GetParamValue(mx, my).InputChar('-');	RedrawParam(mx, my);	}	return TRUE;	}
					case VK_SPACE:{		if (!m_bRotate){	GetParamValue(mx, my).InputChar(' ');	RedrawParam(mx, my);	}	return TRUE;	}
					
					case VK_BACK:{		if (!m_bRotate){	GetParamValue(mx, my).InputBackSpace();	RedrawParam(mx, my);	}	return TRUE;	}
					case VK_RETURN:{	if (!m_bRotate){	GetParamValue(mx, my).InputEnter();		RedrawParam(mx, my);	}	return TRUE;	}
					case VK_ESCAPE:{	if (!m_bRotate){	GetParamValue(mx, my).InputCancel();	RedrawParam(mx, my);	} else {	RotateCancel();	}	return TRUE;	}
					
					case VK_PRIOR:{		if (!m_bRotate){	AddParamValue(mx, my, (bShift)?  4:  1);	RedrawParam(mx, my);	}	return TRUE;	}
					case VK_NEXT:{		if (!m_bRotate){	AddParamValue(mx, my, (bShift)? -4: -1);	RedrawParam(mx, my);	}	return TRUE;	}
					
					case 'Z':{			Play(bShift, 0, _T("c"));	return TRUE;	}
					case 'S':{			Play(bShift, 1, _T("c+"));	return TRUE;	}
					case 'X':{			Play(bShift, 2, _T("d"));	return TRUE;	}
					case 'D':{			Play(bShift, 3, _T("d+"));	return TRUE;	}
					case 'C':{			Play(bShift, 4, _T("e"));	return TRUE;	}
					case 'V':{			Play(bShift, 5, _T("f"));	return TRUE;	}
					case 'G':{			Play(bShift, 6, _T("f+"));	return TRUE;	}
					case 'B':{			Play(bShift, 7, _T("g"));	return TRUE;	}
					case 'H':{			Play(bShift, 8, _T("g+"));	return TRUE;	}
					case 'N':{			Play(bShift, 9, _T("a"));	return TRUE;	}
					case 'J':{			Play(bShift, 10, _T("a+"));	return TRUE;	}
					case 'M':{			Play(bShift, 11, _T("b"));	return TRUE;	}
					case VK_OEM_COMMA:{	Play(bShift, 12, _T("c"));	return TRUE;	}
					
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
				RedrawParam(mx, my);
			}
		}
		
		{	// 
			m_iPrev = m_CTabCtrl.GetCurSel();
		}
	}
	DrawAllParam();
	SetFocus();
}



void CModuleTab::OnBnClickedModuleLoadButton()
{
	FixParam();
	
	CFileDialog FileDialog(true, _T("opnx"), _T("*.opnx"), OFN_FILEMUSTEXIST | OFN_EXTENSIONDIFFERENT);
	if (FileDialog.DoModal() == IDOK){
		SetTabName(FileDialog.GetFileTitle());
		
		{	// 
			nlohmann::json j;
			
			std::filesystem::path Path = (LPCTSTR)FileDialog.GetFileTitle();
			auto Extension = Path.extension();
			if (Extension.empty()) Path += ".opnx";
			
			std::ifstream File;
			try {
				File.open(Path.c_str(), std::ios::in);
				File >> j;
				
				auto v = j.get<CIntermediate>();
				auto iItem = m_CTabCtrl.GetCurSel();
				m_aCTimbre[iItem]->SetIntermediate(v);
				DrawAllParam();
				
				Log(_T("Load"));
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
	FixParam();
	
	CFileDialog FileDialog(false, _T("opnx"), _T("*.opnx"), OFN_OVERWRITEPROMPT | OFN_EXTENSIONDIFFERENT);
	if (FileDialog.DoModal() == IDOK){
		SetTabName(FileDialog.GetFileTitle());
		
		{	// 
			auto iItem = m_CTabCtrl.GetCurSel();
			auto v = m_aCTimbre[iItem]->GetIntermediate();
			nlohmann::json j = v;
			
			std::filesystem::path Path = (LPCTSTR)FileDialog.GetFileTitle();
			auto Extension = Path.extension();
			if (Extension.empty()) Path += ".opnx";
			
			std::ofstream File;
			File.open(Path.c_str(), std::ios::out);
			File << j << std::endl;
			File.close();
			
			Log(_T("Save"));
		}
	}
	SetFocus();
}



void CModuleTab::OnBnClickedModuleAddButton()
{
	if (m_CTabCtrl.GetItemCount() > 0) FixParam();
	
	auto iItem = m_CTabCtrl.GetCurSel()+1;
	m_Mutex.lock();
	m_aCTimbre.insert(m_aCTimbre.begin() + iItem, std::make_shared<CTimbre>(m_Format.nSamplesPerSec));
	m_Mutex.unlock();
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
		m_Mutex.lock();
		m_aCTimbre.erase(m_aCTimbre.begin() + iItem);
		m_Mutex.unlock();
		m_CTabCtrl.DeleteItem(iItem);
		iItem -= (iItem < (nItem-1))? 0: 1;
		
		m_CTabCtrl.SetCurFocus(iItem);
		OnSelchangeTabcontrol(NULL, NULL);
	}
}



void STDMETHODCALLTYPE CModuleTab::OnStreamEnd()
{
}
void STDMETHODCALLTYPE CModuleTab::OnVoiceProcessingPassEnd()
{
}
void STDMETHODCALLTYPE CModuleTab::OnVoiceProcessingPassStart(UINT32 SamplesRequired)
{
}
void STDMETHODCALLTYPE CModuleTab::OnBufferEnd(void* pBufferContext)
{
}
void STDMETHODCALLTYPE CModuleTab::OnBufferStart(void* pBufferContext)
{
	std::fill(m_aOutput.begin(), m_aOutput.end(), 0);
	
	m_Mutex.lock();
	for (auto CTimbre : m_aCTimbre) CTimbre->OnBufferStart(m_aOutput);
	m_Mutex.unlock();
	
	SubmitSourceBuffer();
}
void STDMETHODCALLTYPE CModuleTab::OnLoopEnd(void* pBufferContext)
{
}
void STDMETHODCALLTYPE CModuleTab::OnVoiceError(void* pBufferContext, HRESULT Error)
{
}



void CModuleTab::SubmitSourceBuffer()
{
	int l = 32767;
	auto p = m_aaQueue[m_iQueue].data();
	for (auto& v : m_aOutput){
		v = (int)m_Filter.process(v * m_Volume);
		*p++ = (v > l)? l: (v < -l)? -l: v;
	}
	
	m_Buffer.AudioBytes = (UINT)(m_aaQueue[0].size() * sizeof(m_aaQueue[0][0]));
	m_Buffer.pAudioData = (const BYTE*)m_aaQueue[m_iQueue].data();
	
	HRESULT ret;
	ret = m_pIXAudio2SourceVoice->SubmitSourceBuffer(&m_Buffer);
	if (FAILED(ret)) OutputDebugStringA("SubmitSourceBuffer.Error\n");
	
	m_iQueue ^= 1;
}



CSettingTab& CModuleTab::GetSettingTab()
{
	auto pCTimbreEditorDlg = (CTimbreEditorDlg*)GetTopLevelParent();
	return pCTimbreEditorDlg->GetSettingTab();
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



void CModuleTab::AddParamValue(int x, int y, int Add)
{
	if (GetParamValue(mx, my).AddValue(Add)){
		auto& rCSettingTab = GetSettingTab();
		if (rCSettingTab.IsSLTLLink() && mx == /*SL*/6 && my >= 1 && my <= 4){
			GetParamValue(/*TL*/7, my).AddValue(-Add * 4);
			RedrawParam(/*TL*/7, my);
		}
	}
}



void CModuleTab::DrawAllParam()
{
	for (int y = 0; y < _countof(m_aaParam); ++y){
		for (int x = 0; x < _countof(m_aaParam[0]); ++x){
			auto pCWnd = GetParamWnd(x, y);
			if (pCWnd != nullptr){
				pCWnd->SetWindowText((LPCTSTR)GetParamValue(x, y).GetText());
			}
		}
	}
	
	{	// 
		auto& rValueNew = GetParamValue(2, 0);
		auto ALG = rValueNew.GetValue();
		m_CTimbreTab.SetPicture(ALG);
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



void CModuleTab::MoveCursor(int ax, int ay)
{
	auto ox = mx;
	auto oy = my;
	
	{	// 
		auto& rValueOld = GetParamValue(mx, my);
		
		if ((ax != 0 || ay != 0) && rValueOld.IsEditing()) rValueOld.InputEnter();
		
		mx += ax;
		mx = (mx < 0)? 0: mx;
		mx = (mx < _countof(m_aaParam[0]))? mx: _countof(m_aaParam[0])-1;
		
		my += ay;
		my = (my < 0)? 0: my;
		my = (my < _countof(m_aaParam))? my: _countof(m_aaParam)-1;
	}
	
	RedrawParam(ox, oy);
	RedrawParam(mx, my);
}



void CModuleTab::RedrawParam(int x, int y)
{
	auto& rValue = GetParamValue(x, y);
	m_CTimbreTab.SetCur(mx, my, rValue.IsEditing());
	
	auto pCWnd = GetParamWnd(x, y);
	if (pCWnd != nullptr) pCWnd->SetWindowText((LPCTSTR)rValue.GetText());
	
	if (x == 2 && y == 0){
		auto ALG = rValue.GetValue();
		m_CTimbreTab.SetPicture(ALG);
	}
}



void CModuleTab::FixParam()
{
	auto& rValue = GetParamValue(mx, my);
	if (rValue.IsEditing()){
		rValue.InputEnter();
		RedrawParam(mx, my);
	}
}



void CModuleTab::VolumeUp()
{
	auto& rCSettingTab = GetSettingTab();
	rCSettingTab.SetVolume(rCSettingTab.GetVolume() + 1);
	Log(_T("Volume x{:1.1f}"), rCSettingTab.GetVolume() * 0.1);
}



void CModuleTab::VolumeDown()
{
	auto& rCSettingTab = GetSettingTab();
	rCSettingTab.SetVolume(rCSettingTab.GetVolume() - 1);
	Log(_T("Volume x{:1.1f}"), rCSettingTab.GetVolume() * 0.1);
}



void CModuleTab::Play(bool bShift, int Note, CString Key)
{
	FixParam();
	
	Note += (m_Octave * 12);
	
	Log(_T("o{}{}({})"), ((Note / 12) - 1), (LPCTSTR)Key, Note);
	
	{	// 
		auto& rCSettingTab = GetSettingTab();
		m_Filter.setFilterMode(rCSettingTab.GetFilterMode());
		m_Filter.setCutoff(rCSettingTab.GetCutoff());
		m_Filter.setResonance(rCSettingTab.GetResonance());
		m_Filter.setDCCut(rCSettingTab.IsDCCut());
		m_Filter.setDCCutRate(rCSettingTab.GetDCCutRate());
		m_Volume = rCSettingTab.GetVolume() * 0.1;
		
		bShift ^= rCSettingTab.IsSwapPreview();
		if (bShift){
			for (auto CTimbre : m_aCTimbre) CTimbre->Play(Note);
		} else {
			auto iItem = m_CTabCtrl.GetCurSel();
			m_aCTimbre[iItem]->Play(Note);
		}
	}
}



void CModuleTab::Stop()
{
	for (auto CTimbre : m_aCTimbre) CTimbre->Stop();
}



bool CModuleTab::ClipboardCopy(CString Text)
{
	if (OpenClipboard() == FALSE) return false;
	if (EmptyClipboard() == FALSE) return false;
	
	{	// 
		auto sText = (Text.GetLength() + 1) * sizeof(TCHAR);
		auto hText = GlobalAlloc(GMEM_MOVEABLE, sText);
		auto pText = (hText != NULL)? GlobalLock(hText): NULL;
		if (pText != NULL) memcpy_s(pText, sText, Text.LockBuffer(), sText);
		if (hText != NULL) GlobalUnlock(hText);
		Text.UnlockBuffer();
		
		auto Format = (sizeof(TCHAR) == sizeof(WCHAR))? CF_UNICODETEXT: CF_TEXT;
		auto bResult = (SetClipboardData(Format, hText) != NULL);
		CloseClipboard();
		return bResult;
	}
}



CString CModuleTab::ClipboardPaste()
{
	COleDataObject DataObject;
	auto Format = (sizeof(TCHAR) == sizeof(WCHAR))? CF_UNICODETEXT: CF_TEXT;
	if (DataObject.AttachClipboard() && DataObject.IsDataAvailable(Format)){
		auto hText = DataObject.GetGlobalData(Format);
		auto pText = (LPCTSTR)GlobalLock(hText);
		CString Text(pText);
		GlobalUnlock(hText);
		
		return std::move(Text);
	}
	return std::move(CString());
}



void CModuleTab::Copy(bool bShift)
{
	FixParam();
	
	auto iItem = m_CTabCtrl.GetCurSel();
	auto v = m_aCTimbre[iItem]->GetIntermediate();
	CString Text;
	
	auto& rCSettingTab = GetSettingTab();
	bShift ^= rCSettingTab.IsSwapCopyFormat();
	if (bShift){
		v.ToFormat(rCSettingTab.GetFormatType(), Text);
	} else {
		nlohmann::json j = v;
		Text = CString(j.dump().c_str());
	}
	if (ClipboardCopy(Text)){
		Log(_T("Copy"));
	} else {
		Log(_T("Copy Error"));
	}
}



void CModuleTab::Paste()
{
	FixParam();
	
	CIntermediate v;
	auto Text = ClipboardPaste();
	auto Result = false;
	
	for (int EFormatType = CSettingTab::EFormatType::Num; --EFormatType >= 0 && !Result;){
		try {
			v.FromFormat((CSettingTab::EFormatType)EFormatType, Text);
			Result = true;
			
			auto& rCSettingTab = GetSettingTab();
			if (rCSettingTab.IsAutoCopyFormat()){
				rCSettingTab.SetFormatType((CSettingTab::EFormatType)EFormatType);
			}
		}
		catch (...){}
	}
	if (!Result){
		try {
			auto j = nlohmann::json::parse(CStringA(Text).GetBuffer());
			v = j.get<CIntermediate>();
			Result = true;
		}
		catch (...){}
	}
	if (Result){
		auto iItem = m_CTabCtrl.GetCurSel();
		m_aCTimbre[iItem]->SetIntermediate(v);
		DrawAllParam();
		
		Log(_T("Paste"));
	} else {
		Log(_T("Paste Error"));
	}
}



void CModuleTab::Undo()
{
	FixParam();
	
	auto& rValueOld = GetParamValue(mx, my);
	rValueOld.Undo();
	
	RedrawParam(mx, my);
}



void CModuleTab::Rotate()
{
	auto iRotate = (my-1);
	if (iRotate >= 0){
		if (!m_bRotate){
			FixParam();
			
			m_bRotate = true;
			m_iRotate = iRotate;
		} else {
			if (m_iRotate != iRotate){
				auto iItem = m_CTabCtrl.GetCurSel();
				auto v = m_aCTimbre[iItem]->GetIntermediate();
				
				auto t = v.aOperator[m_iRotate];
				if (m_iRotate < iRotate){
					for (int i = m_iRotate; i < iRotate; ++i) v.aOperator[i] = v.aOperator[i+1];
				} else {
					for (int i = m_iRotate; i > iRotate; --i) v.aOperator[i] = v.aOperator[i-1];
				}
				v.aOperator[iRotate] = t;
				
				m_aCTimbre[iItem]->SetIntermediate(v);
			}
			
			m_bRotate = false;
		}
	}
	
	m_CTimbreTab.SetOperator(m_iRotate, m_bRotate);
	DrawAllParam();
}



void CModuleTab::RotateCancel()
{
	if (m_bRotate){
		m_bRotate = false;
		
		m_CTimbreTab.SetOperator(m_iRotate, m_bRotate);
		DrawAllParam();
	}
}



template<class... Args> void CModuleTab::Log(std::wformat_string<Args...> fmt, Args&& ... args)
{
	auto Log = GetDlgItem(IDC_MODULE_LOG);
	Log->SetWindowText((LPCTSTR)std::format(fmt, std::forward<Args>(args)...).c_str());
}
