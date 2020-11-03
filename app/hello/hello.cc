#include <machine.h>
#include <time.h>
#include <synchronizer.h>
#include <process.h>

using namespace EPOS;

OStream cout;
typedef unsigned int Reg32;


int func1(){
    cout << "th1" << endl;

    Delay time(1000000);
    return 0;
}

int main()
{
    Thread * thread = new Thread(&func1);
    thread->join();
    
    return 0;
}
