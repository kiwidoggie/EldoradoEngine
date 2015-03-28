#pragma once
#include <IInit.h>
#include <Windows.h>

#define LOG_BUF_SIZE	1024

#define WriteLog(format, ...) EldoradoEngine::Utils::Logger::Inst()->InternalWriteLog(__FUNCTION__, __LINE__, format, __VA_ARGS__);

namespace EldoradoEngine
{
	namespace Utils
	{
		class Logger : IInit
		{
		private:
			static Logger* m_Instance;
			HANDLE m_ConsoleHandle;
			HANDLE m_FileHandle;

		private:
			Logger();
			~Logger();

		public:
			static Logger* Inst();
			void Init();
			void InternalWriteLog(char* p_Func, int p_Line, char* fmt, ...);

		};
	}
}