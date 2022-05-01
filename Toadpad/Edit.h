#pragma once

#include "AbstractWindow.h"

class Edit : public BaseWindow
{
public:
	enum Style : unsigned long 
	{
		MULTILINE	= ES_MULTILINE,
		AUTOHSCROLL = ES_AUTOHSCROLL,
		AUTOVSCROLL = ES_AUTOVSCROLL,
		PASSWORD	= ES_PASSWORD,
		READONLY	= ES_READONLY,
		UPPERCASE	= ES_UPPERCASE,
		LOWERCASE	= ES_LOWERCASE,
		RIGHT		= ES_RIGHT,
		LEFT		= ES_LEFT,
		NUMBER		= ES_NUMBER,
		NOHIDESEL	= ES_NOHIDESEL,
		CENTER		= ES_CENTER
	};

	Edit(BaseWindow* p_parent = nullptr, int p_width = 200, int p_height = 20, const wchar_t* p_text = L"",
		unsigned long p_style = BaseWindow::Style::CHILD | Edit::Style::MULTILINE, unsigned long p_wsex = DEFAULT);
	~Edit();

	bool SetWordWrap(bool wordwrap);

	inline const wchar_t* ClassName() override { return L"EDIT"; };
};