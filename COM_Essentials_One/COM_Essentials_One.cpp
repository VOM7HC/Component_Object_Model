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

	// Example 2
	HRESULT hr = S_OK;
	if (S_OK != hr)
	{
		std::cout << "Failed" << std::endl;
	}
	if (S_OK == hr)
	{
		std::cout << "Succeeded" << std::endl;
	}

	// Example 3
	GUID guid;
	HR(CoCreateGuid(&guid));
	uint16_t* rpc_string;
	ASSERT(RPC_S_OK == UuidToString(&guid, &rpc_string));
	TRACE(L"%s\n", rpc_string);

	wchar_t ole_string[39];
	ASSERT(StringFromGUID2(guid, ole_string, _countof(ole_string)));
	TRACE(L"%s\n", ole_string);

	std::wstring std_string(ole_string + 1, _countof(ole_string) - 3);
	TRACE(L"%s\n", std_string.c_str());

	GUID guid2;
	ASSERT(RPC_S_OK == UuidFromString(rpc_string, &guid2));

	ASSERT(RPC_S_OK == RpcStringFree(&rpc_string));

	return 0;
}