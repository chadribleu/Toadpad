#ifndef FILEPICKER_H
#define FILEPICKER_H

#ifdef CHADRIBLEUDIALOGS_EXPORTS
#define CHADRIBLEUDIALOGS_API __declspec(dllexport)
#else
#define CHADRIBLEUDIALOGS_API __declspec(dllimport)
#endif

#define BUFFSIZE MAX_PATH

#include "framework.h"

class CHADRIBLEUDIALOGS_API FilePicker {
public:
	enum class Mode {
		SAVE,
		OPEN
	};

	FilePicker(HWND parent, FilePicker::Mode mode, const std::wstring& caption = L"");
	~FilePicker();

	inline std::wstring getPath() { return std::wstring(m_ofn.lpstrFile); }
	bool showDialog(const std::wstring& initialFileName, const std::wstring& initialDir = L"C:/Users/", const std::wstring& filters = std::wstring());
	void setFilters(const std::wstring& filters, int defaultIndex = 0);

private:
	OPENFILENAME m_ofn;
	FilePicker::Mode m_dlgStyle;
	wchar_t* m_buffer;
};

#endif // FILEPICKER_H