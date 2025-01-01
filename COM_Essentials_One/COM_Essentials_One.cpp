#include <iostream>

#include <Windows.h>

//#include "precompiled.hpp"
#include "../COM_Essentials_One_DLL/Library.hpp"

#pragma comment(lib, "rpcrt4.lib")

#define TRACE(s) OutputDebugString(s)
#define ASSERT _ASSERTE

template<typename T>
class RemoveAddRefRelease : public T
{
public:
	ULONG _stdcall AddRef();
	ULONG _stdcall Release();
};

template<typename T>
class ComPtr
{
private:
	T* m_ptr;
public:
	ComPtr() : m_ptr(nullptr) {}
	//ComPtr(T* const ptr) : m_ptr(ptr) {}
	~ComPtr()
	{
		if (m_ptr)
			m_ptr->Release();
	}
	RemoveAddRefRelease<T>* operator->() const
	{
		ASSERT(m_ptr);
		return static_cast<RemoveAddRefRelease<T>*> (m_ptr);
	}
	//T& operator*() { return *m_ptr; }
	T** GetAddressOf()
	{
		return &m_ptr;
	}
};

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
	//IHen* hen;
	ComPtr<IHen> hen;

	//if (S_OK != CreateHen(&hen))
    if (S_OK != CreateHen(hen.GetAddressOf()))
	{
		return 0;
	}

	hen->Cluck();

	//IHen2* hen2;
	ComPtr<IHen2> hen2;
	//if (S_OK == hen->QueryInterface(__uuidof(IHen2), reinterpret_cast<void**>(&hen2)))
	if (S_OK == hen->QueryInterface(__uuidof(IHen2), reinterpret_cast<void**>(hen2.GetAddressOf())))
	{
		hen2->Forage();
		//hen2->Release();
	}

	//IOfflineChicken* offlineChicken;
	ComPtr<IOfflineChicken> offlineChicken;
	//if (S_OK == hen->QueryInterface(__uuidof(IOfflineChicken), reinterpret_cast<void**>(&offlineChicken)))
	if (S_OK == hen->QueryInterface(__uuidof(IOfflineChicken), reinterpret_cast<void**>(offlineChicken.GetAddressOf())))
	{
		offlineChicken->Load("filename");
		offlineChicken->Save("filename");
		//offlineChicken->Release();
	}

	//hen->Release();

	return 0;
}