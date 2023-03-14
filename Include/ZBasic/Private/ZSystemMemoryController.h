#ifndef ZSystemMemoryController_h
#define ZSystemMemoryController_h

#include"ZBasicDrive.h"
#include"ZThreadSafe.h"

namespace ZEngine
{

	namespace Private
	{

		/*
			ϵͳ�ڴ����뵥����
			Boolean _threadSafe �Ƿ��̰߳�ȫ
		*/
		template<Boolean _threadSafe>
		class ZSystemMemoryController :protected ZThreadSafe<_threadSafe>
		{

		private:

			static constexpr Int32 ADDRESS_NUM_PUR_ADDRESS_LIST_NODE = (SYSTEM_APPLY_MEMORY_UNIT_SIZE - sizeof(Address) / sizeof(Address);


		public:

			/*
				��ȡ����
			*/
			static __forceinline ZSystemMemoryController& Instance();


			/*
				�����ڴ�
				������
					const Int32 _size �ڴ��С
				���أ�
					Address �ڴ��ַ
			*/
			const Address applyMemory(const Int32 _size) noexcept;

		private:

			/*
				��ַ����
				ÿ���ڵ�洢һ���������ڴ��ַָ��
			*/
			struct AddressListNode
			{
				//�洢��ָ��
				Address address[ADDRESS_NUM_PUR_ADDRESS_LIST_NODE];
				//��һ���ڵ�
				AddressListNode* nextListPtr;

			};




		private:

			/*
				���캯��
			*/
			__forceinline ZSystemMemoryController();

			/*
				��������
			*/
			~ZSystemMemoryController() noexcept;


		private:

			//��ǰ����ڵ�
			AddressListNode* currentNodePtr;
			//����ڵ�ͷ
			AddressListNode* headNodePtr;
			//��ǰ�ڵ��ַ����
			Int32 addressCount;

		};


		/*
			����
		*/
		template<Boolean _threadSafe>
		__forceinline ZSystemMemoryController<_threadSafe>& ZSystemMemoryController<_threadSafe>::Instance()
		{
			static ZSystemMemoryController<_threadSafe> systemMemoryController;
			return &systemMemoryController;
		}

		/*
			�����ڴ�
			������
				const Int32 _size �ڴ��С
			���أ�
				Address �ڴ��ַ
		*/
		template<Boolean _threadSafe>
		const Address ZSystemMemoryController<_threadSafe>::applyMemory(const Int32 _size) noexcept
		{
			//�����ڴ�
			Address applyMemoryAddress = malloc(_size);
			//�߳�������
			ZThreadSafe<_threadSafe>::lock();
			//�����ǰ�ڵ��Ѿ���������չ�½ڵ�
			if (addressCount == ADDRESS_NUM_PUR_ADDRESS_LIST_NODE)
			{
				//���������
				addressCount = 0;
				//�����µĽڵ�
				currentNodePtr->nextListPtr = new AddressListNode();
				currentNodePtr = currentNodePtr->nextListPtr;
			}
			//�洢�ڴ�ָ��
			currentNodePtr->address[addressCount++] = applyMemoryAddress;
			//�߳�������
			ZThreadSafe<_threadSafe>::unLock();
			//�����ڴ�ָ��
			return applyMemoryAddress;
		}


		/*
			���캯��
		*/
		template<Boolean _threadSafe>
		__forceinline ZSystemMemoryController<_threadSafe>::ZSystemMemoryController() :
			addressCount(0),
			currentNodePtr(new AddressListNode()),
			headNodePtr(currentNodePtr)
		{}

		/*
			��������
		*/
		template<Boolean _threadSafe>
		ZSystemMemoryController<_threadSafe>::~ZSystemMemoryController() noexcept
		{
			//���ڵ㲻�����ڵ�ǰ
			while (headNodePtr != currentNodePtr)
			{
				//Ҫɾ���Ľڵ�
				AddressListNode* tempNodePtr = headNodePtr;
				//ͷ�ڵ�ָ����һ���ڵ�
				headNodePtr = headNodePtr->nextListPtr;
				//ɾ���ڵ��ڵĵ�ַ
				for (Int32 index = 0; index < ADDRESS_NUM_PUR_ADDRESS_LIST_NODE; index++)
				{
					free(tempNodePtr->address[index]);
				}
				//ɾ���ڵ㱾��
				free(tempNodePtr);
			}
			//ɾ������ڵ�ĵ�ַ
			for (Int32 index = 0; index < addressCount; index++)
			{
				free(headNodePtr->address[index]);
			}
			//ɾ�����½ڵ�
			free(headNodePtr);
		}

	}
}

#endif // !ZSystemMemoryController_h
