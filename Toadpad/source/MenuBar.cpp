#include "MenuBar.h"

MenuBar::MenuBar() 
{
	self = CreateMenu();
}

MenuBar::MenuBar(AbstractWindow* p_parent) : MenuBar()
{
	parent = p_parent;
	p_parent->SetMenuBar(this);
}

MenuBar::~MenuBar()
{
	for (auto item : m_children) {
		delete item;
	}
}

void MenuBar::AddMenu(const wchar_t* p_name, Menu* p_menu) 
{
	HMENU handle = p_menu->GetHandle();
	AppendMenuW(self, MF_POPUP, (UINT_PTR)handle, p_name);
	
	m_children.push_back(p_menu);

	DrawMenuBar(MenuBar::parent->Handle());
}