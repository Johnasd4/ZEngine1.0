#include "ZCore.h"
#include"thread"
using namespace std;
using namespace ZEngine;
using namespace ZEngine::Console;

constexpr ZConstArray<Int32, 10> test1(ZConstArray<Int32, 10>::Init_Polynomial<Int32, Int32, Int32, Int32>, 2, 2, 2, 2);
constexpr ZConstArray<Int32, 10> test2(ZConstArray<Int32, 10>::Init_Polynomial<Int32, Int32, Int32, Int32>, 2, 2, 2, 2);
constexpr ZConstArray<Int32, 10> test([](ZConstArray<Int32, 10>* array, Int32 a, Int32 b)constexpr {
    for (int i = 0; i < array->getSize(); i++) {
        (*array)(i) = a + b;
    }    
    }, 1, 2);
//constexpr ZConstArray<Int32, 10> test1 = test + 1;

template<typename _InitFunc, typename... _Args>
constexpr Int32 testFunc(_InitFunc&& _initFunc, _Args&&... _args) {
    return _initFunc(std::forward<_Args>(_args)...);
}

constexpr Int32 add(Int32 a,Int32 b) {
    return a + b;
}

constexpr Int32 testValue1 = testFunc(add, 1, 2);
constexpr Int32 testValue2 = testFunc([](Int32 a, Int32 b)constexpr ->Int32  {return a + b; }, 1, 2);

class A {


public:

    static constexpr Boolean ifInitial = true;
    ZMemoryPiece* piece;
};

class B:public A {


public:

    static constexpr Boolean ifInitial = false;
};

template<Boolean ifTest>
Boolean testFunc();

template<>
Boolean testFunc<true>() {
    return true;
}

template<>
Boolean testFunc<false>() {
    return false;
}



int main()
{

    ZMemoryPool::CreateInstance();

   
    Int32* b = new Int32(1);
    ZMemoryPiece *a = new ZMemoryPiece();
    //a->size = 0;
    //cout << a->size;
    a->memoryAddress = (Address)a;
    cout << (UIntAddress)a->memoryAddress;
    cout <<  (UIntAddress)(*(Address*)a);
    cout << *b;

    return 0;
 
}
