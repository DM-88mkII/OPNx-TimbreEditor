﻿


#include "pch.h"
#include <cmath>
#include <random>
#include <memory>
#include "Timbre.h"



CTimbre::~CTimbre()
{
}



CTimbre::CTimbre(int SampleRate)
:m_bPlay(false)
,m_bKeyOn(true)
,output_rate(SampleRate)
,output_step(0x100000000ull / output_rate)
,output_pos(0)
,m_pFmChip(std::make_unique<FmChip<ymfm::ym2203>>(output_rate * 72, EChipType::YM2203))
{
	{	// 
		Control.EN.SetValue(1);
		Control.FDE.SetValue(1);
		Control.ALG.SetValue(0);
		Control.FB.SetValue(0);
		Control.NUM.SetValue(0);
		Control.KML.SetValue(0);
		Control.KMH.SetValue(128);
		Control.SE.SetValue(0);
		Control.KT.SetValue(0);
		Control.FDT.SetValue(0);
		
		for (int i = 0; i < 4; ++i){
			aOperator[i].EN.SetValue(1);
			aOperator[i].FDE.SetValue(1);
			
			aOperator[i].AR.SetValue(31);
			aOperator[i].DR.SetValue(0);
			aOperator[i].SR.SetValue(0);
			aOperator[i].RR.SetValue(15);
			aOperator[i].SL.SetValue(0);
			aOperator[i].KS.SetValue(0);
			aOperator[i].MT.SetValue(1);
			aOperator[i].DT.SetValue(0);
			aOperator[i].SSG.SetValue(0);
			
			aOperator[i].SE_FIX.SetValue(0);
			aOperator[i].SE_KT.SetValue(0);
			aOperator[i].SE_FDT.SetValue(0);
		}
		aOperator[0].TL.SetValue(36);
		aOperator[1].TL.SetValue(36);
		aOperator[2].TL.SetValue(36);
		aOperator[3].TL.SetValue(0);
	}
}



IValue& CTimbre::GetValue(int x, int y)
{
	switch (y){
		case 0:{
			switch (x){
				case 0: return Control.EN;
				case 1: return Control.FDE;
				case 2: return Control.ALG;
				case 3: return Control.FB;
				case 4: return Control.NUM;
				case 5: return Control.KML;
				case 6: return Control.KMH;
				case 7: break;
				case 8: break;
				case 9: break;
				case 10: break;
				case 11: break;
				case 12: return Control.SE;
				case 13: return Control.KT;
				case 14: return Control.FDT;
			}
			break;
		}
		default:{
			switch (x){
				case 0: return aOperator[y-1].EN;
				case 1: return aOperator[y-1].FDE;
				case 2: return aOperator[y-1].AR;
				case 3: return aOperator[y-1].DR;
				case 4: return aOperator[y-1].SR;
				case 5: return aOperator[y-1].RR;
				case 6: return aOperator[y-1].SL;
				case 7: return aOperator[y-1].TL;
				case 8: return aOperator[y-1].KS;
				case 9: return aOperator[y-1].MT;
				case 10: return aOperator[y-1].DT;
				case 11: return aOperator[y-1].SSG;
				case 12: return aOperator[y-1].SE_FIX;
				case 13: return aOperator[y-1].SE_KT;
				case 14: return aOperator[y-1].SE_FDT;
			}
			break;
		}
	}
	return Dummy;
}



void CTimbre::OnBufferStart(std::vector<int>& aOutput)
{
	SubmitSourceBuffer(aOutput);
	KeyOn();
}



void CTimbre::SubmitSourceBuffer(std::vector<int>& aOutput)
{
	for (auto& i : aOutput){
		int32_t outputs[1] = {0};
		m_pFmChip->generate(output_pos, output_step, outputs);
		i += outputs[0];
		
		output_pos += output_step;
	}
}



