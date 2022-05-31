#include "MenuItem.h"

MenuItem::MenuItem(const wchar_t* p_itmName, UINT_PTR p_identifier) 
	: identifier(p_identifier), hUncheckedBmp(NULL), hCheckedBmp(NULL), enabled(true), checked(false), _break(false)
{
	wcscpy_s(name, p_itmName);
}

void MenuItem::SetEnabled(bool p_enabled) {
	UINT db = p_enabled ? MF_ENABLED : MF_GRAYED;
	EnableMenuItem(parent, index, db | MF_BYPOSITION);
	this->enabled = p_enabled;
}

void MenuItem::SetChecked(bool p_checked) {
	UINT ck = p_checked ? MF_CHECKED : MF_UNCHECKED;
	CheckMenuItem(parent, index, ck | MF_BYPOSITION);
	this->checked = p_checked;
}

void MenuItem::Break(bool verticalLine) {
	UINT style = verticalLine ? MF_MENUBARBREAK : MF_MENUBREAK;
	ModifyMenuW(parent, index, MF_STRING | style | MF_BYPOSITION, identifier, name);
}

void MenuItem::UnBreak() 
{
	ModifyMenu(parent, index, MF_STRING | MF_BYPOSITION, identifier, name);
}

bool MenuItem::SetBmps(HBITMAP p_checked, HBITMAP p_unchecked) 
{
	// TODO: HBITMAP Object (BitmapManager)
	if (SetMenuItemBitmaps(parent, index, MF_BYPOSITION, p_unchecked, p_checked) != NULL) 
	{
		hCheckedBmp = p_checked;
		hUncheckedBmp = p_unchecked;
	}
	else 
	{
		return false;
	}
	return true;
}

void MenuItem::SetName(const wchar_t* p_name) 
{
	Utils::StringCopy(name, p_name);
	ModifyMenu(parent, index, MF_STRING | MF_BYPOSITION, identifier, name);
}