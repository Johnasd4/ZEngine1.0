#ifndef ZMemoryPiecePool_h
#define ZMemoryPiecePool_h

#include"ZBasicDrive.h"
#include"ZPoolBase.h"
#include"ZMemoryPiece.h"
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
		template<Boolean _threadSafe>
		class ZSmallMemoryPiecePool :ZPoolBase < ZSmallMemoryPiece, sizeof(ZSmallMemoryPiece), _threadSafe>
		{




		protected:

			/*
				节点类型
			*/
			template<typename _ObjectType>
			struct Node
			{
				//下一个object地址
				Node* nextNodePtr;
				//存储的object
				_ObjectType object;

			};

		protected:

			/*
				构造函数，空池子
			*/
			__forceinline ZPoolBase();

			/*
				构造函数
				参数：
					const Int32 _capacity 池子初始object数量

			*/
			__forceinline ZPoolBase(const Int32 _capacity);

			/*
				析构函数
			*/
			__forceinline ~ZPoolBase();


			/*
				拓展函数
				初始化一个数组
				需要修改：
					Node<_ObjectType>* headNodePtr 池内剩余object链表指针
					Int32 capacity 池内object总数
				参数：
					const Int32 _num 添加的数量
				返回：

			*/
			virtual const Void extend(const Int32 _objectNum) = 0;


		private:

			/*
				自动拓展函数
			*/
			__forceinline const Void autoExtend();


		protected:

		private:

			//节点头到object使用位置的偏移量
			static constexpr Int32 OBJECT_BODY_OFFSET = sizeof(Node*) + _objectHeadOffset;

			//链表头
			Node<_ObjectType>* headNodePtr;
			//池内object总数
			Int32 capacity;

		};

		/*
			申请object
			参数：
				Address* _addressPtr 申请object的指针的指针
		*/
		template<typename _ObjectType, Int32 _objectHeadOffset, Boolean _threadSafe>
		const Void ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::applyObject(Address* _addressPtr)
		{
			if (headNodePtr == nullptr)
			{
				autoExtend();
			}
			*_addressPtr = (Address)((SizeT)headNodePtr + OBJECT_BODY_OFFSET);
			headNodePtr = headNodePtr->nextNodePtr;
		}

		/*
			释放object
			参数：
				Address* _addressPtr 需要释放object的指针的指针
		*/
		template<typename _ObjectType, Int32 _objectHeadOffset, Boolean _threadSafe>
		const Void ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::releaseObject(Address* _addressPtr)
		{
			if (*_addressPtr == nullptr)
			{
				return;
			}
			register Node<_ObjectType>* nodeAddress = (Node<_ObjectType>*)((SizeT)(*_addressPtr) - OBJECT_BODY_OFFSET);
			nodeAddress->nextNodePtr = headNodePtr;
			headNodePtr = nodeAddress;
			*_addressPtr = nullptr;
		}

		/*
			构造函数，空池子
		*/
		template<typename _ObjectType, Int32 _objectHeadOffset, Boolean _threadSafe>
		__forceinline ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::ZPoolBase() :
			headNodePtr(nullptr),
			capacity(0)
		{}

		/*
			构造函数
			参数：
				const Int32& _capacity 池子初始object数量

		*/
		template<typename _ObjectType, Int32 _objectHeadOffset, Boolean _threadSafe>
		__forceinline ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::ZPoolBase(const Int32 _capacity)
		{
			extend(_capacity);
		}

		/*
			析构函数
		*/
		template<typename _ObjectType, Int32 _objectHeadOffset, Boolean _threadSafe>
		__forceinline ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::~ZPoolBase()
		{}

		/*
			自动拓展函数
		*/
		template<typename _ObjectType, Int32 _objectHeadOffset, Boolean _threadSafe>
		__forceinline const Void ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::autoExtend()
		{
			extend(capacity * AUTO_EXTEND_MUL_FACTOR);
		}

	}
}

#endif // !ZMemoryPiecePool_h
