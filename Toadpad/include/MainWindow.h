#ifndef MAINWINDOW
#define MAINWINDOW

#include "toadenum.h"

#include "resources.h"
#include "FilePicker.h"
#include "DocumentHandler.h"
#include <windowsx.h>
#include <Windows.h>
#include <map>

#include "AbstractWindow.h"
#include "Edit.h"
#include "accelerators.h"
#include "Menu.h"

class Edit;

class MainWindow : public AbstractWindow {
public:
	MainWindow(HINSTANCE p_instance, int p_cmdShow);
	~MainWindow();

	inline const wchar_t* ClassName() { return L"Toadpad2"; }

private:
	// Controls
	Edit* m_edit;
	MenuBar* m_menuBar;

	Menu* m_fileMenu;
	MenuItem* m_itmNew;
	MenuItem* m_itmOpen;
	MenuItem* m_itmSave;
	MenuItem* m_itmSaveAs;
	MenuItem* m_itmExit;

	Menu* m_editMenu;
	MenuItem* m_itmUndo;
	MenuItem* m_itmCut;
	MenuItem* m_itmCopy;
	MenuItem* m_itmPaste;
	MenuItem* m_itmDelete;
	MenuItem* m_itmSelAll;

	Menu* m_formatMenu;
	MenuItem* m_itm_wordWrap;

	// Messages
	void OnCreate();
	void OnOpen();
	void OnSave();
	void OnSaveAs();
	void OnExit();

	// Main Window loop
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif