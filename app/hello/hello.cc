#include <utility/ostream.h>
#include <time.h>
#include <synchronizer.h>
#include <process.h>

using namespace EPOS;

Thread *t1, *t2;
OStream cout;


int thread1(){
    OStream cout;
    cout << "primeira" << endl;
    return 1;
}

int thread2(){
    OStream cout;
    cout << "segunda" << endl;
    return 2;
}

int bss0;

int main()
{
    cout<< "bss value: " << endl;
    cout<< bss0 << endl;

    
    t1 = new Thread(&thread1);
    t2 = new Thread(&thread2);

    t1->join();
    t2->join();

    cout << "finished" << endl;

    return 0;
}
