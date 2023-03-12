#ifndef ZPoolListBase_h
#define ZPoolListBase_h

#include"ZBasicDrive.h"
#include"..\ZMutex.h"

namespace ZEngine {

	namespace Private {


		/*
			池类链表基类
		*/
		template<typename _ObjectType, Boolean _threadSafe = false>
		class ZPoolListBase {

		private:

			//容器自动拓展空间的倍率
			static constexpr Float32 AUTO_EXTEND_MUL_FACTOR = 1.2F;


		public:

			/*
				申请object
				参数：
					_ObjectType** _objectPtrPtr 申请object的指针的指针
			*/
			const Void applyObject(_ObjectType** _objectPtrPtr);

			/*
				释放object
				参数：
					_ObjectType** _objectPtrPtr 需要释放object的指针的指针
			*/
			const Void releaseObject(_ObjectType** _objectPtrPtr);



		protected:

			/*
				节点类型
			*/
			template<typename _ObjectType>
			struct Node {
				//存储的object
				_ObjectType object;
				//下一个object地址
				Node* nextNodePtr;
			};

		protected:

			/*
				构造函数，空池子
			*/
			__forceinline ZPoolListBase();

			/*
				构造函数
				参数：
					const Int32& _capacity 池子初始object数量

			*/
			__forceinline ZPoolListBase(const Int32& _capacity);




			/*
				拓展函数
				需要修改：
					Node<_ObjectType>* headNodePtr 池内可用object的链表头
					Int32 capacity 内存池剩余object总数
				参数：
					const Int32& _num 添加的数量
			*/
			virtual const Void extend(const Int32& _num) = 0;

			/*
				释放函数
				析构时调用的函数
			*/
			virtual const Void destroy() = 0;

		private:

			/*
				自动拓展函数
			*/
			__forceinline const Void autoExtend();


		protected:

			//链表头
			Node<_ObjectType>* headNodePtr;
			//池内容积
			Int32 capacity;

		};


		/*
			申请object
			参数：
				_ObjectType** _objectPtrPtr 申请object的指针的指针
		*/
		template<typename _ObjectType, Boolean _threadSafe>
		const Void ZPoolListBase<_ObjectType, _threadSafe>::applyObject(_ObjectType** _objectPtrPtr)
		{
			if (headNodePtr == nullptr)
			{
				autoExtend();
			}
			*_objectPtrPtr = (_ObjectType*)headNodePtr;
			headNodePtr = headNodePtr->nextNodePtr;
		}

		/*
			释放object
			参数：
				_ObjectType** _objectPtrPtr 需要释放object的指针的指针
		*/
		template<typename _ObjectType, Boolean _threadSafe>
		const Void ZPoolListBase<_ObjectType, _threadSafe>::releaseObject(_ObjectType** _objectPtrPtr)
		{
			if (*_objectPtrPtr == nullptr)
			{
				return;
			}
			((Node<_ObjectType>*)(*_objectPtrPtr))->nextNodePtr = headNodePtr;
			headNodePtr = (Node<_ObjectType>*)(*_objectPtrPtr);
			*_objectPtrPtr = nullptr;
		}

		/*
			构造函数，空池子
		*/
		template<typename _ObjectType, Boolean _threadSafe>
		__forceinline ZPoolListBase<_ObjectType, _threadSafe>::ZPoolListBase() :
			headNodePtr(nullptr),
			capacity(0)
		{}

		/*
			构造函数
			参数：
				const Int32& _capacity 池子初始object数量

		*/
		template<typename _ObjectType, Boolean _threadSafe>
		__forceinline ZPoolListBase<_ObjectType, _threadSafe>::ZPoolListBase(const Int32& _capacity)
		{
			extend(_capacity);
		}



		/*
			自动拓展函数
		*/
		template<typename _ObjectType, Boolean _threadSafe>
		__forceinline const Void ZPoolListBase<_ObjectType, _threadSafe>::autoExtend()
		{
			extend(capacity * AUTO_EXTEND_MUL_FACTOR);
		}

	}
}

#endif // !ZPoolListBase_h
