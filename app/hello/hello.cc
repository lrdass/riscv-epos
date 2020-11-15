
// EPOS Semaphore Component Test Program

#include <machine/display.h>
#include <time.h>
#include <synchronizer.h>
#include <process.h>

using namespace EPOS;


OStream cout;

int th1(){
   cout << "thread 1 " ;
   return 1;
}

int th2(){
   cout << "thread 2 " ;
   return 2;
}

int main()
{
    Thread* t1 = new Thread(&th1);
    Thread* t2 = new Thread(&th2);

    t1->join();
    t2->join();
    
}
