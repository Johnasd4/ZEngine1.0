#include"ZEngine.h"

using namespace std;
using namespace ZEngine;
using namespace ZEngine::Console;



int main()
{
    ZMemoryPool::CreateInstance();
    ZContainer<ZContainer<Int32>> a;
    ZContainer<ZContainer<Int32>> b(a);
    b = a;
    return 0;
 
}
