// EPOS Alarm Component Test Program

#include <process.h>
#include <time.h>

using namespace EPOS;

const int iterations = 10;

OStream cout;

int func_a()
{
    int i =0;
    while (true)
    {
        cout<< "a running" << endl;
        i++;
    }
    return i;
    
}

int func_b()
{
    int i =0;
    while (true)
    {
        cout<< "b running" << endl;
        i++;
    }
    return i;
}

int main()
{
    Thread* th1 = new Thread(&func_a);
    Thread* th2 = new Thread(&func_b);

    th1->join();
    th2->join();
}
