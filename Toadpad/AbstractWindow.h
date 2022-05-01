#pragma once

#include <Windows.h>
#include <dwmapi.h>

#include "MenuBar.h"

class MenuBar;

class BaseWindow {
public:
	enum Style : unsigned long
	{
		USEDEFAULT			= 0x00000000L,
		OVERLAPPED			= WS_OVERLAPPED,
		OVERLAPPEDWINDOW	= WS_OVERLAPPEDWINDOW,
		CHILD				= WS_CHILD,
		DISABLED			= WS_DISABLED,
		HSCROLL				= WS_HSCROLL,
		VSCROLL				= WS_VSCROLL,
		VISIBLE				= WS_VISIBLE,
		BORDER				= WS_BORDER,
		CAPTION				= WS_CAPTION,
		CLIPCHILDREN		= WS_CLIPCHILDREN,
		CLIPSIBLINGS		= WS_CLIPSIBLINGS,
		DLGFRAME			= WS_DLGFRAME,
		GROUP				= WS_GROUP,
		MINIMIZE			= WS_ICONIC,
		MINIMIZEBUTTON		= WS_MINIMIZEBOX,
		POPUP				= WS_POPUP,
		POPUPMENU			= WS_POPUPWINDOW,
		RESIZEABLE			= WS_THICKFRAME,
		SYSMENU				= WS_SYSMENU,
		TABFOCUS			= WS_TABSTOP
	};

	enum ExStyle : unsigned long
	{
		DEFAULT		= 0x00000000L,
		DGFILES		= WS_EX_ACCEPTFILES,
		CONTEXTHELP = WS_EX_CONTEXTHELP
	};

	BaseWindow();
	
	virtual ~BaseWindow() = 0;
	virtual const wchar_t* ClassName() = 0;

	void SetMenuBar(MenuBar* p_bar);

	inline HWND Handle() const { return self; }
	inline HWND Parent() const { return parent; }

	void SetText(LPCWSTR p_text);
	wchar_t* GetText() const;

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

	// Call this function in each derived class's constructors
	bool Create(const wchar_t* p_title,
		int p_x = CW_USEDEFAULT, int p_y = CW_USEDEFAULT,
		int p_width = 100, int p_height = 100,
		DWORD p_style = Style::OVERLAPPEDWINDOW, DWORD p_exStyle = ExStyle::DEFAULT, BaseWindow* p_parent = NULL,
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