static const int16_t s_aBlockFNumber[]={
//	c       c+      d       d+      e       f       f+      g       g+      a       a+      b
	0x009a, 0x00a3, 0x00ad, 0x00b7, 0x00c2, 0x00ce, 0x00da, 0x00e7, 0x00f5, 0x0104, 0x0113, 0x0123,	// o-1
	0x0135, 0x0147, 0x015b, 0x016f, 0x0185, 0x019c, 0x01b5, 0x01cf, 0x01ea, 0x0208, 0x0227, 0x0247,	// o0
	0x026a, 0x028f, 0x02b6, 0x02df, 0x030b, 0x0339, 0x036a, 0x039e, 0x03d5, 0x0410, 0x044e, 0x048f,	// o1
	0x0a6a, 0x0a8f, 0x0ab6, 0x0adf, 0x0b0b, 0x0b39, 0x0b6a, 0x0b9e, 0x0bd5, 0x0c10, 0x0c4e, 0x0c8f,	// o2
	0x126a, 0x128f, 0x12b6, 0x12df, 0x130b, 0x1339, 0x136a, 0x139e, 0x13d5, 0x1410, 0x144e, 0x148f,	// o3
	0x1a6a, 0x1a8f, 0x1ab6, 0x1adf, 0x1b0b, 0x1b39, 0x1b6a, 0x1b9e, 0x1bd5, 0x1c10, 0x1c4e, 0x1c8f,	// o4
	0x226a, 0x228f, 0x22b6, 0x22df, 0x230b, 0x2339, 0x236a, 0x239e, 0x23d5, 0x2410, 0x244e, 0x248f,	// o5
	0x2a6a, 0x2a8f, 0x2ab6, 0x2adf, 0x2b0b, 0x2b39, 0x2b6a, 0x2b9e, 0x2bd5, 0x2c10, 0x2c4e, 0x2c8f,	// o6
	0x326a, 0x328f, 0x32b6, 0x32df, 0x330b, 0x3339, 0x336a, 0x339e, 0x33d5, 0x3410, 0x344e, 0x348f,	// o7
	0x3a6a, 0x3a8f, 0x3ab6, 0x3adf, 0x3b0b, 0x3b39, 0x3b6a, 0x3b9e, 0x3bd5, 0x3c10, 0x3c4e, 0x3c8f,	// o8
	0x3cd4, 0x3d1e, 0x3d6c, 0x3dbe, 0x3e16, 0x3e72, 0x3ed4, 0x3f3c, 0x3faa, 0x0000, 0x0000, 0x0000,	// o9
};

void CTimbre::BlockFNumber(int Note, int RegH, int RegL, int KT, int DT)
{
	Note += KT;
	Note += Control.KT.GetValue();
	Note = (Note >= 0)? Note: 0;
	Note = (int)((Note < std::size(s_aBlockFNumber))? Note: std::size(s_aBlockFNumber)-1);
	
	auto BlockFNumber = s_aBlockFNumber[Note];
	BlockFNumber += DT;
	BlockFNumber += Control.FDT.GetValue();
	BlockFNumber = (BlockFNumber >= 0)? BlockFNumber: 0;
	BlockFNumber = (BlockFNumber <= 0x3fff)? BlockFNumber: 0x3fff;
	
	m_pFmChip->write(RegH, BlockFNumber>>8);
	m_pFmChip->write(RegL, BlockFNumber&0xff);
}



