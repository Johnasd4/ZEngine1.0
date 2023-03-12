#ifndef ZConstArray_h
#define ZConstArray_h


#include"Private/ZBasicDrive.h"




namespace ZEngine {


	/*
		常量数组，用于编译期计算
	*/
	template<typename _ElementType, Int32 _size>
	class ZConstArray 
	{

	public:


		/*
			初始化函数
			初始化方式为填充相同的元素
			参数：
				const _ElementType& _element 填充的元素
		*/
		constexpr static const Void Init_FillSameElement(ZConstArray* _arrayPtr, const _ElementType& _element);



		/*
			初始化函数
			初始化方式为等差数列
			参数：
				const _ElementType& _firstElement 首项的值
				const _FactorType& _factor 系数
		*/
		template<typename _FactorType>
		constexpr static const Void Init_ArithmeticSequence(ZConstArray* _arrayPtr, const _ElementType& _firstElement, const _FactorType& _factor);

		/*
			初始化函数
			初始化方式为等比数列
			参数：
				const _ElementType& _firstElement 首项的值
				const _FactorType& _factor 系数
		*/
		template<typename _FactorType>
		constexpr static const Void Init_GeometricSequence(ZConstArray* _arrayPtr, const _ElementType& _firstElement, const _FactorType& _factor);


		/*
			初始化函数
			初始化方式为多项式，其中代入值为数组的下标，系数顺序从高次项到低次项
			参数：
				const _FirstFactor& _firstFactor 最高次项系数
				const _OtherFactors&... _otherFactors 其余项系数
		*/
		template<typename _FirstFactor, typename... _OtherFactors>
		constexpr static const Void Init_Polynomial(ZConstArray* _arrayPtr, const _FirstFactor& _firstFactor, const _OtherFactors&... _otherFactors);

		/*
			初始化函数
			初始化方式为数列对位相加
			参数：
				const _FirstSequence& _firstSequence 第一个数列
				const _OtherSequences&... _otherSequences 其余数列
		*/
		template<typename _FirstSequence, typename... _OtherSequences>
		constexpr static const Void Init_AddSequence(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence, const _OtherSequences&... _otherSequences);


		/*
			初始化函数
			初始化方式为数列对位相除（第一个数列除以其余数列）
			参数：
				const _FirstSequence& _firstSequence 第一个数列
				const _OtherSequences&... _otherSequences 其余数列
		*/
		template<typename _FirstSequence, typename... _OtherSequences>
		constexpr static const Void Init_DevideSequence(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence, const _OtherSequences&... _otherSequences);


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
		consteval ZConstArray(_InitFunc&& _initFunc, _Args&&... _args);

		/*
			复制函数
			参数：
				const ZConstArray& _array 倍复制的数组
		*/
		consteval ZConstArray(const ZConstArray& _array);


		/*
			数组初始化
			参数：
				_InitFunc&& _initFunc ZConstArray类空间下的静态函数，Init开头
				_Args&&... _args 函数对应的参数，不需要填入第一个参数，第一个参数为对象本身
		*/
		template<typename _InitFunc, typename... _Args>
		consteval const Void init(_InitFunc&& _initFunc, _Args&&... _args);


		/*
			重载()
			参数：
				const Int32 _index 元素下标
			返回：
				ElementType& 下标对应的元素的引用
		*/
		constexpr _ElementType& operator()(const Int32 _index);

		/*
			重载()
			参数：
				const Int32 _index 元素下标
			返回：
				ElementType& 下标对应的元素的引用
		*/
		constexpr const _ElementType& operator()(const Int32 _index) const;



		/*
			获取数组的大小
			返回：
				const Int32 数组大小
		*/
		consteval static const Int32 getSize();

		/*
			交换数组中两个元素的位置
			返回：
				const Int32 _index1 元素1的下标
				const Int32 _index2 元素2的下标
		*/
		constexpr const Void swap(const Int32 _index1, const Int32 _index2);


	private:

		/*
			初始化函数
			初始化方式为多项式，其中代入值为数组的下标，系数顺序从高次项到低次项
			参数：
				const _FirstFactor& _firstFactor 最高次项系数
				const _OtherFactors&... _otherFactors 其余项系数
		*/
		template<typename _FirstFactor, typename... _OtherFactors>
		constexpr static const Void Init_PolynomialRecurse(ZConstArray* _arrayPtr, const _FirstFactor& _firstFactor, const _OtherFactors&... _otherFactors);




		/*
			初始化函数
			初始化方式为多项式，其中代入值为数组的下标，系数顺序从高次项到低次项
			参数：
				const _FirstFactor& _firstFactor 最高次项系数
		*/
		template<typename _FirstFactor>
		constexpr static const Void Init_PolynomialRecurse(ZConstArray* _arrayPtr, const _FirstFactor& _firstFactor);

