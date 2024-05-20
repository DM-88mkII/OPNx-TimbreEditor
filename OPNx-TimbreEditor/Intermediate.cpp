


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
	
	for (int i = 0; i < _countof(aOperator); ++i){
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
				{"NUM",		Control.NUM,},
				{"KML",		Control.KML,},
				{"KMH",		Control.KMH,},
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
				Control.NUM = o.at("NUM").get<int>();
				Control.KML = o.value("KML", 0);
				Control.KMH = o.value("KMH", 128);
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
				for (int i = 0; i < _countof(aOperator); ++i) SetOperator(o, i);
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
		case CSettingTab::EFormatType::Mucom:{			ToMucom(Text);			break;	}
		case CSettingTab::EFormatType::Pmd:{			ToPmd(Text);			break;	}
		case CSettingTab::EFormatType::FmpF:{			ToFmpF(Text);			break;	}
		case CSettingTab::EFormatType::FmpFA:{			ToFmpFA(Text);			break;	}
		case CSettingTab::EFormatType::FmpFC:{			ToFmpFC(Text);			break;	}
		case CSettingTab::EFormatType::Mml2VgmF:{		ToMml2VgmF(Text);		break;	}
		case CSettingTab::EFormatType::Mml2VgmN:{		ToMml2VgmN(Text);		break;	}
		case CSettingTab::EFormatType::Mml2VgmM:{		ToMml2VgmM(Text);		break;	}
		case CSettingTab::EFormatType::mucomDotNET:{	ToMucomDotNET(Text);	break;	}
		case CSettingTab::EFormatType::MAmidiMemoMOPN:{	ToMAmidiMemoMOPN(Text);	break;	}
		case CSettingTab::EFormatType::MAmidiMemoMOPM:{	ToMAmidiMemoMOPM(Text);	break;	}
	}
}



void CIntermediate::FromFormat(CSettingTab::EFormatType EFormatType, const CString& Text)
{
	switch (EFormatType){
		case CSettingTab::EFormatType::Mucom:{			FromMucom(Text);			break;	}
		case CSettingTab::EFormatType::Pmd:{			FromPmd(Text);				break;	}
		case CSettingTab::EFormatType::FmpF:{			FromFmpF(Text);				break;	}
		case CSettingTab::EFormatType::FmpFA:{			FromFmpFA(Text);			break;	}
		case CSettingTab::EFormatType::FmpFC:{			FromFmpFC(Text);			break;	}
		case CSettingTab::EFormatType::Mml2VgmF:{		FromMml2VgmF(Text);			break;	}
		case CSettingTab::EFormatType::Mml2VgmN:{		FromMml2VgmN(Text);			break;	}
		case CSettingTab::EFormatType::Mml2VgmM:{		FromMml2VgmM(Text);			break;	}
		case CSettingTab::EFormatType::mucomDotNET:{	FromMucomDotNET(Text);		break;	}
		case CSettingTab::EFormatType::MAmidiMemoMOPN:{	FromMAmidiMemoMOPN(Text);	break;	}
		case CSettingTab::EFormatType::MAmidiMemoMOPM:{	FromMAmidiMemoMOPM(Text);	break;	}
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



void CIntermediate::GetOperator(const std::vector<std::string>& Tokens, int iOperator)
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
		++TimbreToken;
	}
}



