#ifndef ZSystemMemoryController_h
#define ZSystemMemoryController_h

#include"ZBasicDrive.h"
#include"ZThreadSafe.h"

namespace ZEngine
{

	namespace Private
	{

		/*
			系统内存申请单例类
			Boolean _threadSafe 是否线程安全
		*/
		template<Boolean _threadSafe>
		class ZSystemMemoryController :protected ZThreadSafe<_threadSafe>
		{

		private:

			static constexpr Int32 ADDRESS_NUM_PUR_ADDRESS_LIST_NODE = (SYSTEM_APPLY_MEMORY_UNIT_SIZE - sizeof(Address) / sizeof(Address);


		public:

			/*
				获取单例
			*/
			static __forceinline ZSystemMemoryController& Instance();


			/*
				申请内存
				参数：
					const Int32 _size 内存大小
				返回：
					Address 内存地址
			*/
			const Address applyMemory(const Int32 _size) noexcept;

		private:

			/*
				地址链表
				每个节点存储一定数量的内存地址指针
			*/
			struct AddressListNode
			{
				//存储的指针
				Address address[ADDRESS_NUM_PUR_ADDRESS_LIST_NODE];
				//下一个节点
				AddressListNode* nextListPtr;

			};




		private:

			/*
				构造函数
			*/
			__forceinline ZSystemMemoryController();

			/*
				析构函数
			*/
			~ZSystemMemoryController() noexcept;


		private:

			//当前链表节点
			AddressListNode* currentNodePtr;
			//链表节点头
			AddressListNode* headNodePtr;
			//当前节点地址数量
			Int32 addressCount;

		};


		/*
			单例
		*/
		template<Boolean _threadSafe>
		__forceinline ZSystemMemoryController<_threadSafe>& ZSystemMemoryController<_threadSafe>::Instance()
		{
			static ZSystemMemoryController<_threadSafe> systemMemoryController;
			return &systemMemoryController;
		}

		/*
			申请内存
			参数：
				const Int32 _size 内存大小
			返回：
				Address 内存地址
		*/
		template<Boolean _threadSafe>
		const Address ZSystemMemoryController<_threadSafe>::applyMemory(const Int32 _size) noexcept
		{
			//申请内存
			Address applyMemoryAddress = malloc(_size);
			//线程锁上锁
			ZThreadSafe<_threadSafe>::lock();
			//如果当前节点已经存满则拓展新节点
			if (addressCount == ADDRESS_NUM_PUR_ADDRESS_LIST_NODE)
			{
				//清零计数器
				addressCount = 0;
				//申请新的节点
				currentNodePtr->nextListPtr = new AddressListNode();
				currentNodePtr = currentNodePtr->nextListPtr;
			}
			//存储内存指针
			currentNodePtr->address[addressCount++] = applyMemoryAddress;
			//线程锁解锁
			ZThreadSafe<_threadSafe>::unLock();
			//返回内存指针
			return applyMemoryAddress;
		}


		/*
			构造函数
		*/
		template<Boolean _threadSafe>
		__forceinline ZSystemMemoryController<_threadSafe>::ZSystemMemoryController() :
			addressCount(0),
			currentNodePtr(new AddressListNode()),
			headNodePtr(currentNodePtr)
		{}

		/*
			析构函数
		*/
		template<Boolean _threadSafe>
		ZSystemMemoryController<_threadSafe>::~ZSystemMemoryController() noexcept
		{
			//当节点不是最后节点前
			while (headNodePtr != currentNodePtr)
			{
				//要删除的节点
				AddressListNode* tempNodePtr = headNodePtr;
				//头节点指向下一个节点
				headNodePtr = headNodePtr->nextListPtr;
				//删除节点内的地址
				for (Int32 index = 0; index < ADDRESS_NUM_PUR_ADDRESS_LIST_NODE; index++)
				{
					free(tempNodePtr->address[index]);
				}
				//删除节点本身
				free(tempNodePtr);
			}
			//删除最近节点的地址
			for (Int32 index = 0; index < addressCount; index++)
			{
				free(headNodePtr->address[index]);
			}
			//删除最新节点
			free(headNodePtr);
		}

	}
}

#endif // !ZSystemMemoryController_h
