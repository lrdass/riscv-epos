#include <machine/display.h>
#include <time.h>
#include <synchronizer.h>
#include <process.h>
#include <utility/ostream.h>

using namespace EPOS;

OStream cout;

int fast_job(int delay){
    int counter = 0;
    while(counter < 2){
        cout << "Thread 1 => Working\n";
        // Delay working(delay);
        counter++;
        cout << "Thread 1 Used => " << delay*counter << "us \n";
    }
    cout << "Thread 1 => Finished\n";

    return 0;
}

int slow_job(int delay){
    int counter = 0;
    while(counter < 3){
        cout << "Thread 2 => Working\n";
        // Delay working(delay);
        counter++;
        cout << "Thread 2 Used => " << delay*counter << "us \n";
    }
    cout << "Thread 2 => Finished\n";
    cout << "Teste Feedback Scheduler Completo!" << endl;

    return 0;
}

int fast_long_job(int delay){
    int counter = 0;
    while(counter < 6){

        cout << "Thread 3 => Working\n";
        // Delay working(delay);
        counter++;
        cout << "Thread 3 Used => " << delay*counter << "us \n";
    }
    cout << "Thread 3 => Finished\n";

    return 0;
}



const int iterations = 10;

void func_a(void);
void func_b(void);

int main()
{
    cout << "Teste Alarme" << endl;

    Function_Handler handler_a(&func_a);
    Alarm alarm_a(2000000, &handler_a, iterations);

    Function_Handler handler_b(&func_b);
    Alarm alarm_b(1000000, &handler_b, iterations);

    // Note that in case of idle-waiting, this thread will go into suspend
    // and the alarm handlers above will trigger the functions in the context
    // of the idle thread!
    Alarm::delay(2000000 * (iterations + 2));

    cout << "Teste Alarme Completo" << endl;




    cout << "Teste Feedback Scheduler" << endl;
    Thread* t1 = new Thread(&fast_job, 15000); // TOTAL 8000
    Thread* t2 = new Thread(&slow_job, 15000); // TOTAL 27000
    // Thread* t3 = new Thread(&fast_long_job, 4000);  // TOTAL = 24000
    
    return 0;
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
