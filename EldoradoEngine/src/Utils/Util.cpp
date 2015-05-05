#include "Util.h"


using namespace EldoradoEngine::Utils;

bool Util::Match(uint8_t* p_Data, const char* p_ByteMask, const char* p_Mask)
{
	for (; *p_Mask; ++p_Mask, ++p_Data, ++p_ByteMask)
		if (*p_Mask == 'x' && *p_Data != *p_ByteMask)
			return false;
	return (*p_Mask) == 0;
}

uint32_t Util::FindPattern(uint32_t p_Address, uint32_t p_Length, const char* p_ByteMask, const char* p_Mask)
{
	for (uint32_t i = 0; i < p_Length; ++i)
		if (Match((uint8_t*)(p_Address + i), p_ByteMask, p_Mask))
			return (uint32_t)(p_Address + i);

	return 0;
}