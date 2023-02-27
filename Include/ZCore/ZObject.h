#ifndef ZObject_h
#define ZObject_h


#include"ZCoreDependence.h"
#include"ZMemoryPool.h"

namespace ZEngine {


	/*
		Object类
		说明：
			该类为基类，所有要使用内存池的类都需要继承自该类
			申请内存池空间的函数的关键词是create，释放空间的函数的关键词是destroy
			析构函数中会自动释放多余的空间

	*/
	class ZObject {

	private:

		//指向所在内存块的指针
		ZMemoryPiece* piecePtr;

	protected:

		/*
			构造函数
		*/
		__forceinline ZObject();

		/*
			析构函数
		*/
		__forceinline ~ZObject();




		/*
			向内存池申请内存（如果使用内存池的话），如果失败则直接向操作系统申请内存
			模板类中填写需要申请内存的指针类型，例如A类中有个CChar*成员变量需要申请内存，则填写CChar
			参数：
				ObjectType** _objectPointerPointer 申请空间地址指针
				const Int32& _objectNum 申请的该数据类型或类的对象的数量
				const Boolean& _ifInitialElement 是否在申请的地址上根据Object的数量进行new操作
			返回：
				const Boolean 是否成功
		*/
		template<typename _ObjectType>
		const Boolean create(_ObjectType** _objectPointerPointer, const Int32& _objectNum, const Boolean& _ifInitialElement);




		/*
			向内存池拓展内存（如果使用内存池的话），如果失败则直接向操作系统申请内存
			模板类中填写需要申请内存的指针类型，例如A类中有个CChar*成员变量需要申请内存，则填写CChar
			参数：
				ObjectType** _objectPointerPointer 申请空间地址指针
				const Int32& _oldObjectNum 拓展该数据类型或类的对象的团战前的总数量
				const Int32& _newObjectNum 拓展该数据类型或类的对象的团战后的总数量
				const Boolean& _ifInitialElement 是否在拓展的地址上根据Object的数量进行new操作
			返回：
				const Boolean 是否成功
		*/
		template<typename _ObjectType>
		const Boolean extend(_ObjectType** _objectPointerPointer, const Int32& _oldObjectNum, const Int32& _newObjectNum, const Boolean& _ifInitialElement);




		/*
			释放内存，自动判断释放给内存池或者操作系统
			返回：
				const ErrorIndex 错误编号
		*/
		const Void destroy();


		/*
			获取object的地址
			返回：
				const Address object的地址
		*/
		__forceinline const Address& getObjectAddress();


	private:



		/*
			向内存池申请内存，如果失败则直接向操作系统申请内存
			参数：
				Object* _objectPointer 申请空间地址指针
				const UInt64& _applyMemorySize 申请的内存大小
			返回：
				const Boolean 是否成功
		*/
		__forceinline const Boolean applyMemoryFromMemoryPool(ZObject* _objectPointer, const UInt64& _applyMemorySize);

		/*
			释放内存，自动判断释放给内存池或者操作系统
			返回：
				const Boolean 是否成功
		*/
		__forceinline const Boolean releaseMemoryToMemoryPool();


		/*
			向操作系统申请内存
			参数：
				Object* _objectPointer 申请空间地址指针
				const UInt64& _applyMemorySize 申请的内存大小
			返回：
				const Boolean 是否成功
		*/
		__forceinline const Boolean applyMemoryFromSystem(ZObject* _objectPointer, const UInt64& _applyMemorySize);

		/*
			向操作系统释放内存
			返回：
				const Boolean 是否成功
		*/
		__forceinline const Boolean releaseMemoryToSystem();

	};

	/*
		构造函数
	*/
	__forceinline ZObject::ZObject() :
		piecePtr(nullptr),
		objectAddress(nullptr),
		size(0ULL)
	{
	}

	/*
		析构函数
	*/
	__forceinline ZObject::~ZObject()
	{
		if (this->objectAddress != nullptr) {
			destroy();
		}
	}


	/*
		向内存池申请内存（如果使用内存池的话），如果失败则直接向操作系统申请内存
		模板类中填写需要申请内存的指针类型，例如A类中有个CChar*成员变量需要申请内存，则填写CChar
		参数：
			ObjectType** _objectPointerPointer 申请空间地址指针
			const Int32& _objectNum 申请的该数据类型或类的对象的数量
			const Boolean& _ifInitialElement 是否在申请的地址上根据Object的数量进行new操作
		返回：
			const Boolean 是否成功
	*/
	template<typename _ObjectType>
	const Boolean ZObject::create(_ObjectType** _objectPointerPointer, const Int32& _objectNum, const Boolean& _ifInitialElement) {

		//计算申请空间的大小
		UInt64 objectSize = _objectNum * sizeof(_ObjectType);

		/*申请内存*/

		//如果当前的内存长度不足以支撑创建新的object
		if (this->size < objectSize) {

			//临时object用来获取内存，防止获取失败后还删除原有object
			ZObject tempObject;

			//判断内存池是否存在，不存在直接向操作系统申请内存
			if (ZEngine::MemoryPool::CurrentMemoryPoolPointer == nullptr) {
				//申请失败则返回错误编号
				IfFalseReturnFalse(applyMemoryFromSystem(&tempObject, objectSize), ErrorMessage::OBJECT_APPLY_MEMORY_FROM_SYETEM_FAILED_MESSAGE);
			}
			//向内存池申请内存
			else {
				//申请失败则向操作系统申请内存
				if (applyMemoryFromMemoryPool(&tempObject, objectSize) == false) {
					//ErrorMessageOutput(ErrorMessage::OBJECT_APPLY_MEMORY_FROM_MEMORY_POOL_FAILED_MESSAGE);
					IfFalseReturnFalse(applyMemoryFromSystem(&tempObject, objectSize), ErrorMessage::OBJECT_APPLY_MEMORY_FROM_SYETEM_FAILED_MESSAGE);
				}
			}

			//释放当前的object占用的内存
			destroy();
			//将临时object转化为当前object
			memcpy(this, &tempObject, sizeof(ZObject));
			//防止销毁临时对象时释放内存
			tempObject.objectAddress = nullptr;
		}


		//申请成功则在指定地址上new该对象或数据（如果需要的话）
		*_objectPointerPointer = _ifInitialElement ? new(this->objectAddress) _ObjectType[_objectNum] : (_ObjectType*)this->objectAddress;

		return true;
	}



