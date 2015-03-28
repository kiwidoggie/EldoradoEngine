#include "Logger.h"
#include <stdio.h>
#include <sstream>

using namespace EldoradoEngine::Utils;

Logger* Logger::m_Instance = nullptr;
Logger* Logger::Inst()
{
	if (!m_Instance)
		m_Instance = new Logger;

	return m_Instance;
}

Logger::Logger() : m_FileHandle(INVALID_HANDLE_VALUE), m_ConsoleHandle(INVALID_HANDLE_VALUE)
{
	Init();
}

Logger::~Logger()
{
	if (m_FileHandle != INVALID_HANDLE_VALUE)
		CloseHandle(m_FileHandle);
}

void Logger::Init()
{
	// Create our file handle
	m_FileHandle = CreateFile("EldoradoEngine.log", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// Allocate a new console
	if (!AllocConsole())
		WriteLog("Unable to allocate console...");

	SetConsoleTitle("EldoradoEngine by kiwidog & help from stoker25");

	// Get the output handle for it for future use
	m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Logger::InternalWriteLog(char* p_Func, int p_Line, char* p_Fmt, ...)
{
	va_list s_Args;
	va_start(s_Args, p_Fmt);

	auto s_FinalLength = _vscprintf(p_Fmt, s_Args) + 1;
	char* s_FinalString = (char*)malloc(s_FinalLength);
	if (!s_FinalLength)
		return;

	vsprintf_s(s_FinalString, s_FinalLength, p_Fmt, s_Args);
	va_end(s_Args);

	std::stringstream s_Stream;
	s_Stream << "[" << p_Func << " : " << p_Line << "] " << s_FinalString << "\r\n";

	auto s_String = s_Stream.str();

	DWORD s_Output = 0;
	if (m_ConsoleHandle != INVALID_HANDLE_VALUE)
		WriteConsole(m_ConsoleHandle, s_String.c_str(), s_String.length(), &s_Output, NULL);

	if (m_FileHandle != INVALID_HANDLE_VALUE)
	{
		WriteFile(m_FileHandle, s_String.c_str(), s_String.length(), &s_Output, NULL);
		FlushFileBuffers(m_FileHandle);
	}
}