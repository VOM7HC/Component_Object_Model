#pragma once

struct IObject
{
	virtual void __stdcall AddRef() = 0;
	virtual void __stdcall Release() = 0;
	virtual void* __stdcall As(char const* type) = 0;
};

struct IHen : IObject
{
	virtual void __stdcall Cluck() = 0;
	virtual void __stdcall Roost() = 0;
};

struct IHen2 : IHen
{
	virtual void __stdcall Forage() = 0;
};

struct IOfflineChicken : IObject
{
	virtual void __stdcall Load(char const* file) = 0;
	virtual void __stdcall Save(char const* file) = 0;
};

IHen* __stdcall CreateHen();