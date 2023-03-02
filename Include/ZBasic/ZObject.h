#ifndef ZObject_h
#define ZObject_h


#include"ZBasicDrive.h"


namespace ZEngine {


	/*
		Object类
		说明：
			该类为所有类的基类

	*/
	class ZObject {

	public:

		/*
			构造函数
		*/
		__forceinline ZObject();

		/*
			构造函数
			完全复制
			参数：
				const ZObject& _object 被复制的object
		*/
		__forceinline ZObject(const ZObject& _object);

		/*
			构造函数
			移动语义
			参数：
				const ZObject&& _object 被移动的object
		*/
		__forceinline ZObject(const ZObject&& _object);

		/*
			析构函数
		*/
		__forceinline ~ZObject();


	public:

		//作为容器对象时是否调用构造函数
		constexpr static Boolean ContainerElementIfCallConstructor = false;


	};

	/*
		构造函数
	*/
	__forceinline ZObject::ZObject(){}

	/*
		构造函数
		完全复制
		参数：
			const ZObject& _object 被复制的object
	*/
	__forceinline ZObject::ZObject(const ZObject& _object) {}

	/*
		构造函数
		移动语义
		参数：
			const ZObject&& _object 被移动的object
	*/
	__forceinline ZObject::ZObject(const ZObject&& _object) {}

	/*
		析构函数
	*/
	__forceinline ZObject::~ZObject(){}



}


#endif // !ZObject_h
