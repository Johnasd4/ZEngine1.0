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


	public:

		/*
			构造函数
		*/
		__forceinline ZObject();

		/*
			构造函数
		*/
		__forceinline ZObject(const Int32& _size);

		/*
			析构函数
		*/
		__forceinline ~ZObject();


	private:

		//指向所在内存块的指针
		ZMemoryPiece* memoryPiecePtr;

	};

	/*
		构造函数
	*/
	__forceinline ZObject::ZObject() :
		memoryPiecePtr(nullptr) 
	{}

	/*
		构造函数
	*/
	__forceinline ZObject::ZObject(const Int32& _size) :
		memoryPiecePtr(ZMemoryPool::InstancePtr->applyMemory(_size))
	{}

	/*
		析构函数
	*/
	__forceinline ZObject::~ZObject()
	{
		//释放内存
		ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
	}



}


#endif // !ZObject_h
