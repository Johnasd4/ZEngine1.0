#include"ZEngine.h"

using namespace std;
using namespace ZEngine;
using namespace ZEngine::Console;




int main()
{
    ZMemoryPool::CreateInstance();
    ZArray<Int32> a(10);
    for (Int32 index = 0; index < 100; index++) {
        a.push(index);
    }
    a.remove(10);
    FIELD_OFFSET();
    for (Int32 index = 0; index < a.getSize(); index++) {
        cout << a(index) << endl;
    }

    Int32* b= new Int32(1);
    Int32** c = &b;

    cout << *b;
    cout << **c;

    return 0;
 
}
