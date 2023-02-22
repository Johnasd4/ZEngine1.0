#ifndef ZSequence_h
#define ZSequence_h





#include"ZCoreDependence.h"
#include"ZArray.h"

namespace ZEngine {



#pragma region ZConstSequence

	/*
		常量数组，用于编译期计算
	*/
	template<typename _ElementType, Int32 _size>
	class ZConstSequence : public ZConstArray<_ElementType, _size> {



	public:

		/*
			构造函数
		*/
		constexpr __forceinline ZConstSequence() noexcept;



		/*
			析构函数
		*/
		constexpr __forceinline ~ZConstSequence() noexcept;

	};


#pragma endregion ZConstSequence



}


#endif // !ZSequence_h