void CTimbre::KeyOn()
{
	if (m_bPlay && !m_bKeyOn){
		m_bKeyOn = true;
		m_pFmChip->write(0x27, (Control.SE.GetValue()<<7));
		m_pFmChip->write(0x32, ((aOperator[0].DT.GetValue()<<4) | aOperator[0].MT.GetValue()));
		m_pFmChip->write(0x3a, ((aOperator[1].DT.GetValue()<<4) | aOperator[1].MT.GetValue()));
		m_pFmChip->write(0x36, ((aOperator[2].DT.GetValue()<<4) | aOperator[2].MT.GetValue()));
		m_pFmChip->write(0x3e, ((aOperator[3].DT.GetValue()<<4) | aOperator[3].MT.GetValue()));
		m_pFmChip->write(0x42, aOperator[0].TL.GetValue());
		m_pFmChip->write(0x4a, aOperator[1].TL.GetValue());
		m_pFmChip->write(0x46, aOperator[2].TL.GetValue());
		m_pFmChip->write(0x4e, aOperator[3].TL.GetValue());
		m_pFmChip->write(0x52, ((aOperator[0].KS.GetValue()<<6) | aOperator[0].AR.GetValue()));
		m_pFmChip->write(0x5a, ((aOperator[1].KS.GetValue()<<6) | aOperator[1].AR.GetValue()));
		m_pFmChip->write(0x56, ((aOperator[2].KS.GetValue()<<6) | aOperator[2].AR.GetValue()));
		m_pFmChip->write(0x5e, ((aOperator[3].KS.GetValue()<<6) | aOperator[3].AR.GetValue()));
		m_pFmChip->write(0x62, aOperator[0].DR.GetValue());
		m_pFmChip->write(0x6a, aOperator[1].DR.GetValue());
		m_pFmChip->write(0x66, aOperator[2].DR.GetValue());
		m_pFmChip->write(0x6e, aOperator[3].DR.GetValue());
		m_pFmChip->write(0x72, aOperator[0].SR.GetValue());
		m_pFmChip->write(0x7a, aOperator[1].SR.GetValue());
		m_pFmChip->write(0x76, aOperator[2].SR.GetValue());
		m_pFmChip->write(0x7e, aOperator[3].SR.GetValue());
		m_pFmChip->write(0x82, ((aOperator[0].SL.GetValue()<<4) | aOperator[0].RR.GetValue()));
		m_pFmChip->write(0x8a, ((aOperator[1].SL.GetValue()<<4) | aOperator[1].RR.GetValue()));
		m_pFmChip->write(0x86, ((aOperator[2].SL.GetValue()<<4) | aOperator[2].RR.GetValue()));
		m_pFmChip->write(0x8e, ((aOperator[3].SL.GetValue()<<4) | aOperator[3].RR.GetValue()));
		m_pFmChip->write(0x92, aOperator[0].SSG.GetValue());
		m_pFmChip->write(0x9a, aOperator[1].SSG.GetValue());
		m_pFmChip->write(0x96, aOperator[2].SSG.GetValue());
		m_pFmChip->write(0x9e, aOperator[3].SSG.GetValue());
		m_pFmChip->write(0xb2, ((Control.FB.GetValue()<<3) | Control.ALG.GetValue()));
		
		if (Control.SE.GetValue() == 0){
			BlockFNumber(m_Note, 0xa6, 0xa2, 0, 0);
		} else {
			BlockFNumber(((aOperator[0].SE_FIX.GetValue() == 0)? m_Note: 0), 0xad, 0xa9, aOperator[0].SE_KT.GetValue(), aOperator[0].SE_FDT.GetValue());
			BlockFNumber(((aOperator[1].SE_FIX.GetValue() == 0)? m_Note: 0), 0xae, 0xaa, aOperator[1].SE_KT.GetValue(), aOperator[1].SE_FDT.GetValue());
			BlockFNumber(((aOperator[2].SE_FIX.GetValue() == 0)? m_Note: 0), 0xac, 0xa8, aOperator[2].SE_KT.GetValue(), aOperator[2].SE_FDT.GetValue());
			BlockFNumber(((aOperator[3].SE_FIX.GetValue() == 0)? m_Note: 0), 0xa6, 0xa2, aOperator[3].SE_KT.GetValue(), aOperator[3].SE_FDT.GetValue());
		}
		
		if (m_Note >= Control.KML.GetValue() && m_Note <= Control.KMH.GetValue()){
			uint8_t KeyOn = 0;
			KeyOn |= (aOperator[0].EN.GetValue()<<4);
			KeyOn |= (aOperator[1].EN.GetValue()<<5);
			KeyOn |= (aOperator[2].EN.GetValue()<<6);
			KeyOn |= (aOperator[3].EN.GetValue()<<7);
			KeyOn = (Control.EN.GetValue() == 0)? 0: KeyOn;
			m_pFmChip->write(0x28, (KeyOn | 0x02));
		}
	}
}



void CTimbre::Play(int Note)
{
	if (!m_bPlay){
		m_Note = Note;
		
		m_bPlay = true;
		m_bKeyOn = false;
		
		m_bFDE = Control.FDE.GetValue();
		m_bFDE1 = (bool)aOperator[0].FDE.GetValue() && m_bFDE;
		m_bFDE2 = (bool)aOperator[1].FDE.GetValue() && m_bFDE;
		m_bFDE3 = (bool)aOperator[2].FDE.GetValue() && m_bFDE;
		m_bFDE4 = (bool)aOperator[3].FDE.GetValue() && m_bFDE;
		
		if (m_bFDE1) m_pFmChip->write(0x82, ((aOperator[0].SL.GetValue()<<4) | /*RR*/15));
		if (m_bFDE2) m_pFmChip->write(0x8a, ((aOperator[1].SL.GetValue()<<4) | /*RR*/15));
		if (m_bFDE3) m_pFmChip->write(0x86, ((aOperator[2].SL.GetValue()<<4) | /*RR*/15));
		if (m_bFDE4) m_pFmChip->write(0x8e, ((aOperator[3].SL.GetValue()<<4) | /*RR*/15));
	}
}
void CTimbre::Stop()
{
	if (m_bPlay){
		m_bPlay = false;
		m_pFmChip->write(0x28, 0x02);
	}
}



