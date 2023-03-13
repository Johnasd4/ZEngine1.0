#ifndef ZSmartPtr_h
#define ZSmartPtr_h

#include"Private/ZBasicDrive.h"

#include"ZMemoryPool.h"



namespace ZEngine
{
	//唯一指针
	template<typename _ObjectType>
	class ZUniquePtr;
	//共享指针
	template<typename _ObjectType>
	class ZSharedPtr;
	//弱指针
	template<typename _ObjectType>
	class ZWeakPtr;
	//共享引用
	template<typename _ObjectType>
	class ZSharedRef;


	namespace Private {


		

		/*
			智能指针所指向的实例
		*/
		template<typename _ObjectType>
		class ZSmartPtrInstance {

			friend class ZUniquePtr<_ObjectType>;
			friend class ZSharedPtr<_ObjectType>;
			friend class ZWeakPtr<_ObjectType>;
			//friend class ZSharedRef<_ObjectType>;


		private:

			/*
				构造函数
				参数：
					Args&&... args 
			*/
			template<typename... Args>
			__forceinline ZSmartPtrInstance(Args&&... args);

			/*
				析构函数
			*/
			__forceinline ~ZSmartPtrInstance();

			
							
			//智能指针友元
			friend class ZUniquePtr<_ObjectType>;
			friend class ZSharedPtr<_ObjectType>;
			friend class ZWeakPtr<_ObjectType>;
			friend class ZSharedRef<_ObjectType>;

		private:

			//内存块
			ZMemoryPiece* memoryPiecePtr;
			//强指针计数器
			Int32 usedCount;
			//弱指针计数器
			Int32 weakCount;

		};

		/*
			构造函数
			参数：
				Args&&... args
		*/
		template<typename _ObjectType>
		template<typename... Args>
		__forceinline ZSmartPtrInstance<_ObjectType>::ZSmartPtrInstance(Args&&... args) :
			usedCount(1),
			weakCount(1)
		{
			//向内存池申请内存
			memoryPiecePtr = ZMemoryPool::applyMemory(sizeof(_ObjectType));
			//初始化对象
			new(memoryPiecePtr->memoryAddress) _ObjectType(std::forward<Args>(args)...);
		}

		/*
			析构函数
		*/
		template<typename _ObjectType>
		__forceinline ZSmartPtrInstance<_ObjectType>::~ZSmartPtrInstance() 
		{
			//析构对象
			(_ObjectType*)memoryPiecePtr->memoryAddress->~_ObjectType();
			//归还内存碎片
			ZMemoryPool::releaseMemory(memoryPiecePtr);
		}


	}


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



#endif // !ZSmartPtr_h
