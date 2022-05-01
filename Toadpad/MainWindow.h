#pragma once

#include "resources.h"
#include "FilePicker.h"
#include "Document.h"

#include "AbstractWindow.h"
#include <windowsx.h>

#include "Edit.h"
#include "Menu.h"

class MainWindow : public BaseWindow {
public:
	MainWindow(HINSTANCE p_instance, int p_cmdShow);
	~MainWindow();

	int Exec();
	inline const wchar_t* ClassName() { return L"Toadpad32"; }

private:
	// Controls
	Edit* edit;

	// Window Manager
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};