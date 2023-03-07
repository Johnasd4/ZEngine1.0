#ifndef ZArray_h
#define ZArray_h

#include"ZBasicDrive.h"

#include"ZContainer.h"

namespace ZEngine 
{

	/*
		动态数组，顺序存储
	*/
	template<typename _ObjectType>
	class ZArray :public ZContainer<_ObjectType> 
	{

	public:

		/*
			构造函数
		*/
		ZArray();

		/*
			构造函数，创造指定大小的数组
			参数：
				const Int32 _capacity 数组大小 
		*/
		ZArray(const Int32 _capacity);

		/*
			构造函数
			深度复制
			参数：
				const Array& _array 被复制的数组
		*/
		ZArray(const ZArray& _array);

		/*
			构造函数
			移动语义
			参数：
				const Array&& _array 被移动的数组
		*/
		ZArray(const ZArray&& _array);


		/*
			析构函数
		*/
		~ZArray();

		/*
			重载()
			参数：
				const Int32 _index object下标
			返回：
				_ObjectType& 下标对应的object的引用
		*/
		__forceinline _ObjectType& operator()(const Int32 _index);

		/*
			重载()
			参数：
				const Int32 _index object下标
			返回：
				const _ObjectType& 下标对应的object的引用
		*/
		__forceinline const _ObjectType& operator()(const Int32 _index) const;

		/*
			重载=
			深度复制
			参数：
				const Array& _array 被复制的数组
		*/
		const Void operator=(const ZArray& _array);

		/*
			重载=
			移动语义
			参数：
				const Array&& _array 数组
		*/
		const Void operator=(const ZArray&& _array);


		/*
			添加object到最后，逻辑使用memcpy进行复制整个object
			参数：
				const _ObjectType& _object 需要添加的object
		*/
		const Void push(const _ObjectType& _object);



		/*
			添加空的object
			参数：
				const Int32 _num 添加的object数量
		*/
		const Void pushEmpty(const Int32 _num);


		/*
			设置object数量
			会判断是否需要拓展空间
			参数：
				const Int32 容器object数量
		*/
		const Void setSize(const Int32 _num);

		/*
			插入object到指定位置，将其余object依次后移
			非常费时，无特别需要慎用
			参数：
				const Int32 _index 插入的下标
				const _ObjectType& _object 需要插入的object
			返回：
				const Boolean 是否成功
		*/
		const Boolean insert(const Int32 _index, const _ObjectType& _object);

		/*
			删除指定位置的object，将后置object前移
			非常费时，无特别需要慎用
			参数：
				const Int32 _index 删除的下标
			返回：
				const Boolean 是否成功
		*/
		const Boolean remove(const Int32 _index);

		/*
			清空数组
		*/
		__forceinline const Void clear();


	};

	/*
		构造函数
	*/
	template<typename _ObjectType>
	ZArray<_ObjectType>::ZArray() :
		ZContainer<_ObjectType>()
	{}

	/*
		构造函数，创造指定大小的数组
		参数：
			const Int32 _capacity 数组大小
	*/
	template<typename _ObjectType>
	ZArray<_ObjectType>::ZArray(const Int32 _capacity) :
		ZContainer<_ObjectType>(_capacity)
	{}

	/*
		构造函数
		深度复制
		参数：
			const Array& _array 被复制的数组
	*/
	template<typename _ObjectType>
	ZArray<_ObjectType>::ZArray(const ZArray& _array) :
		ZContainer<_ObjectType>(_array)
	{}

	/*
		构造函数
		移动语义
		参数：
			const Array&& _array 被移动的数组
	*/
	template<typename _ObjectType>
	ZArray<_ObjectType>::ZArray(const ZArray&& _array) :
		ZContainer<_ObjectType>(std::forward<ZArray>(_array))
	{}


	/*
		析构函数
	*/
	template<typename _ObjectType>
	ZArray<_ObjectType>::~ZArray() {}

	/*
		重载()
		参数：
			const Int32 _index object下标
		返回：
			_ObjectType& 下标对应的object的引用
	*/
	template<typename _ObjectType>
	__forceinline _ObjectType& ZArray<_ObjectType>::operator()(const Int32 _index) 
	{
		return ZContainer<_ObjectType>::operator()(_index);
	}

