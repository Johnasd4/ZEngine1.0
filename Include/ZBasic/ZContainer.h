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
		__forceinline ZContainer();


		/*
			构造函数
			参数：
				const Int32 _capacity 容器大小
		*/
		__forceinline ZContainer(const Int32 _capacity);

		/*
			构造函数
			深度复制
			参数：
				const ZContainer& _container 被复制的容器 
		*/
		__forceinline ZContainer(const ZContainer& _container);

		/*
			构造函数
			移动语义
			参数：
				ZContainer&& _container 被移动的容器
		*/
		__forceinline ZContainer(ZContainer&& _container);

		/*
			析构函数
		*/
		__forceinline ~ZContainer();




		/*
			重载=
			深度复制
			参数：
				const ZContainer& _container 被复制的容器
		*/
		__forceinline const Void operator=(const ZContainer& _container);

		/*
			重载=
			移动语义
			参数：
				ZContainer&& _container 被复制的容器
		*/
		__forceinline const Void operator=(ZContainer&& _container);

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
		template<typename _CheckMemberObjectType, decltype(_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void newObject(const Int32& _index)
		{
			newObjectCallConstructor<_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_index);
		}
		template<typename _CheckMemberObjectType>
		__forceinline const Void newObject(...) {}
		//不调用构造函数
		template<Boolean _ifCallConstructor>
		__forceinline const Void newObjectCallConstructor(const Int32& _index) {}
		//调用构造函数
		template<>
		__forceinline const Void newObjectCallConstructor<true>(const Int32& _index)
		{
			new((Address)(&((*this)(_index)))) _ObjectType();
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
		template<typename _CheckMemberObjectType, decltype(_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void freeObject(const Int32 _index)
		{
			freeObjectCallDestructor<_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_index);
		}
		template<typename _CheckMemberObjectType>
		__forceinline const Void freeObject(...) {}
		//不调用析构函数
		template<Boolean _ifCallDestructor>
		__forceinline const Void freeObjectCallDestructor(const Int32 _index) {}
		//调用析构函数
		template<>
		__forceinline const Void freeObjectCallDestructor<true>(const Int32 _index)
		{
			(*this)(_index).~_ObjectType();
		}

		/**/

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
		template<typename _CheckMemberObjectType, decltype(_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void newContainer(const Address _address, const Int32 _num)
		{
			newContainerCallConstructor<_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_address, _num);
		}
		template<typename _CheckMemberObjectType>
		__forceinline const Void newContainer(...) {}
		//不调用构造函数
		template<Boolean _ifCallConstructor>
		__forceinline const Void newContainerCallConstructor(const Address _address, const Int32 _num) {}
		//调用构造函数
		template<>
		__forceinline const Void newContainerCallConstructor<true>(const Address _address, const Int32 _num)
		{
			new(_address) _ObjectType[_num];
		}

		/*
			复制构造函数
			自动判断是否初始化object
			说明：
				判断类是否存在NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR成员
				如果存在则判断是否需要初始化object
			参数：
				const ZContainer& _container 初始化时复制的容器
		*/
		template<typename _CheckMemberObjectType, decltype(_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void newCopyContainer(const ZContainer& _container)
		{
			newCopyContainerCallConstructor<_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_container);
		}
		template<typename _CheckMemberObjectType>
		__forceinline const Void newCopyContainer(...) {}
		//不调用构造函数
		template<Boolean _ifCallConstructor>
		__forceinline const Void newCopyContainerCallConstructor(const ZContainer& _container) {
			memcpy((Address)(this->getObjectPtr()), (Address)(_container.getObjectPtr()), (UInt64)_container.getCapacity() * sizeof(_ObjectType));
		}
		//调用构造函数
		template<>
		__forceinline const Void newCopyContainerCallConstructor<true>(const ZContainer& _container)
		{
			for (Int32 index = 0; index < _container.capacity; index++) {
				new((Address)(&((*this)(index)))) _ObjectType(_container(index));
			}
		}


		/*
			复制函数
			容器object复制
			说明：
				判断类是否存在NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR成员
				如果存在则判断是否需要深度复制
			参数：
				const ZContainer& _container 复制的容器
		*/
		template<typename _CheckMemberObjectType, decltype(_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void copyContainer(const ZContainer& _container)
		{
			copyContainerCallConstructor<_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_container);
		}
		template<typename _CheckMemberObjectType>
		__forceinline const Void copyContainer(...) {}
		//不调用复制函数
		template<Boolean _ifCallConstructor>
		__forceinline const Void copyContainerCallConstructor(const ZContainer& _container)
		{
			memcpy((Address)(this->getObjectPtr()), (Address)(_container.getObjectPtr()), (UInt64)_container.getCapacity() * sizeof(_ObjectType));
		}
		//调用复制函数
		template<>
		const Void copyContainerCallConstructor<true>(const ZContainer& _container)
		{
			//如果当前容器够大
			if (capacity >= _container.capacity) {
				for (Int32 index = 0; index < _container.capacity; index++) {
					(*this)(index) = _container(index);
				}
			}
			//如果当前容器不够大
			else {
				//当前已经初始化过的直接调用复制函数
				for (Int32 index = 0; index < capacity; index++) {
					(*this)(index) = _container(index);
				}
				//没有初始化过的调用复制构造函数
				for (Int32 index = capacity; index < _container.capacity; index++) {
					new((Address) & (*this)(index)) _ObjectType(_container(index));
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
				const ZContainer& _container 析构的容器
		*/
		template<typename _CheckMemberObjectType, decltype(_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void freeContainer()
		{
			freeContainerCallDestructor<_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>();
		}
		template<typename _CheckMemberObjectType>
		__forceinline const Void freeContainer(...) {}
		//不调用析构函数
		template<Boolean _ifCallDestructor>
		__forceinline const Void freeContainerCallDestructor(){}
		//调用析构函数
		template<>
		const Void freeContainerCallDestructor<true>()
		{
			for (Int32 index = 0; index < this->capacity; index++) {
				(*this)(index).~_ObjectType();
			}
		}


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
	__forceinline ZContainer<_ObjectType>::ZContainer() :
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
		newContainer<_ObjectType>(memoryPiecePtr->memoryAddress, DEFAULT_CAPACITY);
	}


	/*
		构造函数
		多object容器初始化
		参数：
			const Int32 _capacity 容器大小
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::ZContainer(const Int32 _capacity) :
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
		newContainer<_ObjectType>(memoryPiecePtr->memoryAddress, _capacity);
	}

	/*
		构造函数
		深度复制
		参数：
			const ZContainer& _container 被复制的容器
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::ZContainer(const ZContainer& _container) :
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
		newCopyContainer<_ObjectType>(_container);
	}

	/*
		构造函数
		移动语义
		参数：
			ZContainer&& _container 被移动的容器
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::ZContainer(ZContainer&& _container) :
		ZObject(std::forward<ZContainer>(_container)),
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
	__forceinline ZContainer<_ObjectType>::~ZContainer() 
	{
		//释放object
		freeContainer<_ObjectType>();
		//释放内存
		ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
	}



	/*
		重载=
		深度复制
		参数：
			const ZContainer& _container 被复制的容器
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::operator=(const ZContainer& _container) 
	{
		ZObject::operator=(_container);
		//容器需要的内存大小
		ZMemoryPiece::MemoryPieceSizeType memorySize = _container.capacity * sizeof(_ObjectType);
		//判断当前内存块是否不够大
		if (memorySize > memoryPiecePtr->size) {
			changeMemoryPiece(capacity * sizeof(_ObjectType), memorySize);
		}
		//复制object
		copyContainer<_ObjectType>(_container);
		capacity = _container.capacity;
		size = _container.size;

		
	}

	/*
		重载=
		移动语义
		参数：
			ZContainer&& _container 被移动的容器
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::operator=(ZContainer&& _container) 
	{
		ZObject::operator=(std::forward<ZContainer>(_container));
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
	__forceinline _ObjectType& ZContainer<_ObjectType>::operator()(const Int32 _index)
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
	__forceinline const _ObjectType& ZContainer<_ObjectType>::operator()(const Int32 _index) const
	{
		return getObjectPtr()[_index];
	}




	/*
		获取容器存储指针
		返回：
			_ObjectType* 容器存储指针
	*/
	template<typename _ObjectType>
	__forceinline _ObjectType* ZContainer<_ObjectType>::getObjectPtr() 
	{
		return objectPtr;
	}

	/*
		获取容器存储指针
		返回：
			const _ObjectType* 容器存储指针
	*/
	template<typename _ObjectType>
	__forceinline const _ObjectType* ZContainer<_ObjectType>::getObjectPtr() const 
	{
		return objectPtr;
	}

	/*
		获取容器大小
		返回：
			const Int32 容器大小
	*/
	template<typename _ObjectType>
	__forceinline const Int32 ZContainer<_ObjectType>::getCapacity() const 
	{
		return capacity;
	}

	/*
		获取容器object数量
		返回：
			const Int32 容器object数量
	*/
	template<typename _ObjectType>
	__forceinline const Int32 ZContainer<_ObjectType>::getSize() const 
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
	__forceinline const Void ZContainer<_ObjectType>::setSize(const Int32 _size) 
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
	__forceinline const Void ZContainer<_ObjectType>::changeSize(const Int32 _offset) {
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
	__forceinline const Void ZContainer<_ObjectType>::clear() 
	{
		this->size = 0;
	}

	/*
		容器拓展函数
		参数：
			const Int32 _capacity 扩展后容器大小
	*/
	template<typename _ObjectType>
	const Void ZContainer<_ObjectType>::extend(const Int32 _capacity) noexcept
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
		newContainer<_ObjectType>((Address)(((UIntAddress)(memoryPiecePtr->memoryAddress)) + usedMemorySize), applyMemorySize - usedMemorySize);
		//修改容器大小
		capacity = _capacity;
	}

	/*
		容器自动拓展函数
	*/
	template<typename _ObjectType>
	const Void ZContainer<_ObjectType>::autoExtend() noexcept 
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
	const Void ZContainer<_ObjectType>::changeMemoryPiece(const Int32 _usedMemorySize, const Int32 _applyMemorySize)
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
	__forceinline const Void ZContainer<_ObjectType>::move_destroy() 
	{
		memoryPiecePtr = nullptr;
		objectPtr = nullptr;
		capacity = 0;
		size = 0;
	}


}


#endif // !ZContainer_h
