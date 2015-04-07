#include "EngineHooks.h"

using namespace EldoradoEngine::Hooks;

bool EngineHooks::hk_VerifyMapSignature(void* a1)
{
	// Spoof this so we can file mod
	return true;
}