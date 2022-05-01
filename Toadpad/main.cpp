#include "MainWindow.h"

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow) 
{
	MainWindow mainWindow(hInst, nCmdShow);

	return mainWindow.Exec();
}