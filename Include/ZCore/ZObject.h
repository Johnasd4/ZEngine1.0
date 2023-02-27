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

		/*
			向内存池申请内存
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


	private:

		//作为容器元素时是否调用构造函数
		static constexpr Boolean ContainerElementIfCallConstructor = false;

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
		if (memoryPiecePtr != nullptr) {
			ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
		}
	}



}


#endif // !ZObject_h
