#include <cstdlib>
#include <iostream>
#include <string>
#include <Windows.h>

namespace Utils 
{
	wchar_t* StringCopy(wchar_t* destination, const wchar_t* source, unsigned count);
	unsigned int StringSize(const wchar_t* source);
}