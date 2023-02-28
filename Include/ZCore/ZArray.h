#ifndef ZArray_h
#define ZArray_h

#include"ZContainer.h"

namespace ZEngine {

	/*
		��̬���飬˳��洢
	*/
	template<typename _ElementType>
	class ZArray :protected ZContainer {

	public:



	public:

		/*
			���캯��������ʼ����Ա������Ϊ��
			˵����
				Ĭ������������ʽΪ����
				Ĭ������������СΪ1.2
				Ĭ�ϲ�����Ԫ�صĹ��캯��

		*/
		ZArray();

		/*
			���캯��������ָ����С������
			˵����
				Ĭ������������ʽΪ����
				Ĭ������������СΪ1.2
				Ĭ�ϲ�����Ԫ�صĹ��캯��
			������
				const Int32& _arraySize �����С

		*/
		ZArray(const Int32& _arraySize);



		/*
			���캯��������ָ����С������
			˵����
				Ĭ������������ʽΪ����
				Ĭ������������СΪ1.2
			������
				const Int32& _arraySize �����С
				const Boolean& _ifInitialElement �Ƿ����Ԫ�صĹ��캯��
		*/
		ZArray(const Int32& _arraySize, const Boolean& _ifInitialElement);



		/*
			���캯��
			������
				const Array& _array �����Ƶ�����
		*/
		ZArray(const ZArray& _array);


		/*
			��������
		*/
		~ZArray();

		/*
			�������飬�޸�arraySize
			������
				const Int32& _arraySize �����С
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		__forceinline const Boolean create(const Int32& _arraySize);

		/*
			�������飬�޸�arraySize
			������
				const Int32& _arraySize �����С
				const Boolean& _ifInitialElement �Ƿ����Ԫ�صĹ��캯���������޸Ķ����������
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		__forceinline const Boolean create(const Int32& _arraySize, const Boolean& _ifInitialElement);


		/*
			��չ���飬�޸�arraySize
			������
				const Int32& _extendArraySize ��չ��������С
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		__forceinline const Boolean extend(const Int32& _extendArraySize);


		/*
			��չ���飬�޸�arraySize
			������
				const Int32& _extendArraySize ��չ��������С
				const Boolean& _ifInitialElement �Ƿ����Ԫ�صĹ��캯���������޸Ķ����������
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		__forceinline const Boolean extend(const Int32& _extendArraySize, const Boolean& _ifInitialElement);



		/*
			ɾ������
		*/
		__forceinline const Void destroy();


		/*
			����()
			������
				const Int32& _elementIndex Ԫ���±�
			���أ�
				_ElementType& �±��Ӧ��Ԫ�ص�����
		*/
		__forceinline _ElementType& operator()(const Int32& _elementIndex);

		/*
			����()
			������
				const Int32& _elementIndex Ԫ���±�
			���أ�
				const _ElementType& �±��Ӧ��Ԫ�ص�����
		*/
		__forceinline const _ElementType& operator()(const Int32& _elementIndex) const;


		/*
			��ȡ�ַ�
			������
				const Int32& _elementIndex Ԫ���±�
			���أ�
				_ElementType& �±��Ӧ��Ԫ�ص�����
		*/
		__forceinline _ElementType& at(const Int32& _elementIndex);


		/*
			��ȡ�ַ�
			������
				const Int32& _elementIndex Ԫ���±�
			���أ�
				_ElementType& �±��Ӧ��Ԫ�ص�����
		*/
		__forceinline const _ElementType& at(const Int32& _elementIndex) const;

		/*
			����=
			������
				const Array& _array ����
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		const Boolean operator=(const ZArray& _array);


		/*
			��ȡ����Ԫ������
			���أ�
				const Int32& Ԫ������
		*/
		__forceinline const Int32& getLength() const;

		/*
			��������Ԫ������
			������
				const Int32& _arrayLength Ԫ������
		*/
		__forceinline const Void setLength(const Int32& _arrayLength);


		/*
			��ȡ����Ĵ�С
			���أ�
				const Int32& �����С
		*/
		__forceinline const Int32& getSize() const;




		/*
			�Ƿ����
			���أ�
				const Boolean �Ƿ����
		*/
		__forceinline const Boolean ifExsit() const;

		/*
			���Ԫ�ص�����߼�ʹ��memcpy���и�������Ԫ��
			������
				const _ElementType& _element ��Ҫ��ӵ�Ԫ��
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		const Boolean add(const _ElementType& _element);


		/*
			��ӿյ�Ԫ��
			������
				const Int32& _emptyElementNum ��ӵ�Ԫ������
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		__forceinline const Boolean addEmpty(const Int32& _emptyElementNum);



		/*
			����Ԫ�ص�ָ��λ�ã�������Ԫ�����κ���
			�ǳ���ʱ�����ر���Ҫ����
			������
				const _ElementType& _element ��Ҫ�����Ԫ��
				const Int32& _elementIndex ������±�
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		const Boolean insert(const _ElementType& _element, const Int32& _elementIndex);

		/*
			ɾ��ָ��λ�õ�Ԫ�أ�������Ԫ��ǰ��
			�ǳ���ʱ�����ر���Ҫ����
			������
				const Int32& _elementIndex ɾ�����±�
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		const Boolean remove(const Int32& _elementIndex);


		/*
			�������
		*/
		__forceinline const Void clear();



	private:


		/*
			�øú��������ڵ������鳤��
			������
				const Int32& _changeLength ���ȱ仯�Ĵ�С
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		const Boolean changeLength(const Int32& _changeLength);

		/*
			��������趨�õĲ���������ֱ�������µ�ǰ�������С
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		const Boolean autoExtend();


	private:

		//����洢����ָ�� 
		_ElementType* array;
		//�����Ԫ������
		Int32 length;
		//����Ĵ�С
		Int32 Size;




	};


}


#endif // !ZArray_h
