#include "Library.hpp"
#include <Windows.h>
#include <cstdint>
#include <crtdbg.h>

#define ASSERT _ASSERTE
#define TRACE(s) OutputDebugString(s)

struct Hen : IHen2, IOfflineChicken
{
	long m_count;

	Hen() : m_count(0)
	{
		TRACE(L"Cheep!\n");
	}
	~Hen()
	{
		TRACE(L"Chicken soup!\n");
	}

	// IUnknown
	ULONG _stdcall AddRef()
	{
		return _InterlockedIncrement(&m_count);
	}
    ULONG _stdcall Release()
    {
        ULONG const result = _InterlockedDecrement(&m_count);
        if (0 == result)
        {
            delete this;
        }
        return result;
    }
	HRESULT __stdcall QueryInterface(IID const& id, void** result)
	{
		ASSERT(result);

		if (id == __uuidof(IHen) ||
			id == __uuidof(IHen2) ||
			id == __uuidof(IUnknown))
		{
			*result = static_cast<IHen2*>(this);
		}
		else if (id == __uuidof(IOfflineChicken))
		{
			*result = static_cast<IOfflineChicken*>(this);
		}
		else
		{
			*result = nullptr;
			return E_NOINTERFACE;
		}

		static_cast<IUnknown*>(*result)->AddRef();
		return S_OK;
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

HRESULT __stdcall CreateHen(IHen** result)
{
	ASSERT(result);

	*result = new (std::nothrow) Hen();
	
	if (0 == *result)
	{
		return E_OUTOFMEMORY;
	}
	(*result)->AddRef();

	return S_OK;
}
