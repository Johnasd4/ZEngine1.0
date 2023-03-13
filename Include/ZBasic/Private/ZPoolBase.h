#ifndef ZPoolBase_h
#define ZPoolBase_h

#include"ZBasicDrive.h"
#include"ZThreadSafe.h"

namespace ZEngine 
{

	namespace Private 
	{

		/*
			池类链表基
			typename _ObjectType 节点类型
			SizeT _objectOffset 节点类型实际使用的地址偏移量
			Boolean _threadSafe 是否线程安全
		*/
		template<typename _ObjectType, SizeT _objectHeadOffset, Boolean _threadSafe>
		class ZPoolBase :protected ZThreadSafe<_threadSafe>
		{

		private:

			//容器自动拓展空间的倍率
			static constexpr Float32 AUTO_EXTEND_MUL_FACTOR = 1.2F;


		public:

			/*
				申请object
				参数：
					Address* _addressPtr 申请object的指针的指针
			*/
			__forceinline const Void applyObject(Address* _addressPtr);

			/*
				释放object
				参数：
					Address* _addressPtr 需要释放object的指针的指针
			*/
			__forceinline const Void releaseObject(Address* _addressPtr);



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
			*/
			virtual const Void extend(const Int32 _num) = 0;


		private:

			/*
				自动拓展函数
			*/
			__forceinline const Void autoExtend();




		private:

			//节点头到object使用位置的偏移量
			static constexpr SizeT OBJECT_BODY_OFFSET = sizeof(Node*) + _objectHeadOffset;

		protected:

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
		template<typename _ObjectType, SizeT _objectHeadOffset, Boolean _threadSafe>
		__forceinline const Void ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::applyObject(Address* _addressPtr)
		{
			ZThreadSafe<_threadSafe>::lock();
			if (headNodePtr == nullptr)
			{
				autoExtend();
			}
			*_addressPtr = (Address)((SizeT)headNodePtr + OBJECT_BODY_OFFSET);
			headNodePtr = headNodePtr->nextNodePtr;
			ZThreadSafe<_threadSafe>::unLock();
		}

		/*
			释放object
			参数：
				Address* _addressPtr 需要释放object的指针的指针
		*/
		template<typename _ObjectType, SizeT _objectHeadOffset, Boolean _threadSafe>
		__forceinline const Void ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::releaseObject(Address* _addressPtr)
		{
			if (*_addressPtr == nullptr)
			{
				return;
			}
			ZThreadSafe<_threadSafe>::lock();
			Node<_ObjectType>* nodeAddress = (Node<_ObjectType>*)((SizeT)(*_addressPtr) - OBJECT_BODY_OFFSET);
			nodeAddress->nextNodePtr = headNodePtr;
			headNodePtr = nodeAddress;
			ZThreadSafe<_threadSafe>::unLock();
			*_addressPtr = nullptr;
		}

		/*
			构造函数，空池子
		*/
		template<typename _ObjectType, SizeT _objectHeadOffset, Boolean _threadSafe>
		__forceinline ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::ZPoolBase() :
			headNodePtr(nullptr),
			capacity(0)
		{}

		/*
			构造函数
			参数：
				const Int32& _capacity 池子初始object数量

		*/
		template<typename _ObjectType, SizeT _objectHeadOffset, Boolean _threadSafe>
		__forceinline ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::ZPoolBase(const Int32 _capacity)
		{
			extend(_capacity);
		}

		/*
			析构函数
		*/
		template<typename _ObjectType, SizeT _objectHeadOffset, Boolean _threadSafe>
		__forceinline ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::~ZPoolBase()
		{}

		/*
			自动拓展函数
		*/
		template<typename _ObjectType, SizeT _objectHeadOffset, Boolean _threadSafe>
		__forceinline const Void ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::autoExtend()
		{
			extend(capacity * AUTO_EXTEND_MUL_FACTOR);
		}

	}
}

#endif // !ZPoolBase_h
