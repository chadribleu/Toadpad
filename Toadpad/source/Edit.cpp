#include "Edit.h"

Edit::Edit(AbstractWindow* p_parent, int p_width, int p_height, const wchar_t* p_text,
	unsigned long p_style, unsigned long p_wsex, UINT_PTR identifier) {
	Create(p_text, 0, 0, p_width, p_height, p_style, p_wsex, p_parent, (HMENU)identifier);
}

Edit::~Edit() {
	return;
}

bool Edit::setWordWrap(bool wordwrap)
{
	RECT editRect = { 0 };

	GetWindowRect(self, &editRect);

	int width = editRect.right - editRect.left;
	int height = editRect.bottom - editRect.top;

	HWND tempEdit = NULL;
	UINT_PTR winStyle = (UINT_PTR)GetWindowLongPtr(self, GWL_STYLE);

	if ((winStyle & ES_MULTILINE) == 0) { return false; }

	if ((!wordwrap) && ((winStyle & WS_HSCROLL) == 0))
	{
		winStyle |= WS_HSCROLL;

		tempEdit = CreateWindowExW(WS_EX_ACCEPTFILES, ClassName(), L"",
			(DWORD)winStyle,
			0, 0, width, height,
			parent, /*Identifier here*/0, NULL, NULL);
	}
	else if (wordwrap && ((winStyle & WS_HSCROLL) == WS_HSCROLL)) {
		winStyle &= ~WS_HSCROLL;

		tempEdit = CreateWindowExW(WS_EX_ACCEPTFILES, ClassName(), L"",
			(DWORD)winStyle,
			0, 0, width, height,
			parent, /*Identifier here*/0, NULL, NULL);

		if (tempEdit == NULL) {
			return false;
		}
	}
	else {
		return true;
	}

	HLOCAL hTempMem = (HLOCAL)SendMessageW(tempEdit, EM_GETHANDLE, 0, 0);
	HLOCAL hEditMem = (HLOCAL)SendMessageW(self, EM_GETHANDLE, 0, 0);

	SendMessageW(self, EM_SETHANDLE, reinterpret_cast<WPARAM>(hTempMem), 0);
	SendMessageW(tempEdit, EM_SETHANDLE, reinterpret_cast<WPARAM>(hEditMem), 0);

	if (LocalFree(hTempMem) == hTempMem) {
		MessageBox(self, L"Error while freeing the allocated buffer", L"An error has occured", MB_OK);
		return false;
	}

	UpdateWindow(tempEdit);
	ShowWindow(tempEdit, SW_SHOW);
	DestroyWindow(self);

	self = tempEdit;
	SetFocus(self);

	return true;
}

void Edit::replaceSel(std::wstring text) {
	SendMessage(self, EM_REPLACESEL, (WPARAM)TRUE, (LPARAM)text.data());
}

void Edit::undo() {
	SendMessage(self, EM_UNDO, 0, 0);
}

SelectionRange Edit::getSelection() {
	SelectionRange sr{ 0, 0 };
	SendMessage(self, EM_GETSEL, (WPARAM)&sr.begin, (LPARAM)&sr.end);
	return sr;
}

void Edit::select(SelectionRange selectionRange) {
	SendMessage(self, EM_SETSEL, (WPARAM)selectionRange.begin, (LPARAM)selectionRange.end);
}

void Edit::select(unsigned long begin, unsigned long end) {
	select(SelectionRange{ begin, end });
}