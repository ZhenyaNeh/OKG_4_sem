﻿
// laba_3.h: основной файл заголовка для приложения lab_3
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// Clab2App:
// Сведения о реализации этого класса: laba_3.cpp
//

class Clab2App : public CWinApp
{
public:
	Clab2App();


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Clab2App theApp;
