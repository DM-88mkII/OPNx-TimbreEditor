


#include "pch.h"
#include "Intermediate.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <string>



CIntermediate::CIntermediate()
:Control{0}
,aOperator{0}
{
	Control.EN = 1;
	Control.FDE = 1;
	Control.KML = 0;
	Control.KMH = 128;
	Control.VOL = 100;
	
	for (int i = 0; i < 4; ++i){
		aOperator[i].EN = 1;
		aOperator[i].FDE = 1;
	}
}



void CIntermediate::to_json(nlohmann::json& j) const
{
	j = nlohmann::json{
		{"Information",{
			{"Summary",		"Timbre for OPN Series",	},
			{"ChipType",	"YM2203",	},
		}},
		{"Meta",{
			{"Application",	"OPNx-TimbreEditor",	},
			{"Version",		"0.0.0",	},
		}},
		{"Timbre",{
			{"Control",{
				{"EN",		Control.EN,	},
				{"FDE",		Control.FDE,},
				{"ALG",		Control.ALG,},
				{"FB",		Control.FB,	},
				{"KML",		Control.KML,},
				{"KMH",		Control.KMH,},
				{"NUM",		Control.NUM,},
				{"VOL",		Control.VOL,},
				{"SE",		Control.SE,	},
				{"KT",		Control.KT,	},
				{"FDT",		Control.FDT,},
			}},
			{"Operators",{
				{"EN",{		aOperator[0].EN,	aOperator[1].EN,	aOperator[2].EN,	aOperator[3].EN,	}},
				{"FDE",{	aOperator[0].FDE,	aOperator[1].FDE,	aOperator[2].FDE,	aOperator[3].FDE,	}},
				{"AR",{		aOperator[0].AR,	aOperator[1].AR,	aOperator[2].AR,	aOperator[3].AR,	}},
				{"DR",{		aOperator[0].DR,	aOperator[1].DR,	aOperator[2].DR,	aOperator[3].DR,	}},
				{"SR",{		aOperator[0].SR,	aOperator[1].SR,	aOperator[2].SR,	aOperator[3].SR,	}},
				{"RR",{		aOperator[0].RR,	aOperator[1].RR,	aOperator[2].RR,	aOperator[3].RR,	}},
				{"SL",{		aOperator[0].SL,	aOperator[1].SL,	aOperator[2].SL,	aOperator[3].SL,	}},
				{"TL",{		aOperator[0].TL,	aOperator[1].TL,	aOperator[2].TL,	aOperator[3].TL,	}},
				{"KS",{		aOperator[0].KS,	aOperator[1].KS,	aOperator[2].KS,	aOperator[3].KS,	}},
				{"MT",{		aOperator[0].MT,	aOperator[1].MT,	aOperator[2].MT,	aOperator[3].MT,	}},
				{"DT",{		aOperator[0].DT,	aOperator[1].DT,	aOperator[2].DT,	aOperator[3].DT,	}},
				{"SSG",{	aOperator[0].SSG,	aOperator[1].SSG,	aOperator[2].SSG,	aOperator[3].SSG,	}},
				{"SE_FIX",{	aOperator[0].SE_FIX,aOperator[1].SE_FIX,aOperator[2].SE_FIX,aOperator[3].SE_FIX,}},
				{"SE_KT",{	aOperator[0].SE_KT,	aOperator[1].SE_KT,	aOperator[2].SE_KT,	aOperator[3].SE_KT,	}},
				{"SE_FDT",{	aOperator[0].SE_FDT,aOperator[1].SE_FDT,aOperator[2].SE_FDT,aOperator[3].SE_FDT,}},
			}},
		}},
	};
}



