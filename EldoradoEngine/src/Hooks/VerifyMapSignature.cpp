#include "EngineHooks.h"

using namespace EldoradoEngine::Hooks;

HookedFunction(EngineHooks, bool, VerifyMapSignature, __cdecl, void* a1)
{
	WriteLog("Signature verification spoofed.");
	return true;
}