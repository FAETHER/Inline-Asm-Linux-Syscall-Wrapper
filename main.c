
#include <unistd.h>
#include <sys/syscall.h>

void __stack_chk_fail()
{

}

void _syscall(long long syscallnum, long long arg0, long long arg1, long long arg2, long long arg3, long long arg4)
{
  asm volatile
    (
     	"mov %0, %%rax\n"
     	"mov %1, %%rdi\n"
     	"mov %2, %%rsi\n"
     	"mov %3, %%rdx\n"
     	"mov %4, %%r10\n"
     	"mov %5, %%r8\n"
        "syscall\n"
        : 
        : "m"(syscallnum), "m"(arg0), "m"(arg1), "m"(arg2), "m"(arg3), "m"(arg4)
        : "memory" 
    );
}

void _start()
{
	const char msg[] = "Hello World!\n";

	_syscall(__NR_write, STDOUT_FILENO, (long long)msg, sizeof(msg)-1, 0, 0);
	_syscall(__NR_fsync, STDOUT_FILENO, 0, 0, 0, 0);
	_syscall(SYS_exit, 0, 0, 0, 0, 0);
}
