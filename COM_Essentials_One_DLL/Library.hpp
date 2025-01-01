#pragma once

#include <Unknwn.h>

struct __declspec(uuid("c58b7948-3551-4692-91e8-9b6ca7a53a5b")) IHen : IUnknown
{
	virtual void __stdcall Cluck() = 0;
	virtual void __stdcall Roost() = 0;
};

struct __declspec(uuid("f2cb310f-18d2-4c25-8474-c3d62bfdc22e")) IHen2 : IHen
{
	virtual void __stdcall Forage() = 0;
};

struct __declspec(uuid("4ae3eb25-4ea7-4f6e-a1c9-5614ccd5d19b")) IOfflineChicken : IUnknown
{
	virtual void __stdcall Load(char const* file) = 0;
	virtual void __stdcall Save(char const* file) = 0;
};

HRESULT __stdcall CreateHen(IHen** hen);