void CTimbre::SetIntermediate(CIntermediate v)
{
	Control.EN.SetValue(v.Control.EN);
	Control.FDE.SetValue(v.Control.FDE);
	Control.ALG.SetValue(v.Control.ALG);
	Control.FB.SetValue(v.Control.FB);
	Control.NUM.SetValue(v.Control.NUM);
	Control.KML.SetValue(v.Control.KML);
	Control.KMH.SetValue(v.Control.KMH);
	Control.SE.SetValue(v.Control.SE);
	Control.KT.SetValue(v.Control.KT);
	Control.FDT.SetValue(v.Control.FDT);
	
	for (int i = 0; i < 4; ++i){
		aOperator[i].EN.SetValue(v.aOperator[i].EN);
		aOperator[i].FDE.SetValue(v.aOperator[i].FDE);
		aOperator[i].AR.SetValue(v.aOperator[i].AR);
		aOperator[i].DR.SetValue(v.aOperator[i].DR);
		aOperator[i].SR.SetValue(v.aOperator[i].SR);
		aOperator[i].RR.SetValue(v.aOperator[i].RR);
		aOperator[i].SL.SetValue(v.aOperator[i].SL);
		aOperator[i].TL.SetValue(v.aOperator[i].TL);
		aOperator[i].KS.SetValue(v.aOperator[i].KS);
		aOperator[i].MT.SetValue(v.aOperator[i].MT);
		aOperator[i].DT.SetValue(v.aOperator[i].DT);
		aOperator[i].SSG.SetValue(v.aOperator[i].SSG);
		aOperator[i].SE_FIX.SetValue(v.aOperator[i].SE_FIX);
		aOperator[i].SE_KT.SetValue(v.aOperator[i].SE_KT);
		aOperator[i].SE_FDT.SetValue(v.aOperator[i].SE_FDT);
	}
}



CIntermediate CTimbre::GetIntermediate()
{
	CIntermediate v;
	
	v.Control.EN = Control.EN.GetValue();
	v.Control.FDE = Control.FDE.GetValue();
	v.Control.ALG = Control.ALG.GetValue();
	v.Control.FB = Control.FB.GetValue();
	v.Control.NUM = Control.NUM.GetValue();
	v.Control.KML = Control.KML.GetValue();
	v.Control.KMH = Control.KMH.GetValue();
	v.Control.SE = Control.SE.GetValue();
	v.Control.KT = Control.KT.GetValue();
	v.Control.FDT = Control.FDT.GetValue();
	
	for (int i = 0; i < 4; ++i){
		v.aOperator[i].EN = aOperator[i].EN.GetValue();
		v.aOperator[i].FDE = aOperator[i].FDE.GetValue();
		v.aOperator[i].AR = aOperator[i].AR.GetValue();
		v.aOperator[i].DR = aOperator[i].DR.GetValue();
		v.aOperator[i].SR = aOperator[i].SR.GetValue();
		v.aOperator[i].RR = aOperator[i].RR.GetValue();
		v.aOperator[i].SL = aOperator[i].SL.GetValue();
		v.aOperator[i].TL = aOperator[i].TL.GetValue();
		v.aOperator[i].KS = aOperator[i].KS.GetValue();
		v.aOperator[i].MT = aOperator[i].MT.GetValue();
		v.aOperator[i].DT = aOperator[i].DT.GetValue();
		v.aOperator[i].SSG = aOperator[i].SSG.GetValue();
		v.aOperator[i].SE_FIX = aOperator[i].SE_FIX.GetValue();
		v.aOperator[i].SE_KT = aOperator[i].SE_KT.GetValue();
		v.aOperator[i].SE_FDT = aOperator[i].SE_FDT.GetValue();
	}
	
	return std::move(v);
}
