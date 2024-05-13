#pragma once



#include <xaudio2.h>
#include "FmChip.h"
#include "Value.h"
#include "Intermediate.h"



class CTimbre : public IXAudio2VoiceCallback
{
	public:
		virtual ~CTimbre();
		
		CTimbre(IXAudio2* pIXAudio2);
		
		IValue& GetValue(int x, int y);
	
	private:
		struct Control
		{
			CValue<1, 0, 1> EN;
			CValue<1, 0, 1> FDE;
			
			CValue<1, 0, 7> ALG;
			CValue<1, 0, 7> FB;
			
			CValue<3, 0, 128> KML;
			CValue<3, 0, 128> KMH;
			
			CDummy Dummy;
			
			CValue<3, 0, 127> NUM;
			CValue<3, 0, 127> VOL;
			
			CValue<1, 0, 1> SE;
			CValue<4, -128, 128> KT;
			CValue<4, -999, 999> FDT;
		};
		Control Control;
		
		struct Operator
		{
			CValue<1, 0, 1> EN;
			CValue<1, 0, 1> FDE;
			
			CValue<2, 0, 31> AR;
			CValue<2, 0, 31> DR;
			CValue<2, 0, 31> SR;
			CValue<2, 0, 15> RR;
			CValue<2, 0, 15> SL;
			CValue<3, 0, 127> TL;
			CValue<1, 0, 3> KS;
			CValue<2, 0, 15> MT;
			CValue<1, 0, 7> DT;
			CValue<2, 0, 15> SSG;
			
			CValue<1, 0, 1> SE_FIX;
			CValue<4, -128, 128> SE_KT;
			CValue<4, -999, 999> SE_FDT;
		};
		Operator aOperator[4];
		
		HANDLE m_Event;
		IXAudio2SourceVoice* m_pIXAudio2SourceVoice;
		XAUDIO2_BUFFER m_Buffer;
		int16_t m_aaQueue[2][(48000 / /*ms*/1000) * /*ms*/28 * /*ch*/1];
		int m_iQueue;
		
		int m_Note;
		bool m_bPlay;
		bool m_bKeyOn;
		
		bool m_bFDE;
		bool m_bFDE1;
		bool m_bFDE2;
		bool m_bFDE3;
		bool m_bFDE4;
		
		std::unique_ptr<FmChipBase> m_pFmChip;
		uint32_t output_rate;
		emulated_time output_step;
		emulated_time output_pos;
		
		static const int16_t s_aBlockFNumber[/*Octave*/11 * /*Note*/12];
	
	private:
		void SubmitSourceBuffer();
		
		void STDMETHODCALLTYPE OnStreamEnd();
		void STDMETHODCALLTYPE OnVoiceProcessingPassEnd();
		void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32 SamplesRequired);
		void STDMETHODCALLTYPE OnBufferEnd(void* pBufferContext);
		void STDMETHODCALLTYPE OnBufferStart(void* pBufferContext);
		void STDMETHODCALLTYPE OnLoopEnd(void* pBufferContext);
		void STDMETHODCALLTYPE OnVoiceError(void* pBufferContext, HRESULT Error);
		
		void BlockFNumber(int Note, int RegH, int RegL, int KT, int DT);
		void KeyOn();
	
	public:
		void Play(int Note);
		void Stop();
		
		void SetIntermediate(CIntermediate v);
		CIntermediate GetIntermediate();
};
