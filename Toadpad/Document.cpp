#include "Document.h"

// Open the document

Document::Document(LPCWSTR p_path, std::fstream::openmode p_openMode) 
	: Document(p_path, (OpenMode)p_openMode) {}

Document::Document(LPCWSTR p_path, OpenMode p_openMode)
	: Document() {
	openMode = p_openMode;

	if (!Open(p_path, p_openMode)) {
		// MessageBox(NULL, L"Failed to open the document", L"An error has occured", MB_OK);
	}
}

Document::Document()
	: path(reinterpret_cast<wchar_t*>(calloc(MAX_PATH, sizeof(wchar_t)))), saved(false) {
	if (path == NULL) {
		throw std::bad_alloc(); // Problem: Filled with zeros... ;-;
	}
	else
	{
		OutputDebugString(L"A new document has been created");
	}
}

Document::~Document() {
	if (path != NULL) {
		free(path);
	}
	if (this->is_open()) {
		this->close();
	}
}

bool Document::Open(LPCWSTR p_path, OpenMode p_openMode) {
	// Reopen the file if it's already open
	if (this->is_open()) {
		this->close();
	}

	this->open(p_path, p_openMode);
	if (this->is_open()) {
		wchar_t* c = Utils::StringCopy(path, p_path);
		if (c == NULL) {
			free(path);
		}

		eol = (EOL_MODE)EOLMode();

		// Get encoding and set the file encoding
		this->imbue(std::locale("en_US.UTF-8"));
		this->openMode = p_openMode;
		return true;
	}
	this->openMode = p_openMode;
	return false;
}

wchar_t* Document::Read() {
	wchar_t* buffer = nullptr;
	// Check if the file is readable
	if (openMode & OpenMode::READ) { // The file is readable
		this->seekg(beg);

		unsigned int toRealloc = 0;
		unsigned int position = 0;

		wchar_t currChara = L' ';

		buffer = reinterpret_cast<wchar_t*>(malloc(toRealloc * sizeof(wchar_t)));

		while (this->get(currChara)) {
			++toRealloc;
			wchar_t* new_ptr = reinterpret_cast<wchar_t*>(realloc(buffer, toRealloc * sizeof(wchar_t)));
			if (new_ptr == nullptr) {
				free(buffer);
				break;
			}
			buffer = new_ptr;

			if (currChara == L'\n') {
				buffer[position] = L'\r';
				++toRealloc;
				wchar_t* new_ptr = reinterpret_cast<wchar_t*>(realloc(buffer, toRealloc * sizeof(wchar_t)));
				if (new_ptr == nullptr) {
					free(buffer);
					break;
				}
				buffer = new_ptr;
				buffer[position + 1] = L'\n';
				position += 2;
			}
			else {
				buffer[position] = currChara;
				++position;
			}
		}
		wchar_t* new_ptr = reinterpret_cast<wchar_t*>(realloc(buffer, (toRealloc + 1) * sizeof(wchar_t)));
		if (new_ptr == nullptr) {
			free(buffer);
		}
		else {
			buffer = new_ptr;
		}
		buffer[position] = L'\0';
	}

	return buffer;
	/*
		BUFFER CONTENT DEPENDING ON WHAT'S GOING ON TEST
		- if the file cannot be open, buffer equals to NULL or nullptr
		- if the file can be open but there is not enough memory, buffer equals to \0\0\0 and so on...
		- if the file can be open and everything is alright, buffer equals to a pointer which points to
		the first character of the file

		Note: Don't forget to free the memory after reading the content of a file :)
		conclusion: infinite loop :c
	*/
}

bool Document::Write(LPCWSTR content) {
	if (openMode & OpenMode::WRITE) {
		this->seekp(beg);

		wchar_t chara = 0;
		unsigned int strSize = Utils::StringSize(content);

		for (int i = 0; i != strSize; ++i) {
			chara = content[i];
			if (chara != L'\r') {
				this->put(chara);
			}
		}
		this->saved = true;
		return true;
	}
	return false;
}

int Document::EOLMode() {
	this->seekg(beg);
	wchar_t chara;

	while (this->get(chara)) {
		switch (chara) {
		case L'\r':
			if (this->get() == L'\n')
				return EOL_MODE::CRLF;
			else
				return EOL_MODE::CR;
		case L'\n':
			return EOL_MODE::LF;
		}
	}
	return EOL_MODE::UNDEFINED; // Use default : CRLF
}

std::wstring Document::EOL_AsString() const {
	switch (eol) {
	case EOL_MODE::CR:
		return L"CR";
	case EOL_MODE::LF:
		return L"LF";
	case EOL_MODE::CRLF:
		return L"CRLF";
	default:
		return L"CRLF";
	}
}

BOOL Document::IsUnicode() { // Test
	wchar_t c;
	while (this->get(c)) {
		if (c > 0x080) {
			return TRUE;
		}
	}
	return FALSE;
}
