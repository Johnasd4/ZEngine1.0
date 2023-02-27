#include "ZCore.h"
#include"thread"
using namespace std;
using namespace ZEngine;
using namespace ZEngine::Console;

constexpr ZConstArray<Int32, 10> test1(ZConstArray<Int32, 10>::Init_Polynomial<Int32, Int32, Int32, Int32>, 2, 2, 2, 2);
constexpr ZConstArray<Int32, 10> test2(ZConstArray<Int32, 10>::Init_Polynomial<Int32, Int32, Int32, Int32>, 2, 2, 2, 2);
constexpr ZConstArray<Int32, 10> test(ZConstArray<Int32, 10>::Init_AddSequence<ZConstArray<Int32, 10>, ZConstArray<Int32, 10>>, test1, test2);
//constexpr ZConstArray<Int32, 10> test1 = test + 1;



class A {

public:

    int a;

    A() {
        cout << "构造A" << endl;
    }

    ~A() {
        cout << "析构A" << endl;
    }

};




int main()
{
    ZMemoryPool::CreateInstance();

    ZObject object(1000);
    sizeof(ZObject);
}
