#ifndef ZObject_h
#define ZObject_h


#include"ZBasicDrive.h"


namespace ZEngine {


	/*
		Object��
		˵����
			����Ϊ������Ļ���

	*/
	class ZObject {

	public:

		/*
			���캯��
		*/
		__forceinline ZObject();

		/*
			���캯��
			��ȫ����
			������
				const ZObject& _object �����Ƶ�object
		*/
		__forceinline ZObject(const ZObject& _object);

		/*
			���캯��
			�ƶ�����
			������
				const ZObject&& _object ���ƶ���object
		*/
		__forceinline ZObject(const ZObject&& _object);

		/*
			��������
		*/
		__forceinline ~ZObject();


	public:

		//��Ϊ��������ʱ�Ƿ���ù��캯��
		constexpr static Boolean ContainerElementIfCallConstructor = false;


	};

	/*
		���캯��
	*/
	__forceinline ZObject::ZObject(){}

	/*
		���캯��
		��ȫ����
		������
			const ZObject& _object �����Ƶ�object
	*/
	__forceinline ZObject::ZObject(const ZObject& _object) {}

	/*
		���캯��
		�ƶ�����
		������
			const ZObject&& _object ���ƶ���object
	*/
	__forceinline ZObject::ZObject(const ZObject&& _object) {}

	/*
		��������
	*/
	__forceinline ZObject::~ZObject(){}



}


#endif // !ZObject_h
