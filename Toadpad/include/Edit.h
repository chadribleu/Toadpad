#ifndef EDIT_H
#define EDIT_H

#include "MainWindow.h"
#include "toadenum.h"
#include "DocumentHandler.h"

#define DEF_WIDTH 200
#define DEF_HEIGHT 20

namespace EditStyle {
	inline int MULTILINE = ES_MULTILINE;
	inline int AUTOHSCROLL = ES_AUTOHSCROLL;
	inline int AUTOVSCROLL = ES_AUTOVSCROLL;
	inline int PASSWORD = ES_PASSWORD;
	inline int READONLY = ES_READONLY;
	inline int UPPERCASE = ES_UPPERCASE;
	inline int LOWERCASE = ES_LOWERCASE;
	inline int RIGHT = ES_RIGHT;
	inline int LEFT = ES_LEFT;
	inline int NUMBER = ES_NUMBER;
	inline int NOHIDESEL = ES_NOHIDESEL;
	inline int CENTER = ES_CENTER;
};

struct SelectionRange {
	unsigned long begin, end;
};

class Edit : public AbstractWindow
{
public:
	Edit(AbstractWindow* p_parent = nullptr, int p_width = DEF_WIDTH, int p_height = DEF_HEIGHT, const wchar_t* p_text = L"",
		unsigned long p_style = EditStyle::MULTILINE, unsigned long p_wsex = toadenum::style::WindowExStyle::DEFAULT, UINT_PTR identifier = 0);
	~Edit();

	bool setWordWrap(bool wordwrap);
	
	// Selection
	SelectionRange getSelection();
	void select(unsigned long begin, unsigned long end);
	void select(SelectionRange selectionRange);
	void replaceSel(std::wstring str);

	void undo();

	// DocumentHandler related functions
	DocumentHandler* getDocument() { return &m_docHandler; } // Unfinished

	inline const wchar_t* ClassName() override { return L"EDIT"; };

private:
	DocumentHandler m_docHandler;
	SelectionRange m_currSel;
};

#endif