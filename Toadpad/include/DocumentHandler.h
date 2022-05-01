#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H

#include <fstream>
#include "utils.h"

class DocumentHandler {
public:
	using OpenMode = int;
	inline static constexpr OpenMode READ = std::fstream::in;
	inline static constexpr OpenMode WRITE = std::fstream::out;
	inline static constexpr OpenMode BINARY = std::fstream::binary;
	inline static constexpr OpenMode APPEND = std::fstream::app;
	inline static constexpr OpenMode AT_END = std::fstream::ate;
	inline static constexpr OpenMode TRUNCATE = std::fstream::trunc;

	DocumentHandler();
	DocumentHandler(DocumentHandler const& documentHandler);
	DocumentHandler(LPCWSTR p_path, OpenMode p_openMode = READ);
	~DocumentHandler();

	explicit operator bool() const { return m_fileHandle.is_open(); };

	bool openFile(LPCWSTR p_path, OpenMode p_openMode);
	inline void closeFile() { m_fileHandle.close(); };
	
	bool write(LPCWSTR content);
	std::wstring read();

	inline bool isSaved() const { return saved; };
	inline wchar_t* getPath() const { return path; };
	std::wstring EOL_AsString() const;
	BOOL isUnicode();
	inline void setSaved(bool p_saved) { saved = p_saved; };

private:
	enum EOL_Mode {
		LF			= 2, // Unix
		CR			= 4, // MacOS
		CRLF		= 6, // Windows
		UNDEFINED	= 0  // Other OS
	};
	enum class Encoding {
		ANSI,
		UTF8,
		UTF8_WITHBOM,
		UTF16LE,
		UTF16BE,
	};

	int EOLMode();
	wchar_t* path;
	bool saved;
	OpenMode openMode;
	EOL_Mode eol;
	std::wfstream m_fileHandle;
};

#endif