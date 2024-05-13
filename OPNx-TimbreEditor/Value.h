#pragma once



#include <string>



struct IValue
{
	virtual ~IValue(){}
	
	IValue(){}
	
	virtual void InputChar(char v) = 0;
	virtual void InputBackSpace() = 0;
	virtual void InputEnter() = 0;
	virtual void InputCancel() = 0;
	virtual void SetValue(int v) = 0;
	virtual void AddValue(int v) = 0;
	
	virtual bool IsEditing() = 0;
	virtual int GetValue() const = 0;
	virtual CString GetText() = 0;
	
	virtual void Undo() = 0;
};



template <int N, int MIN, int MAX>
struct CValue : IValue
{
	int v[2];
	int i;
	std::wstring s;
	wchar_t c[N+1];
	bool b;
	
	~CValue() override {}
	
	CValue();
	
	void InputChar(char v) override;
	void InputBackSpace() override;
	void InputEnter() override;
	void InputCancel() override;
	void SetValue(int v) override;
	void AddValue(int v) override;
	
	bool IsEditing() override;
	int GetValue() const override;
	CString GetText() override;
	
	void Undo() override;
	
	void Init(std::wstring s, bool b);
};



struct CDummy : IValue
{
	~CDummy() override {}
	CDummy(){}
	
	void InputChar(char v) override {}
	void InputBackSpace() override {}
	void InputEnter() override {}
	void InputCancel() override {}
	void SetValue(int v) override {}
	void AddValue(int v) override {}
	
	bool IsEditing() override { return false; }
	int GetValue() const override { return 0; }
	CString GetText() override { return std::move(CString(_T("-"))); }
	
	void Undo() override {}
};
