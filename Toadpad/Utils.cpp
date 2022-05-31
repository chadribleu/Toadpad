#include "utils.h"

wchar_t* Utils::StringCopy(wchar_t* destination, const wchar_t* source) {
	int i = 0;
	wchar_t character = L' ';
	while (character != L'\0') {
		destination[i] = source[i];
		character = source[i];
		++i;
	}
	return destination;
}

unsigned int Utils::StringSize(const wchar_t* source) {
	int size = 0;
	wchar_t character = L' ';
	while (character != L'\0') {
		character = source[size];
		++size;
	}
	return size;
}