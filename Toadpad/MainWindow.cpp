#include "MainWindow.h"

MainWindow::MainWindow(HINSTANCE p_instance, int p_cmdShow)
{
	RECT rc{ 0, 0, 800, 600 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, TRUE);

	Create(L"Toadpad 2.0", CW_USEDEFAULT, CW_USEDEFAULT, rc.right, rc.bottom, Style::OVERLAPPEDWINDOW, ExStyle::DEFAULT);

	// Controls
	edit = new Edit(this, 350, 120, L"Edit text", BaseWindow::BORDER | BaseWindow::VSCROLL);

	// Create a dummy menu
	Menu fileMenu;
	fileMenu.AddItem(L"Open", 500);
	fileMenu.AddItem(L"Save", 1000);

	Menu editMenu;
	MenuItem* itm = editMenu.AddItem(L"Copy", 2000);
	editMenu.AddItem(L"Paste", 2500);

	MenuBar bar(this);
	bar.AddMenu(L"File", &fileMenu);
	bar.AddMenu(L"Edit", &editMenu);
}

MainWindow::~MainWindow() {}

// ---------------------------------------------
// Messages functions
// ---------------------------------------------

int MainWindow::Exec() {
	MSG message = { 0 };

	while (GetMessage(&message, NULL, NULL, NULL) > 0) 
	{
		TranslateMessage(&message);
		DispatchMessageW(&message);
	}

	return (int)message.wParam;
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	// ----------------------------------------
	// Handle messages
	// ----------------------------------------
	switch (uMsg) 
	{
	case WM_SIZE:
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 500:
			edit->SetWordWrap(true);
			break;
		case 1000:
			edit->SetWordWrap(false);
			break;
		}
		break;

	case WM_DESTROY:
	{
		delete edit;
		int b = GetLastError();
		PostQuitMessage(0);
	}

	default:
		return DefWindowProc(self, uMsg, wParam, lParam);
	}
	return 0;
}