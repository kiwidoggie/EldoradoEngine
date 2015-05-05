#pragma once
#include <stdint.h>

namespace EldoradoEngine
{
	namespace Utils
	{
		class Util
		{
		public:
			static bool Match(uint8_t* p_Data, const char* p_ByteMask, const char* p_Mask);
			static unsigned int FindPattern(uint32_t p_Address, uint32_t p_Length, const char* p_ByteMask, const char* p_Mask);
		};
	}
}