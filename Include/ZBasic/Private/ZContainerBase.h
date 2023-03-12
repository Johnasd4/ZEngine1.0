#ifndef ZContainerBase_h
#define ZContainerBase_h

#include"Private/ZBasicDrive.h"



#include"ZObject.h"
#include"ZMemoryPool.h"

namespace ZEngine 
{


	/*
		ZContainerBase类
		说明：
			该类为容器基类，所有容器继承自该类
			需要拓展容器对象时使用extend函数。
			析构函数中会自动释放内存。
	*/
	template<typename _ObjectType>
	class ZContainerBase: ZObject
	{

	public:

		//初始化和释放时是否需要调用构造函数和析构函数
		static constexpr Boolean NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR = true;
		//容器初始化默认空间大小
		static constexpr Int32 DEFAULT_CAPACITY = 10;
		//容器自动拓展空间的倍率
		static constexpr Float32 AUTO_EXTEND_MUL_FACTOR = 1.2F;

	public:

		/*
			获取容器大小
			返回：
				const Int32 容器大小
		*/
		__forceinline const Int32 getCapacity() const;

		/*
			获取容器object数量
			返回：
				const Int32 容器object数量
		*/
		__forceinline const Int32 getSize() const;

	protected:

		/*
			构造函数
		*/
		__forceinline ZContainerBase();


		/*
			构造函数
			参数：
				const Int32 _capacity 容器大小
		*/
		__forceinline ZContainerBase(const Int32 _capacity);

		/*
			构造函数
			深度复制
			参数：
				const ZContainerBase& _container 被复制的容器 
		*/
		__forceinline ZContainerBase(const ZContainerBase& _container);

		/*
			构造函数
			移动语义
			参数：
				ZContainerBase&& _container 被移动的容器
		*/
		__forceinline ZContainerBase(ZContainerBase&& _container);

		/*
			析构函数
		*/
		__forceinline ~ZContainerBase();




		/*
			重载=
			深度复制
			参数：
				const ZContainerBase& _container 被复制的容器
		*/
		__forceinline const Void operator=(const ZContainerBase& _container);

		/*
			重载=
			移动语义
			参数：
				ZContainerBase&& _container 被复制的容器
		*/
		__forceinline const Void operator=(ZContainerBase&& _container);

		/*
			重载（）
			获取容器object的引用
			参数：
				const Int32 _index object下标
			返回：
				_ObjectType& object的引用
		*/
		__forceinline _ObjectType& operator()(const Int32 _index);

		/*
			重载（）
			获取容器object的引用
			参数：
				const Int32 _index object下标
			返回：
				const _ObjectType& object的引用
		*/
		__forceinline const _ObjectType& operator()(const Int32 _index) const;



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
			设置object数量
			参数：
				const Int32 容器object数量
		*/
		__forceinline const Void setSize(const Int32 _size);

		/*
			改变object数量
			参数：
				const Int32 _offset 偏差值
		*/
		__forceinline const Void changeSize(const Int32 _offset);

		/*
			清空容器
		*/
		__forceinline const Void clear();

		/*
			构造函数
			自动判断是否初始化object
			说明：
				判断类是否存在NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR成员
				如果存在则判断是否需要初始化object
			参数：
				const Address& _address 初始化的地址
		*/
		__forceinline const Void newObject(const Int32& _index);

		/*
			析构函数
			object释放
			说明：
				判断类是否存在NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR成员
				如果存在则判断是否需要进行析构
			参数：
				const Int32 _index 析构object的下标
		*/
		__forceinline const Void deleteObject(const Int32 _index);

	private:

		/*
			容器拓展函数
			参数：
				const Int32 _capacity 扩展后容器大小
		*/
		const Void extend(const Int32 _capacity) noexcept;

		/*
			容器自动拓展函数
		*/
		const Void autoExtend() noexcept;

		/*
			替换内存块
			参数：
				const Int32 _usedMemorySize 原本使用的内存块大小
				const Int32 _applyMemorySize 替换内存块需要的大小
		*/
		const Void changeMemoryPiece(const Int32 _usedMemorySize, const Int32 _applyMemorySize);



		/*
			移动语义摧毁容器
			会将所有容器属性清空而不进行任何操作
			不会归还内存，仅用于移动语义
		*/
		__forceinline const Void move_destroy();

		/*
			构造函数
			自动判断是否初始化object
			说明：
				判断类是否存在NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR成员
				如果存在则判断是否需要初始化object
			参数：
				const Address _address 初始化的地址
				const Int32 _num 初始化的数量
		*/
		__forceinline const Void newObjects(const Address _address, const Int32 _num);


		/*
			复制构造函数
			自动判断是否初始化object
			说明：
				判断类是否存在NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR成员
				如果存在则判断是否需要初始化object
			参数：
				const ZContainerBase& _container 初始化时复制的容器
		*/
		__forceinline const Void newCopyObjects(const ZContainerBase& _container);