	/*
		向内存池拓展内存（如果使用内存池的话），如果失败则直接向操作系统申请内存
		模板类中填写需要申请内存的指针类型，例如A类中有个CChar*成员变量需要申请内存，则填写CChar
		参数：
			ObjectType** _objectPointerPointer 申请空间地址指针
			const Int32& _oldObjectNum 拓展该数据类型或类的对象的团战前的总数量
			const Int32& _newObjectNum 拓展该数据类型或类的对象的团战后的总数量
			const Boolean& _ifInitialElement 是否在拓展的地址上根据Object的数量进行new操作
		返回：
			const Boolean 是否成功
	*/
	template<typename _ObjectType>
	const Boolean ZObject::extend(_ObjectType** _objectPointerPointer, const Int32& _oldObjectNum, const Int32& _newObjectNum, const Boolean& _ifInitialElement) {


		//判断拓展大小是否为非正数
		if (_newObjectNum <= _oldObjectNum) {
			return true;
		}



		//判断当前object是否存在,不存在则进行创建
		if (this->objectAddress == nullptr) {
			return this->create(_objectPointerPointer, _newObjectNum, _ifInitialElement);
		}

		//扩增前的大小
		UInt64 oldObjectSize = _oldObjectNum * sizeof(_ObjectType);
		//扩增后的大小
		UInt64 newObjectSize = _newObjectNum * sizeof(_ObjectType);
		//需要扩增的大小
		UInt64 addObjectSize = newObjectSize - oldObjectSize;

		//如果当前的内存长度不足以支撑拓展object
		if (this->size < newObjectSize) {

			//临时object用来获取内存，防止获取失败后还删除原有object
			ZObject tempObject;

			//判断内存池是否存在，不存在直接向操作系统申请内存
			if (ZEngine::MemoryPool::CurrentMemoryPoolPointer == nullptr) {
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
			memcpy(this, &tempObject, sizeof(ZObject));
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

	/*
		获取object的地址
		返回：
			const Address object的地址
	*/
	__forceinline const Address& ZObject::getObjectAddress() {
		return this->objectAddress;
	}


	/*
		向内存池申请内存，如果失败则直接向操作系统申请内存
		参数：
			Object* _objectPointer 申请空间地址指针
			const UInt64& _applyMemorySize 申请的内存大小
		返回：
			const Boolean 是否成功
	*/
	__forceinline const Boolean ZObject::applyMemoryFromMemoryPool(ZObject* _objectPointer, const UInt64& _applyMemorySize) {
		//判断是否已经从内存池申请过，申请过则继续使用原本内存池
		if (this->piecePtr == nullptr) {
			IfFalseReturnFalse(ZEngine::MemoryPool::CurrentMemoryPoolPointer->applyMemory(_objectPointer, _applyMemorySize), ErrorMessage::OBJECT_APPLY_MEMORY_FROM_MEMORY_POOL_FAILED_MESSAGE);
		}
		else {
			IfFalseReturnFalse(this->piecePtr->ownerMemoryPoolPointer->applyMemory(_objectPointer, _applyMemorySize), ErrorMessage::OBJECT_APPLY_MEMORY_FROM_MEMORY_POOL_FAILED_MESSAGE);
		}
		return true;
	}

	/*
		释放内存，自动判断释放给内存池或者操作系统
		返回：
			const Boolean 是否成功
	*/
	__forceinline const Boolean ZObject::releaseMemoryToMemoryPool() {
		return ZEngine::MemoryPool::CurrentMemoryPoolPointer->releaseMemory(this);
	}

	/*
		向操作系统申请内存
		参数：
			Object* _objectPointer 申请空间地址指针
			const UInt64& _applyMemorySize 申请的内存大小
		返回：
			const Boolean 是否成功
	*/
	__forceinline const Boolean ZObject::applyMemoryFromSystem(ZObject* _objectPointer, const UInt64& _applyMemorySize) {
		_objectPointer->objectAddress = malloc(_applyMemorySize);
		IfNullptrReturnFalse(_objectPointer->objectAddress, ErrorMessage::OBJECT_OUT_OF_MEMORY_MESSAGE);
		this->size = _applyMemorySize;
		return true;
	}

	/*
		向操作系统释放内存
		返回：
			const Boolean 错误编号
	*/
	__forceinline const Boolean ZObject::releaseMemoryToSystem() {
		free(this->objectAddress);
		return true;
	}



}


#endif // !ZObject_h
