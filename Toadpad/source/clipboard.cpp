#include "clipboard.h"

Clipboard::Clipboard() {}

Clipboard::Clipboard(AbstractWindow const& parent)
{
	m_parent = parent.Handle();
}

Clipboard::~Clipboard()
{
	CloseClipboard();
}

bool Clipboard::open(bool delayedRendering)
{
	if (OpenClipboard(!delayedRendering ? m_parent : NULL) == TRUE) {
		return true;
	}
	return false;
}

bool Clipboard::close()
{
	if (CloseClipboard() == TRUE) {
		return true;
	}
	return false;
}

void Clipboard::setText(std::wstring const& text)
{
	int size = Utils::StringSize(text.data());
	// Allocate some memory to store the text
	HANDLE hMemory = GlobalAlloc(GHND, size * sizeof(wchar_t));
	wchar_t* lpText = (wchar_t*)GlobalLock(hMemory); // Allow Windows to use the memory
	
	if (lpText != NULL) {
		wchar_t* tmpPtr = Utils::StringCopy(lpText, text.data(), (unsigned int)text.size());
		if (tmpPtr) {
			GlobalUnlock(hMemory);
			EmptyClipboard();
			SetClipboardData(CF_UNICODETEXT, hMemory);
		}
	}
}

std::wstring Clipboard::getText()
{
	HANDLE hMem = NULL;
	std::wstring text;
	wchar_t* buff = NULL;

	if (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
		hMem = GetClipboardData(CF_UNICODETEXT);
		if (hMem) {
			buff = (wchar_t*)GlobalLock(hMem);
			GlobalUnlock(hMem);
			text = buff;
		}
	}
	return text;
}

bool Clipboard::clear()
{
	if (EmptyClipboard() == TRUE) {
		return true;
	}
	return false;
}

std::vector<UINT> Clipboard::enumAvailableFormats()
{
	UINT result = 0;
	std::vector<UINT> fTable;
	while (result != ERROR_SUCCESS) {
		result = GetLastError();
		fTable.push_back(EnumClipboardFormats(0));
	}
	return fTable;
}