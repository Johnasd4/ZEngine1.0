#include"ZEngine.h"

using namespace std;
using namespace ZEngine;
using namespace ZEngine::Console;



template<typename T>
concept Check = requires{
    T::a;
};

template<typename T>
Int32 testFunc1() 
{
    if constexpr (requires{T::a;})
    {
        return 1;
    }
    else
    {
        return 2;
    }
}



struct A {

    operator Int32() {
        cout << "test";
        return 1;
    }
    int a;
};

#include<thread>
int main()
{

    cout << testFunc1<A>() << endl;
    cout << testFunc1<Int32>() << endl;
    A a = A{1};
    (Int32)a;
    ZMemoryPool::CreateInstance();
    sizeof(std::shared_ptr<Int32>);
    auto b = new Int32[100];
    Int32* test = new Int32(10);
    test->~Int32();
    return 0;
 
}
