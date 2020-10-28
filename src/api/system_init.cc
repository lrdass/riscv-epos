// EPOS System Initialization

#include <system.h>
#include <time.h>
#include <process.h>

__BEGIN_SYS
extern "C" unsigned int *__BSS_END__;
extern "C" unsigned int *__bss_start;

void System::init()
{
    
    if(Traits<Thread>::enabled)
        Thread::init();
}

__END_SYS
