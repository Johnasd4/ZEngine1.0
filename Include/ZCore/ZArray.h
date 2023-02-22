#ifndef ZArray_h
#define ZArray_h

#pragma warning(disable : 6387)
#pragma warning(disable : 26495)


#include"ZCoreDependence.h"


namespace ZEngine {



#pragma region ZConstArray

	/*
		常量数组，用于编译期计算
	*/
	template<typename _ElementType, Int32 _size>
	class ZConstArray {



	public:

		/*
			构造函数
			参数：
				const _ElementType& _initialValue 初始化值
		*/
		constexpr __forceinline ZConstArray(const _ElementType& _initialValue) noexcept;

		/*
			构造函数
			参数：
				const Void(*initialFunction)(_ElementType& _element, const Int32& _index) 通项公式函数
				参数：
					_ElementType& _element 数组元素引用
					const Int32& _index 元素的下标
		*/
		constexpr __forceinline ZConstArray(const Void(*initialFunction)(_ElementType& _element, const Int32& _index)) noexcept;


		/*
			构造函数
			参数：
				const Void(*initialFunction)(_ElementType& _element, const Int32& _index) 通项公式函数
				参数：
					_ElementType& _element 数组元素引用
					const Int32& _index 元素的下标
		*/
		constexpr __forceinline ZConstArray(const Void initialFunction(ZConstArray& _array)) noexcept;


		/*
			析构函数
		*/
		constexpr __forceinline ~ZConstArray() noexcept;

		/*
			重载()
			参数：
				const Int32& _elementIndex 元素下标
			返回：
				ElementType& 下标对应的元素的引用
		*/
		constexpr __forceinline _ElementType& operator()(const Int32& _elementIndex) noexcept;

		/*
			重载()
			参数：
				const Int32& _elementIndex 元素下标
			返回：
				ElementType& 下标对应的元素的引用
		*/
		constexpr __forceinline const _ElementType& operator()(const Int32& _elementIndex) const noexcept;

		/*
			重载()
			参数：
				const Int32&& _elementIndex 元素下标
			返回：
				ElementType& 下标对应的元素的引用
		*/
		constexpr __forceinline _ElementType& operator()(const Int32&& _elementIndex) noexcept;

		/*
			重载()
			参数：
				const Int32&& _elementIndex 元素下标
			返回：
				ElementType& 下标对应的元素的引用
		*/
		constexpr __forceinline const _ElementType& operator()(const Int32&& _elementIndex) const noexcept;


		/*
			获取数组的大小
			返回：
				const Int32 数组大小
		*/
		constexpr __forceinline const Int32 getSize() const noexcept;


	private:

		//数组存储数组指针 
		_ElementType array[_size];

		//数组的大小
		const Int32 size = _size;


	};

	/*
		构造函数
		参数：
			const _ElementType& _initialValue 初始化值
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline ZConstArray<_ElementType, _size>::ZConstArray(const _ElementType& _initialValue) noexcept
	{
		for (Int32 index = 0; index < _size; index++) {
			(*this)(index) = _initialValue;
		}
	}


	/*
		构造函数
		参数：
			const _ElementType& _initialValue 初始化值
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline ZConstArray<_ElementType, _size>::ZConstArray(const Void(*initialFunction)(_ElementType& _element, const Int32& _index)) noexcept {
		for (Int32 index = 0; index < _size; index++) {
			(*initialFunction)((*this)(index), index);
		}
	}

	/*
		构造函数
		参数：
			const Void(*initialFunction)(_ElementType& _element, const Int32& _index) 通项公式函数
			参数：
				_ElementType& _element 数组元素引用
				const Int32& _index 元素的下标
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline ZConstArray<_ElementType, _size>::ZConstArray(const Void initialFunction(ZConstArray& _array)) noexcept {
		initialFunction(*this);
	}



	/*
		析构函数
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline ZConstArray<_ElementType, _size>::~ZConstArray() noexcept {}

	/*
		重载()
		参数：
			const Int32& _elementIndex 元素下标
		返回：
			_ElementType& 下标对应的元素的引用
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32& _elementIndex) noexcept {
		return this->array[_elementIndex];
	}

	/*
		重载()
		参数：
			const Int32& _elementIndex 元素下标
		返回：
			_ElementType& 下标对应的元素的引用
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline const _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32& _elementIndex) const noexcept {
		return this->array[_elementIndex];
	}

	/*
		重载()
		参数：
			const Int32&& _elementIndex 元素下标
		返回：
			_ElementType& 下标对应的元素的引用
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32&& _elementIndex) noexcept {
		return this->array[_elementIndex];
	}

	/*
		重载()
		参数：
			const Int32&& _elementIndex 元素下标
		返回：
			_ElementType& 下标对应的元素的引用
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline const _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32&& _elementIndex) const noexcept {
		return this->array[_elementIndex];
	}


	/*
		获取数组的大小
		返回：
			const Int32 数组大小
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline const Int32 ZConstArray<_ElementType, _size>::getSize() const noexcept {
		return this->size;
	}

#pragma endregion ZConstArray



}


#endif // !ZArray_h
