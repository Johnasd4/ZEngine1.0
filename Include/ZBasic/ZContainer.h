#ifndef ZContainer_h
#define ZContainer_h

#include"ZBasicDrive.h"


#include"ZObject.h"
#include"ZMemoryPool.h"

namespace ZEngine 
{


	/*
		ZContainer类
		说明：
			该类为容器基类，所有容器继承自该类
			需要拓展容器对象时使用extend函数。
			析构函数中会自动释放内存。
	*/
	template<typename _ObjectType>
	class ZContainer: ZObject
	{

	public:

		//作为容器对象时是否调用构造函数
		constexpr static Boolean ContainerElementIfCallConstructor = true;
		//容器自动拓展空间的倍率
		static constexpr Float32 AUTO_GROW_MUL_FACTOR = 0.2F;

	protected:

		/*
			构造函数
			单元素容器初始化，调用构造函数
			参数：
				_ObjectType** _objectPtrPtr 容器地址指针
				Args&&... args 构造函数的参数
		*
		template<typename _ObjectType,typename... Args>
		__forceinline ZContainer(_ObjectType** _objectPtrPtr, Args&&... args);


		/*
			构造函数
			多元素容器初始化
			参数：
				const Int32& _capacity 容器大小
				const Boolean&& _containerElementIfCallConstructor = false 默认不调用构造函数
		*/
		
		__forceinline ZContainer(const Int32& _capacity, const Boolean&& _containerElementIfCallConstructor = false);

		/*
			析构函数
		*/
		__forceinline ~ZContainer() noexcept;


		/*
			容器拓展函数
			参数：
				const Int32& _capacity 扩展后容器大小
				const Boolean&& _containerElementIfCallConstructor = false 默认不调用构造函数
		*/
		const Void extend(const Int32& _capacity, const Boolean&& _containerElementIfCallConstructor = false);

		/*
			获取容器存储指针
			返回：
				_ObjectType* 容器存储指针
		*/
		__forceinline _ObjectType* getObjectPtr() noexcept;

		/*
			获取容器存储指针
			返回：
				const _ObjectType* 容器存储指针
		*/
		__forceinline const _ObjectType* getObjectPtr() const noexcept;

		/*
			获取容器大小
			返回：
				const Int32& 容器大小
		*/
		__forceinline const Int32& getCapacity() const noexcept;
		
		/*
			获取容器元素数量
			返回：
				const Int32& 容器元素数量
		*/
		__forceinline const Int32& getSize() const noexcept;

		/*
			设置元素数量
			参数：
				const Int32& 容器元素数量
		*/
		__forceinline const Void setSize(const Int32& _size) noexcept;

		/*
			清空容器
		*/
		__forceinline const Void clear();

	private:

		/*
			多元素容器拓展函数
			参数：
				const Int32& _capacity 扩展后容器大小
				const Boolean&& _containerElementIfCallConstructor = false 默认不调用构造函数
		*/
		const Void autoExtend(const Boolean&& _containerElementIfCallConstructor = false);


	private:
		//内存块指针
		ZMemoryPiece* memoryPiecePtr;
		//容器的大小
		Int32 capacity;
		//容器的元素数量
		Int32 size;
	};

	/*
		构造函数
		单元素容器初始化，调用构造函数
		参数：
			_ObjectType** _objectPtrPtr 容器地址指针
			Args&&... args 构造函数的参数
	*
	template<typename _ObjectType, typename... Args>
	__forceinline ZContainer::ZContainer(_ObjectType** _objectPtrPtr, Args&&... args) {
		//申请内存
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(capacityof(_ObjectType));
		//申请成功则在指定地址上new该对象或数据（如果需要的话）,并保存到容器指针上
		*_objectPtrPtr = new(memoryPiecePtr->memoryAddress) _ObjectType(std::forward<Args>(args)...);
	}



	/*
		构造函数
		容器初始化
		参数：
			const Int32& _capacity 容器大小
			const Boolean&& _containerElementIfCallConstructor = false 默认不调用构造函数
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::ZContainer(const Int32& _capacity, const Boolean&& _containerElementIfCallConstructor) :
		capacity(_capacity)
	{
		//计算申请空间的大小
		ZMemoryPiece::MemoryPieceSizeType memorySize = _capacity * sizeof(_ObjectType);
		//申请内存
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
		//申请成功则在指定地址上new该对象或数据（如果需要的话）,并保存到容器指针上
		if (_containerElementIfCallConstructor) 
		{
			new(memoryPiecePtr->memoryAddress) _ObjectType[_capacity];
		}
	}

	/*
		析构函数
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::~ZContainer() noexcept 
	{
		//释放内存
		ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
	}

	/*
		容器拓展函数
		参数：
			const Int32& _capacity 扩展后容器大小
			const Boolean&& _containerElementIfCallConstructor = false 默认不调用构造函数
	*/
	template<typename _ObjectType>
	const Void ZContainer<_ObjectType>::extend(const Int32& _capacity, const Boolean&& _containerElementIfCallConstructor) 
	{
		//拓展前容器需要的内存大小
		ZMemoryPiece::MemoryPieceSizeType originMemorySize = capacity * sizeof(_ObjectType);
		//拓展后容器需要的内存大小
		ZMemoryPiece::MemoryPieceSizeType currentMemorySize = _capacity * sizeof(_ObjectType);
		//判断当前内存块是否不够大
		if (currentMemorySize > memoryPiecePtr->size) {
			//向内存池申请内存
			ZMemoryPiece* tempMemoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(currentMemorySize);
			//将当前内存块保存的数据转化到临时内存快上
			memcpy(tempMemoryPiecePtr->memoryAddress, memoryPiecePtr->memoryAddress, originMemorySize);
			//释放当前内存块
			ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
			//修改当前容器的内存块
			memoryPiecePtr = tempMemoryPiecePtr;
		}
		//如果需要初始化拓展内存
		if (_containerElementIfCallConstructor) {
			//在拓展的位置上调用构造函数初始化内存
			new((Address)(((UIntAddress)(memoryPiecePtr->memoryAddress)) + originMemorySize)) _ObjectType[currentMemorySize - originMemorySize];
		}
		//修改容器大小
		capacity = _capacity;
	}

	/*
		获取容器存储指针
		返回：
			_ObjectType* 容器存储指针
	*/
	template<typename _ObjectType>
	__forceinline _ObjectType* ZContainer<_ObjectType>::getObjectPtr() noexcept 
	{
		return (_ObjectType*)memoryPiecePtr->memoryAddress;
	}

	/*
		获取容器存储指针
		返回：
			const _ObjectType* 容器存储指针
	*/
	template<typename _ObjectType>
	__forceinline const _ObjectType* ZContainer<_ObjectType>::getObjectPtr() const noexcept 
	{
		return (_ObjectType*)memoryPiecePtr->memoryAddress;
	}

	/*
		获取容器大小
		返回：
			const Int32& 容器大小
	*/
	template<typename _ObjectType>
	__forceinline const Int32& ZContainer<_ObjectType>::getCapacity() const noexcept 
	{
		return capacity;
	}

	/*
		获取容器元素数量
		返回：
			const Int32& 容器元素数量
	*/
	template<typename _ObjectType>
	__forceinline const Int32& ZContainer<_ObjectType>::getSize() const noexcept 
	{
		return size;
	}

	/*
		设置元素数量
		参数：
			const Int32& 容器元素数量
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::setSize(const Int32& _size) noexcept 
	{
		size = _size;
	}

	/*
		清空容器
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::clear() 
	{
		this->size = 0;
	}

}


#endif // !ZContainer_h
