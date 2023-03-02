#ifndef ZInstance_h
#define ZInstance_h

#include"ZBasicDrive.h"

#include"ZObject.h"
#include"ZMemoryPool.h"

namespace ZEngine
{


	/*
		ZInstance类
		说明：
			该类为单例类。
			实现指针的效果。
			析构函数中会自动释放内存。
	*/
	template<typename _Object>
	class ZInstance : ZObject
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
				const Int32& 容器大小
		*/
		__forceinline const Int32& getCapacity() const;

		/*
			获取容器object数量
			返回：
				const Int32& 容器object数量
		*/
		__forceinline const Int32& getSize() const;

	protected:

		/*
			构造函数
		*/
		__forceinline ZInstance();


		/*
			构造函数
			参数：
				const Int32& _capacity 容器大小
		*/
		__forceinline ZInstance(const Int32& _capacity);

		/*
			构造函数
			深度复制
			参数：
				const ZInstance& _container 被复制的容器
		*/
		__forceinline ZInstance(const ZInstance& _container);

		/*
			构造函数
			移动语义
			参数：
				const ZInstance&& _container 被移动的容器
		*/
		__forceinline ZInstance(const ZInstance&& _container);

		/*
			析构函数
		*/
		__forceinline ~ZInstance();




		/*
			重载=
			深度复制
			参数：
				const ZInstance& _container 被复制的容器
		*/
		__forceinline const Void operator=(const ZInstance& _container);

		/*
			重载=
			移动语义
			参数：
				const ZInstance&& _container 被复制的容器
		*/
		__forceinline const Void operator=(const ZInstance&& _container);

		/*
			重载（）
			获取容器object的引用
			参数：
				const Int32& _index object下标
			返回：
				_Object& object的引用
		*/
		__forceinline _Object& operator()(const Int32& _index);

		/*
			重载（）
			获取容器object的引用
			参数：
				const Int32& _index object下标
			返回：
				const _Object& object的引用
		*/
		__forceinline const _Object& operator()(const Int32& _index) const;



		/*
			获取容器存储指针
			返回：
				_Object* 容器存储指针
		*/
		__forceinline _Object* getObjectPtr();

		/*
			获取容器存储指针
			返回：
				const _Object* 容器存储指针
		*/
		__forceinline const _Object* getObjectPtr() const;

		/*
			设置object数量
			参数：
				const Int32& 容器object数量
		*/
		__forceinline const Void setSize(const Int32& _size);

		/*
			改变object数量
			参数：
				const Int32& _offset 偏差值
		*/
		__forceinline const Void changeSize(const Int32& _offset);

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
		template<typename _CheckMemberObject, decltype(_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void newObject(const Int32& _index)
		{
			newObjectCallConstructor<_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_index);
		}
		template<typename _CheckMemberObject>
		__forceinline const Void newObject(...) {}
		//不调用构造函数
		template<Boolean _ifCallConstructor>
		__forceinline const Void newObjectCallConstructor(const Int32& _index) {}
		//调用构造函数
		template<>
		__forceinline const Void newObjectCallConstructor<true>(const Int32& _index)
		{
			new((Address)(&((*this)(_index)))) _Object();
		}


		/*
			析构函数
			object释放
			说明：
				判断类是否存在NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR成员
				如果存在则判断是否需要进行析构
			参数：
				const Int32& _index 析构object的下标
		*/
		template<typename _CheckMemberObject, decltype(_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void freeObject(const Int32& _index)
		{
			freeObjectCallDestructor<_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_index);
		}
		template<typename _CheckMemberObject>
		__forceinline const Void freeObject(...) {}
		//不调用析构函数
		template<Boolean _ifCallDestructor>
		__forceinline const Void freeObjectCallDestructor(const Int32& _index) {}
		//调用析构函数
		template<>
		__forceinline const Void freeObjectCallDestructor<true>(const Int32& _index)
		{
			(*this)(_index).~_Object();
		}

