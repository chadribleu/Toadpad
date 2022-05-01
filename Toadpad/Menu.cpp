#include "Menu.h"

Menu::Menu() 
{
	self = CreatePopupMenu();
}

MenuItem* Menu::AddItem(const wchar_t* p_name, UINT_PTR p_identifier)
{
	AppendMenuW(self, MF_STRING, p_identifier, p_name);

	MenuItem* item = new MenuItem(p_name, p_identifier);
	int index = (int)mi.size();

	item->index = index;
	item->parent = self;

	mi.push_back(item);

	return item;
}

void Menu::AddSeparator() 
{
	AppendMenuW(self, MF_SEPARATOR, NULL, NULL);
}

void Menu::SetParent(const MenuBar* p_parent) 
{
	parentBar = p_parent->GetHandle();
}

void Menu::AddMenu(const wchar_t* p_name, const Menu& p_menu) 
{
	AppendMenuW(self, MF_POPUP, (UINT_PTR)p_menu.self, p_name);
}

Menu::~Menu() {}