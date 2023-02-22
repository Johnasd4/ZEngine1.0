#ifndef ZSequence_h
#define ZSequence_h





#include"ZCoreDependence.h"
#include"ZArray.h"

namespace ZEngine {



#pragma region ZConstSequence

	/*
		�������飬���ڱ����ڼ���
	*/
	template<typename _ElementType, Int32 _size>
	class ZConstSequence : public ZConstArray<_ElementType, _size> {



	public:

		/*
			���캯��
		*/
		constexpr __forceinline ZConstSequence() noexcept;



		/*
			��������
		*/
		constexpr __forceinline ~ZConstSequence() noexcept;

	};


#pragma endregion ZConstSequence



}


#endif // !ZSequence_h
