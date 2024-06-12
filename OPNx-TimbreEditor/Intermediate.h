#pragma once



#include "SettingTab.h"



struct CIntermediate
{
	public:
		virtual ~CIntermediate() = default;
		
		CIntermediate();
	
	public:
		struct Control
		{
			int EN;
			int FDE;
			
			int ALG;
			int FB;
			
			int NUM;
			int KML;
			int KMH;
			
			int SE;//OPN
			
			int WF;//OPM
			int FRQ;//OPM
			int AMS;//OPM
			int AMD;//OPM
			int PMS;//OPM
			int PMD;//OPM
			int LFR;//OPM
			
			int KT;
			int FDT;
		};
		Control Control;
		
		struct Operator
		{
			int EN;
			int FDE;
			
			int AR;
			union { int DR; int D1R; };
			union { int SR; int D2R; };
			int RR;
			union { int SL; int D1L; };
			int TL;
			int KS;
			int MT;
			union { int DT; int DT1; };
			
			int SSG;//OPN
			int SE_FIX;//OPN
			int SE_KT;//OPN
			int SE_FDT;//OPN
			
			int DT2;//OPM
			int AME;//OPM
		};
		Operator aOperator[4];
	
	public:
		void to_json(nlohmann::json& j) const;
		void from_json(const nlohmann::json& j);
		
		void ToFormat(CSettingTab::EFormatType EFormatType, CString& Text);
		void FromFormat(CSettingTab::EFormatType EFormatType, const CString& Text);
	
	private:
		void Replace(std::string& source, const std::string& target, const std::string& replace, bool IsRecursive = true);
		std::vector<std::string> GetLines(const CString& Text);
		std::vector<std::string> GetToken(const std::string& Line, char delim);
		std::string CommentCut(const std::string& Line, const std::string& target);
		std::string Trim(const std::string& Token, const std::string& trim);
		int ToValue(const std::string& Token);
		
		void GetOperatorOPN(const std::vector<std::string>& Tokens, int iOperator);
		void GetOperatorOPM(const std::vector<std::string>& Tokens, int iOperator);
		
		void ToMucom(CString& Text);
		void FromMucom(const CString& Text);
		
		void ToPmdOPN(CString& Text);
		void FromPmdOPN(const CString& Text);
		
		void ToPmdOPM(CString& Text);
		void FromPmdOPM(const CString& Text);
		
		void ToFmp(CString& Text);
		void FromFmp(const CString& Text);
		
		void ToFmpA(CString& Text);
		void FromFmpA(const CString& Text);
		
		void ToFmp7F(CString& Text);
		void FromFmp7F(const CString& Text);
		
		void ToFmp7FA(CString& Text);
		void FromFmp7FA(const CString& Text);
		
		void ToFmp7FC(CString& Text);
		void FromFmp7FC(const CString& Text);
		
		void ToMml2VgmF(CString& Text);
		void FromMml2VgmF(const CString& Text);
		
		void ToMml2VgmN(CString& Text);
		void FromMml2VgmN(const CString& Text);
		
		void ToMml2VgmM(CString& Text);
		void FromMml2VgmM(const CString& Text);
		
		void ToMucomDotNET(CString& Text);
		void FromMucomDotNET(const CString& Text);
		
		void ToMAmidiMemoMOPN(CString& Text);
		void FromMAmidiMemoMOPN(const CString& Text);
		
		void ToMAmidiMemoMOPM(CString& Text);
		void FromMAmidiMemoMOPM(const CString& Text);
		
		void ToZMusicV(CString& Text);
		void FromZMusicV(const CString& Text);
		
		void ToZMusicAt(CString& Text);
		void FromZMusicAt(const CString& Text);
		
		void ToNagDrv(CString& Text);
		void FromNagDrv(const CString& Text);
		
		void ToNrtDrv(CString& Text);
		void FromNrtDrv(const CString& Text);
		
		void ToMmlDrv(CString& Text);
		void FromMmlDrv(const CString& Text);
		
		void ToMmlGui(CString& Text);
		void FromMmlGui(const CString& Text);
		
		void ToMuap98(CString& Text);
		void FromMuap98(const CString& Text);
		
		void ToV3MmlOPN(CString& Text);
		void FromV3MmlOPN(const CString& Text);
		
		void ToV3MmlOPNA(CString& Text);
		void FromV3MmlOPNA(const CString& Text);
		
		void ToV3MmlOPM(CString& Text);
		void FromV3MmlOPM(const CString& Text);
		
		void ToN88Basic(CString& Text);
		void FromN88Basic(const CString& Text);
};



void to_json(nlohmann::json& j, const CIntermediate& r);
void from_json(const nlohmann::json& j, CIntermediate& r);
