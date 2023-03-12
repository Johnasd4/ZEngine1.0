#ifndef ZPoolListBase_h
#define ZPoolListBase_h

#include"ZBasicDrive.h"
#include"..\ZMutex.h"

namespace ZEngine {

	namespace Private {


		/*
			�����������
		*/
		template<typename _ObjectType, Boolean _threadSafe = false>
		class ZPoolListBase {

		private:

			//�����Զ���չ�ռ�ı���
			static constexpr Float32 AUTO_EXTEND_MUL_FACTOR = 1.2F;


		public:

			/*
				����object
				������
					_ObjectType** _objectPtrPtr ����object��ָ���ָ��
			*/
			const Void applyObject(_ObjectType** _objectPtrPtr);

			/*
				�ͷ�object
				������
					_ObjectType** _objectPtrPtr ��Ҫ�ͷ�object��ָ���ָ��
			*/
			const Void releaseObject(_ObjectType** _objectPtrPtr);



		protected:

			/*
				�ڵ�����
			*/
			template<typename _ObjectType>
			struct Node {
				//�洢��object
				_ObjectType object;
				//��һ��object��ַ
				Node* nextNodePtr;
			};

		protected:

			/*
				���캯�����ճ���
			*/
			__forceinline ZPoolListBase();

			/*
				���캯��
				������
					const Int32& _capacity ���ӳ�ʼobject����

			*/
			__forceinline ZPoolListBase(const Int32& _capacity);




			/*
				��չ����
				��Ҫ�޸ģ�
					Node<_ObjectType>* headNodePtr ���ڿ���object������ͷ
					Int32 capacity �ڴ��ʣ��object����
				������
					const Int32& _num ��ӵ�����
			*/
			virtual const Void extend(const Int32& _num) = 0;

			/*
				�ͷź���
				����ʱ���õĺ���
			*/
			virtual const Void destroy() = 0;

		private:

			/*
				�Զ���չ����
			*/
			__forceinline const Void autoExtend();


		protected:

			//����ͷ
			Node<_ObjectType>* headNodePtr;
			//�����ݻ�
			Int32 capacity;

		};


		/*
			����object
			������
				_ObjectType** _objectPtrPtr ����object��ָ���ָ��
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
			�ͷ�object
			������
				_ObjectType** _objectPtrPtr ��Ҫ�ͷ�object��ָ���ָ��
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
			���캯�����ճ���
		*/
		template<typename _ObjectType, Boolean _threadSafe>
		__forceinline ZPoolListBase<_ObjectType, _threadSafe>::ZPoolListBase() :
			headNodePtr(nullptr),
			capacity(0)
		{}

		/*
			���캯��
			������
				const Int32& _capacity ���ӳ�ʼobject����

		*/
		template<typename _ObjectType, Boolean _threadSafe>
		__forceinline ZPoolListBase<_ObjectType, _threadSafe>::ZPoolListBase(const Int32& _capacity)
		{
			extend(_capacity);
		}



		/*
			�Զ���չ����
		*/
		template<typename _ObjectType, Boolean _threadSafe>
		__forceinline const Void ZPoolListBase<_ObjectType, _threadSafe>::autoExtend()
		{
			extend(capacity * AUTO_EXTEND_MUL_FACTOR);
		}

	}
}

#endif // !ZPoolListBase_h
