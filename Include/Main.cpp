#include"ZEngine.h"

using namespace std;
using namespace ZEngine;
using namespace ZEngine::Console;



/* 模板函数，检查T是否有名为's'的成员
 * value 为bool型检查结果
 * type为s成员的类型(value为true是有效)
 */
template<typename T>struct has_member_s {
    template <typename _T>
    static auto check(_T) -> typename std::decay<decltype(_T::s)>::type;
    static void check(...);
    using type = decltype(check(std::declval<T>()));
    enum { value = !std::is_void<type>::value };
};


class A {
public:
    int a;

};


template <typename T>
void f(typename T::foo) {}

struct Derived : A {
    int a;
};


typedef char ArrayOfOne[1];

int main()
{
    decltype(A::a) a;

    ArrayOfOne a;
    ZMemoryPool::CreateInstance();

    Int32 A::* b = new Int32(1);

    return 0;
 
}
