#ifndef ZPoolBase_h
#define ZPoolBase_h

#include"ZBasicDrive.h"
#include"ZThreadSafe.h"

namespace ZEngine 
{

	namespace Private 
	{

		/*
			���������
			typename _ObjectType �ڵ�����
			SizeT _objectOffset �ڵ�����ʵ��ʹ�õĵ�ַƫ����
			Boolean _threadSafe �Ƿ��̰߳�ȫ
		*/
		template<typename _ObjectType, SizeT _objectHeadOffset, Boolean _threadSafe>
		class ZPoolBase :protected ZThreadSafe<_threadSafe>
		{

		private:

			//�����Զ���չ�ռ�ı���
			static constexpr Float32 AUTO_EXTEND_MUL_FACTOR = 1.2F;


		public:

			/*
				����object
				������
					Address* _addressPtr ����object��ָ���ָ��
			*/
			__forceinline const Void applyObject(Address* _addressPtr);

			/*
				�ͷ�object
				������
					Address* _addressPtr ��Ҫ�ͷ�object��ָ���ָ��
			*/
			__forceinline const Void releaseObject(Address* _addressPtr);



		protected:

			/*
				�ڵ�����
			*/
			template<typename _ObjectType>
			struct Node 
			{
				//��һ��object��ַ
				Node* nextNodePtr;
				//�洢��object
				_ObjectType object;

			};

		protected:

			/*
				���캯�����ճ���
			*/
			__forceinline ZPoolBase();

			/*
				���캯��
				������
					const Int32 _capacity ���ӳ�ʼobject����

			*/
			__forceinline ZPoolBase(const Int32 _capacity);

			/*
				��������
			*/
			__forceinline ~ZPoolBase();


			/*
				��չ����
				��ʼ��һ������
				��Ҫ�޸ģ�
					Node<_ObjectType>* headNodePtr ����ʣ��object����ָ��
					Int32 capacity ����object����
				������
					const Int32 _num ��ӵ�����
			*/
			virtual const Void extend(const Int32 _num) = 0;


		private:

			/*
				�Զ���չ����
			*/
			__forceinline const Void autoExtend();




		private:

			//�ڵ�ͷ��objectʹ��λ�õ�ƫ����
			static constexpr SizeT OBJECT_BODY_OFFSET = sizeof(Node*) + _objectHeadOffset;

		protected:

			//����ͷ
			Node<_ObjectType>* headNodePtr;
			//����object����
			Int32 capacity;

		};

		/*
			����object
			������
				Address* _addressPtr ����object��ָ���ָ��
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
			�ͷ�object
			������
				Address* _addressPtr ��Ҫ�ͷ�object��ָ���ָ��
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
			���캯�����ճ���
		*/
		template<typename _ObjectType, SizeT _objectHeadOffset, Boolean _threadSafe>
		__forceinline ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::ZPoolBase() :
			headNodePtr(nullptr),
			capacity(0)
		{}

		/*
			���캯��
			������
				const Int32& _capacity ���ӳ�ʼobject����

		*/
		template<typename _ObjectType, SizeT _objectHeadOffset, Boolean _threadSafe>
		__forceinline ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::ZPoolBase(const Int32 _capacity)
		{
			extend(_capacity);
		}

		/*
			��������
		*/
		template<typename _ObjectType, SizeT _objectHeadOffset, Boolean _threadSafe>
		__forceinline ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::~ZPoolBase()
		{}

		/*
			�Զ���չ����
		*/
		template<typename _ObjectType, SizeT _objectHeadOffset, Boolean _threadSafe>
		__forceinline const Void ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::autoExtend()
		{
			extend(capacity * AUTO_EXTEND_MUL_FACTOR);
		}

	}
}

#endif // !ZPoolBase_h
