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


		constexpr static const Void Init_AddSequence(ZConstArray* _array, const Int32& number) {
			for (Int32 i = 0; i < _array->getSize(); i++) {
				(*_array)(i) = number;
			}
		}



	public:

		/*
			构造函数
			参数：
				_InitialFunc&& _initialFunc ZConstArray类空间下的静态函数，Init开头
				_Args&&... _args 函数对应的参数，不需要填入第一个参数，第一个参数为对象本身
		*/
		template <typename _InitialFunc, typename... _Args>
		constexpr __forceinline ZConstArray(_InitialFunc&& _initialFunc, _Args&&... _args);


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
			_InitialFunc&& _initialFunc ZConstArray类空间下的静态函数，Init开头
			_Args&&... _args 函数对应的参数，不需要填入第一个参数，第一个参数为对象本身
	*/
	template<typename _ElementType, Int32 _size>
	template <typename _InitialFunc, typename... _Args>
	constexpr __forceinline ZConstArray<_ElementType, _size>::ZConstArray(_InitialFunc&& _initialFunc, _Args&&... _args) {
		_initialFunc(this, std::forward<_Args...>(_args...));
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
