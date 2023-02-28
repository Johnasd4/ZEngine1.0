#ifndef ZContainer_h
#define ZContainer_h


#include"ZCoreDependence.h"
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
	class ZContainer: ZObject{

	protected:

		/*
			构造函数
			多元素容器初始化
			参数：
				_ObjectType** _objectPtrPtr 容器指针的指针
				const Int32& _size 容器大小
				const Boolean&& _containerElementIfCallConstructor = false 默认不调用构造函数
		*/
		template<typename _ObjectType>
		__forceinline ZContainer(_ObjectType** _objectPtrPtr, const Int32& _size, const Boolean&& _containerElementIfCallConstructor = false);

		/*
			析构函数
		*/
		__forceinline ~ZContainer();


		/*
			多元素容器拓展函数
			参数：
				const Int32& _originSize 原先容器大小
				const Int32& _currentSize 扩展后容器大小
				const Boolean&& _containerElementIfCallConstructor = false 默认不调用构造函数
		*
		template<typename _ObjectType>
		_ObjectType* extend(const Int32& _originSize, const Int32& _currentSize, const Boolean&& _containerElementIfCallConstructor = false) {

			//扩增前的大小
			UInt64 oldObjectSize = _oldObjectNum * sizeof(_ObjectType);
			//扩增后的大小
			UInt64 newObjectSize = _newObjectNum * sizeof(_ObjectType);
			//需要扩增的大小
			UInt64 addObjectSize = newObjectSize - oldObjectSize;

			//如果当前的内存长度不足以支撑拓展object
			if (this->size < newObjectSize) {

				//临时object用来获取内存，防止获取失败后还删除原有object
				Object tempObject;

				//判断内存池是否存在，不存在直接向操作系统申请内存
				if (Core::MemoryPool::CurrentMemoryPoolPointer == nullptr) {
					//申请失败则返回
					IfFalseReturnFalse(applyMemoryFromSystem(&tempObject, newObjectSize), ErrorMessage::OBJECT_APPLY_MEMORY_FROM_SYETEM_FAILED_MESSAGE);
				}
				//向内存池申请内存
				else {
					//申请失败则向操作系统申请内存
					if (applyMemoryFromMemoryPool(&tempObject, newObjectSize) == false) {
						//ErrorMessageOutput(ErrorMessage::OBJECT_APPLY_MEMORY_FROM_MEMORY_POOL_FAILED_MESSAGE);
						IfFalseReturnFalse(applyMemoryFromSystem(&tempObject, newObjectSize), ErrorMessage::OBJECT_APPLY_MEMORY_FROM_SYETEM_FAILED_MESSAGE);

					}
				}

				//将子类的地址指针指向新的地址
				*_objectPointerPointer = (_ObjectType*)tempObject.objectAddress;
				//将当前object保存的数据转化到临时object上
				memcpy(tempObject.objectAddress, this->objectAddress, oldObjectSize);
				//释放当前的object占用的内存
				destroy();
				//将临时object转化为当前object
				memcpy(this, &tempObject, sizeof(Object));
				//防止销毁临时对象时释放内存
				tempObject.objectAddress = nullptr;
			}

			//如果需要初始化拓展内存
			if (_ifInitialElement == true) {
				//在拓展空间位置上调用构造函数初始化内存
				//for (Int32 objectCount = 0; objectCount < newObjectNum - oldObjectNum; objectCount++) {
				new((Address)(((UInt64)*_objectPointerPointer) + oldObjectSize)) _ObjectType[_newObjectNum - _oldObjectNum];
				//}
			}

			return true;
		}
		*/

	private:

		//内存块指针
		ZMemoryPiece* memoryPiecePtr;

	};

	/*
		构造函数
		多元素容器初始化
		参数：
			_ObjectType** _objectPtrPtr 容器指针的指针
			const Int32& _size 容器大小
			const Boolean&& _containerElementIfCallConstructor = false 默认不调用构造函数
	*/
	template<typename _ObjectType>
	__forceinline ZContainer::ZContainer(_ObjectType** _objectPtrPtr, const Int32& _size, const Boolean&& _containerElementIfCallConstructor) {
		//计算申请空间的大小
		ZMemoryPool::MemoryPieceSizeType applyMemorySize = _size * sizeof(_ObjectType);
		//申请内存
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(applyMemorySize);
		//申请成功则在指定地址上new该对象或数据（如果需要的话）,并保存到容器指针上
		*_objectPtrPtr = _containerElementIfCallConstructor ? new(memoryPiecePtr->memoryAddress) _ObjectType[_size] : (_ObjectType*)memoryPiecePtr->memoryAddress;
	}

	/*
		析构函数
	*/
	__forceinline ZContainer::~ZContainer() {
		//释放内存
		if (memoryPiecePtr != nullptr) {
			ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
		}
	}



}


#endif // !ZContainer_h
