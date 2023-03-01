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



int main()
{

    ZMemoryPool::CreateInstance();


    return 0;
 
}
