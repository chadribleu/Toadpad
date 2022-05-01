#pragma once

#include <Windows.h>
#include <vector>

#include "AbstractWindow.h"
#include "Menu.h"

class BaseWindow;
class Menu;

class MenuBar 
{
public:
	MenuBar();
	MenuBar(BaseWindow* p_parent);
	
	inline void SetParent(BaseWindow* p_parent) { parent = p_parent; }
	inline BaseWindow* GetParent() const { return parent; }
	inline HMENU GetHandle() const { return self; }

	void AddMenu(const wchar_t* p_name, Menu* p_menu);

private:
	BaseWindow* parent;
	HMENU self;
};