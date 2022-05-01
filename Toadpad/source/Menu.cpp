#include "Menu.h"

Menu::Menu() : self(CreatePopupMenu()) {}

Menu::~Menu() {}

MenuItem* Menu::AddItem(const wchar_t* p_name, UINT_PTR p_identifier, KeyboardAccelDesc* shortcut) {
	AppendMenuW(self, MF_STRING, p_identifier, p_name);

	MenuItem* item = new MenuItem(p_name, p_identifier, shortcut);
	int index = (int)mi.size();

	item->index = index;
	item->parent = self;

	mi.push_back(item);

	if (shortcut != nullptr) {
		item->assignShortcut(*shortcut);
	}

	return item;
}

void Menu::AddSeparator() { // Create an empty item that is inaccessible to the user of the class
	AppendMenu(self, MF_SEPARATOR, 0, NULL);
	MenuItem* itmEmpty = new MenuItem(L"-", 0);
	itmEmpty->index = mi.size();
	itmEmpty->parent = self;
	mi.push_back(itmEmpty);
}

void Menu::SetParent(const MenuBar* p_parent) {
	parentBar = p_parent->GetHandle();
}

void Menu::AddMenu(const wchar_t* p_name, const Menu& p_menu) {
	AppendMenuW(self, MF_POPUP, (UINT_PTR)p_menu.self, p_name);
}