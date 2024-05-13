
// TimbreEditor.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CTimbreEditorApp:
// このクラスの実装については、TimbreEditor.cpp を参照してください
//

class CTimbreEditorApp : public CWinApp
{
public:
	CTimbreEditorApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()

public:
	int GetValue(CString Key, int Default);
	bool SetValue(CString Key, int Value);
};

extern CTimbreEditorApp theApp;
