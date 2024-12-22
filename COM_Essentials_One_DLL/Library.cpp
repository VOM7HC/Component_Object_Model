#include "Library.hpp"
#include <Windows.h>
#include <cstdint>

#define TRACE(s) OutputDebugString(s)

struct Hen : IHen2, IOfflineChicken
{
	uint32_t m_count;

	Hen() : m_count(0)
	{
		TRACE(L"Cheep!\n");
	}
	~Hen()
	{
		TRACE(L"Chicken soup!\n");
	}

	// IObject
	void _stdcall AddRef()
	{
		++m_count;
	}
	void _stdcall Release()
	{
		if (--m_count == 0)
		{
			delete this;
		}
	}
	void* __stdcall As(char const* type)
	{
		if (0 == strcmp(type, "IHen") ||
			0 == strcmp(type, "IHen2") ||
			0 == strcmp(type, "IObject"))
		{
			AddRef();
			return static_cast<IHen2*>(this);
		}
		else if (0 == strcmp(type, "IOfflineChicken"))
		{
			AddRef();
			return static_cast<IOfflineChicken*>(this);
		}
		else
		{
			return 0;
		}
		return nullptr;
	}

	// IHen
	void _stdcall Cluck()
	{
		TRACE(L"Cluck\n");
	}
	void _stdcall Roost()
	{
		TRACE(L"Zzzz\n");
	}

	// IHen2
	void _stdcall Forage()
	{
		TRACE(L"Forage!\n");
	}

	// IOfflineChicken
	void _stdcall Load(char const* file)
	{
		TRACE(L"Load\n");
	}
	void _stdcall Save(char const* file)
	{
		TRACE(L"Save\n");
	}
};

IHen* __stdcall CreateHen()
{
	IHen* hen = new Hen;
	hen->AddRef();
	return hen;
}
