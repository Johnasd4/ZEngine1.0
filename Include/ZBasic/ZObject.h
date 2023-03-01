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
		__forceinline ZObject() noexcept;

		/*
			析构函数
		*/
		__forceinline ~ZObject() noexcept;


	public:

		//作为容器对象时是否调用构造函数
		constexpr static Boolean ContainerElementIfCallConstructor = false;


	};

	/*
		构造函数
	*/
	__forceinline ZObject::ZObject() noexcept{}



	/*
		析构函数
	*/
	__forceinline ZObject::~ZObject() noexcept{}



}


#endif // !ZObject_h