		/**/

	private:

		/*
			容器拓展函数
			参数：
				const Int32& _capacity 扩展后容器大小
		*/
		const Void extend(const Int32& _capacity) noexcept;

		/*
			容器自动拓展函数
		*/
		const Void autoExtend() noexcept;

		/*
			构造函数
			自动判断是否初始化object
			说明：
				判断类是否存在NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR成员
				如果存在则判断是否需要初始化object
			参数：
				const Address& _address 初始化的地址
				const Int32& _num 初始化的数量
		*/
		template<typename _CheckMemberObject, decltype(_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void newContainer(const Address& _address, const Int32& _num)
		{
			newContainerCallConstructor<_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_address, _num);
		}
		template<typename _CheckMemberObject>
		__forceinline const Void newContainer(...) {}
		//不调用构造函数
		template<Boolean _ifCallConstructor>
		__forceinline const Void newContainerCallConstructor(const Address& _address, const Int32& _num) {}
		//调用构造函数
		template<>
		__forceinline const Void newContainerCallConstructor<true>(const Address& _address, const Int32& _num)
		{
			new(_address) _Object[_num];
		}

		/*
			复制构造函数
			自动判断是否初始化object
			说明：
				判断类是否存在NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR成员
				如果存在则判断是否需要初始化object
			参数：
				const ZInstance& _container 初始化时复制的容器
		*/
		template<typename _CheckMemberObject, decltype(_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void newCopyContainer(const ZInstance& _container)
		{
			newCopyContainerCallConstructor<_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_container);
		}
		template<typename _CheckMemberObject>
		__forceinline const Void newCopyContainer(...) {}
		//不调用构造函数
		template<Boolean _ifCallConstructor>
		__forceinline const Void newCopyContainerCallConstructor(const ZInstance& _container) {
			memcpy((Address)(this->getObjectPtr()), (Address)(_container.getObjectPtr()), (UInt64)_container.getCapacity() * sizeof(_Object));
		}
		//调用构造函数
		template<>
		__forceinline const Void newCopyContainerCallConstructor<true>(const ZInstance& _container)
		{
			for (Int32 index = 0; index < _container.capacity; index++) {
				new((Address)(&((*this)(index)))) _Object(_container(index));
			}
		}

		/*
			复制函数
			容器object复制
			说明：
				判断类是否存在NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR成员
				如果存在则判断是否需要深度复制
			参数：
				const ZInstance& _container 复制的容器
		*/
		template<typename _CheckMemberObject, decltype(_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void copyContainer(const ZInstance& _container)
		{
			copyContainerCallConstructor<_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_container);
		}
		template<typename _CheckMemberObject>
		__forceinline const Void copyContainer(...) {}
		//不调用复制函数
		template<Boolean _ifCallConstructor>
		__forceinline const Void copyContainerCallConstructor(const ZInstance& _container)
		{
			memcpy((Address)(this->getObjectPtr()), (Address)(_container.getObjectPtr()), (UInt64)_container.getCapacity() * sizeof(_Object));
		}
		//调用复制函数
		template<>
		const Void copyContainerCallConstructor<true>(const ZInstance& _container)
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
					new((Address) & (*this)(index)) _Object(_container(index));
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
				const ZInstance& _container 析构的容器
		*/
		template<typename _CheckMemberObject, decltype(_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void freeContainer()
		{
			freeContainerCallDestructor<_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>();
		}
		template<typename _CheckMemberObject>
		__forceinline const Void freeContainer(...) {}
		//不调用析构函数
		template<Boolean _ifCallDestructor>
		__forceinline const Void freeContainerCallDestructor() {}
		//调用析构函数
		template<>
		const Void freeContainerCallDestructor<true>()
		{
			for (Int32 index = 0; index < this->capacity; index++) {
				(*this)(index).~_Object();
			}
		}


	private:
		//内存块指针
		ZMemoryPiece* memoryPiecePtr;
		//容器的大小
		Int32 capacity;
		//容器的object数量
		Int32 size;
	};

