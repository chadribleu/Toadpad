#pragma once

#ifdef CHADRIBLEUDIALOGS_EXPORTS
#define CHADRIBLEUDIALOGS_API __declspec(dllexport)
#else
#define CHADRIBLEUDIALOGS_API __declspec(dllimport)
#endif

#include <string>

#include "framework.h"

#define BUFFSIZE MAX_PATH

class CHADRIBLEUDIALOGS_API FilePicker {
public:
	enum class mode {
		SAVE,
		OPEN
	};

	FilePicker(HWND parent, FilePicker::mode mode, LPCWSTR caption = L"");
	~FilePicker();

	std::wstring FileName() { return ofn.lpstrFile; };
	bool ShowDialog(LPCWSTR initialFileName, LPCWSTR initialDir, LPCWSTR filters);

private:
	OPENFILENAME ofn;
	mode dlgStyle;
	wchar_t* buffer;
};
