﻿#pragma once



#include "FmChip.h"
#include "Value.h"
#include "Intermediate.h"



class CTimbre
{
	public:
		virtual ~CTimbre();
		
		CTimbre(int SampleRate);
		
		IValue& GetValue(int x, int y);
	
	private:
		CDummy Dummy;
		
		struct Control
		{
			CValue<1, 0, 1> EN;
			CValue<1, 0, 1> FDE;
			
			CValue<1, 0, 7> ALG;
			CValue<1, 0, 7> FB;
			
			CValue<3, 0, 999> NUM;
			CValue<3, 0, 128> KML;
			CValue<3, 0, 128> KMH;
			
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
		
		int m_Note;
		bool m_bPlay;
		bool m_bKeyOn;
		
		bool m_bFDE;
		bool m_bFDE1;
		bool m_bFDE2;
		bool m_bFDE3;
		bool m_bFDE4;
		
		uint32_t output_rate;
		emulated_time output_step;
		emulated_time output_pos;
		std::unique_ptr<FmChipBase> m_pFmChip;
	
	private:
		void SubmitSourceBuffer(std::vector<int>& aOutput);
		
		void BlockFNumber(int Note, int RegH, int RegL, int KT, int DT);
		void KeyOn();
	
	public:
		void Play(int Note);
		void Stop();
		
		void OnBufferStart(std::vector<int>& aOutput);
		
		void SetIntermediate(CIntermediate v);
		CIntermediate GetIntermediate();
};
