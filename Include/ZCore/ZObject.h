#ifndef ZObject_h
#define ZObject_h


#include"ZCoreDependence.h"


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
	__forceinline ZObject::ZObject() {}



	/*
		��������
	*/
	__forceinline ZObject::~ZObject(){}



}


#endif // !ZObject_h
