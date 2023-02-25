#ifndef ZArray_h
#define ZArray_h



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
			初始化函数
			初始化方式为填充相同的元素
			参数：
				const _ElementType& _element 填充的元素
		*/
		constexpr static const Void Init_FillSameElement(ZConstArray* _array, const _ElementType& _element) noexcept;



		/*
			初始化函数
			初始化方式为等差数列
			参数：
				const _ElementType& _firstElement 首项的值
				const _FactorType& _factor 系数
		*/
		template<typename _FactorType>
		constexpr static const Void Init_ArithmeticSequence(ZConstArray* _array, const _ElementType& _firstElement, const _FactorType& _factor) noexcept;

		/*
			初始化函数
			初始化方式为等比数列
			参数：
				const _ElementType& _firstElement 首项的值
				const _FactorType& _factor 系数
		*/
		template<typename _FactorType>
		constexpr static const Void Init_GeometricSequence(ZConstArray* _array, const _ElementType& _firstElement, const _FactorType& _factor) noexcept;


	public:

		/*
			构造函数
			参数：
				_InitFunc&& _initFunc ZConstArray类空间下的静态函数，Init开头
				_Args&&... _args 函数对应的参数，不需要填入第一个参数，第一个参数为对象本身
			注：
				如果需要自定义初始化函数，函数的第一个参数必须是【ZConstArray*】，后续为公式所需参数
		*/
		template<typename _InitFunc, typename... _Args>
		constexpr __forceinline ZConstArray(_InitFunc&& _initFunc, _Args&&... _args) noexcept;


		/*
			析构函数
		*/
		constexpr __forceinline ~ZConstArray() noexcept;

		/*
			数组初始化
			参数：
				_InitFunc&& _initFunc ZConstArray类空间下的静态函数，Init开头
				_Args&&... _args 函数对应的参数，不需要填入第一个参数，第一个参数为对象本身
		*/
		template<typename _InitFunc, typename... _Args>
		constexpr __forceinline const Void init(_InitFunc&& _initFunc, _Args&&... _args) noexcept;


		/*
			重载()
			参数：
				const Int32& _index 元素下标
			返回：
				ElementType& 下标对应的元素的引用
		*/
		constexpr __forceinline _ElementType& operator()(const Int32& _index) noexcept;

		/*
			重载()
			参数：
				const Int32& _index 元素下标
			返回：
				ElementType& 下标对应的元素的引用
		*/
		constexpr __forceinline const _ElementType& operator()(const Int32& _index) const noexcept;

		/*
			重载()
			参数：
				const Int32&& _index 元素下标
			返回：
				ElementType& 下标对应的元素的引用
		*/
		constexpr __forceinline _ElementType& operator()(const Int32&& _index) noexcept;

		/*
			重载()
			参数：
				const Int32&& _index 元素下标
			返回：
				ElementType& 下标对应的元素的引用
		*/
		constexpr __forceinline const _ElementType& operator()(const Int32&& _index) const noexcept;


		/*
			获取数组的大小
			返回：
				const Int32 数组大小
		*/
		constexpr static __forceinline const Int32 getSize() noexcept;

		/*
			交换数组中两个元素的位置
			返回：
				const Int32& _index1 元素1的下标
				const Int32& _index2 元素2的下标
		*/
		constexpr __forceinline const Void swap(const Int32& _index1, const Int32& _index2) noexcept;




	private:

		//数组存储数组指针 
		_ElementType array[_size];


	};


	/*
		初始化函数
		初始化方式为填充相同的元素
		参数：
			const _ElementType& _element 填充的元素
	*/
	template<typename _ElementType, Int32 _size>
	constexpr static const Void ZConstArray<_ElementType, _size>::Init_FillSameElement(ZConstArray* _array, const _ElementType& _element) noexcept {
		for (Int32 index = 0; index < _array->getSize(); index++) {
			(*_array)(index) = _element;
		}
	}


	/*
		初始化函数
		初始化方式为等差数列
		参数：
			const _ElementType& _firstElement 首项的值
			const _FactorType& _factor 系数
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FactorType>
	constexpr static const Void ZConstArray<_ElementType, _size>::Init_ArithmeticSequence(ZConstArray* _array, const _ElementType& _firstElement, const _FactorType& _factor) noexcept {
		(*_array)(0) = _firstElement;
		for (Int32 index = 1; index < _array->getSize(); index++) {
			(*_array)(index) = (*_array)(index - 1) + _factor;
		}
	}

	/*
		初始化函数
		初始化方式为等比数列
		参数：
			const _ElementType& _firstElement 首项的值
			const _FactorType& _factor 系数
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FactorType>
	constexpr static const Void ZConstArray<_ElementType, _size>::Init_GeometricSequence(ZConstArray* _array, const _ElementType& _firstElement, const _FactorType& _factor) noexcept {
		(*_array)(0) = _firstElement;
		for (Int32 index = 1; index < _array->getSize(); index++) {
			(*_array)(index) = (*_array)(index - 1) * _factor;
		}
	}


	/*
		初始化函数
		初始化方式为填充相同的元素
		参数：
			const _ElementType& _element 填充的元素
	*/
	template<typename _ElementType, Int32 _size>
	constexpr static const Void ZConstArray<_ElementType, _size>::Init_FillSameElement(ZConstArray* _array, const _ElementType& _element) noexcept {
		for (Int32 index = 0; index < _array->getSize(); index++) {
			(*_array)(index) = _element;
		}
	}


	/*
		初始化函数
		初始化方式为等差数列
		参数：
			const _ElementType& _firstElement 首项的值
			const _FactorType& _factor 差值
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FactorType>
	constexpr static const Void ZConstArray<_ElementType, _size>::Init_ArithmeticSequence(ZConstArray* _array, const _ElementType& _firstElement, const _FactorType& _factor) noexcept {
		(*_array)(0) = _firstElement;
		for (Int32 index = 1; index < _array->getSize(); index++) {
			(*_array)(index) = (*_array)(index - 1) + _factor;
		}
	}
	
	/*
		初始化函数
		初始化方式为等比数列
		参数：
			const _ElementType& _firstElement 首项的值
			const _FactorType& _factor 差值
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FactorType>
	constexpr static const Void ZConstArray<_ElementType, _size>::Init_GeometricSequence(ZConstArray* _array, const _ElementType& _firstElement, const _FactorType& _factor) noexcept {
		(*_array)(0) = _firstElement;
		for (Int32 index = 1; index < _array->getSize(); index++) {
			(*_array)(index) = (*_array)(index - 1) * _factor;
		}
	}


	/*
		构造函数
		参数：
			_InitFunc&& _initFunc ZConstArray类空间下的静态函数，Init开头
			_Args&&... _args 函数对应的参数，不需要填入第一个参数，第一个参数为对象本身
			注：
				如果需要自定义初始化函数，函数的第一个参数必须是【ZConstArray*】，后续为公式所需参数
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _InitFunc, typename... _Args>
	constexpr __forceinline ZConstArray<_ElementType, _size>::ZConstArray(_InitFunc&& _initFunc, _Args&&... _args) noexcept {
		this->init(std::forward<_InitFunc>(_initFunc), std::forward<_Args>(_args)...);
	}

	/*
		析构函数
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline ZConstArray<_ElementType, _size>::~ZConstArray() noexcept {}

	/*
		数组初始化
		参数：
			_InitFunc&& _initFunc ZConstArray类空间下的静态函数，Init开头
			_Args&&... _args 函数对应的参数，不需要填入第一个参数，第一个参数为对象本身
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _InitFunc, typename... _Args>
	constexpr __forceinline const Void ZConstArray<_ElementType, _size>::init(_InitFunc&& _initFunc, _Args&&... _args) noexcept {
		_initFunc(this, std::forward<_Args>(_args)...);
	}


	/*
		重载()
		参数：
			const Int32& _index 元素下标
		返回：
			_ElementType& 下标对应的元素的引用
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32& _index) noexcept {
		return this->array[_index];
	}

	/*
		重载()
		参数：
			const Int32& _index 元素下标
		返回：
			_ElementType& 下标对应的元素的引用
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline const _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32& _index) const noexcept {
		return this->array[_index];
	}

	/*
		重载()
		参数：
			const Int32&& _index 元素下标
		返回：
			_ElementType& 下标对应的元素的引用
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32&& _index) noexcept {
		return this->array[_index];
	}

	/*
		重载()
		参数：
			const Int32&& _index 元素下标
		返回：
			_ElementType& 下标对应的元素的引用
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline const _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32&& _index) const noexcept {
		return this->array[_index];
	}



	/*
		获取数组的大小
		返回：
			const Int32 数组大小
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline const Int32 ZConstArray<_ElementType, _size>::getSize() noexcept {
		return _size;
	}


	/*
		交换数组中两个元素的位置
		返回：
			const Int32& _index1 元素1的下标
			const Int32& _index2 元素2的下标
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline const Void ZConstArray<_ElementType, _size>::swap(const Int32& _index1, const Int32& _index2) noexcept {
		_ElementType tempElement = (*this)(_index1);
		(*this)(_index1) = (*this)(_index2);
		(*this)(_index2) = tempElement;
	}



#pragma endregion ZConstArray

#pragma region ZFixedArray


	/*
		静态数组，顺序存储，存储在栈区
		注意，过大数组请使用ZArray将数组存储在堆区
		不适合用于存储需要申请内存的类型
	*/
	template<typename _ElementType, Int32 _size>
	class ZFixedArray {

	public:

		/*
			构造函数
		*/
		__forceinline ZFixedArray();

		/*
			析构函数
		*/
		__forceinline ~ZFixedArray();

		/*
			重载()
			参数：
				const Int32& _index 元素下标
			返回：
				ElementType& 下标对应的元素的引用
		*/
		__forceinline _ElementType& operator()(const Int32& _index);

		/*
			重载()
			参数：
				const Int32& _index 元素下标
			返回：
				const _ElementType& 下标对应的元素的引用
		*/
		__forceinline const _ElementType& operator()(const Int32& _index) const;

		/*
			获取数组的大小
			返回：
				const Int32 数组大小
		*/
		constexpr static __forceinline const Int32 getSize() noexcept;



	private:

		//数组存储数组指针 
		_ElementType array[_size];

	};

	/*
		构造函数
	*/
	template<typename _ElementType, Int32 _size>
	__forceinline ZFixedArray<_ElementType, _size>::ZFixedArray(){}


	/*
		析构函数
	*/
	template<typename _ElementType, Int32 _size>
	__forceinline ZFixedArray<_ElementType, _size>::~ZFixedArray() {}


	/*
		重载()
		参数：
			const Int32& _index 元素下标
		返回：
			_ElementType& 下标对应的元素的引用
	*/
	template<typename _ElementType, Int32 _size>
	__forceinline _ElementType& ZFixedArray<_ElementType, _size>::operator()(const Int32& _index) {
		return this->array[_index];
	}

	/*
		重载()
		参数：
			const Int32& _index 元素下标
		返回：
			const _ElementType& 下标对应的元素的引用
	*/
	template<typename _ElementType, Int32 _size>
	__forceinline const _ElementType& ZFixedArray<_ElementType, _size>::operator()(const Int32& _index) const {
		return this->array[_index];
	}

	/*
		获取数组的大小
		返回：
			const Int32 数组大小
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline const Int32 ZFixedArray<_ElementType, _size>::getSize() noexcept {
		return _size;
	}


#pragma endregion ZFixedArray


}


#endif // !ZArray_h
