


#include "pch.h"
#include "Value.h"



template <int N, int MIN, int MAX> CValue<N, MIN, MAX>::CValue()
:v{0}
,i(0)
,s(_T("0"))
{
	Init(s, false);
}



template <int N, int MIN, int MAX> void CValue<N, MIN, MAX>::InputChar(char v)
{
	if (!b) Init(_T(""), true);
	
	for (int i = 0; i < N; ++i) c[i] = c[i+1];
	c[N-1] = v;
}



template <int N, int MIN, int MAX> void CValue<N, MIN, MAX>::InputBackSpace()
{
	b = true;
	
	for (int i = N-2; i >= 0; --i) c[i+1] = c[i];
	c[0] = ' ';
}



template <int N, int MIN, int MAX> void CValue<N, MIN, MAX>::InputEnter()
{
	if (b){
		CString s(c);
		s.Trim(_T(" "));
		while (s.Replace(_T("--"), _T("-")) != 0);
		Init(CStringW(s).GetBuffer(), b);
		
		SetValue((s.FindOneOf(_T("0123456789")) >= 0)? std::stoi(c): 0);
	} else {
		b = true;
	}
}



template <int N, int MIN, int MAX> void CValue<N, MIN, MAX>::InputCancel()
{
	if (b) Init(s, false);
}



template <int N, int MIN, int MAX> bool CValue<N, MIN, MAX>::SetValue(int v)
{
	int o = v;
	
	v = (v > MIN)? v: MIN;
	v = (v < MAX)? v: MAX;
	auto s = std::to_wstring(v);
	
	Init(s, false);
	this->s = s;
	
	i ^= 1;
	this->v[i] = v;
	
	return (v == o);
}



template <int N, int MIN, int MAX> bool CValue<N, MIN, MAX>::AddValue(int v)
{
	if (b) InputEnter();
	return SetValue(this->v[i] + v);
}



template <int N, int MIN, int MAX> bool CValue<N, MIN, MAX>::IsEditing()
{
	return b;
}



template <int N, int MIN, int MAX> int CValue<N, MIN, MAX>::GetValue() const
{
	return v[i];
}



template <int N, int MIN, int MAX> CString CValue<N, MIN, MAX>::GetText()
{
	return std::move(CString((b)? c: s.c_str()));
}



template <int N, int MIN, int MAX> void CValue<N, MIN, MAX>::Undo()
{
	SetValue(v[i^1]);
}



template <int N, int MIN, int MAX> void CValue<N, MIN, MAX>::Init(std::wstring s, bool b)
{
	c[N] = 0;
	for (int i = 0; i < N; ++i) c[i] = ' ';
	for (auto i = s.begin(); i != s.end(); ++i) InputChar((char)*i);
	
	this->b = b;
}



template struct CValue<1, 0, 1>;
template struct CValue<1, 0, 3>;
template struct CValue<1, 0, 7>;
template struct CValue<2, 0, 15>;
template struct CValue<2, 0, 31>;
template struct CValue<3, 0, 127>;
template struct CValue<3, 0, 128>;
template struct CValue<3, 0, 999>;
template struct CValue<4, -128, 128>;
template struct CValue<4, -999, 999>;
