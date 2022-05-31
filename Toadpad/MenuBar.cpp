#include "MenuBar.h"

MenuBar::MenuBar() 
{
	self = CreateMenu();
}

MenuBar::MenuBar(BaseWindow* p_parent) : MenuBar()
{
	parent = p_parent;
	p_parent->SetMenuBar(this);
}

void MenuBar::AddMenu(const wchar_t* p_name, Menu* p_menu) 
{
	HMENU handle = p_menu->GetHandle();
	AppendMenuW(self, MF_POPUP, (UINT_PTR)handle, p_name);
	
	DrawMenuBar(MenuBar::parent->Handle());
}