void CIntermediate::from_json(const nlohmann::json& j)
{
	std::exception_ptr pException;
	try {
		{	// 
			auto Information = j.at("Information");
			auto Application = Information.at("Summary").get<std::string>();
			auto ChipType = Information.at("ChipType").get<std::string>();
		}
		
		{	// 
			auto Meta = j.at("Meta");
			auto Application = Meta.at("Application").get<std::string>();
			auto Version = Meta.at("Version").get<std::string>();
		}
		
		{	// 
			auto Timbre = j.at("Timbre");
			
			{	// 
				auto o = Timbre.at("Control");
				Control.EN = o.at("EN").get<int>();
				Control.FDE = o.at("FDE").get<int>();
				Control.ALG = o.at("ALG").get<int>();
				Control.FB = o.at("FB").get<int>();
				Control.KML = o.value("KML", 0);
				Control.KMH = o.value("KMH", 128);
				Control.NUM = o.at("NUM").get<int>();
				Control.VOL = o.at("VOL").get<int>();
				Control.SE = o.at("SE").get<int>();
				Control.KT = o.at("KT").get<int>();
				Control.FDT = o.at("FDT").get<int>();
			}
			
			{	// 
				auto SetOperator = [this](nlohmann::json& Timbre, int i)
				{
					aOperator[i].EN = Timbre.at("EN").at(i).get<int>();
					aOperator[i].FDE = Timbre.at("FDE").at(i).get<int>();
					aOperator[i].AR = Timbre.at("AR").at(i).get<int>();
					aOperator[i].DR = Timbre.at("DR").at(i).get<int>();
					aOperator[i].SR = Timbre.at("SR").at(i).get<int>();
					aOperator[i].RR = Timbre.at("RR").at(i).get<int>();
					aOperator[i].SL = Timbre.at("SL").at(i).get<int>();
					aOperator[i].TL = Timbre.at("TL").at(i).get<int>();
					aOperator[i].KS = Timbre.at("KS").at(i).get<int>();
					aOperator[i].MT = Timbre.at("MT").at(i).get<int>();
					aOperator[i].DT = Timbre.at("DT").at(i).get<int>();
					aOperator[i].SSG = Timbre.at("SSG").at(i).get<int>();
					aOperator[i].SE_FIX = Timbre.at("SE_FIX").at(i).get<int>();
					aOperator[i].SE_KT = Timbre.at("SE_KT").at(i).get<int>();
					aOperator[i].SE_FDT = Timbre.at("SE_FDT").at(i).get<int>();
				};
				
				auto o = Timbre.at("Operators");
				for (int i = 0; i < 4; ++i) SetOperator(o, i);
			}
		}
	}
	catch (...)
	{
		pException = std::current_exception();
	}
	if (pException){
		std::rethrow_exception(pException);
	}
}



void CIntermediate::ToFormat(CSettingTab::EFormatType EFormatType, CString& Text)
{
	switch (EFormatType){
		case CSettingTab::EFormatType::MUCOM:{		ToMucom(Text);		break;	}
		case CSettingTab::EFormatType::FMP:{		ToFmp(Text);		break;	}
		case CSettingTab::EFormatType::PMD:{		ToPmd(Text);		break;	}
		case CSettingTab::EFormatType::MAmidiMemo:{	ToMAmidiMemo(Text);	break;	}
	}
}



void CIntermediate::FromFormat(CSettingTab::EFormatType EFormatType, const CString& Text)
{
	switch (EFormatType){
		case CSettingTab::EFormatType::MUCOM:{		FromMucom(Text);		break;	}
		case CSettingTab::EFormatType::FMP:{		FromFmp(Text);			break;	}
		case CSettingTab::EFormatType::PMD:{		FromPmd(Text);			break;	}
		case CSettingTab::EFormatType::MAmidiMemo:{	FromMAmidiMemo(Text);	break;	}
	}
}



void CIntermediate::Replace(std::string& source, const std::string& target, const std::string& replace)
{
	size_t p = 0;
	size_t o = 0;
	size_t n = target.length();
	int c = 0;
	while ((p = source.find(target, o)) != std::string::npos){
		source.replace(p, n, replace);
		o = p + replace.length();
		++c;
	}
	if (c > 0) Replace(source, target, replace);
}


std::vector<std::string> CIntermediate::GetLines(const CString& Text)
{
	std::string s = CStringA(Text).GetBuffer();
	Replace(s, "\r\n", "\n");
	Replace(s, "\n\n", "\n");
	
	std::stringstream ss(s);
	std::string Line;
	std::vector<std::string> Lines;
	while (std::getline(ss, Line, '\n')) Lines.push_back(Line);
	return Lines;
}



std::vector<std::string> CIntermediate::GetToken(const std::string& Line, char delim)
{
	std::stringstream ss(Line);
	std::string Token;
	std::vector<std::string> Tokens;
	while (std::getline(ss, Token, delim)) Tokens.push_back(Token);
	return Tokens;
}



std::string CIntermediate::Trim(const std::string& Token, const std::string& trim)
{
	std::string Result;
	auto First = Token.find_first_not_of(trim);
	if (First != std::string::npos){
		auto Last = Token.find_last_not_of(trim);
		Result = Token.substr(First, Last - First + 1);
	}
	return Result;
}



int CIntermediate::ToValue(const std::string& Token)
{
	auto Value = Trim(Token, " ");
	return (Value.empty())? 0: std::stoi(Value);
}



void CIntermediate::GetOperator(const std::vector<std::string>& Tokens, int iOperator, int SSG)
{
	int TimbreToken = 0;
	for (auto Token : Tokens){
		switch (TimbreToken){
			case 0:{	aOperator[iOperator].AR = ToValue(Token);	break;	}
			case 1:{	aOperator[iOperator].DR = ToValue(Token);	break;	}
			case 2:{	aOperator[iOperator].SR = ToValue(Token);	break;	}
			case 3:{	aOperator[iOperator].RR = ToValue(Token);	break;	}
			case 4:{	aOperator[iOperator].SL = ToValue(Token);	break;	}
			case 5:{	aOperator[iOperator].TL = ToValue(Token);	break;	}
			case 6:{	aOperator[iOperator].KS = ToValue(Token);	break;	}
			case 7:{	aOperator[iOperator].MT = ToValue(Token);	break;	}
			case 8:{	aOperator[iOperator].DT = ToValue(Token);	break;	}
		}
		if (TimbreToken == SSG) aOperator[iOperator].SSG = ToValue(Token);
		++TimbreToken;
	}
}



void CIntermediate::ToMucom(CString& Text)
{
	std::string s;
	s += "  @No:{\n";
	s += std::format(" {:>3},{:>3}\n", Control.FB, Control.ALG);
	for (int i = 0; i < 4; ++i){
		s += std::format(" {:>3}", aOperator[i].AR);
		s += std::format(",{:>3}", aOperator[i].DR);
		s += std::format(",{:>3}", aOperator[i].SR);
		s += std::format(",{:>3}", aOperator[i].RR);
		s += std::format(",{:>3}", aOperator[i].SL);
		s += std::format(",{:>3}", aOperator[i].TL);
		s += std::format(",{:>3}", aOperator[i].KS);
		s += std::format(",{:>3}", aOperator[i].MT);
		s += std::format(",{:>3}", aOperator[i].DT);
		s += (i < 3)? "\n": ",\"\"}\n";
	}
	Text = s.c_str();
}



void CIntermediate::FromMucom(const CString& Text)
{
	auto IsTimbre = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		auto o = Line.find_first_not_of(" \t");
		if (Line.size() > 0 && o != std::string::npos && Line[o] == ';') continue;
		
		if (!IsTimbre){
			auto m1 = Line.find_first_of("  @");
			auto m2 = Line.find_first_of(":{");
			if (m1 == 0 && m2 != std::string::npos && m1 < m2){
				IsTimbre = true;
			}
		} else {
			Replace(Line, "\t", " ");
			Replace(Line, "  ", " ");
			
			auto Tokens = GetToken(Line, ',');
			switch (TimbreLine){
				case 0:{
					int TimbreToken = 0;
					for (auto Token : Tokens){
						switch (TimbreToken){
							case 0:{	Control.FB = ToValue(Token);	break;	}
							case 1:{	Control.ALG = ToValue(Token);	break;	}
						}
						++TimbreToken;
					}
					break;
				}
				case 1:
				case 2:
				case 3:
				case 4:
				{
					GetOperator(Tokens, iOperator);
					++iOperator;
					break;
				}
			}
			++TimbreLine;
		}
	}
}



void CIntermediate::ToFmp(CString& Text)
{
	std::string s;
	s += "'@ F No \"\"\n";
	for (int i = 0; i < 4; ++i){
		s += "'@";
		s += std::format(" {:>3}", aOperator[i].AR);
		s += std::format(",{:>3}", aOperator[i].DR);
		s += std::format(",{:>3}", aOperator[i].SR);
		s += std::format(",{:>3}", aOperator[i].RR);
		s += std::format(",{:>3}", aOperator[i].SL);
		s += std::format(",{:>3}", aOperator[i].TL);
		s += std::format(",{:>3}", aOperator[i].KS);
		s += std::format(",{:>3}", aOperator[i].MT);
		s += std::format(",{:>3}", aOperator[i].DT);
		s += "\n";
	}
	s += std::format("'@ {:>3},{:>3}\n", Control.ALG, Control.FB);
	Text = s.c_str();
}



