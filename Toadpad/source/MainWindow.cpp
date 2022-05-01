#include "MainWindow.h"

MainWindow::MainWindow(HINSTANCE p_instance, int p_cmdShow)
{
	RECT rc{ 0, 0, 800, 600 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, TRUE);

	this->Create(L"Toadpad 2.0", CW_USEDEFAULT, CW_USEDEFAULT, rc.right, rc.bottom, 
		toadenum::style::Window::OVERLAPPEDWINDOW, toadenum::style::WindowExStyle::DEFAULT);
}

MainWindow::~MainWindow() {}

void MainWindow::OnCreate() {
	m_edit = new Edit(this, 0, 0, L"", toadenum::style::Window::VSCROLL | EditStyle::MULTILINE);
	
	// File
	KeyboardAccelDesc shNew(Modifiers::CTRL, L'n');
	KeyboardAccelDesc shOpen(Modifiers::CTRL, L'o');
	KeyboardAccelDesc shSave(Modifiers::CTRL, L's');
	KeyboardAccelDesc shSaveAs(Modifiers::CTRL | Modifiers::SHIFT, L's');
	
	// Edit
	KeyboardAccelDesc shUndo(Modifiers::CTRL, L'z');
	KeyboardAccelDesc shCut(Modifiers::CTRL, L'x');
	KeyboardAccelDesc shCopy(Modifiers::CTRL, L'c');
	KeyboardAccelDesc shPaste(Modifiers::CTRL, L'v');
	KeyboardAccelDesc shSelAll(Modifiers::CTRL, L'a');

	// File menu
	m_menuBar = new MenuBar(this);

	m_fileMenu = new Menu;
	m_itmNew = m_fileMenu->AddItem(L"New", ID_NEW, &shNew);
	
	MenuItem* itmOpenTab = m_fileMenu->AddItem(L"Open a new tab", ID_NEWTAB);
	itmOpenTab->SetEnabled(false);
	
	m_itmOpen = m_fileMenu->AddItem(L"Open", ID_OPEN, &shOpen);
	m_itmSave = m_fileMenu->AddItem(L"Save", ID_SAVE, &shSave);
	m_itmSaveAs = m_fileMenu->AddItem(L"Save as...", ID_SAVEAS, &shSaveAs);
	
	m_fileMenu->AddSeparator();
	
	m_itmExit = m_fileMenu->AddItem(L"Exit", ID_EXIT);

	// Edit menu
	m_editMenu = new Menu;
	m_itmUndo = m_editMenu->AddItem(L"Undo", ID_UNDO, &shUndo);
	
	m_editMenu->AddSeparator();
	
	m_itmCut = m_editMenu->AddItem(L"Cut", ID_CUT, &shCut);
	m_itmCopy = m_editMenu->AddItem(L"Copy", ID_COPY, &shCopy);
	m_itmPaste = m_editMenu->AddItem(L"Paste", ID_PASTE, &shPaste);
	m_itmDelete = m_editMenu->AddItem(L"Delete", ID_DELETE);

	m_editMenu->AddSeparator();

	m_itmSelAll = m_editMenu->AddItem(L"Select All", ID_SELALL, &shSelAll);

	m_formatMenu = new Menu;
	m_itm_wordWrap = m_formatMenu->AddItem(L"Word Wrap", ID_ENABLEWORDWRAP);

	m_menuBar->AddMenu(L"File", m_fileMenu);
	m_menuBar->AddMenu(L"Edit", m_editMenu);
	m_menuBar->AddMenu(L"Format", m_formatMenu);
}

void MainWindow::OnOpen()
{
	FilePicker fp(self, FilePicker::mode::OPEN);
	fp.setDefaultIndex(2);

	std::map<std::wstring, std::wstring> filters = 
	{
		{ L"Code files", L"hpp;;h;;cpp;;c;;js;;xml;;rc" }, // Code files (*.HPP;*.H;*CPP;*.C;*.JS;*.XML;*.RC)
		{ L"All files", L"*" }
	};

	std::vector<std::wstring> arr { L"Text files (*.txt)|*.txt;*.bmp;*.fft|Code files|*.cpp;*.h;", L"Pictures|*;bmp;ai;", L"f" };

	fp.setFilters(filters);
	fp.ShowDialog(L"New File", L"C:/", L"");
	/*Set document path*/fp.FileName();
}

void MainWindow::OnSave()
{
}

void MainWindow::OnSaveAs()
{
}

void MainWindow::OnExit()
{
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	// ----------------------------------------
	// Handle messages
	// ----------------------------------------
	switch (uMsg) {
	case WM_CREATE:
		OnCreate();
		return 0;

	case WM_SIZE:
		m_edit->SetGeometry(LOWORD(lParam), HIWORD(lParam));
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_NEW:
		break;
		case ID_OPEN:
			OnOpen();
			break;
		case ID_SAVE:
			break;
		case ID_SAVEAS:
			break;
		case ID_EXIT:
			break;
		}
		break;

	case WM_DESTROY:
	{
		PostQuitMessage(GetLastError());
	}

	default:
		return DefWindowProc(self, uMsg, wParam, lParam);
	}
	return 0;
}