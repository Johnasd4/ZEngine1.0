#ifndef ZSequence_h
#define ZSequence_h

#pragma warning(disable : 6387)
#pragma warning(disable : 26495)


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
			������
				const _ElementType& _firstItem ����
				const Void(*_formulas)(_ElementType& _currentItem,const _ElementType& _previousItem) ͨ�ʽ

		*
		constexpr ZConstSequence(
			const _ElementType _firstItem, 
			const Void(*_formulas)(_ElementType& _currentItem, const _ElementType& _previousItem)
		) noexcept;

		*/

		constexpr ZConstSequence(
			const _ElementType _firstItem
			//const Void(*_formulas)(_ElementType& _currentItem, const _ElementType& _previousItem)
		) noexcept {
			//(*this)(0) = _firstItem;
			for (Int32 index = 0; index < _size; index++) {
				(*this)(index) = index;
			}
		}

		/*
			��������
		*/
		constexpr __forceinline ~ZConstSequence() noexcept;

	};

	/*
		���캯��
		������
			const _ElementType& _firstItem ����
			constexpr const Void(*_formulas)(_ElementType& _currentItem,const _ElementType& _previousItem) ͨ�ʽ

	*
	template<typename _ElementType, Int32 _size>
	constexpr ZConstSequence<_ElementType, _size>::ZConstSequence(
		const _ElementType _firstItem, 
		const Void(*_formulas)(_ElementType& _currentItem, const _ElementType& _previousItem)
	) noexcept:
		ZConstArray<_ElementType, _size>()
	{
		(*this)(0) = _firstItem;
		for (Int32 index = 1, index < _size; index++) {
			(*this)(index) = (*this)(index - 1);
		}
	}
	*/

	/*
		��������
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline ZConstSequence<_ElementType, _size>::~ZConstSequence() noexcept {}





#pragma endregion ZConstSequence



}


#endif // !ZSequence_h
