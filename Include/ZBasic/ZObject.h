#ifndef ZObject_h
#define ZObject_h

#pragma warning(disable : 26439)

#include"ZBasicDrive.h"


namespace ZEngine {


	/*
		Object��
		˵����
			����Ϊ������Ļ���

	*/
	class ZObject {

	public:

		//��ʼ�����ͷ�ʱ�Ƿ���Ҫ���ù��캯������������
		static constexpr Boolean NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR = false;

	protected:

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

		/*
			����=
			��ȸ���
			������
				const ZObject& _object �����Ƶ�object
		*/
		__forceinline const Void operator=(const ZObject& _object);

		/*
			����=
			ǳ�ȸ���
			������
				const ZObject&& _object �����Ƶ�object
		*/
		__forceinline const Void operator=(const ZObject&& _object);




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
	__forceinline ZObject::ZObject(const ZObject&& _object){}

	/*
		��������
	*/
	__forceinline ZObject::~ZObject(){}

	/*
		����=
		��ȸ���
		������
			const ZObject& _object �����Ƶ�object
	*/
	__forceinline const Void ZObject::operator=(const ZObject& _object){}

	/*
		����=
		ǳ�ȸ���
		������
			const ZObject&& _object �����Ƶ�object
	*/
	__forceinline const Void ZObject::operator=(const ZObject&& _object){}

}


#endif // !ZObject_h
