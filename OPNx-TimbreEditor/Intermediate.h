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
			
			int KML;
			int KMH;
			
			int NUM;
			int VOL;
			
			int SE;
			int KT;
			int FDT;
		};
		Control Control;
		
		struct Operator
		{
			int EN;
			int FDE;
			
			int AR;
			int DR;
			int SR;
			int RR;
			int SL;
			int TL;
			int KS;
			int MT;
			int DT;
			int SSG;
			
			int SE_FIX;
			int SE_KT;
			int SE_FDT;
		};
		Operator aOperator[4];
	
	public:
		void to_json(nlohmann::json& j) const;
		void from_json(const nlohmann::json& j);
		
		void ToFormat(CSettingTab::EFormatType EFormatType, CString& Text);
		void FromFormat(CSettingTab::EFormatType EFormatType, const CString& Text);
	
	private:
		void Replace(std::string& source, const std::string& target, const std::string& replace);
		std::vector<std::string> GetLines(const CString& Text);
		std::vector<std::string> GetToken(const std::string& Line, char delim);
		std::string Trim(const std::string& Token, const std::string& trim);
		int ToValue(const std::string& Token);
		void GetOperator(const std::vector<std::string>& Tokens, int iOperator);
		
		void ToMucom(CString& Text);
		void FromMucom(const CString& Text);
		
		void ToFmp(CString& Text);
		void FromFmp(const CString& Text);
		
		void ToPmd(CString& Text);
		void FromPmd(const CString& Text);
		
		void ToMAmidiMemo(CString& Text);
		void FromMAmidiMemo(const CString& Text);
};



void to_json(nlohmann::json& j, const CIntermediate& r);
void from_json(const nlohmann::json& j, CIntermediate& r);
