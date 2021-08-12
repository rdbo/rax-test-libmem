#include <stdio.h>
#include <unistd.h>

long
callme(long rdi, long rsi, long rdx, long rcx,
       long r8, long r9, long stk0, long stk1)
{
	printf("[*] CallMe RDI: %li\n", rdi);
	printf("[*] CallMe RSI: %li\n", rsi);
	printf("[*] CallMe RDX: %li\n", rdx);
	printf("[*] CallMe RCX: %li\n", rcx);
	printf("[*] CallMe R8: %li\n", r8);
	printf("[*] CallMe R9: %li\n", r9);
	printf("[*] CallMe Stack Args: { %li, %li }\n", stk0, stk1);
	return 1337;
}

int
main()
{
	printf("[*] PID: %d\n", getpid());
	printf("[*] CallMe Addr: %p\n", callme);

	for (;;) {
		printf("[*] Waiting...\n");
		sleep(1);
	}
	return 0;
}
