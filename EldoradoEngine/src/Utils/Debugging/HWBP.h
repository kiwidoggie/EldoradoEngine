#pragma once
// http://www.unknowncheats.me/forum/c-and-c/58959-cbreakpoint-hardware-int3-breakpoints-they-work-and-class-wrote-manage-them.html
#include <Windows.h>

namespace EldoradoEngine
{
	namespace Utils
	{
		namespace Debugging
		{
			enum BreakType : char
			{
				BType_Execution = 0,
				BType_Write = 1,
				BType_Reserved = 2,
				BType_ReadWrite = 3
			};

			enum BreakpointType : char
			{
				BPType_Local = 1,
				BPType_Global = 2
			};

			enum BreakpointClass
			{
				BPClass_Hardware = 1,
				BPClass_Software = 2
			};

			enum BreakpointSize : char
			{
				BPSize_1B = 0,
				BPSize_2B = 1,
				BPSize_DWORD = 2,
				BPSize_WORD = 3
			};

			enum DebugRegisterIndex
			{
				DbgReg0 = 0,
				DbgReg1 = 1,
				DbgReg2 = 2,
				DbgReg3 = 3,
			};

			struct Bp
			{
				unsigned int m_TargetAddress;
				unsigned char m_BackupByte; // Used for setting software breakpoints
				HANDLE m_Thread; // HANDLE

				unsigned short m_Class; // Breakpoint Class
				unsigned short m_Type; // Breakpoint Type
				unsigned short m_Register; // Debug Register
				unsigned char m_Size; // Breakpoint Size
			};

			class HwBp
			{
			public:
				static int SetBp(Bp* p_Breakpoint);
				static int RestoreBp(Bp* p_Breakpoint);
				static int RestoreHwBpContext(Bp* p_Breakpoint, CONTEXT& p_Context);

			private:
				static int FetchDebugIndex(Bp* p_Breakpoint);
				static char GetByteTypeById(int p_Id);

				static int SetHardwareBreakpoint(Bp* p_Breakpoint);
				static int SetSoftwareBreakpoint(Bp* p_Breakpoint);

				static int RestoreHardwareBreakpoint(Bp* p_Breakpoint);
				static int RestoreSoftwareBreakpoint(Bp* p_Breakpoint);
			};
		}
	}
}