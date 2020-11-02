#include <utility/ostream.h>

using namespace EPOS;

OStream cout;
typedef unsigned int Reg32;

int main()
{
    // volatile Reg32* mtimecmp = reinterpret_cast<Reg32*>(Memory_Map::TIMER_BASE);
    // volatile Reg32* mtime = reinterpret_cast<Reg32*>(Memory_Map::PRIVATE_TIMER_BASE);
    // *mtimecmp = *mtime + 10000000;
    cout << "Hello world!" << endl;
    while(1){
        continue;
    }
    
    return 0;
}