	/*
		构造函数
	*/
	template<typename _Object>
	__forceinline ZInstance<_Object>::ZInstance() :
		ZObject(),
		capacity(DEFAULT_CAPACITY),
		size(0)
	{
		//计算申请空间的大小
		ZMemoryPiece::MemoryPieceSizeType memorySize = DEFAULT_CAPACITY * sizeof(_Object);
		//申请内存
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
		//申请成功则在指定地址上new该对象或数据（如果需要的话）,并保存到容器指针上		
		newContainer<_Object>(memoryPiecePtr->memoryAddress, DEFAULT_CAPACITY);
	}


	/*
		构造函数
		多object容器初始化
		参数：
			const Int32& _capacity 容器大小
	*/
	template<typename _Object>
	__forceinline ZInstance<_Object>::ZInstance(const Int32& _capacity) :
		ZObject(),
		capacity(_capacity),
		size(0)
	{
		//计算申请空间的大小
		ZMemoryPiece::MemoryPieceSizeType memorySize = _capacity * sizeof(_Object);
		//申请内存
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
		//申请成功则在指定地址上new该对象或数据（如果需要的话）,并保存到容器指针上		
		newContainer<_Object>(memoryPiecePtr->memoryAddress, _capacity);
	}

	/*
		构造函数
		深度复制
		参数：
			const ZInstance& _container 被复制的容器
	*/
	template<typename _Object>
	__forceinline ZInstance<_Object>::ZInstance(const ZInstance& _container) :
		ZObject(_container),
		capacity(_container.capacity),
		size(_container.size)
	{
		//计算申请空间的大小
		ZMemoryPiece::MemoryPieceSizeType memorySize = capacity * sizeof(_Object);
		//申请内存
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
		//申请成功则在指定地址上new该对象或数据（如果需要的话）,并保存到容器指针上		
		newCopyContainer<_Object>(_container);
	}

	/*
		构造函数
		移动语义
		参数：
			const ZInstance&& _container 被移动的容器
	*/
	template<typename _Object>
	__forceinline ZInstance<_Object>::ZInstance(const ZInstance&& _container) :
		ZObject(std::forward<ZInstance>(_container)),
		memoryPiecePtr(_container.memoryPiecePtr),
		capacity(_container.capacity),
		size(_container.size)
	{
		//防止内存块被释放两次
		_container.memoryPiecePtr = nullptr;
	}

	/*
		析构函数
	*/
	template<typename _Object>
	__forceinline ZInstance<_Object>::~ZInstance()
	{
		//释放object
		freeContainer<_Object>();
		//释放内存
		ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
	}



	/*
		重载=
		深度复制
		参数：
			const ZInstance& _container 被复制的容器
	*/
	template<typename _Object>
	__forceinline const Void ZInstance<_Object>::operator=(const ZInstance& _container)
	{
		ZObject::operator=(_container);

		//容器需要的内存大小
		ZMemoryPiece::MemoryPieceSizeType memorySize = _container.capacity * sizeof(_Object);

		//判断当前内存块是否不够大
		if (memorySize > memoryPiecePtr->size) {
			//向内存池申请内存
			ZMemoryPiece* tempMemoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
			//将当前内存块保存的数据转化到临时内存快上
			memcpy(tempMemoryPiecePtr->memoryAddress, memoryPiecePtr->memoryAddress, capacity * sizeof(_Object));
			//释放当前内存块
			ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
			//修改当前容器的内存块
			memoryPiecePtr = tempMemoryPiecePtr;
		}
		//复制object
		copyContainer<_Object>(_container);
		capacity = _container.capacity;
		size = _container.size;


	}

