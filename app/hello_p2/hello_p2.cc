// EPOS Alarm Component Test Program

#include <process.h>
#include <time.h>
#include <synchronizer.h>
#include <process.h>
#include <utility/ostream.h>

using namespace EPOS;

OStream cout;


const int iterations = 10;

void func_a(void);
void func_b(void);


int fast_job(){
    int counter = 0;
    while(counter < 3){
        cout << "Thread 1 => Working\n";
        int i = 0;
        while(i < 200000){i++;}
        counter++;
    }
    cout << "Thread 1 => Finished\n";

    return 0;
}

int slow_job(){
    int counter = 0;
    while(counter < 3){
        cout << "Thread 2 => Working\n";
        int i = 0;
        while(i < 1000000){i++;}
        counter++;
    }
    cout << "Thread 2 => Finished\n";

    return 0;
}

int fast_long_job(){
    int counter = 0;
    while(counter < 150){
        cout << "Thread 3 => Working\n";
        int i = 0;
        while(i < 100000){i++;}
        counter++;
    }
    cout << "Thread 3 => Finished\n";
    cout << "Teste de Escalonador e Preempção finalizado!" << endl;

    return 0;
}


int main()
{
    cout << "Teste de Alarme" << endl;
    Function_Handler handler_a(&func_a);
    Alarm alarm_a(2000000, &handler_a, iterations);

    Function_Handler handler_b(&func_b);
    Alarm alarm_b(1000000, &handler_b, iterations);
    Alarm::delay(2000000 * (iterations + 2));

    cout << "Teste de Alarme finalizado!" << endl;



    cout << "Teste de Escalonador e Preempção" << endl;
    Thread* th1 = new Thread(&fast_job);
    Thread* th2 = new Thread(&fast_long_job);
    Thread* th3 = new Thread(&slow_job);
}


void func_a()
{
    for(int i = 0; i < 79; i++)
        cout << "a";
    cout << endl;
}

void func_b(void)
{
    for(int i = 0; i < 79; i++)
        cout << "b";
    cout << endl;
}
