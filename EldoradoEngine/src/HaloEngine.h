#pragma once

namespace EldoradoEngine
{
	namespace Halo
	{
		enum MapType : unsigned int
		{
			MapType_Singleplayer = 1,
			MapType_Multiplayer = 2,
			MapType_Count
		};
		/*enum MapType : unsigned int
		{
			MapType_Singleplayer = 0,
			MapType_Multiplayer = 1,
			MapType_Mainmenu = 2,
			MapType_Shared = 3,
			MapType_SingleplayerShared = 4,
			MapType_Count
		};*/

		enum Language : unsigned char
		{
			Language_English = 0x00,
			Language_Russian = 0x0B
		};
	}
}