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

		public:
			void Init();
		};
	}
}