		/*
			初始化函数
			初始化方式为数列对位相加
			参数：
				const _FirstSequence& _firstSequence 第一个数列
				const _OtherSequences&... _otherSequences 其余数列
		*/
		template<typename _FirstSequence, typename... _OtherSequences>
		constexpr static const Void Init_AddSequenceRecurse(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence, const _OtherSequences&... _otherSequences);

		/*
			初始化函数
			初始化方式为数列对位相加
			参数：
				const _FirstSequence& _firstSequence 第一个数列
		*/
		template<typename _FirstSequence>
		constexpr static const Void Init_AddSequenceRecurse(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence);

		/*
			初始化函数
			初始化方式为数列对位相除（第一个数列除以其余数列）
			参数：
				const _FirstSequence& _firstSequence 第一个数列
				const _OtherSequences&... _otherSequences 其余数列
		*/
		template<typename _FirstSequence, typename... _OtherSequences>
		constexpr static const Void Init_DevideSequenceRecurse(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence, const _OtherSequences&... _otherSequences);

		/*
			初始化函数
			初始化方式为数列对位相除（第一个数列除以其余数列）
			参数：
				const _FirstSequence& _firstSequence 第一个数列
				const _OtherSequences&... _otherSequences 其余数列
		*/
		template<typename _FirstSequence>
		constexpr static const Void Init_DevideSequenceRecurse(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence);




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
	constexpr const Void ZConstArray<_ElementType, _size>::Init_FillSameElement(ZConstArray* _arrayPtr, const _ElementType& _element)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) = _element;
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
	constexpr const Void ZConstArray<_ElementType, _size>::Init_ArithmeticSequence(ZConstArray* _arrayPtr, const _ElementType& _firstElement, const _FactorType& _factor)
	{
		(*_arrayPtr)(0) = _firstElement;
		for (Int32 index = 1; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) = (*_arrayPtr)(index - 1) + _factor;
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
	constexpr const Void ZConstArray<_ElementType, _size>::Init_GeometricSequence(ZConstArray* _arrayPtr, const _ElementType& _firstElement, const _FactorType& _factor)
	{
		(*_arrayPtr)(0) = _firstElement;
		for (Int32 index = 1; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) = (*_arrayPtr)(index - 1) * _factor;
		}
	}

