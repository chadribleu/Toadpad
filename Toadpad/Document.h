#pragma once

#include <fstream>
#include "utils.h"

class Document : private std::wfstream {
public:
	enum OpenMode {
		READ		= in,
		WRITE		= out,
		READWRITE	= in | out,
		BINARY		= binary,
		APPEND		= app,
		AT_END		= ate,
		TRUNCATE	= trunc
	};

	Document();
	Document(LPCWSTR p_path, OpenMode p_openMode = OpenMode::READ);
	Document(LPCWSTR p_path, std::fstream::openmode p_openMode);
	~Document();

	// explicit operator bool() const; /* if(document) -- if is_open */

	wchar_t* Read();
	bool Open(LPCWSTR p_path, OpenMode p_openMode);
	bool Write(LPCWSTR content);
	inline bool IsSaved() const { return saved; };
	inline bool IsOpen() const { return this->is_open(); }
	inline wchar_t* GetPath() const { return path; };
	std::wstring EOL_AsString() const;
	BOOL IsUnicode();
	inline void SetSaved(bool p_saved) { saved = p_saved; };

	/*void Move(const wchar_t* p_path);
	void Copy(const wchar_t* p_path);
	void SaveAs();
	void Save();*/

private:
	enum EOL_MODE {
		LF			= 2, // Unix
		CR			= 4, // MacOS
		CRLF		= 6, // Windows
		UNDEFINED	= 0  // None of them 
	};
	enum class ENCODING {
		ANSI,
		UTF8,
		UTF8_WITHBOM,
		UTF16LE,
		UTF16BE,
	};
	int EOLMode();
	wchar_t* path;
	bool saved;
	std::ios_base::openmode openMode;
	EOL_MODE eol;
};
