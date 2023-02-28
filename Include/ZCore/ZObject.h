#ifndef ZObject_h
#define ZObject_h


#include"ZCoreDependence.h"


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
	__forceinline ZObject::ZObject() {}



	/*
		析构函数
	*/
	__forceinline ZObject::~ZObject(){}



}


#endif // !ZObject_h
