


#include "pch.h"
#include "TimbreEditor.h"
#include "afxdialogex.h"
#include "SettingTab.h"



IMPLEMENT_DYNAMIC(CSettingTab, CDialogEx)



CSettingTab::~CSettingTab()
{
}



CSettingTab::CSettingTab(CWnd* pParent /*=nullptr*/)
:CDialogEx(IDD_SETTING_TAB, pParent)
{

}



void CSettingTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(CSettingTab, CDialogEx)
END_MESSAGE_MAP()
