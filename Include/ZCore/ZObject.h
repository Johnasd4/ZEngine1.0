#ifndef ZObject_h
#define ZObject_h


#include"ZCoreDependence.h"
#include"ZMemoryPool.h"

namespace ZEngine {


	/*
		Object��
		˵����
			����Ϊ���࣬����Ҫʹ���ڴ�ص��඼��Ҫ�̳��Ը���
			�����ڴ�ؿռ�ĺ����Ĺؼ�����create���ͷſռ�ĺ����Ĺؼ�����destroy
			���������л��Զ��ͷŶ���Ŀռ�

	*/
	class ZObject {


	public:

		/*
			���캯��
		*/
		__forceinline ZObject();

		/*
			���캯��
		*/
		__forceinline ZObject(const Int32& _size);

		/*
			��������
		*/
		__forceinline ~ZObject();


	private:

		//ָ�������ڴ���ָ��
		ZMemoryPiece* memoryPiecePtr;

	};

	/*
		���캯��
	*/
	__forceinline ZObject::ZObject() :
		memoryPiecePtr(nullptr) 
	{}

	/*
		���캯��
	*/
	__forceinline ZObject::ZObject(const Int32& _size) :
		memoryPiecePtr(ZMemoryPool::InstancePtr->applyMemory(_size))
	{}

	/*
		��������
	*/
	__forceinline ZObject::~ZObject()
	{
		//�ͷ��ڴ�
		ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
	}



}


#endif // !ZObject_h
