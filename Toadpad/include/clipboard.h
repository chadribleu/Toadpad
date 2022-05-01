#pragma once

#include <string>
#include <vector>

#include <Windows.h>

#include "utils.h"
#include "AbstractWindow.h"

class AbstractWindow;

class Clipboard
{
public:
	Clipboard();
	Clipboard(AbstractWindow const& parent);
	Clipboard(Clipboard const&) = delete;
	~Clipboard();

	bool open(bool delayedRendering = false);
	bool close();
	void setText(const std::wstring& text);
	std::wstring getText();
	bool clear();

	/*void addFormatListener();
	void removeFormatListener();*/
	std::vector<UINT> enumAvailableFormats();

private:
	HWND m_parent;
	// DWORD m_format;
	bool m_isOpen;
};