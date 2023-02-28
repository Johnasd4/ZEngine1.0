#ifndef ZContainer_h
#define ZContainer_h

#include"ZObject.h"
#include"ZMemoryPool.h"

namespace ZEngine {


	/*
		ZContainer类
		说明：
			该类为容器基类，所有容器继承自该类
			需要拓展容器对象时使用extend函数。
			析构函数中会自动释放内存。
	*/
	template<typename _ObjectType>
	class ZContainer: ZObject{

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
				_ObjectType** _objectPtrPtr 容器地址指针
				const Int32& _size 容器大小
				const Boolean&& _containerElementIfCallConstructor = false 默认不调用构造函数
		*/
		
		__forceinline ZContainer(_ObjectType** _objectPtrPtr, const Int32& _size, const Boolean&& _containerElementIfCallConstructor = false);

		/*
			析构函数
		*/
		__forceinline ~ZContainer();


		/*
			多元素容器拓展函数
			参数：
				_ObjectType** _objectPtrPtr 容器地址指针
				const Int32& _originSize 原先容器大小
				const Int32& _currentSize 扩展后容器大小
				const Boolean&& _containerElementIfCallConstructor = false 默认不调用构造函数
		*/
		const Void extend(_ObjectType** _objectPtrPtr, const Int32& _originSize, const Int32& _currentSize, const Boolean&& _containerElementIfCallConstructor = false);

		_ObjectType* getObjectPtr() const;
		const Int32& getSize();

	private:
		//内存块指针
		ZMemoryPiece* memoryPiecePtr;

		//容器的大小
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
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(sizeof(_ObjectType));
		//申请成功则在指定地址上new该对象或数据（如果需要的话）,并保存到容器指针上
		*_objectPtrPtr = new(memoryPiecePtr->memoryAddress) _ObjectType(std::forward<Args>(args)...);
	}



	/*
		构造函数
		多元素容器初始化
		参数：
			_ObjectType** _objectPtrPtr 容器地址指针
			const Int32& _size 容器大小
			const Boolean&& _containerElementIfCallConstructor = false 默认不调用构造函数
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::ZContainer(_ObjectType** _objectPtrPtr, const Int32& _size, const Boolean&& _containerElementIfCallConstructor) {
		//计算申请空间的大小
		ZMemoryPiece::MemoryPieceSizeType memorySize = _size * sizeof(_ObjectType);
		//申请内存
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
		//申请成功则在指定地址上new该对象或数据（如果需要的话）,并保存到容器指针上
		*_objectPtrPtr = _containerElementIfCallConstructor ? new(memoryPiecePtr->memoryAddress) _ObjectType[_size] : (_ObjectType*)memoryPiecePtr->memoryAddress;
	}

	/*
		析构函数
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::~ZContainer() {
		//释放内存
		ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
	}

	/*
		多元素容器拓展函数
		参数：
			_ObjectType** _objectPtrPtr 容器地址指针
			const Int32& _originSize 原先容器大小
			const Int32& _currentSize 扩展后容器大小
			const Boolean&& _containerElementIfCallConstructor = false 默认不调用构造函数
	*/
	template<typename _ObjectType>
	const Void ZContainer<_ObjectType>::extend(_ObjectType** _objectPtrPtr, const Int32& _originSize, const Int32& _currentSize, const Boolean&& _containerElementIfCallConstructor) {

		//拓展前容器需要的内存大小
		ZMemoryPiece::MemoryPieceSizeType originMemorySize = _originSize * sizeof(_ObjectType);
		//拓展后容器需要的内存大小
		ZMemoryPiece::MemoryPieceSizeType currentMemorySize = _currentSize * sizeof(_ObjectType);
		//判断当前内存块是否不够大
		if (_currentSize * sizeof(_ObjectType) > memoryPiecePtr->size) {
			//向内存池申请内存
			ZMemoryPiece* tempMemoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(currentMemorySize);
			//将当前内存块保存的数据转化到临时内存快上
			memcpy(tempMemoryPiecePtr->memoryAddress, (Address)_objectPtrPtr, originMemorySize);
			//释放当前内存块
			ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
			//将新的容器地址赋予容器地址指针
			*_objectPtrPtr = (_ObjectType*)tempMemoryPiecePtr->memoryAddress;
			//修改当前容器的内存块
			memoryPiecePtr = tempMemoryPiecePtr;
		}
		//如果需要初始化拓展内存
		if (_containerElementIfCallConstructor) {
			//在拓展的位置上调用构造函数初始化内存
			new((Address)(((UIntAddress)(*_objectPtrPtr)) + originMemorySize)) _ObjectType[currentMemorySize - originMemorySize];
		}
	}

}


#endif // !ZContainer_h
