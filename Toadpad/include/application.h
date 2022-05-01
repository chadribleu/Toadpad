#ifndef APPLICATION
#define APPLICATION

#include <Windows.h>
#include "accelerators.h"
#include "clipboard.h"
#include "AbstractWindow.h"

class AbstractWindow;
class Clipboard;

using ICCTYPE = int;
namespace ICCStyle {
	static inline const int ANIMATE			= ICC_ANIMATE_CLASS;
	static inline const int BAR				= ICC_BAR_CLASSES;
	static inline const int REBAR			= ICC_COOL_CLASSES;
	static inline const int DATE			= ICC_DATE_CLASSES;
	static inline const int HOTKEY			= ICC_HOTKEY_CLASS;
	static inline const int IPADDRESS		= ICC_INTERNET_CLASSES;
	static inline const int HYPERLINKCTL	= ICC_LINK_CLASS;
	static inline const int LISTVIEW		= ICC_LISTVIEW_CLASSES;
	static inline const int NATIVEFNTCTL	= ICC_NATIVEFNTCTL_CLASS;
	static inline const int PAGESCROLLER	= ICC_PAGESCROLLER_CLASS;
	static inline const int PROGRESSBAR		= ICC_PROGRESS_CLASS;
	static inline const int TABCTL			= ICC_TAB_CLASSES;
	static inline const int TREEVIEW		= ICC_TREEVIEW_CLASSES;
	static inline const int UPDOWNCTL		= ICC_UPDOWN_CLASS;
	static inline const int COMBOBOXEX		= ICC_USEREX_CLASSES;
	static inline const int WIN95STD		= ICC_WIN95_CLASSES;
	static inline const int STANDARD = ICC_STANDARD_CLASSES;
}

class application
{
public:
	static void Configure(AbstractWindow const& window);
	static int Exec();
	static inline KeyboardAccelTable* GetShortcutTable() { return &g_hAccel; }
	static inline Clipboard* GetClipboard() { return &g_clpd; }
	static bool EnableVisualStyle(ICCTYPE ctl);

private:
	static HWND g_hWnd;
	static KeyboardAccelTable g_hAccel;
	static Clipboard g_clpd;
};

#endif