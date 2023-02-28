#ifndef ZArray_h
#define ZArray_h

#include"ZContainer.h"

namespace ZEngine {

	/*
		动态数组，顺序存储
	*/
	template<typename _ElementType>
	class ZArray :protected ZContainer {

	public:



	public:

		/*
			构造函数，仅初始化成员，数组为空
			说明：
				默认数组增长形式为倍增
				默认增长参数大小为1.2
				默认不调用元素的构造函数

		*/
		ZArray();

		/*
			构造函数，创造指定大小的数组
			说明：
				默认数组增长形式为倍增
				默认增长参数大小为1.2
				默认不调用元素的构造函数
			参数：
				const Int32& _arraySize 数组大小

		*/
		ZArray(const Int32& _arraySize);



		/*
			构造函数，创造指定大小的数组
			说明：
				默认数组增长形式为倍增
				默认增长参数大小为1.2
			参数：
				const Int32& _arraySize 数组大小
				const Boolean& _ifInitialElement 是否调用元素的构造函数
		*/
		ZArray(const Int32& _arraySize, const Boolean& _ifInitialElement);



		/*
			构造函数
			参数：
				const Array& _array 被复制的数组
		*/
		ZArray(const ZArray& _array);


		/*
			析构函数
		*/
		~ZArray();

		/*
			创建数组，修改arraySize
			参数：
				const Int32& _arraySize 数组大小
			返回：
				const Boolean 是否成功
		*/
		__forceinline const Boolean create(const Int32& _arraySize);

		/*
			创建数组，修改arraySize
			参数：
				const Int32& _arraySize 数组大小
				const Boolean& _ifInitialElement 是否调用元素的构造函数，不会修改对象本身的设置
			返回：
				const Boolean 是否成功
		*/
		__forceinline const Boolean create(const Int32& _arraySize, const Boolean& _ifInitialElement);


		/*
			拓展数组，修改arraySize
			参数：
				const Int32& _extendArraySize 拓展后的数组大小
			返回：
				const Boolean 是否成功
		*/
		__forceinline const Boolean extend(const Int32& _extendArraySize);


		/*
			拓展数组，修改arraySize
			参数：
				const Int32& _extendArraySize 拓展后的数组大小
				const Boolean& _ifInitialElement 是否调用元素的构造函数，不会修改对象本身的设置
			返回：
				const Boolean 是否成功
		*/
		__forceinline const Boolean extend(const Int32& _extendArraySize, const Boolean& _ifInitialElement);



		/*
			删除数组
		*/
		__forceinline const Void destroy();


		/*
			重载()
			参数：
				const Int32& _elementIndex 元素下标
			返回：
				_ElementType& 下标对应的元素的引用
		*/
		__forceinline _ElementType& operator()(const Int32& _elementIndex);

		/*
			重载()
			参数：
				const Int32& _elementIndex 元素下标
			返回：
				const _ElementType& 下标对应的元素的引用
		*/
		__forceinline const _ElementType& operator()(const Int32& _elementIndex) const;


		/*
			获取字符
			参数：
				const Int32& _elementIndex 元素下标
			返回：
				_ElementType& 下标对应的元素的引用
		*/
		__forceinline _ElementType& at(const Int32& _elementIndex);


		/*
			获取字符
			参数：
				const Int32& _elementIndex 元素下标
			返回：
				_ElementType& 下标对应的元素的引用
		*/
		__forceinline const _ElementType& at(const Int32& _elementIndex) const;

		/*
			重载=
			参数：
				const Array& _array 数组
			返回：
				const Boolean 是否成功
		*/
		const Boolean operator=(const ZArray& _array);


		/*
			获取数组元素数量
			返回：
				const Int32& 元素数量
		*/
		__forceinline const Int32& getLength() const;

		/*
			设置数组元素数量
			参数：
				const Int32& _arrayLength 元素数量
		*/
		__forceinline const Void setLength(const Int32& _arrayLength);


		/*
			获取数组的大小
			返回：
				const Int32& 数组大小
		*/
		__forceinline const Int32& getSize() const;




		/*
			是否存在
			返回：
				const Boolean 是否存在
		*/
		__forceinline const Boolean ifExsit() const;

		/*
			添加元素到最后，逻辑使用memcpy进行复制整个元素
			参数：
				const _ElementType& _element 需要添加的元素
			返回：
				const Boolean 是否成功
		*/
		const Boolean add(const _ElementType& _element);


		/*
			添加空的元素
			参数：
				const Int32& _emptyElementNum 添加的元素数量
			返回：
				const Boolean 是否成功
		*/
		__forceinline const Boolean addEmpty(const Int32& _emptyElementNum);



		/*
			插入元素到指定位置，将其余元素依次后移
			非常费时，无特别需要慎用
			参数：
				const _ElementType& _element 需要插入的元素
				const Int32& _elementIndex 插入的下标
			返回：
				const Boolean 是否成功
		*/
		const Boolean insert(const _ElementType& _element, const Int32& _elementIndex);

		/*
			删除指定位置的元素，将后置元素前移
			非常费时，无特别需要慎用
			参数：
				const Int32& _elementIndex 删除的下标
			返回：
				const Boolean 是否成功
		*/
		const Boolean remove(const Int32& _elementIndex);


		/*
			清空数组
		*/
		__forceinline const Void clear();



	private:


		/*
			用该函数在类内调整数组长度
			参数：
				const Int32& _changeLength 长度变化的大小
			返回：
				const Boolean 是否成功
		*/
		const Boolean changeLength(const Int32& _changeLength);

		/*
			数组根据设定好的参数自增，直到能容下当前的数组大小
			返回：
				const Boolean 是否成功
		*/
		const Boolean autoExtend();


	private:

		//数组存储数组指针 
		_ElementType* array;
		//数组的元素数量
		Int32 length;
		//数组的大小
		Int32 Size;




	};


}


#endif // !ZArray_h
