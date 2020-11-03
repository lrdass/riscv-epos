#include <machine.h>
#include <time.h>
#include <synchronizer.h>
#include <process.h>

using namespace EPOS;

OStream cout;
typedef unsigned int Reg32;


int func1(){
    while(1){
        cout << "Func1 \n" << endl;
        Alarm::delay(10000);
    }
    return 0;
}

int func2(){
    while(1){
        cout << "Func2 \n" << endl;
        Alarm::delay(20000);
    }
    return 0;
}

int main()
{
    Thread * thread = new Thread(&func1);
    Thread * thread2 = new Thread(&func2);
    thread->join();
    thread2->join();
    
    return 0;
}
