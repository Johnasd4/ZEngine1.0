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

		/*
			���ڴ�������ڴ�
			ģ��������д��Ҫ�����ڴ��ָ�����ͣ�����A�����и�CChar*��Ա������Ҫ�����ڴ棬����дCChar
			������
				ObjectType** _objectPointerPointer ����ռ��ַָ��
				const Int32& _objectNum ����ĸ��������ͻ���Ķ��������
				const Boolean& _ifInitialElement �Ƿ�������ĵ�ַ�ϸ���Object����������new����
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		template<typename _ObjectType>
		const Boolean create(_ObjectType** _objectPointerPointer, const Int32& _objectNum, const Boolean& _ifInitialElement);




		/*
			���ڴ����չ�ڴ棨���ʹ���ڴ�صĻ��������ʧ����ֱ�������ϵͳ�����ڴ�
			ģ��������д��Ҫ�����ڴ��ָ�����ͣ�����A�����и�CChar*��Ա������Ҫ�����ڴ棬����дCChar
			������
				ObjectType** _objectPointerPointer ����ռ��ַָ��
				const Int32& _oldObjectNum ��չ���������ͻ���Ķ������սǰ��������
				const Int32& _newObjectNum ��չ���������ͻ���Ķ������ս���������
				const Boolean& _ifInitialElement �Ƿ�����չ�ĵ�ַ�ϸ���Object����������new����
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		template<typename _ObjectType>
		const Boolean extend(_ObjectType** _objectPointerPointer, const Int32& _oldObjectNum, const Int32& _newObjectNum, const Boolean& _ifInitialElement);




		/*
			�ͷ��ڴ棬�Զ��ж��ͷŸ��ڴ�ػ��߲���ϵͳ
			���أ�
				const ErrorIndex ������
		*/
		const Void destroy();


	private:

		//��Ϊ����Ԫ��ʱ�Ƿ���ù��캯��
		static constexpr Boolean ContainerElementIfCallConstructor = false;

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
		if (memoryPiecePtr != nullptr) {
			ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
		}
	}



}


#endif // !ZObject_h
