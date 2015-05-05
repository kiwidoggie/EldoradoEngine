#include "EngineHooks.h"
#include <Utils/Logger.h>

using namespace EldoradoEngine::Hooks;

//void __cdecl EngineHooks::hk_CloseGame()
//{
//	void ** puEBP = nullptr;
//	__asm { mov puEBP, ebp };
//	void * pvReturn = puEBP[1]; // this is the caller of my function
//
//	puEBP = (void**)puEBP[0];    // walk back to the previous frame
//	void * pvReturn2 = puEBP[1]; // this is the caller's caller
//
//	WriteLog("CloseGame Called from %x pvReturn, caller's caller %x.", pvReturn, pvReturn2);
//
//	// halo_isClosing
//	*(unsigned char*)0x022B473C = 0;
//}