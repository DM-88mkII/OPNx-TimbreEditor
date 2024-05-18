#pragma once



#include "afxdialogex.h"
#include "TimbreTab.h"
#include "Timbre.h"
#include <memory>
#include <vector>
#include <format>
#include <xaudio2.h>
#include <mmsystem.h>
#include "martin-finke/Filter.h"
#include <mutex>

#pragma comment(lib, "xaudio2.lib")
#pragma comment(lib, "winmm.lib")



class CModuleTab : public CDialogEx, IXAudio2VoiceCallback
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
		std::mutex m_Mutex;
		std::vector<std::shared_ptr<CTimbre>> m_aCTimbre;
		int m_aaParam[5][15];
		int mx;
		int my;
		int m_iPrev;
		int m_Octave;
		bool m_bRotate;
		int m_iRotate;
		
		IXAudio2* m_pIXAudio2;
		IXAudio2MasteringVoice* m_pIXAudio2MasteringVoice;
		
		HANDLE m_Event;
		WAVEFORMATEX m_Format;
		IXAudio2SourceVoice* m_pIXAudio2SourceVoice;
		XAUDIO2_BUFFER m_Buffer;
		
		int m_iQueue;
		std::vector<int16_t> m_aaQueue[2];
		std::vector<int> m_aOutput;
		
		Filter m_Filter;
	
	protected:
		virtual BOOL OnInitDialog();
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		afx_msg void OnSelchangeTabcontrol(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg void OnBnClickedModuleLoadButton();
		afx_msg void OnBnClickedModuleSaveButton();
		afx_msg void OnBnClickedModuleAddButton();
		afx_msg void OnBnClickedModuleDeleteButton();
		
		void STDMETHODCALLTYPE OnStreamEnd();
		void STDMETHODCALLTYPE OnVoiceProcessingPassEnd();
		void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32 SamplesRequired);
		void STDMETHODCALLTYPE OnBufferEnd(void* pBufferContext);
		void STDMETHODCALLTYPE OnBufferStart(void* pBufferContext);
		void STDMETHODCALLTYPE OnLoopEnd(void* pBufferContext);
		void STDMETHODCALLTYPE OnVoiceError(void* pBufferContext, HRESULT Error);
		void SubmitSourceBuffer();
		
		void SetTabName(CString Name);
		
		CWnd* GetParamWnd(int x, int y);
		IValue& GetParamValue(int x, int y);
		void DrawAllParam();
		
		void RedrawParam(int ax = 0, int ay = 0);
		void FocusNextTab();
		void FocusPrevTab();
		
		void Play(bool bShift, int Note, CString Key);
		void Stop();
		
		bool ClipboardCopy(CString Text);
		CString ClipboardPaste();
		void Copy(bool bShift);
		void Paste();
		void Undo();
		void Rotate();
		
		template<class... Args> void Log(std::wformat_string<Args...> fmt, Args&& ... args);
	
	public:
		void FixParam();
		void RotateCancel();
};
