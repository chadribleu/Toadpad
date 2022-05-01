#ifndef MENUITEM_H
#define MENUITEM_H

#include "utils.h"
#include "application.h"
#include "accelerators.h"
#include <Windows.h>

#define MAX_MEMALLOC 64

class MenuItem 
{
public:
	friend class Menu;

	MenuItem(const wchar_t* p_itmName, UINT_PTR p_identifier, KeyboardAccelDesc* shortcut = nullptr);

	// Getter
	inline HMENU GetParent() const 
	{ return parent; }
	inline const wchar_t* GetName() const 
	{ return name; }
	inline UINT_PTR GetIdentifier() const 
	{ return identifier; }
	inline int GetIndex() const 
	{ return index; }
	inline bool IsChecked() const 
	{ return checked; }
	inline bool IsEnabled() const 
	{ return enabled; }

	void SetName(const wchar_t* p_name);
	void SetEnabled(bool enabled);
	void SetChecked(bool checked);
	void Break(bool verticalLine);
	void UnBreak();
	bool SetBmps(HBITMAP p_checked, HBITMAP p_unchecked);
	
	// New naming convention
	void assignShortcut(KeyboardAccelDesc& shortcutItem); // set the KeyboardAccelDesc 'cmd' variable to the item identifier

private:
	HMENU parent;
	int index;

	UINT_PTR identifier;
	wchar_t name[MAX_MEMALLOC];

	// Bitmaps
	HBITMAP hCheckedBmp;
	HBITMAP hUncheckedBmp;

	// Shortcut
	KeyboardAccelDesc keybAcc;

	// Booleans
	bool enabled;
	bool checked;
	bool _break;
	bool hasShortcut;
};

#endif