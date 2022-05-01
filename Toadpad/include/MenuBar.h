#ifndef MENUBAR_H
#define MENUBAR_H

#include <Windows.h>
#include <vector>

#include "AbstractWindow.h"
#include "Menu.h"

class AbstractWindow;
class Menu;

class MenuBar 
{
public:
	MenuBar();
	MenuBar(AbstractWindow* p_parent);
	~MenuBar();
	
	inline void SetParent(AbstractWindow* p_parent) { parent = p_parent; }
	inline AbstractWindow* GetParent() const { return parent; }
	inline HMENU GetHandle() const { return self; }

	void AddMenu(const wchar_t* p_name, Menu* p_menu);

private:
	AbstractWindow* parent;
	HMENU self;
	std::vector<Menu*> m_children;
};

#endif