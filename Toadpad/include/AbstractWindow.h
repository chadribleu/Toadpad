#pragma once

#include <Windows.h>
#include <dwmapi.h>
#include <string>

#include "toadenum.h"
#include "Menu.h"
#include "MenuBar.h"
#include "MenuItem.h"
#include "accelerators.h"

class MenuBar;

class AbstractWindow {
public:
	AbstractWindow();

	virtual ~AbstractWindow() = 0;
	virtual const wchar_t* ClassName() = 0;

	void SetMenuBar(MenuBar* p_bar);

	inline HWND Handle() const { return self; }
	inline HWND Parent() const { return parent; }

	void SetText(LPCWSTR p_text);
	std::wstring GetText() const;

	bool Show(bool show = true);
	bool Move(int p_x, int p_y, int p_width, int p_height);
	bool SetGeometry(int p_width, int p_height);
	bool SetPos(int p_x, int p_y);

	unsigned long GetTextLenght();

protected:
	// -----------------------------------------------------------------------------
	// Implement this function as public in any class whose inherits from BaseWindow
	// -----------------------------------------------------------------------------
	virtual LRESULT HandleMessage(UINT, WPARAM, LPARAM);

	bool Create(const wchar_t* p_title,
		int p_x = CW_USEDEFAULT, int p_y = CW_USEDEFAULT,
		int p_width = 100, int p_height = 100,
		DWORD p_style = toadenum::style::Window::OVERLAPPEDWINDOW, DWORD p_exStyle = toadenum::style::WindowExStyle::DEFAULT, AbstractWindow* p_parent = NULL,
		HMENU p_menu = (HMENU)NULL, HINSTANCE hInst = GetModuleHandle(NULL));

	HWND self;
	HWND parent;
	HINSTANCE hInst;

private:
	static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	ATOM Register(HINSTANCE p_instance);
	WNDCLASSEX wcex;

	bool menu;
	DWORD styles;
	DWORD exStyles;
};