	/*
		重载()
		参数：
			const Int32 _index object下标
		返回：
			const _ObjectType& 下标对应的object的引用
	*/
	template<typename _ObjectType>
	__forceinline const _ObjectType& ZArray<_ObjectType>::operator()(const Int32 _index) const 
	{
		return ZContainer<_ObjectType>::operator()(_index);
	}

	/*
		重载=
		深度复制
		参数：
			const Array& _array 被复制的数组
	*/
	template<typename _ObjectType>
	const Void ZArray<_ObjectType>::operator=(const ZArray& _array) 
	{
		ZContainer<_ObjectType>::operator=(_array);
	}

	/*
		重载=
		移动语义
		参数：
			const Array&& _array 数组
	*/
	template<typename _ObjectType>
	const Void ZArray<_ObjectType>::operator=(const ZArray&& _array) 
	{
		ZContainer<_ObjectType>::operator=(std::forward<ZArray>(_array));
	}


	/*
		添加object到最后，逻辑使用memcpy进行复制整个object
		参数：
			const _ObjectType& _object 需要添加的object
	*/
	template<typename _ObjectType>
	const Void ZArray<_ObjectType>::push(const _ObjectType& _object)
	{
		ZContainer<_ObjectType>::changeSize(1);
		(*this)(ZContainer<_ObjectType>::getSize() - 1) = _object;
	}



	/*
		添加空的object
		参数：
			const Int32 _num 添加的object数量
	*/
	template<typename _ObjectType>
	const Void ZArray<_ObjectType>::pushEmpty(const Int32 _num) 
	{
		ZContainer<_ObjectType>::changeSize(_num);
	}

	/*
		设置object数量
		会判断是否需要拓展空间
		参数：
			const Int32 容器object数量
	*/
	template<typename _ObjectType>
	const Void ZArray<_ObjectType>::setSize(const Int32 _num) 
	{
		ZContainer<_ObjectType>::setSize(_num);
	}

	/*
		插入object到指定位置，将其余object依次后移
		非常费时，无特别需要慎用
		参数：
			const Int32 _index 插入的下标
			const _ObjectType& _object 需要插入的object
		返回：
			const Boolean 是否成功
	*/
	template<typename _ObjectType>
	const Boolean ZArray<_ObjectType>::insert(const Int32 _index, const _ObjectType& _object)
	{
		if (_index > ZContainer<_ObjectType>::getSize()) 
		{
			return false;
		}
		//增加object数量
		ZContainer<_ObjectType>::changeSize(1);
		//插入位置后的object后移
		for (Int32 index = ZContainer<_ObjectType>::getSize() - 1; index > _index; index--) 
		{
			(*this)(index) = (*this)(index - 1);
		}
		//插入object
		(*this)(_index) = _object;
		return true;
	}

	/*
		删除指定位置的object，将后置object前移
		非常费时，无特别需要慎用
		参数：
			const Int32 _index 删除的下标
		返回：
			const Boolean 是否成功
	*/
	template<typename _ObjectType>
	const Boolean ZArray<_ObjectType>::remove(const Int32 _index) {
		if (_index >= ZContainer<_ObjectType>::getSize()) {
			return false;
		}
		//减少object数量
		ZContainer<_ObjectType>::changeSize(-1);
		//先释放删除object的资源
		ZContainer<_ObjectType>::deleteObject(_index);
		//将删除object后面的object前移
		memcpy((Address)(&(*this)(_index)), (Address)(&(*this)(_index + 1)), (ZContainer<_ObjectType>::getSize() - _index) * sizeof(_ObjectType));
		//空余元素位置补充，防止析构时二次释放
		ZContainer<_ObjectType>::newObject(ZContainer<_ObjectType>::getSize());
		return true;
	}

	/*
		清空数组
	*/
	template<typename _ObjectType>
	__forceinline const Void ZArray<_ObjectType>::clear() {
		ZContainer<_ObjectType>::clear();
	}


}


#endif // !ZArray_h
