#include "EldoradoEngine.h"
#include <Windows.h>

#include "Utils/Logger.h"
#include "Hooks/EngineHooks.h"
#include "Functions/EngineFunctions.h"

using namespace EldoradoEngine;

// Singleton, we only want to have 1 instance of this per game.
Client* Client::m_Instance = nullptr;
Client* Client::Inst()
{
	if (!m_Instance)
		m_Instance = new Client;
	return m_Instance;
}


void Client::Init()
{
	PreInit();

	WriteLog("Init Stage");
	
	m_EngineHooks = (IInit*)new Hooks::EngineHooks;
	m_EngineFunctions = (IInit*)new Functions::EngineFunctions;

	m_EngineHooks->Init();
	m_EngineFunctions->Init();

	PostInit();
}

void Client::PreInit()
{
	WriteLog("Pre-Init Stage");

	Patch_CloseGame();
}

void Client::PostInit()
{
	WriteLog("Post-Init Stage");

	//Patch_MPLoading();
}

void Client::LoadMap(char* p_MapName, Halo::MapType p_Type)
{
	// Map Type
	memcpy_s((void*)0x2391800, 4, &p_Type, 4);

	// Map Name
	auto s_Length = strnlen_s(p_MapName, 32);
	strncpy_s((char*)0x2391824, 32, p_MapName, s_Length);

	// Map Reset bit
	memset((void*)0x23917F0, 1, 1);
}

void Client::Patch_CloseGame()
{
	DWORD s_Protection;
	DWORD s_CloseGameOffset = 0x005056D0;
	VirtualProtect((void*)s_CloseGameOffset, 1, PAGE_EXECUTE_READWRITE, &s_Protection);
	memset((void*)s_CloseGameOffset, 0xC3, 1);
	VirtualProtect((void*)s_CloseGameOffset, 1, s_Protection, &s_Protection);

	WriteLog("Force closing of game patched.");
}

void Client::Patch_MPLoading()
{
	DWORD s_Protection;
	DWORD s_MpPatchOffset = 0x006D26DF;
	VirtualProtect((void*)s_MpPatchOffset, 5, PAGE_EXECUTE_READWRITE, &s_Protection);
	memset((void*)s_MpPatchOffset, 0x90, 5);
	VirtualProtect((void*)s_MpPatchOffset, 5, s_Protection, &s_Protection);

	WriteLog("Multiplayer game modes patched.");
}


DWORD WINAPI ClientInit(LPVOID)
{
	Client::Inst()->Init();

	// Shitty ass button hooks
	for (;;)
	{
		if (GetAsyncKeyState(VK_F2) & 0x8000)
		{
			WriteLog("Force-loading Guardian...");
			Client::Inst()->LoadMap("maps\\guardian.map", Halo::MapType_Multiplayer);
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F3) & 0x8000)
		{
			WriteLog("Force-loading Valhalla...");
			Client::Inst()->LoadMap("maps\\riverworld.map", Halo::MapType_Multiplayer);
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F4) & 0x8000)
		{
			WriteLog("Force-loading Avalanche...");
			Client::Inst()->LoadMap("maps\\s3d_avalanche.map", Halo::MapType_Multiplayer);
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F5) & 0x8000)
		{
			WriteLog("Force-loading Edge...");
			Client::Inst()->LoadMap("maps\\s3d_edge.map", Halo::MapType_Multiplayer);
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F6) & 0x8000)
		{
			WriteLog("Force-loading Reactor...");
			Client::Inst()->LoadMap("maps\\s3d_reactor.map", Halo::MapType_Multiplayer);
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F7) & 0x8000)
		{
			WriteLog("Force-loading Turf...");
			Client::Inst()->LoadMap("maps\\s3d_turf.map", Halo::MapType_Multiplayer);
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_F8) & 0x8000)
		{
			WriteLog("Force-loading mainmenu...");
			Client::Inst()->LoadMap("maps\\mainmenu.map", (Halo::MapType)0);
			Sleep(100);
		}
		Sleep(200);
	}
	return 0;
}

BOOL WINAPI DllMain(HMODULE p_Module, DWORD p_Reason, LPVOID p_Reserved)
{
	if (p_Reason == DLL_PROCESS_ATTACH)
		CreateThread(0, 0, ClientInit, 0, 0, 0);

	return TRUE;
}