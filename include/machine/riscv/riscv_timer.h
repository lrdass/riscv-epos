// EPOS RISC-V Timer Mediator Declarations

#ifndef __riscv_timer_h
#define __riscv_timer_h

#include <architecture/cpu.h>
#include <machine/ic.h>
#include <machine/timer.h>
#include <system/memory_map.h>
#include <utility/convert.h>

__BEGIN_SYS

// Tick timer used by the system
class Timer: private Timer_Common
{
    friend Machine;
    friend IC;
    friend class Init_System;

protected:
    static const unsigned int CHANNELS = 2;
    static const unsigned int FREQUENCY = Traits<Timer>::FREQUENCY;

    typedef IC_Common::Interrupt_Id Interrupt_Id;
    typedef unsigned long  Reg32;

public:
    using Timer_Common::Tick;
    using Timer_Common::Handler;

    // Channels
    enum {
        SCHEDULER,
        ALARM
    };

    // Registers offsets from CLINT_BASE
    enum {
        /**
        Address         Description     Note
        BASE + 0x0      msip            Machine mode software interrupt (IPI)
        BASE + 0x4000   mtimecmp        Machine mode timer compare register for Hart 0
        BASE + 0xBFF8   mtime           Timer register
        **/
        MTIMECMP        = 0X00004000,
        MTIME           = 0x0000BFF8
    };

    static const Hertz CLOCK = Traits<Machine>::TIMER_CLOCK;

protected:
    Timer(unsigned int channel, const Hertz & frequency, const Handler & handler, bool retrigger = true)
    : _channel(channel), _initial(FREQUENCY / frequency), _retrigger(retrigger), _handler(handler) {
        db<Timer>(TRC) << "Timer(f=" << frequency << ",h=" << reinterpret_cast<void*>(handler) << ",ch=" << channel << ") => {count=" << _initial << "}" << endl;

        if(_initial && (channel < CHANNELS) && !_channels[channel])
            _channels[channel] = this;
        else
            db<Timer>(WRN) << "Timer not installed!"<< endl;

        for(unsigned int i = 0; i < Traits<Machine>::CPUS; i++)
            _current[i] = _initial;
    }

public:
    ~Timer() {
        db<Timer>(TRC) << "~Timer(f=" << frequency() << ",h=" << reinterpret_cast<void*>(_handler) << ",ch=" << _channel << ") => {count=" << _initial << "}" << endl;

        _channels[_channel] = 0;
    }

    Hertz frequency() const { return (FREQUENCY / _initial); }
    void frequency(const Hertz & f) { _initial = FREQUENCY / f; reset(); }

    Tick read() { return _current[CPU::id()]; }

    int reset() {
        db<Timer>(TRC) << "Timer::reset() => {f=" << frequency()
                       << ",h=" << reinterpret_cast<void*>(_handler)
                       << ",count=" << _current[CPU::id()] << "}" << endl;

        int percentage = _current[CPU::id()] * 100 / _initial;
        _current[CPU::id()] = _initial;

        return percentage;
    }

    void enable() {}

    void disable() {}

    void handler(const Handler & handler) { _handler = handler; }

    static void config(const Hertz & frequency) {
        // IMPLEMENT: set timer to next interrupt
        reg(MTIMECMP) = reg(MTIME) + frequency;
    }

    static Hertz clock() {
        return CLOCK;
    }

private:
    static volatile CPU::Reg32 & reg(unsigned int o) { return reinterpret_cast<volatile CPU::Reg32 *>(Memory_Map::CLINT_BASE)[o / sizeof(CPU::Reg32)]; }

    static void int_handler(Interrupt_Id i);

    static void init();

private:
    unsigned int _channel;
    Tick _initial;
    bool _retrigger;
    volatile Tick _current[Traits<Build>::CPUS];
    Handler _handler;

    static Timer * _channels[CHANNELS];
};

// Timer used by Thread::Scheduler
class Scheduler_Timer: public Timer
{
public:
    Scheduler_Timer(const Microsecond & quantum, const Handler & handler): Timer(SCHEDULER, 1000000 / quantum, handler) {}
};

// Timer used by Alarm
class Alarm_Timer: public Timer
{
public:
    static const unsigned int FREQUENCY = Timer::FREQUENCY;

public:
    Alarm_Timer(const Handler & handler): Timer(ALARM, FREQUENCY, handler) {}
};

__END_SYS

#endif
