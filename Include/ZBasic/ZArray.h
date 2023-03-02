#ifndef ZArray_h
#define ZArray_h

#include"ZBasicDrive.h"

#include"ZContainer.h"

namespace ZEngine {

	/*
		��̬���飬˳��洢
	*/
	template<typename _ElementType>
	class ZArray :public ZContainer<_ElementType> 
	{

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
			������
				const Int32& _arraySize �����С
				const Boolean& _ifInitialElement �Ƿ����Ԫ�صĹ��캯��
		*/
		ZArray(const Int32& _size, const Boolean& _containerElementIfCallConstructor = false);



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
			����=
			������
				const Array& _array ����
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		const Void operator=(const ZArray& _array);

		/*
			��ȡ����Ԫ������
			���أ�
				const Int32& Ԫ������
		*/
		__forceinline const Int32& getLength() const;

		/*
			���Ԫ�ص�����߼�ʹ��memcpy���и�������Ԫ��
			������
				const _ElementType& _element ��Ҫ��ӵ�Ԫ��
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		const Boolean push(const _ElementType& _element);


		/*
			��ӿյ�Ԫ��
			������
				const Int32& _emptyElementNum ��ӵ�Ԫ������
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		__forceinline const Boolean pushEmpty(const Int32& _emptyElementNum);



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

		//�����Ԫ������
		Int32 length;




	};


}


#endif // !ZArray_h
