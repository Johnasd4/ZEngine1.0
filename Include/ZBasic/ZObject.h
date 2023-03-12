#ifndef ZObject_h
#define ZObject_h

#pragma warning(disable : 26439)

#include"Private/ZBasicDrive.h"



namespace ZEngine 
{





	/*
		Object类
		说明：
			该类为所有类的基类
	*/
	class ZObject 
	{

	public:

		//初始化和释放时是否需要调用构造函数和析构函数
		static constexpr Boolean NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR = false;

	protected:

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
				ZObject&& _object 被移动的object
		*/
		__forceinline ZObject(ZObject&& _object);

		/*
			析构函数
		*/
		__forceinline ~ZObject();

		/*
			重载=
			深度复制
			参数：
				const ZObject& _object 被复制的object
		*/
		__forceinline const Void operator=(const ZObject& _object);

		/*
			重载=
			浅度复制
			参数：
				ZObject&& _object 被复制的object
		*/
		__forceinline const Void operator=(ZObject&& _object);

	private:

		/*
			移动语义摧毁容器
			会将所有容器属性清空而不进行任何操作
			不会归还内存，仅用于移动语义
		*/
		__forceinline const Void move_destroy();


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
			ZObject&& _object 被移动的object
	*/
	__forceinline ZObject::ZObject(ZObject&& _object)
	{
		_object.move_destroy();
	}

	/*
		析构函数
	*/
	__forceinline ZObject::~ZObject(){}

	/*
		重载=
		深度复制
		参数：
			const ZObject& _object 被复制的object
	*/
	__forceinline const Void ZObject::operator=(const ZObject& _object){}

	/*
		重载=
		浅度复制
		参数：
			ZObject&& _object 被复制的object
	*/
	__forceinline const Void ZObject::operator=(ZObject&& _object)
	{
		_object.move_destroy();
	}

	/*
		移动语义摧毁容器
		会将所有容器属性清空而不进行任何操作
		不会归还内存，仅用于移动语义
	*/
	__forceinline const Void ZObject::move_destroy() {}

}


#endif // !ZObject_h
