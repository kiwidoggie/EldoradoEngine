#include "HWBP.h"
#include "BitTools.h"

#include <Aclapi.h>
#define CHWBP_BYTE_INDEX_DR_BPFLAGS  0
#define CHWBP_BYTE_INDEX_DR_BPTYPE_SIZE   16

using namespace EldoradoEngine::Utils::Debugging;

int HwBp::FetchDebugIndex(Bp* p_Breakpoint)
{
	if (p_Breakpoint->m_Class != BPClass_Hardware)
		return -1;

	if (p_Breakpoint->m_Register < 0 || p_Breakpoint->m_Register > 3)
		return -1;

	return p_Breakpoint->m_Register;
}

char HwBp::GetByteTypeById(int p_Id)
{
	if (p_Id < 0 || p_Id > 3)
		return 0;

	return (char)p_Id;
}

int HwBp::SetHardwareBreakpoint(Bp* p_Breakpoint)
{
	auto s_DbgRegisterIndex = FetchDebugIndex(p_Breakpoint);

	if (s_DbgRegisterIndex < 0)
		return -1;

	auto s_Thread = ((p_Breakpoint->m_Thread == 0) ? GetCurrentThread() : p_Breakpoint->m_Thread);
	p_Breakpoint->m_Thread = s_Thread;

	SetSecurityInfo(s_Thread, SE_UNKNOWN_OBJECT_TYPE, THREAD_ALL_ACCESS, 0, 0, 0, 0);

	CONTEXT s_ThreadContext;
	ZeroMemory(&s_ThreadContext, sizeof(CONTEXT));

	s_ThreadContext.ContextFlags = CONTEXT_DEBUG_REGISTERS | CONTEXT_FULL;
	GetThreadContext(s_Thread, &s_ThreadContext);

	*(unsigned long*)(&s_ThreadContext.Dr0 + s_DbgRegisterIndex * sizeof(DWORD)) = p_Breakpoint->m_TargetAddress;

	//Setting  Flags
	OrBit<DWORD>(s_ThreadContext.Dr7,
		CHWBP_BYTE_INDEX_DR_BPFLAGS + (s_DbgRegisterIndex * 2),
		BPType_Local, //Forces a Localization of all HW breakpoints set with this class. Windows does not allow globalized breakpoints.
		2,
		false);

	//Setting Type
	OrBit<DWORD>(s_ThreadContext.Dr7,
		CHWBP_BYTE_INDEX_DR_BPTYPE_SIZE + (s_DbgRegisterIndex * 4),
		GetByteTypeById(p_Breakpoint->m_Type),
		2,
		false);


	//Setting Size
	OrBit<DWORD>(s_ThreadContext.Dr7, CHWBP_BYTE_INDEX_DR_BPTYPE_SIZE + (s_DbgRegisterIndex * 4) + 2,
		p_Breakpoint->m_Size,
		2,
		false);

	s_ThreadContext.ContextFlags = CONTEXT_FULL | CONTEXT_DEBUG_REGISTERS;

	if (SetThreadContext(s_Thread, &s_ThreadContext) == 0)
		return -1;

	return 1;
}

int HwBp::SetSoftwareBreakpoint(Bp* p_Breakpoint)
{
	if (p_Breakpoint->m_Type != BType_Execution ||
		p_Breakpoint->m_Size != BPSize_1B)
		return -1;

	p_Breakpoint->m_BackupByte = *(char*)p_Breakpoint->m_TargetAddress;
	*(char*)p_Breakpoint->m_TargetAddress = 0xCC;
	return 1;
}

