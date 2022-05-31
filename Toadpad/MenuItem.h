#pragma once

#include "utils.h"

#define MAX_MEMALLOC 64

class MenuItem {
public:
	friend class Menu;

	MenuItem(const wchar_t* p_itmName, UINT_PTR p_identifier);

	// Getter
	inline HMENU GetParent() const { return parent; }
	inline const wchar_t* GetName() const { return name; }
	inline UINT_PTR GetIdentifier() const { return identifier; }
	inline int GetIndex() const { return index; }
	inline bool IsChecked() const { return checked; }
	inline bool IsEnabled() const { return enabled; }

	void SetName(const wchar_t* p_name);
	void SetEnabled(bool enabled);
	void SetChecked(bool checked);
	void Break(bool verticalLine);
	void UnBreak();
	bool SetBmps(HBITMAP p_checked, HBITMAP p_unchecked);

private:
	HMENU parent;
	int index;

	UINT_PTR identifier;
	wchar_t name[MAX_MEMALLOC];

	// Bitmaps
	HBITMAP hCheckedBmp;
	HBITMAP hUncheckedBmp;

	bool enabled;
	bool checked;
	bool _break;
};