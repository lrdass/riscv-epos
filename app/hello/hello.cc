// EPOS RISC-V 32 Test Program

#include <architecture/cpu.h>

using namespace EPOS;

int main()
{
    OStream cout;
    cout << "RISC-V 32bits test" << endl;

    CPU cpu;

    {
        volatile int number = 100;
        volatile int tmp;
        if((tmp = cpu.fdec(number)) != 100)
            cout << "fdec(): doesn't function properly (n=" << tmp << ", should be 100)!" << endl;
        else
            if((tmp = cpu.fdec(number)) != 99)
                cout << "fdec(): doesn't function properly (n=" << tmp << ", should be 99)!" << endl;
            else
                cout << "fdec(): ok" << endl;
    }
    {
        volatile int number = 100;
        volatile int compare = number;
        volatile int replacement = number - 1;
        volatile int tmp;
        if((tmp = cpu.cas(number, compare, replacement)) != compare)
            cout << "cas(): doesn't function properly [1] (n=" << tmp << ", should be " << compare << ")!" << endl;
        else
            if((tmp = cpu.cas(number, compare, replacement)) != replacement)
                cout << "cas(): doesn't function properly [2] (n=" << tmp << ", should be " << replacement << ")!" << endl;
            else
                cout << "cas(): ok" << endl;
    }

    cout << "RISC-V 32bits test finished" << endl;

    return 0;
}
