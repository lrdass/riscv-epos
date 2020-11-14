// EPOS PC Timer Mediator Initialization

#include <machine/timer.h>
#include <machine/ic.h>

__BEGIN_SYS

void Timer::init()
{
    db<Init, Timer>(TRC) << "Timer::init()" << endl;

    CPU::int_disable();

    CPU::smp_barrier();
    if(!Traits<System>::multicore || (CPU::id() == 0))
        IC::int_vector(IC::INT_SYS_TIMER, int_handler);

    CPU::smp_barrier();
    Engine::config(0, Engine::clock() / FREQUENCY);
    IC::enable(IC::INT_SYS_TIMER);

    CPU::smp_barrier();
    CPU::int_enable();
}

__END_SYS
