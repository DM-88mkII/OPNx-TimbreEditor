#pragma once



struct CIntermediate
{
	public:
		virtual ~CIntermediate() = default;
		
		CIntermediate():Control{0},aOperator{0}{};
	
	public:
		struct Control
		{
			int EN;
			int FDE;
			
			int ALG;
			int FB;
			
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
};



void to_json(nlohmann::json& j, const CIntermediate& r);
void from_json(const nlohmann::json& j, CIntermediate& r);