	/*
		初始化函数
		初始化方式为多项式，其中代入值为数组的下标，系数顺序从高次项到低次项
		参数：
			const _FirstFactor& _firstFactor 最高次项系数
			const _OtherFactors&... _otherFactors 其余项系数
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FirstFactor, typename... _OtherFactors>
	constexpr const Void ZConstArray<_ElementType, _size>::Init_Polynomial(ZConstArray* _arrayPtr, const _FirstFactor& _firstFactor, const _OtherFactors&... _otherFactors)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) = _firstFactor;
		}
		Init_PolynomialRecurse<_OtherFactors...>(_arrayPtr, _otherFactors...);
	}

	/*
		初始化函数
		初始化方式为多项式，其中代入值为数组的下标，系数顺序从高次项到低次项
		参数：
			const _FirstFactor& _firstFactor 最高次项系数
			const _OtherFactors&... _otherFactors 其余项系数
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FirstFactor, typename... _OtherFactors>
	constexpr const Void ZConstArray<_ElementType, _size>::Init_PolynomialRecurse(ZConstArray* _arrayPtr, const _FirstFactor& _firstFactor, const _OtherFactors&... _otherFactors)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) *= index;
			(*_arrayPtr)(index) += _firstFactor;
		}
		Init_PolynomialRecurse<_OtherFactors...>(_arrayPtr, _otherFactors...);

	}




	/*
		初始化函数
		初始化方式为多项式，其中代入值为数组的下标，系数顺序从高次项到低次项
		参数：
			const _FirstFactor& _firstFactor 最高次项系数
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FirstFactor>
	constexpr const Void ZConstArray<_ElementType, _size>::Init_PolynomialRecurse(ZConstArray* _arrayPtr, const _FirstFactor& _firstFactor)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) *= index;
			(*_arrayPtr)(index) += _firstFactor;
		}
	}

	/*
		初始化函数
		初始化方式为数列对位相加
		参数：
			const _FirstSequence& _firstSequence 第一个数列
			const _OtherSequences&... _otherSequences 其余数列
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FirstSequence, typename... _OtherSequences>
	constexpr const Void ZConstArray<_ElementType, _size>::Init_AddSequence(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence, const _OtherSequences&... _otherSequences)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) = _firstSequence(index);
		}
		Init_AddSequenceRecurse<_OtherSequences...>(_arrayPtr, _otherSequences...);
	}

	/*
		初始化函数
		初始化方式为数列对位相加
		参数：
			const _FirstSequence& _firstSequence 第一个数列
			const _OtherSequences&... _otherSequences 其余数列
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FirstSequence, typename... _OtherSequences>
	constexpr const Void ZConstArray<_ElementType, _size>::Init_AddSequenceRecurse(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence, const _OtherSequences&... _otherSequences)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) += _firstSequence(index);
		}
		Init_AddSequenceRecurse<_OtherSequences...>(_arrayPtr, _otherSequences...);
	}

	/*
		初始化函数
		初始化方式为数列对位相加
		参数：
			const _FirstSequence& _firstSequence 第一个数列
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FirstSequence>
	constexpr const Void ZConstArray<_ElementType, _size>::Init_AddSequenceRecurse(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) += _firstSequence(index);
		}
	}

	/*
		初始化函数
		初始化方式为数列对位相除（第一个数列除以其余数列）
		参数：
			const _FirstSequence& _firstSequence 第一个数列
			const _OtherSequences&... _otherSequences 其余数列
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FirstSequence, typename... _OtherSequences>
	constexpr const Void ZConstArray<_ElementType, _size>::Init_DevideSequence(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence, const _OtherSequences&... _otherSequences)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) = _firstSequence(index);
		}
		Init_DevideSequenceRecurse<_OtherSequences...>(_arrayPtr, _otherSequences...);
	}

	/*
		初始化函数
		初始化方式为数列对位相除（第一个数列除以其余数列）
		参数：
			const _FirstSequence& _firstSequence 第一个数列
			const _OtherSequences&... _otherSequences 其余数列
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FirstSequence, typename... _OtherSequences>
	constexpr const Void ZConstArray<_ElementType, _size>::Init_DevideSequenceRecurse(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence, const _OtherSequences&... _otherSequences)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) /= _firstSequence(index);
		}
		Init_DevideSequenceRecurse<_OtherSequences...>(_arrayPtr, _otherSequences...);
	}

	/*
		初始化函数
		初始化方式为数列对位相除（第一个数列除以其余数列）
		参数：
			const _FirstSequence& _firstSequence 第一个数列
			const _OtherSequences&... _otherSequences 其余数列
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FirstSequence>
	constexpr const Void ZConstArray<_ElementType, _size>::Init_DevideSequenceRecurse(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) /= _firstSequence(index);
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
	consteval ZConstArray<_ElementType, _size>::ZConstArray(_InitFunc&& _initFunc, _Args&&... _args)
	{
		this->init(std::forward<_InitFunc>(_initFunc), std::forward<_Args>(_args)...);
	}

	/*
		复制函数
		参数：
			const ZConstArray& _array 倍复制的数组
	*/
	template<typename _ElementType, Int32 _size>
	consteval ZConstArray<_ElementType, _size>::ZConstArray(const ZConstArray& _array)
	{
		for (Int32 index = 0; index < _size; index++) 
		{
			(*this)(index) = _array(index);
		}
	}


	/*
		数组初始化
		参数：
			_InitFunc&& _initFunc ZConstArray类空间下的静态函数，Init开头
			_Args&&... _args 函数对应的参数，不需要填入第一个参数，第一个参数为对象本身
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _InitFunc, typename... _Args>
	consteval const Void ZConstArray<_ElementType, _size>::init(_InitFunc&& _initFunc, _Args&&... _args)
	{
		_initFunc(this, std::forward<_Args>(_args)...);
	}


	/*
		重载()
		参数：
			const Int32 _index 元素下标
		返回：
			_ElementType& 下标对应的元素的引用
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32 _index) 
	{
		return this->array[_index];
	}

	/*
		重载()
		参数：
			const Int32 _index 元素下标
		返回：
			_ElementType& 下标对应的元素的引用
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline const _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32 _index) const 
	{
		return this->array[_index];
	}


	/*
		获取数组的大小
		返回：
			const Int32 数组大小
	*/
	template<typename _ElementType, Int32 _size>
	consteval const Int32 ZConstArray<_ElementType, _size>::getSize()
	{
		return _size;
	}


	/*
		交换数组中两个元素的位置
		返回：
			const Int32 _index1 元素1的下标
			const Int32 _index2 元素2的下标
	*/
	template<typename _ElementType, Int32 _size>
	constexpr const Void ZConstArray<_ElementType, _size>::swap(const Int32 _index1, const Int32 _index2)
	{
		_ElementType tempElement = (*this)(_index1);
		(*this)(_index1) = (*this)(_index2);
		(*this)(_index2) = tempElement;
	}




}


#endif // !ZConstArray_h
