
// Planets.h: основной файл заголовка для приложения Planets
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CPlanetsApp:
// Сведения о реализации этого класса: Planets.cpp
//

class CPlanetsApp : public CWinApp
{
public:
	CPlanetsApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPlanetsApp theApp;
