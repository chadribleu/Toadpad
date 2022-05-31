#include "Edit.h"

Edit::Edit(BaseWindow* p_parent, int p_width, int p_height, const wchar_t* p_text,
	unsigned long p_style, unsigned long p_wsex)
{
	Create(p_text, 0, 0, p_width, p_height, p_style, p_wsex, p_parent);
}

Edit::~Edit() 
{
	return;
}

bool Edit::SetWordWrap(bool wordwrap)
{
	RECT editRect = { 0 };

	GetWindowRect(self, &editRect);

	int width = editRect.right - editRect.left;
	int height = editRect.bottom - editRect.top;

	HWND tempEdit = NULL;
	DWORD eStyles = (DWORD)GetWindowLongPtr(self, GWL_STYLE);

	if (!wordwrap && ((eStyles & WS_HSCROLL) == 0)) // If wordwrap == false and the window does not contains a horizontal scrollbar
	{
		tempEdit = CreateWindowExW(WS_EX_ACCEPTFILES, ClassName(), (LPCWSTR)NULL,
			eStyles | WS_HSCROLL | ES_MULTILINE,
			0, 0, width, height,
			parent, /*Identifier here*/0, NULL, NULL);
	}
	else if (wordwrap && ((eStyles & WS_HSCROLL) == 0)) // If wordwrap == true and the window does not contains a horizontal scrollbar
	{
		tempEdit = CreateWindowExW(WS_EX_ACCEPTFILES, ClassName(), NULL,
			eStyles | ~WS_HSCROLL,
			0, 0, width, height,
			parent, /*Identifier here*/0, NULL, NULL);
	}
	else
	{
		return wordwrap;
	}

	// Swap buffers and destroy the old EDIT Window
	HANDLE hTempMem = (HANDLE)SendMessageW(tempEdit, EM_GETHANDLE, 0, 0);
	HANDLE hEditMem = (HANDLE)SendMessage(self, EM_GETHANDLE, 0, 0);

	SendMessageW(self, EM_SETHANDLE, reinterpret_cast<WPARAM>(hTempMem), 0);
	SendMessageW(tempEdit, EM_SETHANDLE, reinterpret_cast<WPARAM>(hEditMem), 0);

	// Delete the temporary buffer
	UpdateWindow(tempEdit);
	if (LocalFree(hTempMem) == hTempMem)
	{
		MessageBox(self, L"Error while freeing the allocated buffer", L"An error has occured", MB_OK);
	}

	// Update the current area
	ShowWindow(tempEdit, SW_SHOW);
	DestroyWindow(self);
	
	self = tempEdit;
	SetFocus(self);

	return wordwrap;
}