void CIntermediate::FromFmp(const CString& Text)
{
	auto IsTimbre = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		Replace(Line, "\t", " ");
		Replace(Line, "  ", " ");
		
		if (Line.size() > 0 && Line[0] != '\'') continue;
		
		if (!IsTimbre){
			auto m1 = Line.find_first_of("'@ F ");
			if (m1 == 0){
				IsTimbre = true;
			}
		} else {
			auto Tokens = GetToken(Trim(Line, "'@"), ',');
			switch (TimbreLine){
				case 4:{
					int TimbreToken = 0;
					for (auto Token : Tokens){
						switch (TimbreToken){
							case 0:{	Control.ALG = ToValue(Token);	break;	}
							case 1:{	Control.FB = ToValue(Token);	break;	}
						}
						++TimbreToken;
					}
					break;
				}
				case 0:
				case 1:
				case 2:
				case 3:
				{
					GetOperator(Tokens, iOperator);
					++iOperator;
					break;
				}
			}
			++TimbreLine;
		}
	}
}



void CIntermediate::ToPmd(CString& Text)
{
	std::string s;
	s += std::format("@No  {:03} {:03}\n", Control.ALG, Control.FB);
	for (int i = 0; i < 4; ++i){
		s += std::format(" {:03}", aOperator[i].AR);
		s += std::format(" {:03}", aOperator[i].DR);
		s += std::format(" {:03}", aOperator[i].SR);
		s += std::format(" {:03}", aOperator[i].RR);
		s += std::format(" {:03}", aOperator[i].SL);
		s += std::format(" {:03}", aOperator[i].TL);
		s += std::format(" {:03}", aOperator[i].KS);
		s += std::format(" {:03}", aOperator[i].MT);
		s += std::format(" {:03}", aOperator[i].DT);
		s += " 000";//AMS
		s += "\n";
	}
	Text = s.c_str();
}



void CIntermediate::FromPmd(const CString& Text)
{
	auto IsTimbre = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		Replace(Line, "\t", " ");
		Replace(Line, "  ", " ");
		
		auto o = Line.find_first_not_of(" ");
		if (Line.size() > 0 && o != std::string::npos && Line[o] == ';') continue;
		
		if (!IsTimbre){
			auto m1 = Line.find_first_of("@");
			if (m1 == 0){
				IsTimbre = true;
				
				auto Tokens = GetToken(Line, ' ');
				int TimbreToken = 0;
				for (auto Token : Tokens){
					switch (TimbreToken){
						case 1:{	Control.ALG = ToValue(Token);	break;	}
						case 2:{	Control.FB = ToValue(Token);	break;	}
					}
					++TimbreToken;
				}
			}
		} else {
			auto Tokens = GetToken(Trim(Line, " "), ' ');
			switch (TimbreLine){
				case 0:
				case 1:
				case 2:
				case 3:
				{
					GetOperator(Tokens, iOperator);
					++iOperator;
					break;
				}
			}
			++TimbreLine;
		}
	}
}



void CIntermediate::ToMAmidiMemo(CString& Text)
{
	std::string s;
	s += "*.mopn\n";
	s += "1.0\n";
	s += "1\n";
	s += "name\n";
	s += std::format("{},{},0,0,0,,\n", Control.ALG, Control.FB);
	for (int i = 0; i < 4; ++i){
		s += "1";
		s += std::format(",{}", aOperator[i].AR);
		s += std::format(",{}", aOperator[i].DR);
		s += std::format(",{}", aOperator[i].SR);
		s += std::format(",{}", aOperator[i].RR);
		s += std::format(",{}", aOperator[i].SL);
		s += std::format(",{}", aOperator[i].TL);
		s += std::format(",{}", aOperator[i].KS);
		s += std::format(",{}", aOperator[i].MT);
		s += std::format(",{}", aOperator[i].DT);
		s += ",0";//AM
		s += std::format(",{}", aOperator[i].SSG);
		s += "\n";
	}
	Text = s.c_str();
}



void CIntermediate::FromMAmidiMemo(const CString& Text)
{
	auto IsTimbre = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	int Header = 5;
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		if (!IsTimbre){
			if (--Header == 0){
				IsTimbre = true;
				
				auto Tokens = GetToken(Line, ',');
				int TimbreToken = 0;
				for (auto Token : Tokens){
					switch (TimbreToken){
						case 0:{	Control.ALG = ToValue(Token);	break;	}
						case 1:{	Control.FB = ToValue(Token);	break;	}
					}
					++TimbreToken;
				}
			}
		} else {
			auto Tokens = GetToken(Line, ',');
			switch (TimbreLine){
				case 0:
				case 1:
				case 2:
				case 3:
				{
					GetOperator(Tokens, iOperator, 10);
					++iOperator;
					break;
				}
			}
			++TimbreLine;
		}
	}
}



void to_json(nlohmann::json& j, const CIntermediate& r){ r.to_json(j); }
void from_json(const nlohmann::json& j, CIntermediate& r){ r.from_json(j); }
