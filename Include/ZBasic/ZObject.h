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
		__forceinline ZObject() noexcept;

		/*
			��������
		*/
		__forceinline ~ZObject() noexcept;


	public:

		//��Ϊ��������ʱ�Ƿ���ù��캯��
		constexpr static Boolean ContainerElementIfCallConstructor = false;


	};

	/*
		���캯��
	*/
	__forceinline ZObject::ZObject() noexcept{}



	/*
		��������
	*/
	__forceinline ZObject::~ZObject() noexcept{}



}


#endif // !ZObject_h
