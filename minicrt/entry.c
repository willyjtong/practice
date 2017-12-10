// entry.c

#include "minicrt.h"

#ifdef WIN32
#include <Windows.h>
#endif

extern int main(int argc, char* argv[]);
void exit(int);

static void crt_fatal_error(const char* msg)
{
    // printf("fatal error: %s", msg);
    exit(1);
}

void mini_crt_entry(void)
{
    int ret;

#ifdef WIN32
    int flag = 0;
    int argc = 0;
    char* argv[16];  // max 16 args
    char* cl = GetCommandLineA();

    // parse commnd line
    argv[0] = cl;
    argc++;
    while(*cl)
    {
        if (*cl == '\"')
            if (flag == 0) flag = 1;
            else flag = 0;
        else if (*cl == ' ' && flag == 0)
        {
            if (*(cl+1))
            {
                argv[argc] = cl + 1;
                argc++;
            }
            *cl == '\0';
        }
        cl++;
    }
#else
    int argc;
    char** argv;

    char* ebp_reg = 0;
    // ebp_reg = &ebp
    asm("movl %%ebp,%0 \n\t":"=r"(ebp_reg));
    argc = *(int*)(ebp_reg + 4);
    argv = (char**)(ebp_reg + 8);
#endif  // WIN32

    if (!mini_crt_heap_init())
        crt_fatal_error("heap initialize failed");
    if (!mini_crt_io_init())
        crt_fatal_error("IO initialize failed");
    do_global_ctors();
    ret = main(argc, argv);
    exit(ret);
}


void exit(int exitcode)
{
    mini_crt_call_exit_routine();
#ifdef WIN32
    ExitProcess(exitcode);
#else
    asm("movl %0,%%ebx \n\t"
        "movl $1,%%eax \n\t"
        "int $0x80 \n\t"
        "hlt \n\t"::"m"(exitcode));
#endif
}
