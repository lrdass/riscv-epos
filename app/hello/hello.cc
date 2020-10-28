#include <utility/ostream.h>
#include <time.h>
#include <synchronizer.h>
#include <process.h>

using namespace EPOS;

Thread *t1, *t2;
OStream cout;

int thread1(){
    cout << "Primeira Thread criada com tempo maior!" << endl;
    return 1;
}

int thread2(){
    cout << "Segunda Thread criada com tempo menor!" << endl;
    return 2;
}

int main()
{
    
    t1 = new Thread(Thread::Configuration(Thread::READY, Thread::Criterion(180)), &thread1);
    t2 = new Thread(Thread::Configuration(Thread::READY, Thread::Criterion(100)), &thread2);
    t1->join();
    t2->join();

    cout << "finished" << endl;

    return 0;
}
