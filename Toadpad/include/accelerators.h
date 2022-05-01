#ifndef KEYBOARDACCELTABLE
#define KEYBOARDACCELTABLE

#include <string>
#include <vector>
#include <cwctype>
#include <Windows.h>
#include "toadenum.h"

#define MINACCEL 1
#define MAXACCEL 32767

class KeyboardAccelTable;
class KeyboardAccelDesc;

namespace Modifiers
{
	static int ALT	 = FALT;
	static int CTRL	 = FCONTROL;
	static int SHIFT = FSHIFT;
}

class KeyboardAccelTable
{
	static int objcount;

public:
	KeyboardAccelTable();
	KeyboardAccelTable(KeyboardAccelTable const& copy);
	~KeyboardAccelTable();

	KeyboardAccelTable& operator=(KeyboardAccelTable const& other);

	void addEntry(KeyboardAccelDesc& kad);
	void swapShortcuts(KeyboardAccelTable& table);

	ACCEL* getEntry(int index);
	
	HACCEL create();
	HACCEL getHandle() const 
	{ return m_handle; }

private:
	int m_accelSize;
	ACCEL* m_accelList;
	HACCEL m_handle;
};

class KeyboardAccelDesc
{
public:
	KeyboardAccelDesc(DWORD modifier, wchar_t key);

	std::wstring toStr();
	ACCEL* getStruct()
	{
		return &m_struct;
	}

private:
	ACCEL m_struct;
};

#endif