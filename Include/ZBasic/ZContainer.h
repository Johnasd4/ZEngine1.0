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
		//容器初始化默认空间大小
		static constexpr Int32 DEFAULT_CAPACITY = 10;
		//容器自动拓展空间的倍率
		static constexpr Float32 AUTO_GROW_MUL_FACTOR = 0.2F;


	protected:

		/*
			构造函数
			多元素容器初始化
			参数：
				const Int32& _capacity 容器大小
				const Boolean&& _containerElementIfCallConstructor = false 默认不调用构造函数
		*/
		__forceinline ZContainer(const Int32& _capacity = DEFAULT_CAPACITY);

		/*
			构造函数
			完全复制
			参数：
				const ZContainer& _container 被复制的容器 
		*/
		__forceinline ZContainer(const ZContainer& _container);

		/*
			构造函数
			移动语义
			参数：
				const ZContainer&& _container 被移动的容器
		*/
		__forceinline ZContainer(const ZContainer&& _container);

		/*
			析构函数
		*/
		__forceinline ~ZContainer();


		/*
			容器拓展函数
			参数：
				const Int32& _capacity 扩展后容器大小
				const Boolean&& _containerElementIfCallConstructor = false 默认不调用构造函数
		*/
		const Void extend(const Int32& _capacity) noexcept;

		/*
			获取容器存储指针
			返回：
				_ObjectType* 容器存储指针
		*/
		__forceinline _ObjectType* getObjectPtr();

		/*
			获取容器存储指针
			返回：
				const _ObjectType* 容器存储指针
		*/
		__forceinline const _ObjectType* getObjectPtr() const;

		/*
			获取容器大小
			返回：
				const Int32& 容器大小
		*/
		__forceinline const Int32& getCapacity() const;
		
		/*
			获取容器元素数量
			返回：
				const Int32& 容器元素数量
		*/
		__forceinline const Int32& getSize() const;

		/*
			设置元素数量
			参数：
				const Int32& 容器元素数量
		*/
		__forceinline const Void setSize(const Int32& _size);

		/*
			清空容器
		*/
		__forceinline const Void clear();

	private:


		/*
			自动判断是否初始化Object
			说明：
				判断类是否存在ContainerElementIfCallConstructor成员
				如果存在则判断是否需要初始化Object
			参数：
				const Address& address 初始化的地址
				const Int32& objectNum 初始化的数量
		*/
		template<typename __ObjectType>
		__forceinline const Void initObject(Address&& address, Int32&& objectNum)
		{
			callConstructor<__ObjectType::ContainerElementIfCallConstructor>(std::forward<Address&&>(address), std::forward<Int32&&>(objectNum));
		}
		template<typename __ObjectType>
		__forceinline const Void initObject(...) {}
		template<Boolean _ifCallConstructor>
		__forceinline const Void callConstructor(const Address& address, const Int32& objectNum) {}
		template<>
		__forceinline const Void callConstructor<true>(const Address& address, const Int32& objectNum) 
		{
			new(address) _ObjectType[objectNum];
		}


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
		多元素容器初始化
		参数：
			const Int32& _capacity 容器大小
			const Boolean&& _containerElementIfCallConstructor = false 默认不调用构造函数
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::ZContainer(const Int32& _capacity) :
		ZObject(),
		capacity(_capacity),
		size(0)
	{
		//计算申请空间的大小
		ZMemoryPiece::MemoryPieceSizeType memorySize = _capacity * sizeof(_ObjectType);
		//申请内存
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
		//申请成功则在指定地址上new该对象或数据（如果需要的话）,并保存到容器指针上		
		initObject<_ObjectType>(memoryPiecePtr->memoryAddress, _capacity);
	}

	/*
		构造函数
		完全复制
		参数：
			const ZContainer& _container 被复制的容器
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::ZContainer(const ZContainer& _container) :
		ZObject(_container),
		capacity(_container.capacity),
		size(_container.size)
	{

	}

	/*
		构造函数
		移动语义
		参数：
			const ZContainer&& _container 被移动的容器
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::ZContainer(const ZContainer&& _container) :
		ZObject(_container),
		memoryPiecePtr(_container.memoryPiecePtr),
		capacity(_container.capacity),
		size(_container.size)
	{
		_container.memoryPiecePtr = nullptr;
	}

	/*
		析构函数
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::~ZContainer() 
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
	const Void ZContainer<_ObjectType>::extend(const Int32& _capacity) noexcept
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
		//如果需要在拓展的位置上调用构造函数初始化内存
		initObject<_ObjectType>((Address)(((UIntAddress)(memoryPiecePtr->memoryAddress)) + originMemorySize), currentMemorySize - originMemorySize);
		//修改容器大小
		capacity = _capacity;
	}

	/*
		获取容器存储指针
		返回：
			_ObjectType* 容器存储指针
	*/
	template<typename _ObjectType>
	__forceinline _ObjectType* ZContainer<_ObjectType>::getObjectPtr() 
	{
		return (_ObjectType*)memoryPiecePtr->memoryAddress;
	}

	/*
		获取容器存储指针
		返回：
			const _ObjectType* 容器存储指针
	*/
	template<typename _ObjectType>
	__forceinline const _ObjectType* ZContainer<_ObjectType>::getObjectPtr() const 
	{
		return (_ObjectType*)memoryPiecePtr->memoryAddress;
	}

	/*
		获取容器大小
		返回：
			const Int32& 容器大小
	*/
	template<typename _ObjectType>
	__forceinline const Int32& ZContainer<_ObjectType>::getCapacity() const 
	{
		return capacity;
	}

	/*
		获取容器元素数量
		返回：
			const Int32& 容器元素数量
	*/
	template<typename _ObjectType>
	__forceinline const Int32& ZContainer<_ObjectType>::getSize() const 
	{
		return size;
	}

	/*
		设置元素数量
		参数：
			const Int32& 容器元素数量
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::setSize(const Int32& _size) 
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
