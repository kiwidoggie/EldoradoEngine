#include "EngineHooks.h"
#include <detours.h>
#include <Utils/Logger.h>

using namespace EldoradoEngine::Hooks;

EngineHooks::SetCurrentLanguage_t EngineHooks::SetCurrentLanguage = nullptr;
EngineHooks::StartCountdownTimer_t EngineHooks::StartCountdownTimer = nullptr;
EngineHooks::CloseGame_t EngineHooks::CloseGame = nullptr;
EngineHooks::Unknown_t EngineHooks::Unknown = nullptr;
EngineHooks::DisplayCameraInfo_t EngineHooks::DisplayCameraInfo = nullptr;
EngineHooks::VerifyMapSignature_t EngineHooks::VerifyMapSignature = nullptr;

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

	Unknown = (Unknown_t)DetourFunction((PBYTE)0x006D26A0, (PBYTE)hk_Unknown);
	WriteLog("Unknown hooked.");


	// Crashes when Player dies... do not use
	//DetourFunction((PBYTE)0x005D2B40, (PBYTE)hk_DisplayCameraInfo);
	//WriteLog("DisplayCameraInfo hooked.");

	// Disable Map Verification
	VerifyMapSignature = (VerifyMapSignature_t)DetourFunction((PBYTE)0x00502210, (PBYTE)hk_VerifyMapSignature);
}