#include"ZEngine.h"

using namespace std;
using namespace ZEngine;
using namespace ZEngine::Console;



int main()
{
    ZMemoryPool::CreateInstance();
    ZArray<Int32> a;
    //ZArray<ZArray<Int32>> b(a);
    //ZArray<ZArray<Int32>> c = a;
    for (Int32 index = 0; index < 30; index++) {
        a.push(index);
    }
    
    a.insert(10, 100);
    a.remove(10);

    for (Int32 index = 0; index < a.getSize(); index++) {
        cout << a(index) << endl;
    }



    return 0;
 
}
