#ifndef ZFixedArray_h
#define ZFixedArray_h

#pragma warning(disable : 26495)


#include"ZBasicDrive.h"



namespace ZEngine 
{

	/*
		静态数组，顺序存储，存储在栈区
		注意，过大数组请使用ZArray将数组存储在堆区
		不适合用于存储需要申请内存的类型
	*/
	template<typename _ElementType, Int32 _size>
	class ZFixedArray 
	{

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
				const Int32 _index 元素下标
			返回：
				ElementType& 下标对应的元素的引用
		*/
		__forceinline _ElementType& operator()(const Int32 _index);

		/*
			重载()
			参数：
				const Int32 _index 元素下标
			返回：
				const _ElementType& 下标对应的元素的引用
		*/
		__forceinline const _ElementType& operator()(const Int32 _index) const;

		/*
			获取数组的大小
			返回：
				const Int32 数组大小
		*/
		consteval static const Int32 getSize();



	private:

		//数组存储数组指针 
		_ElementType array[_size];

	};

	/*
		构造函数
	*/
	template<typename _ElementType, Int32 _size>
	__forceinline ZFixedArray<_ElementType, _size>::ZFixedArray() {}


	/*
		析构函数
	*/
	template<typename _ElementType, Int32 _size>
	__forceinline ZFixedArray<_ElementType, _size>::~ZFixedArray() {}


	/*
		重载()
		参数：
			const Int32 _index 元素下标
		返回：
			_ElementType& 下标对应的元素的引用
	*/
	template<typename _ElementType, Int32 _size>
	__forceinline _ElementType& ZFixedArray<_ElementType, _size>::operator()(const Int32 _index) 
	{
		return this->array[_index];
	}

	/*
		重载()
		参数：
			const Int32 _index 元素下标
		返回：
			const _ElementType& 下标对应的元素的引用
	*/
	template<typename _ElementType, Int32 _size>
	__forceinline const _ElementType& ZFixedArray<_ElementType, _size>::operator()(const Int32 _index) const 
	{
		return this->array[_index];
	}

	/*
		获取数组的大小
		返回：
			const Int32 数组大小
	*/
	template<typename _ElementType, Int32 _size>
	consteval static const Int32 ZFixedArray<_ElementType, _size>::getSize()
	{
		return _size;
	}

}


#endif // !ZFixedArray_h
