#include "accelerators.h"

int KeyboardAccelTable::objcount = 0;

KeyboardAccelTable::KeyboardAccelTable() : m_accelSize(0), m_accelList(new ACCEL[MAXACCEL]), m_handle(NULL)
{
	++objcount;
}

KeyboardAccelTable::KeyboardAccelTable(KeyboardAccelTable const& copy)
{
	++objcount;

	HACCEL handle = copy.m_handle;
	if (handle) 
	{
		this->m_handle = copy.m_handle;
	}

	ACCEL* tmpPtr = new ACCEL[MAXACCEL];

	if (copy.m_accelSize > 0) // The memory can be allocated
	{
		ACCEL* tempPtr = new ACCEL[MAXACCEL];
		memcpy(tempPtr, copy.m_accelList, sizeof(m_accelList) * (copy.m_accelSize));

		if (tempPtr)
		{
			this->m_accelSize = copy.m_accelSize;
			this->m_accelList = tempPtr;
		}
		else
		{
			this->m_accelSize = 0;
		}
	}
}

KeyboardAccelTable::~KeyboardAccelTable()
{
	--objcount;
	delete[] m_accelList;
}

KeyboardAccelTable& KeyboardAccelTable::operator=(KeyboardAccelTable const& other)
{
	KeyboardAccelTable table(other);

	this->m_handle = table.m_handle;
	this->m_accelList = table.m_accelList;
	this->m_accelSize = table.m_accelSize;

	return *this;
}

void KeyboardAccelTable::addEntry(KeyboardAccelDesc& description)
{
	++m_accelSize;
	m_accelList[m_accelSize - 1] = *description.getStruct();
}

ACCEL* KeyboardAccelTable::getEntry(int index)
{
	if (index > m_accelSize || index < 0) {
		return nullptr;
	}
	return &m_accelList[index];
}

HACCEL KeyboardAccelTable::create()
{
	if (!m_handle)
	{
		int size = m_accelSize <= 0 ? 0 : m_accelSize + 1;
		if (size > 0)
		{
			m_handle = CreateAcceleratorTableW(m_accelList, size);
			return m_handle;
		}
	}
	return NULL;
}

void KeyboardAccelTable::swapShortcuts(KeyboardAccelTable& table)
{
	DestroyAcceleratorTable(m_handle);
	this->create();
}


KeyboardAccelDesc::KeyboardAccelDesc(DWORD modifier, wchar_t key) : m_struct{ 0 }
{
	m_struct.fVirt = modifier | FVIRTKEY;
	m_struct.key = key;
}

std::wstring KeyboardAccelDesc::toStr()
{
	std::wstring strModifier;

	if ((m_struct.fVirt & toadenum::KeyboardKeys::CTRL) == toadenum::KeyboardKeys::CTRL)
	{
		strModifier += L"Ctrl+";
	}
	
	if ((m_struct.fVirt & toadenum::KeyboardKeys::ALT) == toadenum::KeyboardKeys::ALT)
	{
		strModifier += L"Alt+";
	}
	
	if ((m_struct.fVirt & toadenum::KeyboardKeys::SHIFT) == toadenum::KeyboardKeys::SHIFT)
	{
		strModifier += L"Shift+";
	}

	return std::wstring(strModifier + (wchar_t)std::towupper((wchar_t)m_struct.key));
}