		/*
			复制函数
			容器object复制
			说明：
				判断类是否存在NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR成员
				如果存在则判断是否需要深度复制
			参数：
				const ZContainerBase& _container 复制的容器
		*/
		__forceinline const Void copyObjects(const ZContainerBase& _container);

		/*
			析构函数
			容器object释放
			说明：
				判断类是否存在NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR成员
				如果存在则判断是否需要进行析构
			参数：
				const ZContainerBase& _container 析构的容器
		*/
		__forceinline const Void deleteObjects();



	private:
		//内存块指针
		ZMemoryPiece* memoryPiecePtr;
		//指向容器的指针
		_ObjectType* objectPtr;
		//容器的大小
		Int32 capacity;
		//容器的object数量
		Int32 size;
	};

	/*
		构造函数
	*/
	template<typename _ObjectType>
	__forceinline ZContainerBase<_ObjectType>::ZContainerBase() :
		ZObject(),
		capacity(DEFAULT_CAPACITY),
		size(0) 
	{
		//计算申请空间的大小
		ZMemoryPiece::MemoryPieceSizeType memorySize = DEFAULT_CAPACITY * sizeof(_ObjectType);
		//申请内存
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
		//初始化容器指针
		objectPtr = (_ObjectType*)memoryPiecePtr->memoryAddress;
		//申请成功则在指定地址上new该对象或数据（如果需要的话）,并保存到容器指针上		
		newObjects(memoryPiecePtr->memoryAddress, DEFAULT_CAPACITY);
	}


	/*
		构造函数
		多object容器初始化
		参数：
			const Int32 _capacity 容器大小
	*/
	template<typename _ObjectType>
	__forceinline ZContainerBase<_ObjectType>::ZContainerBase(const Int32 _capacity) :
		ZObject(),
		capacity(_capacity),
		size(0)
	{
		//计算申请空间的大小
		ZMemoryPiece::MemoryPieceSizeType memorySize = _capacity * sizeof(_ObjectType);
		//申请内存
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
		//初始化容器指针
		objectPtr = (_ObjectType*)memoryPiecePtr->memoryAddress;
		//申请成功则在指定地址上new该对象或数据（如果需要的话）,并保存到容器指针上		
		newObjects(memoryPiecePtr->memoryAddress, _capacity);
	}

	/*
		构造函数
		深度复制
		参数：
			const ZContainerBase& _container 被复制的容器
	*/
	template<typename _ObjectType>
	__forceinline ZContainerBase<_ObjectType>::ZContainerBase(const ZContainerBase& _container) :
		ZObject(_container),
		capacity(_container.capacity),
		size(_container.size)
	{
		//计算申请空间的大小
		ZMemoryPiece::MemoryPieceSizeType memorySize = capacity * sizeof(_ObjectType);
		//申请内存
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
		//初始化容器指针
		objectPtr = (_ObjectType*)memoryPiecePtr->memoryAddress;
		//申请成功则在指定地址上new该对象或数据（如果需要的话）,并保存到容器指针上		
		newCopyObjects(_container);
	}

	/*
		构造函数
		移动语义
		参数：
			ZContainerBase&& _container 被移动的容器
	*/
	template<typename _ObjectType>
	__forceinline ZContainerBase<_ObjectType>::ZContainerBase(ZContainerBase&& _container) :
		ZObject(std::forward<ZContainerBase>(_container)),
		memoryPiecePtr(_container.memoryPiecePtr),
		objectPtr(_container.objectPtr),
		capacity(_container.capacity),
		size(_container.size)
	{
		//防止内存块被释放两次
		_container.move_destroy();
	}

	/*
		析构函数
	*/
	template<typename _ObjectType>
	__forceinline ZContainerBase<_ObjectType>::~ZContainerBase() 
	{
		//释放object
		deleteObjects();
		//释放内存
		ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
	}



	/*
		重载=
		深度复制
		参数：
			const ZContainerBase& _container 被复制的容器
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainerBase<_ObjectType>::operator=(const ZContainerBase& _container) 
	{
		ZObject::operator=(_container);
		//容器需要的内存大小
		ZMemoryPiece::MemoryPieceSizeType memorySize = _container.capacity * sizeof(_ObjectType);
		//判断当前内存块是否不够大
		if (memorySize > memoryPiecePtr->size) {
			changeMemoryPiece(capacity * sizeof(_ObjectType), memorySize);
		}
		//复制object
		copyObjects(_container);
		capacity = _container.capacity;
		size = _container.size;

		
	}

	/*
		重载=
		移动语义
		参数：
			ZContainerBase&& _container 被移动的容器
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainerBase<_ObjectType>::operator=(ZContainerBase&& _container) 
	{
		ZObject::operator=(std::forward<ZContainerBase>(_container));
		memoryPiecePtr = _container.memoryPiecePtr;
		objectPtr = _container.objectPtr;
		capacity = _container.capacity;
		size = _container.size;
		//防止内存块被释放两次
		_container.move_destroy();
	}

	/*
		重载（）
		获取容器object的引用
		参数：
			const Int32 _index object下标
		返回：
			_ObjectType& object的引用
	*/
	template<typename _ObjectType>
	__forceinline _ObjectType& ZContainerBase<_ObjectType>::operator()(const Int32 _index)
	{
		return getObjectPtr()[_index];
	}

