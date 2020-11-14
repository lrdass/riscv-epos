// EPOS RISC-V Timer Mediator Initialization

#include <machine/timer.h>
#include <machine/ic.h>

__BEGIN_SYS

void Timer::init()
{
    db<Init, Timer>(TRC) << "Timer::init()" << endl;

    CPU::smp_barrier();
    IC::int_vector(IC::INT_SYS_TIMER, int_handler);
    IC::enable(IC::INT_SYS_TIMER);
    
    CPU::smp_barrier();
    config(FREQUENCY);
}

__END_SYS
