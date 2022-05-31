#pragma once

#include <Windows.h>
#include <vector>

#include "MenuBar.h"
#include "MenuItem.h"

class MenuBar;

class Menu 
{
public:
	Menu();
	~Menu();

	MenuItem* AddItem(const wchar_t* p_name, UINT_PTR p_identifier);

	// Getter
	inline HMENU GetParent() const { return parentBar; }
	inline HMENU GetHandle() const { return self; }

	void AddMenu(const wchar_t* p_name, const Menu& p_menu);
	void AddSeparator();
	void SetParent(const MenuBar* p_parent);

private:
	HMENU parentBar;
	HMENU self;
	std::vector<MenuItem*> mi;
};