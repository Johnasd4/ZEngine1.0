#ifndef ZArray_h
#define ZArray_h

#include"ZBasicDrive.h"

#include"ZContainer.h"

namespace ZEngine 
{

	/*
		��̬���飬˳��洢
	*/
	template<typename _Object>
	class ZArray :public ZContainer<_Object> 
	{

	public:

		/*
			���캯��
		*/
		ZArray();

		/*
			���캯��������ָ����С������
			������
				const Int32 _capacity �����С 
		*/
		ZArray(const Int32 _capacity);

		/*
			���캯��
			��ȸ���
			������
				const Array& _array �����Ƶ�����
		*/
		ZArray(const ZArray& _array);

		/*
			���캯��
			�ƶ�����
			������
				const Array&& _array ���ƶ�������
		*/
		ZArray(const ZArray&& _array);


		/*
			��������
		*/
		~ZArray();

		/*
			����()
			������
				const Int32 _index object�±�
			���أ�
				_Object& �±��Ӧ��object������
		*/
		__forceinline _Object& operator()(const Int32 _index);

		/*
			����()
			������
				const Int32 _index object�±�
			���أ�
				const _Object& �±��Ӧ��object������
		*/
		__forceinline const _Object& operator()(const Int32 _index) const;

		/*
			����=
			��ȸ���
			������
				const Array& _array �����Ƶ�����
		*/
		const Void operator=(const ZArray& _array);

		/*
			����=
			�ƶ�����
			������
				const Array&& _array ����
		*/
		const Void operator=(const ZArray&& _array);


		/*
			���object������߼�ʹ��memcpy���и�������object
			������
				const _Object& _object ��Ҫ��ӵ�object
		*/
		const Void push(const _Object& _object);



		/*
			��ӿյ�object
			������
				const Int32 _num ��ӵ�object����
		*/
		const Void pushEmpty(const Int32 _num);


		/*
			����object����
			���ж��Ƿ���Ҫ��չ�ռ�
			������
				const Int32 ����object����
		*/
		const Void setSize(const Int32 _num);

		/*
			����object��ָ��λ�ã�������object���κ���
			�ǳ���ʱ�����ر���Ҫ����
			������
				const Int32 _index ������±�
				const _Object& _object ��Ҫ�����object
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		const Boolean insert(const Int32 _index, const _Object& _object);

		/*
			ɾ��ָ��λ�õ�object��������objectǰ��
			�ǳ���ʱ�����ر���Ҫ����
			������
				const Int32 _index ɾ�����±�
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		const Boolean remove(const Int32 _index);

		/*
			�������
		*/
		__forceinline const Void clear();


	};

	/*
		���캯��
	*/
	template<typename _Object>
	ZArray<_Object>::ZArray() :
		ZContainer<_Object>()
	{}

	/*
		���캯��������ָ����С������
		������
			const Int32 _capacity �����С
	*/
	template<typename _Object>
	ZArray<_Object>::ZArray(const Int32 _capacity) :
		ZContainer<_Object>(_capacity)
	{}

	/*
		���캯��
		��ȸ���
		������
			const Array& _array �����Ƶ�����
	*/
	template<typename _Object>
	ZArray<_Object>::ZArray(const ZArray& _array) :
		ZContainer<_Object>(_array)
	{}

	/*
		���캯��
		�ƶ�����
		������
			const Array&& _array ���ƶ�������
	*/
	template<typename _Object>
	ZArray<_Object>::ZArray(const ZArray&& _array) :
		ZContainer<_Object>(std::forward<ZArray>(_array))
	{}


	/*
		��������
	*/
	template<typename _Object>
	ZArray<_Object>::~ZArray() {}

	/*
		����()
		������
			const Int32 _index object�±�
		���أ�
			_Object& �±��Ӧ��object������
	*/
	template<typename _Object>
	__forceinline _Object& ZArray<_Object>::operator()(const Int32 _index) 
	{
		return ZContainer<_Object>::operator()(_index);
	}

