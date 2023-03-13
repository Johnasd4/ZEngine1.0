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
			���������
			typename _ObjectType �ڵ�����
			Int32 _objectOffset �ڵ�����ʵ��ʹ�õĵ�ַƫ����
			Boolean _threadSafe �Ƿ��̰߳�ȫ
		*/
		template<Boolean _threadSafe>
		class ZSmallMemoryPiecePool :ZPoolBase < ZSmallMemoryPiece, sizeof(ZSmallMemoryPiece), _threadSafe>
		{




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
				���أ�

			*/
			virtual const Void extend(const Int32 _objectNum) = 0;


		private:

			/*
				�Զ���չ����
			*/
			__forceinline const Void autoExtend();


		protected:

		private:

			//�ڵ�ͷ��objectʹ��λ�õ�ƫ����
			static constexpr Int32 OBJECT_BODY_OFFSET = sizeof(Node*) + _objectHeadOffset;

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
			�ͷ�object
			������
				Address* _addressPtr ��Ҫ�ͷ�object��ָ���ָ��
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
			���캯�����ճ���
		*/
		template<typename _ObjectType, Int32 _objectHeadOffset, Boolean _threadSafe>
		__forceinline ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::ZPoolBase() :
			headNodePtr(nullptr),
			capacity(0)
		{}

		/*
			���캯��
			������
				const Int32& _capacity ���ӳ�ʼobject����

		*/
		template<typename _ObjectType, Int32 _objectHeadOffset, Boolean _threadSafe>
		__forceinline ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::ZPoolBase(const Int32 _capacity)
		{
			extend(_capacity);
		}

		/*
			��������
		*/
		template<typename _ObjectType, Int32 _objectHeadOffset, Boolean _threadSafe>
		__forceinline ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::~ZPoolBase()
		{}

		/*
			�Զ���չ����
		*/
		template<typename _ObjectType, Int32 _objectHeadOffset, Boolean _threadSafe>
		__forceinline const Void ZPoolBase<_ObjectType, _objectHeadOffset, _threadSafe>::autoExtend()
		{
			extend(capacity * AUTO_EXTEND_MUL_FACTOR);
		}

	}
}

#endif // !ZMemoryPiecePool_h
