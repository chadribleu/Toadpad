// -------------------------------------------------------------------------------------------
// Toadpad entrypoint, see the other files
// -------------------------------------------------------------------------------------------

#include "MainWindow.h"
#include "application.h"

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow) {
	application::EnableVisualStyle(ICCStyle::STANDARD | ICCStyle::WIN95STD);

	MainWindow mainWindow(hInst, nCmdShow);

	application::Configure(mainWindow);
	return application::Exec();
}