#ifndef ZObjectPointer_h
#define ZObjectPointer_h

#pragma warning(disable : 26439)

#include"ZBasicDrive.h"

#include"ZMemoryPool.h"



namespace ZEngine 
{


	/*
		ObjectPointer类
		说明：
			Object通过new创建出来的指针对象。
	*/
	template<typename _Object>
	class ObjectPointer 
	{
	public:

		/*
			构造函数
		*/
		__forceinline ObjectPointer();

		/*
			重构符号*
			返回：
				_Object& 对象的引用
		*/
		__forceinline _Object& operator*();

		/*
			重构符号*
			返回：
				const _Object& 对象的引用
		*/
		__forceinline const _Object& operator*() const;

		/*
			重构符号=
			参数：
				const _Object* _objectPtr 被复制的地址
		*/
		__forceinline const Void operator=(const _Object* _objectPtr);

		/*
			重构符号==
			参数：
				const ObjectPointer& _objectPtr 物体指针
			返回：
				const _Object& 对象的引用
		*/
		__forceinline Boolean operator==(const ObjectPointer& _objectPtr) const;


		/*
			构造函数
		*/
		__forceinline ~ObjectPointer();


	private:

		//内存块指针
		ZMemoryPiece* memoryPiecePtr;


	};





}



#endif // !ZObjectPointer_h
