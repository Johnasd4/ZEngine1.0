#ifndef ZObjectPointer_h
#define ZObjectPointer_h

#pragma warning(disable : 26439)

#include"ZBasicDrive.h"

#include"ZMemoryPool.h"



namespace ZEngine 
{


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



#endif // !ZObjectPointer_h
