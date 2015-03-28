#include "EngineHooks.h"
#include <detours.h>
#include <Utils/Logger.h>

using namespace EldoradoEngine::Hooks;

EngineHooks::SetCurrentLanguage_t EngineHooks::SetCurrentLanguage = nullptr;
EngineHooks::StartCountdownTimer_t EngineHooks::StartCountdownTimer = nullptr;
EngineHooks::CloseGame_t EngineHooks::CloseGame = nullptr;

void EngineHooks::Init()
{
	//PrintLog = (PrintLog_t)DetourFunction((PBYTE)0x00DCD320, (PBYTE)hk_PrintLog);
	SetCurrentLanguage = (SetCurrentLanguage_t)DetourFunction((PBYTE)0x00530100, (PBYTE)hk_SetCurrentLanguage);
	WriteLog("SetCurrentLanguage hooked.");

	StartCountdownTimer = (StartCountdownTimer_t)DetourFunction((PBYTE)0x007123A0, (PBYTE)hk_StartCountdownTimer);
	WriteLog("StartCountdownTimer hooked.");

	// When patch is enabled this hook does nothing. This hook still lets the game close some kind of way...
	//CloseGame = (CloseGame_t)DetourFunction((PBYTE)0x005056D0, (PBYTE)hk_CloseGame);
	//WriteLog("CloseGame hooked.");
}