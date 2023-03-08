#ifndef ZArray_h
#define ZArray_h

#include"ZBasicDrive.h"

#include"ZContainer.h"

namespace ZEngine 
{

	/*
		��̬���飬˳��洢
	*/
	template<typename _ObjectType>
	class ZArray :public ZContainer<_ObjectType> 
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
				_ObjectType& �±��Ӧ��object������
		*/
		__forceinline _ObjectType& operator()(const Int32 _index);

		/*
			����()
			������
				const Int32 _index object�±�
			���أ�
				const _ObjectType& �±��Ӧ��object������
		*/
		__forceinline const _ObjectType& operator()(const Int32 _index) const;

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
				const _ObjectType& _object ��Ҫ��ӵ�object
		*/
		const Void push(const _ObjectType& _object);



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
				const _ObjectType& _object ��Ҫ�����object
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		const Boolean insert(const Int32 _index, const _ObjectType& _object);

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
	template<typename _ObjectType>
	ZArray<_ObjectType>::ZArray() :
		ZContainer<_ObjectType>()
	{}

	/*
		���캯��������ָ����С������
		������
			const Int32 _capacity �����С
	*/
	template<typename _ObjectType>
	ZArray<_ObjectType>::ZArray(const Int32 _capacity) :
		ZContainer<_ObjectType>(_capacity)
	{}

	/*
		���캯��
		��ȸ���
		������
			const Array& _array �����Ƶ�����
	*/
	template<typename _ObjectType>
	ZArray<_ObjectType>::ZArray(const ZArray& _array) :
		ZContainer<_ObjectType>(_array)
	{}

	/*
		���캯��
		�ƶ�����
		������
			const Array&& _array ���ƶ�������
	*/
	template<typename _ObjectType>
	ZArray<_ObjectType>::ZArray(const ZArray&& _array) :
		ZContainer<_ObjectType>(std::forward<ZArray>(_array))
	{}


	/*
		��������
	*/
	template<typename _ObjectType>
	ZArray<_ObjectType>::~ZArray() {}

	/*
		����()
		������
			const Int32 _index object�±�
		���أ�
			_ObjectType& �±��Ӧ��object������
	*/
	template<typename _ObjectType>
	__forceinline _ObjectType& ZArray<_ObjectType>::operator()(const Int32 _index) 
	{
		return ZContainer<_ObjectType>::operator()(_index);
	}

	/*
		����()
		������
			const Int32 _index object�±�
		���أ�
			const _ObjectType& �±��Ӧ��object������
	*/
	template<typename _ObjectType>
	__forceinline const _ObjectType& ZArray<_ObjectType>::operator()(const Int32 _index) const 
	{
		return ZContainer<_ObjectType>::operator()(_index);
	}

	/*
		����=
		��ȸ���
		������
			const Array& _array �����Ƶ�����
	*/
	template<typename _ObjectType>
	const Void ZArray<_ObjectType>::operator=(const ZArray& _array) 
	{
		ZContainer<_ObjectType>::operator=(_array);
	}

	/*
		����=
		�ƶ�����
		������
			const Array&& _array ����
	*/
	template<typename _ObjectType>
	const Void ZArray<_ObjectType>::operator=(const ZArray&& _array) 
	{
		ZContainer<_ObjectType>::operator=(std::forward<ZArray>(_array));
	}


	/*
		���object������߼�ʹ��memcpy���и�������object
		������
			const _ObjectType& _object ��Ҫ��ӵ�object
	*/
	template<typename _ObjectType>
	const Void ZArray<_ObjectType>::push(const _ObjectType& _object)
	{
		ZContainer<_ObjectType>::changeSize(1);
		(*this)(ZContainer<_ObjectType>::getSize() - 1) = _object;
	}



	/*
		��ӿյ�object
		������
			const Int32 _num ��ӵ�object����
	*/
	template<typename _ObjectType>
	const Void ZArray<_ObjectType>::pushEmpty(const Int32 _num) 
	{
		ZContainer<_ObjectType>::changeSize(_num);
	}

	/*
		����object����
		���ж��Ƿ���Ҫ��չ�ռ�
		������
			const Int32 ����object����
	*/
	template<typename _ObjectType>
	const Void ZArray<_ObjectType>::setSize(const Int32 _num) 
	{
		ZContainer<_ObjectType>::setSize(_num);
	}

	/*
		����object��ָ��λ�ã�������object���κ���
		�ǳ���ʱ�����ر���Ҫ����
		������
			const Int32 _index ������±�
			const _ObjectType& _object ��Ҫ�����object
		���أ�
			const Boolean �Ƿ�ɹ�
	*/
	template<typename _ObjectType>
	const Boolean ZArray<_ObjectType>::insert(const Int32 _index, const _ObjectType& _object)
	{
		if (_index > ZContainer<_ObjectType>::getSize()) 
		{
			return false;
		}
		//����object����
		ZContainer<_ObjectType>::changeSize(1);
		//����λ�ú��object����
		for (Int32 index = ZContainer<_ObjectType>::getSize() - 1; index > _index; index--) 
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
	template<typename _ObjectType>
	const Boolean ZArray<_ObjectType>::remove(const Int32 _index) {
		if (_index >= ZContainer<_ObjectType>::getSize()) {
			return false;
		}
		//����object����
		ZContainer<_ObjectType>::changeSize(-1);
		//���ͷ�ɾ��object����Դ
		ZContainer<_ObjectType>::deleteObject(_index);
		//��ɾ��object�����objectǰ��
		memcpy((Address)(&(*this)(_index)), (Address)(&(*this)(_index + 1)), (ZContainer<_ObjectType>::getSize() - _index) * sizeof(_ObjectType));
		//����Ԫ��λ�ò��䣬��ֹ����ʱ�����ͷ�
		ZContainer<_ObjectType>::newObject(ZContainer<_ObjectType>::getSize());
		return true;
	}

	/*
		�������
	*/
	template<typename _ObjectType>
	__forceinline const Void ZArray<_ObjectType>::clear() {
		ZContainer<_ObjectType>::clear();
	}


}


#endif // !ZArray_h
