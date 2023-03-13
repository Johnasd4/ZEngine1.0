#ifndef ZSmartPtr_h
#define ZSmartPtr_h

#include"Private/ZBasicDrive.h"

#include"ZMemoryPool.h"



namespace ZEngine
{
	//Ψһָ��
	template<typename _ObjectType>
	class ZUniquePtr;
	//����ָ��
	template<typename _ObjectType>
	class ZSharedPtr;
	//��ָ��
	template<typename _ObjectType>
	class ZWeakPtr;
	//��������
	template<typename _ObjectType>
	class ZSharedRef;


	namespace Private {


		

		/*
			����ָ����ָ���ʵ��
		*/
		template<typename _ObjectType>
		class ZSmartPtrInstance {

			friend class ZUniquePtr<_ObjectType>;
			friend class ZSharedPtr<_ObjectType>;
			friend class ZWeakPtr<_ObjectType>;
			//friend class ZSharedRef<_ObjectType>;


		private:

			/*
				���캯��
				������
					Args&&... args 
			*/
			template<typename... Args>
			__forceinline ZSmartPtrInstance(Args&&... args);

			/*
				��������
			*/
			__forceinline ~ZSmartPtrInstance();

			
							
			//����ָ����Ԫ
			friend class ZUniquePtr<_ObjectType>;
			friend class ZSharedPtr<_ObjectType>;
			friend class ZWeakPtr<_ObjectType>;
			friend class ZSharedRef<_ObjectType>;

		private:

			//�ڴ��
			ZMemoryPiece* memoryPiecePtr;
			//ǿָ�������
			Int32 usedCount;
			//��ָ�������
			Int32 weakCount;

		};

		/*
			���캯��
			������
				Args&&... args
		*/
		template<typename _ObjectType>
		template<typename... Args>
		__forceinline ZSmartPtrInstance<_ObjectType>::ZSmartPtrInstance(Args&&... args) :
			usedCount(1),
			weakCount(1)
		{
			//���ڴ�������ڴ�
			memoryPiecePtr = ZMemoryPool::applyMemory(sizeof(_ObjectType));
			//��ʼ������
			new(memoryPiecePtr->memoryAddress) _ObjectType(std::forward<Args>(args)...);
		}

		/*
			��������
		*/
		template<typename _ObjectType>
		__forceinline ZSmartPtrInstance<_ObjectType>::~ZSmartPtrInstance() 
		{
			//��������
			(_ObjectType*)memoryPiecePtr->memoryAddress->~_ObjectType();
			//�黹�ڴ���Ƭ
			ZMemoryPool::releaseMemory(memoryPiecePtr);
		}


	}


	/*
		ObjectPointer��
		˵����
			Objectͨ��new����������ָ�����
	*/
	template<typename _Object>
	class ObjectPointer
	{
	public:

		/*
			���캯��
		*/
		__forceinline ObjectPointer();

		/*
			�ع�����*
			���أ�
				_Object& ���������
		*/
		__forceinline _Object& operator*();

		/*
			�ع�����*
			���أ�
				const _Object& ���������
		*/
		__forceinline const _Object& operator*() const;

		/*
			�ع�����=
			������
				const _Object* _objectPtr �����Ƶĵ�ַ
		*/
		__forceinline const Void operator=(const _Object* _objectPtr);

		/*
			�ع�����==
			������
				const ObjectPointer& _objectPtr ����ָ��
			���أ�
				const _Object& ���������
		*/
		__forceinline Boolean operator==(const ObjectPointer& _objectPtr) const;


		/*
			���캯��
		*/
		__forceinline ~ObjectPointer();


	private:

		//�ڴ��ָ��
		ZMemoryPiece* memoryPiecePtr;


	};





}



#endif // !ZSmartPtr_h
