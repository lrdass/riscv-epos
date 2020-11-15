// EPOS Thread Initialization

#include <machine/timer.h>
#include <machine/ic.h>
#include <system.h>
#include <process.h>

__BEGIN_SYS

extern "C" { void __epos_app_entry(); }

void Thread::init()
{
    db<Init, Thread>(TRC) << "Thread::init()" << endl;

    // If EPOS is a library, then adjust the application entry point to __epos_app_entry,
    // which will directly call main(). In this case, _init will have already been called,
    // before Init_Application to construct MAIN's global objects.

    // Idle thread creation does not cause rescheduling (see Thread::constructor_epilogue)

    // The installation of the scheduler timer handler does not need to be done after the
    // creation of threads, since the constructor won't call reschedule() which won't call
    // dispatch that could call timer->reset()
    // Letting reschedule() happen during thread creation is also harmless, since MAIN is
    // created first and dispatch won't replace it nor by itself neither by IDLE (which
    // has a lower priority)
    CPU::smp_barrier();

    if(CPU::id() == 0) {
        // If EPOS is a library, then adjust the application entry point to __epos_app_entry,
        // which will directly call main(). In this case, _init will have already been called,
        // before Init_Application to construct MAIN's global objects.
        new (SYSTEM) Thread(Thread::Configuration(Thread::RUNNING, Thread::MAIN), reinterpret_cast<int (*)()>(__epos_app_entry));

        // Idle thread creation does not cause rescheduling (see Thread::constructor_epilogue)
        new (SYSTEM) Thread(Thread::Configuration(Thread::READY, Thread::IDLE), &Thread::idle);
    } else
        new (SYSTEM) Thread(Thread::Configuration(Thread::RUNNING, Thread::IDLE), &Thread::idle);

    CPU::smp_barrier();
    
    if(Criterion::timed && CPU::id() == 0)
        _timer = new (SYSTEM) Scheduler_Timer(QUANTUM, time_slicer);

    // Transition from CPU-based locking to thread-based locking
    This_Thread::not_booting();
}

__END_SYS