	/*
		重载（）
		获取容器object的引用
		参数：
			const Int32 _index object下标
		返回：
			const _ObjectType& object的引用
	*/
	template<typename _ObjectType>
	__forceinline const _ObjectType& ZContainerBase<_ObjectType>::operator()(const Int32 _index) const
	{
		return getObjectPtr()[_index];
	}




	/*
		获取容器存储指针
		返回：
			_ObjectType* 容器存储指针
	*/
	template<typename _ObjectType>
	__forceinline _ObjectType* ZContainerBase<_ObjectType>::getObjectPtr() 
	{
		return objectPtr;
	}

	/*
		获取容器存储指针
		返回：
			const _ObjectType* 容器存储指针
	*/
	template<typename _ObjectType>
	__forceinline const _ObjectType* ZContainerBase<_ObjectType>::getObjectPtr() const 
	{
		return objectPtr;
	}

	/*
		获取容器大小
		返回：
			const Int32 容器大小
	*/
	template<typename _ObjectType>
	__forceinline const Int32 ZContainerBase<_ObjectType>::getCapacity() const 
	{
		return capacity;
	}

	/*
		获取容器object数量
		返回：
			const Int32 容器object数量
	*/
	template<typename _ObjectType>
	__forceinline const Int32 ZContainerBase<_ObjectType>::getSize() const 
	{
		return size;
	}

	/*
		设置object数量
		会判断是否需要拓展空间
		参数：
			const Int32 容器object数量
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainerBase<_ObjectType>::setSize(const Int32 _size) 
	{
		size = _size;
		//如果object过多，则自动拓展容器
		if (size > capacity) {
			autoExtend();
		}
	}

	/*
		改变object数量
		参数：
			const Int32 _offset 偏差值
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainerBase<_ObjectType>::changeSize(const Int32 _offset) {
		size += _offset;
		//如果object过多，则自动拓展容器
		if (size > capacity) {
			autoExtend();
		}
	}

	/*
		清空容器
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainerBase<_ObjectType>::clear() 
	{
		this->size = 0;	
	}

	/*
		构造函数
		自动判断是否初始化object
		说明：
			判断类是否存在NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR成员
			如果存在则判断是否需要初始化object
		参数：
			const Address& _address 初始化的地址
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainerBase<_ObjectType>::newObject(const Int32& _index)
	{
		//判断成员是否存在
		if constexpr (requires{_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR; })
		{
			//是否调用object的构造函数
			if constexpr (_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR == true)
			{
				new((Address)(&((*this)(_index)))) _ObjectType();
			}
		}
	}

	/*
		析构函数
		object释放
		说明：
			判断类是否存在NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR成员
			如果存在则判断是否需要进行析构
		参数：
			const Int32 _index 析构object的下标
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainerBase<_ObjectType>::deleteObject(const Int32 _index)
	{
		//判断成员是否存在
		if constexpr (requires{_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR; })
		{
			//是否调用object的析构函数
			if constexpr (_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR == true)
			{
				(*this)(_index).~_ObjectType();
			}
		}
	}


	/*
		容器拓展函数
		参数：
			const Int32 _capacity 扩展后容器大小
	*/
	template<typename _ObjectType>
	const Void ZContainerBase<_ObjectType>::extend(const Int32 _capacity) noexcept
	{
		//拓展前容器需要的内存大小
		ZMemoryPiece::MemoryPieceSizeType usedMemorySize = capacity * sizeof(_ObjectType);
		//拓展后容器需要的内存大小
		ZMemoryPiece::MemoryPieceSizeType applyMemorySize = _capacity * sizeof(_ObjectType);
		//判断当前内存块是否不够大
		if (applyMemorySize > memoryPiecePtr->size) {
			changeMemoryPiece(usedMemorySize, applyMemorySize);
		}
		//如果需要在拓展的位置上调用构造函数初始化内存
		newObjects((Address)(((UIntAddress)(memoryPiecePtr->memoryAddress)) + usedMemorySize), applyMemorySize - usedMemorySize);
		//修改容器大小
		capacity = _capacity;
	}

