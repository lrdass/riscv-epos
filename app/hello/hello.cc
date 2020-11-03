// EPOS Alarm Component Test Program

#include <time.h>

using namespace EPOS;

const int iterations = 10;

void func_a(void);
void func_b(void);

OStream cout;

int main()
{
    cout << "Alarm test" << endl;

    cout << "I'm the first thread of the first task created in the system." << endl;
    cout << "I'll now create two alarms and put myself in a delay ..." << endl;

    Function_Handler handler_a(&func_a);
    Alarm alarm_a(2000000, &handler_a, iterations);

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

void func_a()
{
    Thread * thread = new Thread(&func1);
    Thread * thread2 = new Thread(&func2);
    thread->join();
    thread2->join();
    
    return 0;
}
