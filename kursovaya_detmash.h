
// kursovaya_detmash.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CkursovayadetmashApp:
// Сведения о реализации этого класса: kursovaya_detmash.cpp
//

class CkursovayadetmashApp : public CWinApp
{
public:
	CkursovayadetmashApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CkursovayadetmashApp theApp;
