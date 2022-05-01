#include "DocumentHandler.h"

DocumentHandler::DocumentHandler(LPCWSTR p_path, OpenMode p_openMode) : DocumentHandler() {
	m_fileHandle.open(p_path, p_openMode);
	if (m_fileHandle.is_open()) {
		Utils::StringCopy(path, p_path, Utils::StringSize(p_path));
	}
	openMode = p_openMode;
}

DocumentHandler::DocumentHandler()
	: path(reinterpret_cast<wchar_t*>(calloc(MAX_PATH, sizeof(wchar_t)))), saved(false) {
	if (path == NULL) {
		throw std::bad_alloc();
	}
}

DocumentHandler::DocumentHandler(DocumentHandler const& documentHandler) {
	// Copy the path to a new location of the memory to avoid an unexpected write into a deleted pointer
	unsigned strSize = Utils::StringSize(documentHandler.path);
	path = reinterpret_cast<wchar_t*>(malloc(sizeof(wchar_t) * strSize));
	Utils::StringCopy(path, documentHandler.path, strSize);

	// Copy the others properties
	this->openMode = documentHandler.openMode;

	if (openFile(path, documentHandler.openMode))
	{
		this->saved = documentHandler.saved;
		this->eol = documentHandler.eol;
	}
}

DocumentHandler::~DocumentHandler() {
	if (path != NULL) {
		free(path);
	}
	if (m_fileHandle.is_open()) {
		m_fileHandle.close();
	}
}

bool DocumentHandler::openFile(LPCWSTR p_path, OpenMode p_openMode) {
	if (m_fileHandle.is_open()) {
		m_fileHandle.close();
	}

	m_fileHandle.open(p_path, p_openMode); // Open the file in output mode for the moment to make sure it is allowed to write on the file
	
	if (!m_fileHandle.is_open()) {
		m_fileHandle.open(p_path, WRITE);
		if (!m_fileHandle.is_open()) {
			return false;
		}
	}
	else {
		m_fileHandle.close();
		m_fileHandle.open(p_path, p_openMode);
	}

	wchar_t* tempPtr = Utils::StringCopy(path, p_path, Utils::StringSize(p_path));
	if (tempPtr == NULL) {
		free(path);
	}

	eol = static_cast<EOL_Mode>(EOLMode());

	// File encoding
	m_fileHandle.imbue(std::locale("en_US.UTF-8"));
	this->openMode = p_openMode;

	return true;
}

std::wstring DocumentHandler::read() {
	wchar_t* buffer = nullptr;

	if (m_fileHandle && (openMode & WRITE)) {
		m_fileHandle.seekg(std::fstream::beg);

		unsigned int toRealloc = 0;
		unsigned int position = 0;

		wchar_t currChara = L' ';

		buffer = reinterpret_cast<wchar_t*>(malloc(sizeof(wchar_t)));

		while (m_fileHandle.get(currChara)) {
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
	std::wstring str(buffer);
	free(buffer);
	return str;
}

bool DocumentHandler::write(LPCWSTR content) {
	if (m_fileHandle.is_open()) {
		m_fileHandle.clear();
		m_fileHandle.seekp(std::fstream::beg);

		wchar_t chara = 0;
		unsigned int strSize = Utils::StringSize(content);

		if (strSize > 0) {
			--strSize;
		}

		for (int i = 0; i != strSize; ++i) {
			chara = content[i];
			if (chara != L'\r') {
				m_fileHandle << chara;
			}
		}
		this->saved = true;
		return true;
	}
	return false;
}

int DocumentHandler::EOLMode() {
	m_fileHandle.seekg(std::fstream::beg);
	wchar_t chara;

	while (m_fileHandle.get(chara)) {
		switch (chara) {
		case L'\r':
			if (m_fileHandle.get() == L'\n')
				return EOL_Mode::CRLF;
			else
				return EOL_Mode::CR;
		case L'\n':
			return EOL_Mode::LF;
		}
	}
	return EOL_Mode::UNDEFINED; // Use default : CRLF
}

std::wstring DocumentHandler::EOL_AsString() const {
	switch (eol) {
	case EOL_Mode::CR:
		return L"CR";
	case EOL_Mode::LF:
		return L"LF";
	case EOL_Mode::CRLF:
		return L"CRLF";
	default:
		return L"CRLF";
	}
}

BOOL DocumentHandler::isUnicode() { // Test
	wchar_t c;
	while (m_fileHandle.get(c)) {
		if (c > 0x080) {
			return TRUE;
		}
	}
	return FALSE;
}