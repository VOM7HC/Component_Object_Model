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
	IHen* hen;

	if (S_OK != CreateHen(&hen))
	{
		return 0;
	}

	hen->Cluck();

	IHen2* hen2;
	if (S_OK == hen->QueryInterface(__uuidof(IHen2), reinterpret_cast<void**>(&hen2)))
	{
		hen2->Forage();
		hen2->Release();
	}

	IOfflineChicken* offlineChicken;
	if (S_OK == hen->QueryInterface(__uuidof(IOfflineChicken), reinterpret_cast<void**>(&offlineChicken)))
	{
		offlineChicken->Load("filename");
		offlineChicken->Save("filename");
		offlineChicken->Release();
	}

	hen->Release();

	return 0;
}