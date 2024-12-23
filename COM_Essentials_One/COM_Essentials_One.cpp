#include <iostream>

#include <Windows.h>

//#include "precompiled.hpp"
#include "../COM_Essentials_One_DLL/Library.hpp"

#pragma comment(lib, "rpcrt4.lib")

#define TRACE(s) OutputDebugString(s)
#define ASSERT _ASSERTE

struct ComException
{
	HRESULT hr;
	ComException(HRESULT const value) : hr(value) {}
};

inline void HR(HRESULT const hr)
{
	if (S_OK != hr)
	{
		throw ComException(hr);
	}
}

int main()
{
	// Example 1
	IHen* hen = CreateHen();
	hen->Cluck();

	IHen2* hen2 = static_cast<IHen2*>(hen->As("IHen2"));

	if (hen2)
	{
		hen2->Forage();
		hen2->Release();
	}

	IOfflineChicken* offlineChicken = static_cast<IOfflineChicken*>(hen->As("IOfflineChicken"));

	if (offlineChicken)
	{
		offlineChicken->Load("filename");
		offlineChicken->Save("filename");
		offlineChicken->Release();
	}

	hen->Release();

	return 0;
}