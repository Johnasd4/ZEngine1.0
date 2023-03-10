#ifndef ZMemoryPiecePool_h
#define ZMemoryPiecePool_h

#include"ZBasicDrive.h"
#include"ZPoolBase.h"
#include"ZMemoryPiece.h"
#include"ZSystemMemoryController.h"
#include"..\ZMutex.h"
namespace ZEngine
{

	namespace Private
	{


		/*
			池类链表基
			typename _ObjectType 节点类型
			Int32 _objectOffset 节点类型实际使用的地址偏移量
			Boolean _threadSafe 是否线程安全
		*/
		template<Int32 Memory, Boolean _threadSafe>
		class ZSmallMemoryPiecePool :public ZPoolBase<ZMemoryPiece, sizeof(ZMemoryPiece), _threadSafe>
		{



		protected:

			/*
				构造函数，空池子
			*/
			__forceinline ZSmallMemoryPiecePool();

			/*
				构造函数
				参数：
					const Int32 _capacity 池子初始object数量
			*/
			__forceinline ZSmallMemoryPiecePool(const Int32 _capacity);

			/*
				析构函数
			*/
			__forceinline ~ZSmallMemoryPiecePool();


			/*
				拓展函数
				初始化一个数组
				需要修改：
					Node<_ObjectType>* headNodePtr 池内剩余object链表指针
					Int32 capacity 池内object总数
				参数：
					const Int32 _num 添加的数量
			*/
			virtual const Void extend(const Int32 _num);

		private:

			

		};

		/*
			构造函数，空池子
		*/
		template<Boolean _threadSafe>
		__forceinline ZSmallMemoryPiecePool<_threadSafe>::ZSmallMemoryPiecePool() :
			ZPoolBase<ZSmallMemoryPiece, sizeof(ZSmallMemoryPiece), _threadSafe>()
		{}

		/*
			构造函数
			参数：
				const Int32& _capacity 池子初始object数量
		*/
		template<Boolean _threadSafe>
		__forceinline ZSmallMemoryPiecePool<_threadSafe>::ZSmallMemoryPiecePool(const Int32 _capacity) :
			ZPoolBase<ZSmallMemoryPiece, sizeof(ZSmallMemoryPiece), _threadSafe>(_capacity)
		{}

		/*
			析构函数
		*/
		template<Boolean _threadSafe>
		__forceinline ZSmallMemoryPiecePool<_threadSafe>::~ZSmallMemoryPiecePool()
		{}

		/*
			拓展函数
			初始化一个数组
			需要修改：
				Node<_ObjectType>* headNodePtr 池内剩余object链表指针
				Int32 capacity 池内object总数
			参数：
				const Int32 _num 添加的数量
		*/
		template<Boolean _threadSafe>
		const Void ZSmallMemoryPiecePool<_threadSafe>::extend(const Int32 _num)
		{
			
		}

	}
}

#endif // !ZMemoryPiecePool_h