	/*
		����()
		������
			const Int32 _index object�±�
		���أ�
			const _Object& �±��Ӧ��object������
	*/
	template<typename _Object>
	__forceinline const _Object& ZArray<_Object>::operator()(const Int32 _index) const 
	{
		return ZContainer<_Object>::operator()(_index);
	}

	/*
		����=
		��ȸ���
		������
			const Array& _array �����Ƶ�����
	*/
	template<typename _Object>
	const Void ZArray<_Object>::operator=(const ZArray& _array) 
	{
		ZContainer<_Object>::operator=(_array);
	}

	/*
		����=
		�ƶ�����
		������
			const Array&& _array ����
	*/
	template<typename _Object>
	const Void ZArray<_Object>::operator=(const ZArray&& _array) 
	{
		ZContainer<_Object>::operator=(std::forward<ZArray>(_array));
	}


	/*
		���object������߼�ʹ��memcpy���и�������object
		������
			const _Object& _object ��Ҫ��ӵ�object
	*/
	template<typename _Object>
	const Void ZArray<_Object>::push(const _Object& _object)
	{
		ZContainer<_Object>::changeSize(1);
		(*this)(ZContainer<_Object>::getSize() - 1) = _object;
	}



	/*
		��ӿյ�object
		������
			const Int32 _num ��ӵ�object����
	*/
	template<typename _Object>
	const Void ZArray<_Object>::pushEmpty(const Int32 _num) 
	{
		ZContainer<_Object>::changeSize(_num);
	}

	/*
		����object����
		���ж��Ƿ���Ҫ��չ�ռ�
		������
			const Int32 ����object����
	*/
	template<typename _Object>
	const Void ZArray<_Object>::setSize(const Int32 _num) 
	{
		ZContainer<_Object>::setSize(_num);
	}

	/*
		����object��ָ��λ�ã�������object���κ���
		�ǳ���ʱ�����ر���Ҫ����
		������
			const Int32 _index ������±�
			const _Object& _object ��Ҫ�����object
		���أ�
			const Boolean �Ƿ�ɹ�
	*/
	template<typename _Object>
	const Boolean ZArray<_Object>::insert(const Int32 _index, const _Object& _object)
	{
		if (_index > ZContainer<_Object>::getSize()) 
		{
			return false;
		}
		//����object����
		ZContainer<_Object>::changeSize(1);
		//����λ�ú��object����
		for (Int32 index = ZContainer<_Object>::getSize() - 1; index > _index; index--) 
		{
			(*this)(index) = (*this)(index - 1);
		}
		//����object
		(*this)(_index) = _object;
		return true;
	}

	/*
		ɾ��ָ��λ�õ�object��������objectǰ��
		�ǳ���ʱ�����ر���Ҫ����
		������
			const Int32 _index ɾ�����±�
		���أ�
			const Boolean �Ƿ�ɹ�
	*/
	template<typename _Object>
	const Boolean ZArray<_Object>::remove(const Int32 _index) {
		if (_index >= ZContainer<_Object>::getSize()) {
			return false;
		}
		//����object����
		ZContainer<_Object>::changeSize(-1);
		//���ͷ�ɾ��object����Դ
		ZContainer<_Object>::template freeObject<_Object>(_index);
		//��ɾ��object�����objectǰ��
		memcpy((Address)(&(*this)(_index)), (Address)(&(*this)(_index + 1)), (ZContainer<_Object>::getSize() - _index) * sizeof(_Object));
		//����Ԫ��λ�ò��䣬��ֹ����ʱ�����ͷ�
		ZContainer<_Object>::template newObject<_Object>(ZContainer<_Object>::getSize());
		return true;
	}

	/*
		�������
	*/
	template<typename _Object>
	__forceinline const Void ZArray<_Object>::clear() {
		ZContainer<_Object>::clear();
	}


}


#endif // !ZArray_h
