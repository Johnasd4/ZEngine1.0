#include"ZEngine.h"
#include<list>
using namespace std;
using namespace ZEngine;
using namespace ZEngine::Private;
using namespace ZEngine::Console;


const Int32 test(int a) {
    return a++;
}


#include<tuple>

int main()
{
    cout<<test(1);
    ZMemoryPool::Instance();
    std::tuple<Int32>;
    return 0;

}
