#include "application.h"

KeyboardAccelTable application::g_hAccel = KeyboardAccelTable();
Clipboard application::g_clpd;
HWND application::g_hWnd = NULL;

void application::Configure(AbstractWindow const& window)
{
	g_hWnd = window.Handle();
	g_clpd = Clipboard(window);
	g_hAccel.create();
}

int application::Exec()
{
	MSG message = { 0 };
	HACCEL hAcc = g_hAccel.getHandle(); // You need to create the table first

	while (GetMessage(&message, NULL, NULL, NULL) > 0) {
		if (!TranslateAccelerator(g_hWnd, hAcc, &message)) {
			TranslateMessage(&message);
			DispatchMessageW(&message);
		}
	}
	return (int)message.wParam;
}

bool application::EnableVisualStyle(ICCTYPE ctl)
{
	INITCOMMONCONTROLSEX iccex;
	iccex.dwSize = sizeof(iccex);
	iccex.dwICC = ctl;

	if (FALSE == InitCommonControlsEx(&iccex)) {
		return false;
	}
	return true;
}