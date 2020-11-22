// EPOS Alarm Component Test Program

#include <process.h>
#include <time.h>
#include <synchronizer.h>
#include <process.h>
#include <utility/ostream.h>

using namespace EPOS;

OStream cout;


const int fast_jobs = 27;
const int slow_jobs = 9;
const int long_jobs = 3;


int fast_job(int id){
    int counter = 0;
    while(counter < 3){
        cout << "Fast Job " << id << " => Working <" << CPU::id() << ">\n";
        int i = 0;
        while(i < 200000){i++;}
        counter++;
    }
    cout << "Fast Job " << id << " => Finished <" << CPU::id() << ">\n";

    return 0;
}

int slow_job(int id){
    int counter = 0;
    while(counter < 3){
        cout << "Slow Job " << id << " => Working <" << CPU::id() << ">\n";
        int i = 0;
        while(i < 1000000){i++;}
        counter++;
    }
    cout << "Slow Job " << id << " => Finished <" << CPU::id() << ">\n";

    return 0;
}

int fast_long_job(int id){
    int counter = 0;
    while(counter < 150){
        cout << "Long Job " << id << " => Working <" << CPU::id() << ">\n";
        int i = 0;
        while(i < 100000){i++;}
        counter++;
    }
    cout << "Long Job " << id << " => Finished <" << CPU::id() << ">\n";

    return 0;
}


int main()
{

    cout << "Teste de Escalonador e Preempção" << endl;
    
    for(int i = 0; i < fast_jobs; i++){
        new Thread(&fast_job, i);
    }

    for(int i = 0; i < slow_jobs; i++){
        new Thread(&slow_job, i);
    }

    for(int i = 0; i < long_jobs; i++){
        new Thread(&fast_long_job, i);
    }



}
