#include <Windows.h>
#include <cstdint>
#include <iostream>

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
	HR(CLSIDFromString(ole_string, &guid2));

	ASSERT(RPC_S_OK == UuidFromString(reinterpret_cast<uint16_t*>(const_cast<wchar_t*>(std_string.c_str())), &guid2));

	ASSERT(RPC_S_OK == RpcStringFree(&rpc_string));

	// Example 4
	GUID guid3
	{
		0x12345678, 0x9ABC, 0xDEFF, { 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xFF }
	};

	struct __declspec(uuid("12345678-9ABC-DEFF-1234-56789ABCDEF0")) TypeName;
	GUID guid4 = __uuidof(TypeName);
}