	/*
		容器自动拓展函数
	*/
	template<typename _ObjectType>
	const Void ZContainerBase<_ObjectType>::autoExtend() noexcept 
	{
		Float32 tempCapacity = (Float32)capacity;
		do {
			tempCapacity *= AUTO_EXTEND_MUL_FACTOR;
		} while (tempCapacity < this->size);
		extend((Int32)tempCapacity);
	}

	/*
		替换内存块
		参数：
			const Int32 _usedMemorySize 原本使用的内存块大小
			const Int32 _applyMemorySize 替换内存块需要的大小
	*/
	template<typename _ObjectType>
	const Void ZContainerBase<_ObjectType>::changeMemoryPiece(const Int32 _usedMemorySize, const Int32 _applyMemorySize)
	{
		//向内存池申请内存
		ZMemoryPiece* tempMemoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(_applyMemorySize);
		//将当前内存块保存的数据转化到临时内存快上
		memcpy(tempMemoryPiecePtr->memoryAddress, memoryPiecePtr->memoryAddress, _usedMemorySize);
		//释放当前内存块
		ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
		//修改当前容器的内存块
		memoryPiecePtr = tempMemoryPiecePtr;
		//修改容器指针
		objectPtr = (_ObjectType*)memoryPiecePtr->memoryAddress;
	}


	/*
		移动语义摧毁容器
		会将所有容器属性清空而不进行任何操作
		不会归还内存，仅用于移动语义
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainerBase<_ObjectType>::move_destroy() 
	{
		memoryPiecePtr = nullptr;
		objectPtr = nullptr;
		capacity = 0;
		size = 0;
	}

	/*
		构造函数
		自动判断是否初始化object
		说明：
			判断类是否存在NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR成员
			如果存在则判断是否需要初始化object
		参数：
			const Address _address 初始化的地址
			const Int32 _num 初始化的数量
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainerBase<_ObjectType>::newObjects(const Address _address, const Int32 _num)
	{
		//判断成员是否存在
		if constexpr (requires{_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR; })
		{
			//是否调用object的构造函数
			if constexpr (_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR == true)
			{
				new(_address) _ObjectType[_num];
			}
		}
	}


	/*
		复制构造函数
		自动判断是否初始化object
		说明：
			判断类是否存在NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR成员
			如果存在则判断是否需要初始化object
		参数：
			const ZContainerBase& _container 初始化时复制的容器
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainerBase<_ObjectType>::newCopyObjects(const ZContainerBase& _container)
	{
		//判断成员是否存在
		if constexpr (requires{_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR; })
		{
			//是否调用object的构造函数
			if constexpr (_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR == true)
			{
				for (Int32 index = 0; index < _container.capacity; index++)
				{
					new((Address)(&((*this)(index)))) _ObjectType(_container(index));
				}
			}
			else
			{
				memcpy((Address)(this->getObjectPtr()), (Address)(_container.getObjectPtr()), (SizeT)_container.getCapacity() * sizeof(_ObjectType));
			}
		}
	}



	/*
		复制函数
		容器object复制
		说明：
			判断类是否存在NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR成员
			如果存在则判断是否需要深度复制
		参数：
			const ZContainerBase& _container 复制的容器
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainerBase<_ObjectType>::copyObjects(const ZContainerBase& _container)
	{
		//判断成员是否存在
		if constexpr (requires{_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR; })
		{
			//是否调用object的构造函数
			if constexpr (_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR == true)
			{
				//如果当前容器够大
				if (capacity >= _container.capacity)
				{
					for (Int32 index = 0; index < _container.capacity; index++)
					{
						(*this)(index) = _container(index);
					}
				}
				//如果当前容器不够大
				else {
					//当前已经初始化过的直接调用复制函数
					for (Int32 index = 0; index < capacity; index++)
					{
						(*this)(index) = _container(index);
					}
					//没有初始化过的调用复制构造函数
					for (Int32 index = capacity; index < _container.capacity; index++)
					{
						new((Address)(&((*this)(index)))) _ObjectType(_container(index));
					}
				}
			}
			else {
				memcpy((Address)(this->getObjectPtr()), (Address)(_container.getObjectPtr()), (SizeT)_container.getCapacity() * sizeof(_ObjectType));
			}
		}
	}


	/*
		析构函数
		容器object释放
		说明：
			判断类是否存在NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR成员
			如果存在则判断是否需要进行析构
		参数：
			const ZContainerBase& _container 析构的容器
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainerBase<_ObjectType>::deleteObjects()
	{
		//判断成员是否存在
		if constexpr (requires{_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR; })
		{
			//是否调用object的析构函数
			if constexpr (_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR == true)
			{
				for (Int32 index = 0; index < this->capacity; index++)
				{
					(*this)(index).~_ObjectType();
				}
			}
		}
	}


}


#endif // !ZContainerBase_h
