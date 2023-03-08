#ifndef ZFixedArray_h
#define ZFixedArray_h

#pragma warning(disable : 26495)


#include"ZBasicDrive.h"



namespace ZEngine 
{

	/*
		��̬���飬˳��洢���洢��ջ��
		ע�⣬����������ʹ��ZArray������洢�ڶ���
		���ʺ����ڴ洢��Ҫ�����ڴ������
	*/
	template<typename _ElementType, Int32 _size>
	class ZFixedArray 
	{

	public:

		/*
			���캯��
		*/
		__forceinline ZFixedArray();

		/*
			��������
		*/
		__forceinline ~ZFixedArray();

		/*
			����()
			������
				const Int32 _index Ԫ���±�
			���أ�
				ElementType& �±��Ӧ��Ԫ�ص�����
		*/
		__forceinline _ElementType& operator()(const Int32 _index);

		/*
			����()
			������
				const Int32 _index Ԫ���±�
			���أ�
				const _ElementType& �±��Ӧ��Ԫ�ص�����
		*/
		__forceinline const _ElementType& operator()(const Int32 _index) const;

		/*
			��ȡ����Ĵ�С
			���أ�
				const Int32 �����С
		*/
		consteval static const Int32 getSize();



	private:

		//����洢����ָ�� 
		_ElementType array[_size];

	};

	/*
		���캯��
	*/
	template<typename _ElementType, Int32 _size>
	__forceinline ZFixedArray<_ElementType, _size>::ZFixedArray() {}


	/*
		��������
	*/
	template<typename _ElementType, Int32 _size>
	__forceinline ZFixedArray<_ElementType, _size>::~ZFixedArray() {}


	/*
		����()
		������
			const Int32 _index Ԫ���±�
		���أ�
			_ElementType& �±��Ӧ��Ԫ�ص�����
	*/
	template<typename _ElementType, Int32 _size>
	__forceinline _ElementType& ZFixedArray<_ElementType, _size>::operator()(const Int32 _index) 
	{
		return this->array[_index];
	}

	/*
		����()
		������
			const Int32 _index Ԫ���±�
		���أ�
			const _ElementType& �±��Ӧ��Ԫ�ص�����
	*/
	template<typename _ElementType, Int32 _size>
	__forceinline const _ElementType& ZFixedArray<_ElementType, _size>::operator()(const Int32 _index) const 
	{
		return this->array[_index];
	}

	/*
		��ȡ����Ĵ�С
		���أ�
			const Int32 �����С
	*/
	template<typename _ElementType, Int32 _size>
	consteval static const Int32 ZFixedArray<_ElementType, _size>::getSize()
	{
		return _size;
	}

}


#endif // !ZFixedArray_h
