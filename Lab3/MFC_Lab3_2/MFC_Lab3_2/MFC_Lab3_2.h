
// MFC_Lab3_2.h: основной файл заголовка для приложения MFC_Lab3_2
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CMFCLab32App:
// Сведения о реализации этого класса: MFC_Lab3_2.cpp
//

class CMFCLab32App : public CWinApp
{
public:
	CMFCLab32App() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCLab32App theApp;
