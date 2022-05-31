#include "pch.h"
#include "FilePicker.h"

FilePicker::FilePicker(HWND parent, FilePicker::mode mode, LPCWSTR caption)
	: dlgStyle(mode) {
	this->buffer = (wchar_t*)calloc(BUFFSIZE, sizeof(wchar_t));

	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = parent;
	ofn.hInstance = GetModuleHandle(NULL);
	ofn.lpstrTitle = caption[0] == NULL ? NULL : caption;

	ofn.nFilterIndex = 2; // All files
	ofn.Flags = OFN_NONETWORKBUTTON |
		OFN_OVERWRITEPROMPT |
		OFN_PATHMUSTEXIST;
}

bool FilePicker::ShowDialog(LPCWSTR initialFileName, LPCWSTR initialDir, LPCWSTR filters) {
	if (!initialFileName[0] == NULL) {
		int k = 0;
		for (int i = (int)*initialFileName; i != '\0';) {
			buffer[k] = initialFileName[k];
			i = buffer[k];
			++k;
		}
	}
	ofn.nMaxFile = BUFFSIZE * sizeof(wchar_t);
	ofn.lpstrInitialDir = initialDir;
	ofn.lpstrFile = this->buffer;
	ofn.lpstrFilter = filters;

	BOOL result;
	switch (dlgStyle) {
	case FilePicker::mode::SAVE:
		result = GetSaveFileName(&this->ofn);
		break;
	case FilePicker::mode::OPEN:
		result = GetOpenFileName(&this->ofn);
		break;
	}

	if (result == FALSE) {
		DWORD c = CommDlgExtendedError();
		return false;
	}

	return true;
}

FilePicker::~FilePicker() {
	free(buffer);
}