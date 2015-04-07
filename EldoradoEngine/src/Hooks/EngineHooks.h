#pragma once
#include <IInit.h>

namespace EldoradoEngine
{
	namespace Hooks
	{
		class EngineHooks : IInit
		{
		public:
			typedef void* (__cdecl* SetCurrentLanguage_t)(int p_LanguageIndex);
			static SetCurrentLanguage_t SetCurrentLanguage;
			static void* __cdecl hk_SetCurrentLanguage(int p_LanguageIndex);

			typedef void(__fastcall* StartCountdownTimer_t)(void* a1);
			static StartCountdownTimer_t StartCountdownTimer;
			static void __fastcall hk_StartCountdownTimer(void* a1);

			typedef void(__cdecl* CloseGame_t)();
			static CloseGame_t CloseGame;
			static void __cdecl hk_CloseGame();

			typedef void* (__cdecl* Unknown_t)(void* a1, void* a2);
			static Unknown_t Unknown;
			static void* __cdecl hk_Unknown(void* a1, void* a2);

			typedef bool (__cdecl* DisplayCameraInfo_t)();
			static DisplayCameraInfo_t DisplayCameraInfo;
			static bool __cdecl hk_DisplayCameraInfo();

			typedef bool(__cdecl* VerifyMapSignature_t)(void* a1);
			static VerifyMapSignature_t VerifyMapSignature;
			static bool __cdecl hk_VerifyMapSignature(void* a1);

		public:
			void Init();
		};
	}
}