void CIntermediate::ToMucom(CString& Text)
{
	std::string s;
	s += std::format("  @{}:", Control.NUM);
	s += "{\n";
	s += std::format(" {:>3},{:>3}\n", Control.FB, Control.ALG);
	for (int i = 0; i < _countof(aOperator); ++i){
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
			auto m1 = Line.find("  @");
			if (m1 == 0){
				IsTimbre = true;
				
				auto Token = Line.substr(m1+3);
				Control.NUM = ToValue(Token);
			}
		} else {
			Replace(Line, ",", " ");
			Replace(Line, "\t", " ");
			Replace(Line, "  ", " ");
			
			auto Tokens = GetToken(Trim(Line, " "), ' ');
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
	if (!(IsTimbre && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToPmd(CString& Text)
{
	std::string s;
	s += std::format("@{:03} {:03} {:03}\n", Control.NUM, Control.ALG, Control.FB);
	for (int i = 0; i < _countof(aOperator); ++i){
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
			auto m1 = Line.find("@");
			if (m1 == 0){
				IsTimbre = true;
				
				Replace(Line, ",", " ");
				auto Tokens = GetToken(Trim(Line, "@ "), ' ');
				int TimbreToken = 0;
				for (auto Token : Tokens){
					switch (TimbreToken){
						case 0:{	Control.NUM = ToValue(Token);	break;	}
						case 1:{	Control.ALG = ToValue(Token);	break;	}
						case 2:{	Control.FB = ToValue(Token);	break;	}
					}
					++TimbreToken;
				}
			}
		} else {
			Replace(Line, ",", " ");
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
	if (!(IsTimbre && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToFmpF(CString& Text)
{
	std::string s;
	s += std::format("'@ F {}\n", Control.NUM);
	for (int i = 0; i < _countof(aOperator); ++i){
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



void CIntermediate::FromFmpF(const CString& Text)
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
			auto m1 = Line.find("'@ F ");
			if (m1 == 0){
				IsTimbre = true;
				
				auto Token = Line.substr(m1+5);
				Control.NUM = ToValue(Token);
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
	if (!(IsTimbre && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToFmpFA(CString& Text)
{
	std::string s;
	s += std::format("'@ FA {}\n", Control.NUM);
	for (int i = 0; i < _countof(aOperator); ++i){
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
		s += ",  0";//AM
		s += "\n";
	}
	s += std::format("'@ {:>3},{:>3}\n", Control.ALG, Control.FB);
	Text = s.c_str();
}



void CIntermediate::FromFmpFA(const CString& Text)
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
			auto m1 = Line.find("'@ FA ");
			if (m1 == 0){
				IsTimbre = true;
				
				auto Token = Line.substr(m1+6);
				Control.NUM = ToValue(Token);
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
	if (!(IsTimbre && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToFmpFC(CString& Text)
{
	std::string s;
	s += std::format("'@ FC {}\n", Control.NUM);
	for (int i = 0; i < _countof(aOperator); ++i){
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
		s += ",  0";//DT2
		s += ",  0";//AM
		s += "\n";
	}
	s += std::format("'@ {:>3},{:>3}\n", Control.ALG, Control.FB);
	Text = s.c_str();
}



void CIntermediate::FromFmpFC(const CString& Text)
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
			auto m1 = Line.find("'@ FC ");
			if (m1 == 0){
				IsTimbre = true;
				
				auto Token = Line.substr(m1+6);
				Control.NUM = ToValue(Token);
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
	if (!(IsTimbre && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToMml2VgmF(CString& Text)
{
	std::string s;
	s += std::format("'@ F {} \"\"\n", Control.NUM);
	for (int i = 0; i < _countof(aOperator); ++i){
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



void CIntermediate::FromMml2VgmF(const CString& Text)
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
			auto m1 = Line.find("'@ F ");
			auto m2 = Line.find("\"");
			if (m1 == 0 && m2 != std::string::npos && m1 < m2){
				IsTimbre = true;
				
				auto Token = Line.substr(m1+5, m2-m1-5);
				Control.NUM = ToValue(Token);
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
	if (!(IsTimbre && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToMml2VgmN(CString& Text)
{
	std::string s;
	s += std::format("'@ N {} \"\"\n", Control.NUM);
	for (int i = 0; i < _countof(aOperator); ++i){
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
		s += ",  0";//AM
		s += "\n";
	}
	s += std::format("'@ {:>3},{:>3}\n", Control.ALG, Control.FB);
	Text = s.c_str();
}



void CIntermediate::FromMml2VgmN(const CString& Text)
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
			auto m1 = Line.find("'@ N ");
			auto m2 = Line.find("\"");
			if (m1 == 0 && m2 != std::string::npos && m1 < m2){
				IsTimbre = true;
				
				auto Token = Line.substr(m1+5, m2-m1-5);
				Control.NUM = ToValue(Token);
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
	if (!(IsTimbre && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToMml2VgmM(CString& Text)
{
	std::string s;
	s += std::format("'@ M {} \"\"\n", Control.NUM);
	for (int i = 0; i < _countof(aOperator); ++i){
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
		s += ",  0";//DT2
		s += ",  0";//AM
		s += "\n";
	}
	s += std::format("'@ {:>3},{:>3}\n", Control.ALG, Control.FB);
	Text = s.c_str();
}



void CIntermediate::FromMml2VgmM(const CString& Text)
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
			auto m1 = Line.find("'@ M ");
			auto m2 = Line.find("\"");
			if (m1 == 0 && m2 != std::string::npos && m1 < m2){
				IsTimbre = true;
				
				auto Token = Line.substr(m1+5, m2-m1-5);
				Control.NUM = ToValue(Token);
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
	if (!(IsTimbre && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToMucomDotNET(CString& Text)
{
	std::string s;
	s += std::format("  @M{}\n", Control.NUM);
	s += std::format(" {:>3},{:>3}\n", Control.FB, Control.ALG);
	for (int i = 0; i < _countof(aOperator); ++i){
		s += std::format(" {:>3}", aOperator[i].AR);
		s += std::format(",{:>3}", aOperator[i].DR);
		s += std::format(",{:>3}", aOperator[i].SR);
		s += std::format(",{:>3}", aOperator[i].RR);
		s += std::format(",{:>3}", aOperator[i].SL);
		s += std::format(",{:>3}", aOperator[i].TL);
		s += std::format(",{:>3}", aOperator[i].KS);
		s += std::format(",{:>3}", aOperator[i].MT);
		s += std::format(",{:>3}", aOperator[i].DT);
		s += ",  0\n";//DT2
		s += "\n";
	}
	Text = s.c_str();
}



void CIntermediate::FromMucomDotNET(const CString& Text)
{
	auto IsTimbre = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		auto o = Line.find_first_not_of(" \t");
		if (Line.size() > 0 && o != std::string::npos && Line[o] == ';') continue;
		
		if (!IsTimbre){
			auto m1 = Line.find("  @M");
			if (m1 == 0){
				IsTimbre = true;
				
				auto Token = Line.substr(m1+4);
				Control.NUM = ToValue(Token);
			}
		} else {
			Replace(Line, ",", " ");
			Replace(Line, "\t", " ");
			Replace(Line, "  ", " ");
			
			auto Tokens = GetToken(Trim(Line, " "), ' ');
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
	if (!(IsTimbre && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToMAmidiMemoMOPN(CString& Text)
{
	std::string s;
	s += "*.mopn\n";
	s += "1.0\n";
	s += "1\n";
	s += std::format("@{}\n", Control.NUM);
	s += std::format("{},{},0,0,0,,\n", Control.ALG, Control.FB);
	for (int i = 0; i < _countof(aOperator); ++i){
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



void CIntermediate::FromMAmidiMemoMOPN(const CString& Text)
{
	auto IsTimbre = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	int Header = 0;
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		if (!IsTimbre){
			switch (Header){
				case 0:{	if (Line.compare("*.mopn") == 0){	++Header; }	break;	}
				case 1:{	if (Line.compare("1.0") == 0){		++Header; }	break;	}
				case 2:{	if (Line.compare("1") == 0){		++Header; }	break;	}
				case 3:{
					if (Line.size() > 0 && Line[0] == '@'){
						auto Token = Trim(Line, "@");
						Control.NUM = ToValue(Token);
					}
					++Header;
					break;
				}
				case 4:{
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
					break;
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
					int TimbreToken = 0;
					for (auto Token : Tokens){
						switch (TimbreToken){
							case 0:{	aOperator[iOperator].EN = ToValue(Token);	break;	}
							case 1:{	aOperator[iOperator].AR = ToValue(Token);	break;	}
							case 2:{	aOperator[iOperator].DR = ToValue(Token);	break;	}
							case 3:{	aOperator[iOperator].SR = ToValue(Token);	break;	}
							case 4:{	aOperator[iOperator].RR = ToValue(Token);	break;	}
							case 5:{	aOperator[iOperator].SL = ToValue(Token);	break;	}
							case 6:{	aOperator[iOperator].TL = ToValue(Token);	break;	}
							case 7:{	aOperator[iOperator].KS = ToValue(Token);	break;	}
							case 8:{	aOperator[iOperator].MT = ToValue(Token);	break;	}
							case 9:{	aOperator[iOperator].DT = ToValue(Token);	break;	}
							case 11:{	aOperator[iOperator].SSG = ToValue(Token);	break;	}
						}
						++TimbreToken;
					}
					++iOperator;
					break;
				}
			}
			++TimbreLine;
		}
	}
	if (!(IsTimbre && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void CIntermediate::ToMAmidiMemoMOPM(CString& Text)
{
	std::string s;
	s += "*.mopm\n";
	s += "1.0\n";
	s += "1\n";
	s += std::format("@{}\n", Control.NUM);
	s += std::format("{},{},0,0,0,,,,,,\n", Control.ALG, Control.FB);
	for (int i = 0; i < _countof(aOperator); ++i){
		s += std::format( "{}", aOperator[i].EN);
		s += std::format(",{}", aOperator[i].AR);
		s += std::format(",{}", aOperator[i].DR);
		s += std::format(",{}", aOperator[i].SR);
		s += std::format(",{}", aOperator[i].RR);
		s += std::format(",{}", aOperator[i].SL);
		s += std::format(",{}", aOperator[i].TL);
		s += std::format(",{}", aOperator[i].KS);
		s += std::format(",{}", aOperator[i].MT);
		s += std::format(",{}", aOperator[i].DT);
		s += ",0";//AME
		s += ",0";//DT2
		s += ",0";//LS
		s += ",-1";//KSV
		s += "\n";
	}
	Text = s.c_str();
}



void CIntermediate::FromMAmidiMemoMOPM(const CString& Text)
{
	auto IsTimbre = false;
	int TimbreLine = 0;
	int iOperator = 0;
	
	int Header = 0;
	auto Lines = GetLines(Text);
	for (auto& Line : Lines){
		if (!IsTimbre){
			switch (Header){
				case 0:{	if (Line.compare("*.mopm") == 0){	++Header; }	break;	}
				case 1:{	if (Line.compare("1.0") == 0){		++Header; }	break;	}
				case 2:{	if (Line.compare("1") == 0){		++Header; }	break;	}
				case 3:{
					if (Line.size() > 0 && Line[0] == '@'){
						auto Token = Trim(Line, "@");
						Control.NUM = ToValue(Token);
					}
					++Header;
					break;
				}
				case 4:{
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
					break;
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
					int TimbreToken = 0;
					for (auto Token : Tokens){
						switch (TimbreToken){
							case 0:{	aOperator[iOperator].EN = ToValue(Token);	break;	}
							case 1:{	aOperator[iOperator].AR = ToValue(Token);	break;	}
							case 2:{	aOperator[iOperator].DR = ToValue(Token);	break;	}
							case 3:{	aOperator[iOperator].SR = ToValue(Token);	break;	}
							case 4:{	aOperator[iOperator].RR = ToValue(Token);	break;	}
							case 5:{	aOperator[iOperator].SL = ToValue(Token);	break;	}
							case 6:{	aOperator[iOperator].TL = ToValue(Token);	break;	}
							case 7:{	aOperator[iOperator].KS = ToValue(Token);	break;	}
							case 8:{	aOperator[iOperator].MT = ToValue(Token);	break;	}
							case 9:{	aOperator[iOperator].DT = ToValue(Token);	break;	}
						}
						++TimbreToken;
					}
					++iOperator;
					break;
				}
			}
			++TimbreLine;
		}
	}
	if (!(IsTimbre && iOperator == _countof(aOperator))){
		throw std::runtime_error("Format Error");
	}
}



void to_json(nlohmann::json& j, const CIntermediate& r){ r.to_json(j); }
void from_json(const nlohmann::json& j, CIntermediate& r){ r.from_json(j); }