int HwBp::RestoreHwBpContext(Bp* p_Breakpoint, CONTEXT& p_Context)
{

	int s_DbRegisterIndex = FetchDebugIndex(p_Breakpoint);

	if (s_DbRegisterIndex < 0 || p_Breakpoint->m_Thread == 0)
		return -1;

	auto s_Thread = p_Breakpoint->m_Thread;

	SetSecurityInfo(s_Thread, SE_UNKNOWN_OBJECT_TYPE, THREAD_ALL_ACCESS, 0, 0, 0, 0);

	//Setting Deebug registry target address
	*(unsigned long*)(&p_Context.Dr0 + s_DbRegisterIndex * sizeof(DWORD)) = 0;

	//Setting  Flags
	AndBit<DWORD>(p_Context.Dr7,
		CHWBP_BYTE_INDEX_DR_BPFLAGS + (s_DbRegisterIndex * 2),
		0,
		2,
		false);

	//Setting Type
	AndBit<DWORD>(p_Context.Dr7,
		CHWBP_BYTE_INDEX_DR_BPTYPE_SIZE + (s_DbRegisterIndex * 4),
		0,
		2,
		false);

	//Setting Size
	AndBit<DWORD>(p_Context.Dr7, CHWBP_BYTE_INDEX_DR_BPTYPE_SIZE + (s_DbRegisterIndex * 4) + 2,
		0,
		2,
		false);

	return 1;
}

int HwBp::RestoreHardwareBreakpoint(Bp* p_Breakpoint)
{

	int s_DbgRegisterIndex = FetchDebugIndex(p_Breakpoint);

	if (s_DbgRegisterIndex < 0 || p_Breakpoint->m_Thread == 0)
		return -1;

	auto s_Thread = p_Breakpoint->m_Thread;

	SetSecurityInfo(s_Thread, SE_UNKNOWN_OBJECT_TYPE, THREAD_ALL_ACCESS, 0, 0, 0, 0);

	CONTEXT s_ThreadContext;
	ZeroMemory(&s_ThreadContext, sizeof(CONTEXT));


	s_ThreadContext.ContextFlags = CONTEXT_DEBUG_REGISTERS | CONTEXT_FULL;
	GetThreadContext(s_Thread, &s_ThreadContext);

	//Setting Deebug registry target address
	*(unsigned long*)(&s_ThreadContext.Dr0 + s_DbgRegisterIndex * sizeof(DWORD)) = 0;

	//Setting  Flags
	AndBit<DWORD>(s_ThreadContext.Dr7,
		CHWBP_BYTE_INDEX_DR_BPFLAGS + (s_DbgRegisterIndex * 2),
		0,
		2,
		false);

	//Setting Type
	AndBit<DWORD>(s_ThreadContext.Dr7,
		CHWBP_BYTE_INDEX_DR_BPTYPE_SIZE + (s_DbgRegisterIndex * 4),
		0,
		2,
		false);

	//Setting Size
	AndBit<DWORD>(s_ThreadContext.Dr7, CHWBP_BYTE_INDEX_DR_BPTYPE_SIZE + (s_DbgRegisterIndex * 4) + 2,
		0,
		2,
		false);


	s_ThreadContext.ContextFlags = CONTEXT_FULL | CONTEXT_DEBUG_REGISTERS;

	if (SetThreadContext(s_Thread, &s_ThreadContext) == 0)
		return -1;

	return 1;
}

int HwBp::RestoreSoftwareBreakpoint(Bp* p_Breakpoint)
{
	*(char*)p_Breakpoint->m_TargetAddress = p_Breakpoint->m_BackupByte;
	p_Breakpoint->m_BackupByte = 0;
	return 1;
}


int HwBp::RestoreBp(Bp* p_Breakpoint)
{
	switch (p_Breakpoint->m_Class)
	{
	case BPClass_Hardware:
		return RestoreHardwareBreakpoint(p_Breakpoint);
		break;
	case BPClass_Software:
		return RestoreSoftwareBreakpoint(p_Breakpoint);
		break;
	default:
		return -1;
	}
	return -1;
}

int HwBp::SetBp(Bp* p_Breakpoint)
{
	switch (p_Breakpoint->m_Class)
	{
	case BPClass_Hardware:
		return SetHardwareBreakpoint(p_Breakpoint);
		break;
	case BPClass_Software:
		return SetSoftwareBreakpoint(p_Breakpoint);
		break;
	default:
		return -1;
	}
	return -1;
}