	/*
		重载=
		移动语义
		参数：
			const ZInstance&& _container 被移动的容器
	*/
	template<typename _Object>
	__forceinline const Void ZInstance<_Object>::operator=(const ZInstance&& _container)
	{
		ZObject::operator=(std::forward<ZInstance>(_container));
		memoryPiecePtr = _container.memoryPiecePtr;
		capacity = _container.capacity;
		size = _container.size;
		//防止内存块被释放两次
		_container.memoryPiecePtr = nullptr;
	}

	/*
		重载（）
		获取容器object的引用
		参数：
			const Int32& _index object下标
		返回：
			_Object& object的引用
	*/
	template<typename _Object>
	__forceinline _Object& ZInstance<_Object>::operator()(const Int32& _index)
	{
		return getObjectPtr()[_index];
	}

	/*
		重载（）
		获取容器object的引用
		参数：
			const Int32& _index object下标
		返回：
			const _Object& object的引用
	*/
	template<typename _Object>
	__forceinline const _Object& ZInstance<_Object>::operator()(const Int32& _index) const
	{
		return getObjectPtr()[_index];
	}


	/*
		获取容器存储指针
		返回：
			_Object* 容器存储指针
	*/
	template<typename _Object>
	__forceinline _Object* ZInstance<_Object>::getObjectPtr()
	{
		return (_Object*)memoryPiecePtr->memoryAddress;
	}

	/*
		获取容器存储指针
		返回：
			const _Object* 容器存储指针
	*/
	template<typename _Object>
	__forceinline const _Object* ZInstance<_Object>::getObjectPtr() const
	{
		return (_Object*)memoryPiecePtr->memoryAddress;
	}

	/*
		获取容器大小
		返回：
			const Int32& 容器大小
	*/
	template<typename _Object>
	__forceinline const Int32& ZInstance<_Object>::getCapacity() const
	{
		return capacity;
	}

	/*
		获取容器object数量
		返回：
			const Int32& 容器object数量
	*/
	template<typename _Object>
	__forceinline const Int32& ZInstance<_Object>::getSize() const
	{
		return size;
	}

	/*
		设置object数量
		会判断是否需要拓展空间
		参数：
			const Int32& 容器object数量
	*/
	template<typename _Object>
	__forceinline const Void ZInstance<_Object>::setSize(const Int32& _size)
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
			const Int32& _offset 偏差值
	*/
	template<typename _Object>
	__forceinline const Void ZInstance<_Object>::changeSize(const Int32& _offset) {
		size += _offset;
		//如果object过多，则自动拓展容器
		if (size > capacity) {
			autoExtend();
		}
	}

	/*
		清空容器
	*/
	template<typename _Object>
	__forceinline const Void ZInstance<_Object>::clear()
	{
		this->size = 0;
	}

	/*
		容器拓展函数
		参数：
			const Int32& _capacity 扩展后容器大小
	*/
	template<typename _Object>
	const Void ZInstance<_Object>::extend(const Int32& _capacity) noexcept
	{
		//拓展前容器需要的内存大小
		ZMemoryPiece::MemoryPieceSizeType originMemorySize = capacity * sizeof(_Object);
		//拓展后容器需要的内存大小
		ZMemoryPiece::MemoryPieceSizeType currentMemorySize = _capacity * sizeof(_Object);
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
		newContainer<_Object>((Address)(((UIntAddress)(memoryPiecePtr->memoryAddress)) + originMemorySize), currentMemorySize - originMemorySize);
		//修改容器大小
		capacity = _capacity;
	}

	/*
		容器自动拓展函数
	*/
	template<typename _Object>
	const Void ZInstance<_Object>::autoExtend() noexcept {
		Float32 tempCapacity = (Float32)capacity;
		do {
			tempCapacity *= AUTO_EXTEND_MUL_FACTOR;
		} while (tempCapacity < this->size);
		extend((Int32)tempCapacity);
	}

}


#endif // !ZInstance_h
