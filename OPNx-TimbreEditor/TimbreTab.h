#pragma once



#include "afxdialogex.h"



class CTimbreTab : public CDialogEx
{
	DECLARE_DYNAMIC(CTimbreTab)
	
public:
	virtual ~CTimbreTab();
	
	CTimbreTab(CWnd* pParent = nullptr);
	
	#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMBRE_TAB };
	#endif
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual void OnCancel();
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	DECLARE_MESSAGE_MAP()
	
protected:
	int mx;
	int my;
	bool mbEditing;
	
	void SetColor(CDC* pDC, int x, int y);
public:
	void SetCur(int x, int y, bool bEditing);
};
