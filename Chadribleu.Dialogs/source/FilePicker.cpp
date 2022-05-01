#include "pch.h"
#include "FilePicker.h"

FilePicker::FilePicker(HWND parent, FilePicker::Mode mode, const std::wstring& caption)
	: m_dlgStyle(mode) {
	m_buffer = new wchar_t[BUFFSIZE];

	memset(&m_ofn, 0, sizeof(OPENFILENAME));
	m_ofn.lStructSize = sizeof(OPENFILENAME);
	m_ofn.hwndOwner = parent;
	m_ofn.hInstance = GetModuleHandle(NULL);
	m_ofn.lpstrTitle = caption.data() == NULL ? NULL : caption.data();
	m_ofn.Flags = OFN_NONETWORKBUTTON |
		OFN_OVERWRITEPROMPT |
		OFN_PATHMUSTEXIST;
}

// TODO: Replace the default initial directory with the user's "Documents" path
bool FilePicker::showDialog(const std::wstring& initialFileName, const std::wstring& initialDir, const std::wstring& filters) {
	if (!initialFileName[0] == NULL) {
		size_t initFileName = initialFileName.length();
		for (size_t i = 0; i < initFileName; ++i) {
			m_buffer[i] = initialFileName[i];
			i = m_buffer[i];
		}
	}
	m_ofn.nMaxFile = BUFFSIZE * sizeof(wchar_t);
	m_ofn.lpstrInitialDir = initialDir.data();
	m_ofn.lpstrFile = m_buffer;
	m_ofn.lpstrFilter = filters.data();

	BOOL result;
	switch (m_dlgStyle) {
	case FilePicker::Mode::SAVE:
		result = GetSaveFileName(&m_ofn);
		break;
	case FilePicker::Mode::OPEN:
		result = GetOpenFileName(&m_ofn);
		break;
	}

	if (result == FALSE) {
		DWORD c = CommDlgExtendedError();
		return false;
	}

	return true;
}

void FilePicker::setFilters(const std::wstring& filters, int defaultIndex)
{
	size_t strLength = filters.length();
	wchar_t wchar;

	for (size_t i = 0; i != strLength; ++i) {
		wchar = filters[i];
		if (wchar == L'|') {
			m_buffer[i] = '\0';
		}
		else {
			m_buffer[i] = filters.data()[i];
		}
	}
	m_ofn.nFilterIndex = defaultIndex;
}

FilePicker::~FilePicker() {
	delete m_buffer;
}