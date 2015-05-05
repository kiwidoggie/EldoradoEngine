#include "EngineHooks.h"
#include <detours.h>
#include <Utils/Logger.h>

using namespace EldoradoEngine::Hooks;


void EngineHooks::Init()
{
	uint32_t s_Base = 0x00401000;
	uint32_t s_Size = 0x00C77000;

	//DeclareHookPattern(VerifyMapSignature, s_Base, s_Size, "\x55\x8B\xEC\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x53\x56\x8B", "xxxx??xxx???xxxx");
	////PrintLog = (PrintLog_t)DetourFunction((PBYTE)0x00DCD320, (PBYTE)hk_PrintLog);
	//SetCurrentLanguage = (SetCurrentLanguage_t)DetourFunction((PBYTE)0x00530100, (PBYTE)hk_SetCurrentLanguage);
	//WriteLog("SetCurrentLanguage hooked.");

	//StartCountdownTimer = (StartCountdownTimer_t)DetourFunction((PBYTE)0x007123A0, (PBYTE)hk_StartCountdownTimer);
	//WriteLog("StartCountdownTimer hooked.");

	//// When patch is enabled this hook does nothing. This hook still lets the game close some kind of way...
	////CloseGame = (CloseGame_t)DetourFunction((PBYTE)0x005056D0, (PBYTE)hk_CloseGame);
	////WriteLog("CloseGame hooked.");

	//Unknown = (Unknown_t)DetourFunction((PBYTE)0x006D26A0, (PBYTE)hk_Unknown);
	//WriteLog("Unknown hooked.");


	//// Crashes when Player dies... do not use
	////DetourFunction((PBYTE)0x005D2B40, (PBYTE)hk_DisplayCameraInfo);
	////WriteLog("DisplayCameraInfo hooked.");

	//// Disable Map Verification
	//VerifyMapSignature = (VerifyMapSignature_t)DetourFunction((PBYTE)0x00502210, (PBYTE)hk_VerifyMapSignature);
}

