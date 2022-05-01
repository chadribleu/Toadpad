#include "AbstractWindow.h"

AbstractWindow::AbstractWindow()
	: self(NULL), parent(NULL), hInst(GetModuleHandle(NULL)), menu(false), wcex{ 0 } {}

AbstractWindow::~AbstractWindow()
{
	DestroyWindow(self);
}

// ---------------------------------------
// Register the window class
// Start the main loop
// ---------------------------------------
ATOM AbstractWindow::Register(HINSTANCE p_instance) {
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hInstance = hInst;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.lpfnWndProc = WindowProcedure;
	wcex.lpszClassName = ClassName();

	return RegisterClassExW(&wcex);
}

// ---------------------------------------
// Default Window Procedure, assign the 
// window its HandleMessage function
// ---------------------------------------
LRESULT AbstractWindow::WindowProcedure(HWND p_hWnd, UINT p_uMsg, WPARAM p_wParam, LPARAM p_lParam) {
	AbstractWindow* pThis = NULL;

	if (p_uMsg == WM_NCCREATE)
	{
		CREATESTRUCT* pCreateData = reinterpret_cast<CREATESTRUCT*>(p_lParam);
		pThis = (AbstractWindow*)pCreateData->lpCreateParams;
		SetWindowLongPtr(p_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));

		pThis->self = p_hWnd;
	}
	else
	{
		pThis = (AbstractWindow*)GetWindowLongPtr(p_hWnd, GWLP_USERDATA);
	}
	if (pThis)
	{
		return pThis->HandleMessage(p_uMsg, p_wParam, p_lParam);
	}
	else
	{
		LRESULT ch = DefWindowProc(p_hWnd, p_uMsg, p_wParam, p_lParam);
		return ch;
	}
}

// ---------------------------------------
// Set Window properties
// ---------------------------------------
void AbstractWindow::SetMenuBar(MenuBar* p_bar)
{
	// Warning: SetMenu replace the old menu if there's any, but it doesn't destroy it!
	SetMenu(self, p_bar->GetHandle());
}

void AbstractWindow::SetText(LPCWSTR p_text)
{
	SendMessage(self, WM_SETTEXT, 0, (LPARAM)p_text);
}

std::wstring AbstractWindow::GetText() const
{
	int size = GetWindowTextLength(self);
	wchar_t* str = (wchar_t*)malloc(size * sizeof(wchar_t));
	GetWindowText(self, str, size);

	std::wstring string(str);
	free(str);

	return string;
}

LRESULT AbstractWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(self, uMsg, wParam, lParam);
}

bool AbstractWindow::Create(const wchar_t* p_title, int p_x, int p_y, int p_width, int p_height, DWORD p_style, DWORD p_exStyle,
	AbstractWindow* p_parent, HMENU p_menu, HINSTANCE p_instance)
{
	bool isChild = false;
	DWORD styles = p_style;

	if (p_parent != NULL)
	{
		isChild = true;
		parent = p_parent->Handle();
		styles += toadenum::style::Window::CHILD;
	}

	WNDCLASSEX tempWcx{ 0 };
	if (GetClassInfoEx(p_instance, ClassName(), &tempWcx) == FALSE) // The class does not exist
	{
		Register(p_instance);
	}

	self = CreateWindowExW(p_exStyle, ClassName(), p_title,
		styles, p_x, p_y, p_width, p_height,
		isChild ? p_parent->Handle() : NULL,
		p_menu, p_instance, this);

	if (NULL == self)
	{
		int err = GetLastError();
		return false;
	}
	else
	{
		ShowWindow(self, SW_SHOW);
		UpdateWindow(self);

		return true;
	}
}

bool AbstractWindow::Show(bool show)
{
	if (ShowWindow(self, show ? SW_SHOW : SW_HIDE) == TRUE)
	{
		return true;
	}
	return false;
}

bool AbstractWindow::Move(int p_x, int p_y, int p_width, int p_height) {
	if (SetPos(p_x, p_y) == TRUE && SetGeometry(p_width, p_height) == TRUE) {
		return true;
	}
	else
	{
		return false;
	}
}

bool AbstractWindow::SetGeometry(int p_width, int p_height) {
	RECT rec = { 0 }, newClient{ 0, 0, p_width, p_height };
	GetWindowRect(self, &rec);
	AdjustWindowRectEx(&newClient, WS_OVERLAPPEDWINDOW, false, 0);

	if (SetWindowPos(self, NULL, 0, 0, p_width, p_height, SWP_NOMOVE | SWP_NOOWNERZORDER) == TRUE) {
		return true;
	}
	else
	{
		return false;
	}
}

bool AbstractWindow::SetPos(int p_x, int p_y) {
	RECT rec = { 0 };
	GetClientRect(self, &rec);

	// Get Current Screen + origin

	RECT dwm = { 0 }, window = { 0 };
	GetWindowRect(self, &window);
	DwmGetWindowAttribute(self, DWMWA_EXTENDED_FRAME_BOUNDS, &dwm, sizeof(RECT));

	if (MoveWindow(self, p_x - (dwm.left - window.left), p_y, rec.right, rec.bottom, TRUE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

unsigned long AbstractWindow::GetTextLenght()
{
	const int size = GetWindowTextLengthW(self);
	wchar_t* tempBuff = new wchar_t[size];
	unsigned long buffSize = (int)SendMessageW(self, WM_GETTEXT, (WPARAM)size, (LPARAM)tempBuff);
	delete tempBuff;

	return buffSize;
}