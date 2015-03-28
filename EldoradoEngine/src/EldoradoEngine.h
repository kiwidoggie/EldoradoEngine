#pragma once
#include <IInit.h>
#include <HaloEngine.h>

namespace EldoradoEngine
{
	class Client : IInit
	{
	private:
		static Client* m_Instance;

		IInit* m_EngineHooks;
		IInit* m_EngineFunctions;

	public:
		static Client* Inst();

	public:

		void Init();
		void PreInit();
		void PostInit();

		void LoadMap(char* p_MapName, Halo::MapType p_MapType);

		// Patches
		void Patch_CloseGame();
		void Patch_Language();
		void Patch_MPLoading();
	};
}