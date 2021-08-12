#include "libmem/libmem.h"

int
main()
{
	lm_process_t proc;
	lm_tchar_t   procpath[LM_PATH_MAX] = { 0 };
	lm_module_t  mod;
	lm_address_t callme_addr;
	lm_datio_t   arg0;
	lm_uintptr_t arg0dat = 10;

	lm_datio_t   arg1;
	lm_uintptr_t arg1dat = 20;

	lm_datio_t   arg2;
	lm_uintptr_t arg2dat = 30;

	lm_datio_t   arg3;
	lm_uintptr_t arg3dat = 40;

	lm_datio_t   arg4;
	lm_uintptr_t arg4dat = 50;

	lm_datio_t   arg5;
	lm_uintptr_t arg5dat = 69;

	lm_datio_t   arg6;
	lm_uintptr_t arg6dat = 69420;

	lm_datio_t   arg7;
	lm_uintptr_t arg7dat = 1337;

	lm_datio_t   ret0;
	lm_uintptr_t retbuf;

	LM_OpenProcessEx(LM_GetProcessIdEx(LM_STR("target")), &proc);
	printf("[*] PID: %d\n", proc.pid);

	LM_GetProcessPathEx(proc, procpath, LM_ARRLEN(procpath));
	printf("[*] Process Path: %s\n", procpath);


	LM_GetModuleEx(proc, LM_MOD_BY_STR, procpath, &mod);
	printf("[*] Module Base: %p\n", mod.base);
	printf("[*] Module End:  %p\n", mod.end);

	callme_addr = LM_GetSymbolEx(proc, mod, "callme");
	printf("[*] CallMe Address: %p\n", callme_addr);

	arg0.datloc = LM_DATLOC_RDI;
	arg0.data   = (lm_byte_t *)&arg0dat;

	arg1.datloc = LM_DATLOC_RSI;
	arg1.data   = (lm_byte_t *)&arg1dat;
	
	arg2.datloc = LM_DATLOC_RDX;
	arg2.data   = (lm_byte_t *)&arg2dat;
	
	arg3.datloc = LM_DATLOC_RCX;
	arg3.data   = (lm_byte_t *)&arg3dat;

	arg4.datloc = LM_DATLOC_R8;
	arg4.data   = (lm_byte_t *)&arg4dat;

	arg5.datloc = LM_DATLOC_R9;
	arg5.data   = (lm_byte_t *)&arg5dat;

	arg6.datloc = LM_DATLOC_STACK;
	arg6.data   = (lm_byte_t *)&arg6dat;
	arg6.size   = sizeof(arg6dat);

	arg7.datloc = LM_DATLOC_STACK;
	arg7.data   = (lm_byte_t *)&arg7dat;
	arg7.size   = sizeof(arg7dat);

	ret0.datloc = LM_DATLOC_RAX;
	ret0.data   = (lm_byte_t *)&retbuf;

	/* LM_FunctionCallEx(proc, -8, callme_addr, 8, 1, arg7, arg6, arg5, arg4, arg3, arg2, arg1, arg0, ret0);
	sleep(2); */
	LM_FunctionCallEx(proc, -8, callme_addr, 8, 1, arg7, arg6, arg5, arg4, arg3, arg2, arg1, arg0, ret0);
	retbuf = 0xfffffffffffffdfc;
	LM_FunctionCallEx(proc, -8, callme_addr, 9, 1, ret0, arg7, arg6, arg5, arg4, arg3, arg2, arg1, arg0, ret0);
	retbuf = 0;
	LM_FunctionCallEx(proc, -8, callme_addr, 9, 1, ret0, arg7, arg6, arg5, arg4, arg3, arg2, arg1, arg0, ret0);
	

	printf("[*] CallMe Return Value: %li\n", retbuf);

	LM_CloseProcess(&proc);

	return 0;
}