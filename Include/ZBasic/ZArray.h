#ifndef ZArray_h
#define ZArray_h

#include"Private/ZBasicDrive.h"
#include"Private/ZContainerBase.h"

namespace ZEngine 
{

	/*
		��̬���飬˳��洢
	*/
	template<typename _ObjectType>
	class ZArray :public ZContainerBase<_ObjectType> 
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
		ZContainerBase<_ObjectType>()
	{}

	/*
		���캯��������ָ����С������
		������
			const Int32 _capacity �����С
	*/
	template<typename _ObjectType>
	ZArray<_ObjectType>::ZArray(const Int32 _capacity) :
		ZContainerBase<_ObjectType>(_capacity)
	{}

	/*
		���캯��
		��ȸ���
		������
			const Array& _array �����Ƶ�����
	*/
	template<typename _ObjectType>
	ZArray<_ObjectType>::ZArray(const ZArray& _array) :
		ZContainerBase<_ObjectType>(_array)
	{}

	/*
		���캯��
		�ƶ�����
		������
			const Array&& _array ���ƶ�������
	*/
	template<typename _ObjectType>
	ZArray<_ObjectType>::ZArray(const ZArray&& _array) :
		ZContainerBase<_ObjectType>(std::forward<ZArray>(_array))
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
		return ZContainerBase<_ObjectType>::operator()(_index);
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
		return ZContainerBase<_ObjectType>::operator()(_index);
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
		ZContainerBase<_ObjectType>::operator=(_array);
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
		ZContainerBase<_ObjectType>::operator=(std::forward<ZArray>(_array));
	}


	/*
		���object������߼�ʹ��memcpy���и�������object
		������
			const _ObjectType& _object ��Ҫ��ӵ�object
	*/
	template<typename _ObjectType>
	const Void ZArray<_ObjectType>::push(const _ObjectType& _object)
	{
		ZContainerBase<_ObjectType>::changeSize(1);
		(*this)(ZContainerBase<_ObjectType>::getSize() - 1) = _object;
	}



	/*
		��ӿյ�object
		������
			const Int32 _num ��ӵ�object����
	*/
	template<typename _ObjectType>
	const Void ZArray<_ObjectType>::pushEmpty(const Int32 _num) 
	{
		ZContainerBase<_ObjectType>::changeSize(_num);
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
		ZContainerBase<_ObjectType>::setSize(_num);
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
		if (_index > ZContainerBase<_ObjectType>::getSize()) 
		{
			return false;
		}
		//����object����
		ZContainerBase<_ObjectType>::changeSize(1);
		//����λ�ú��object����
		for (Int32 index = ZContainerBase<_ObjectType>::getSize() - 1; index > _index; index--) 
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
		if (_index >= ZContainerBase<_ObjectType>::getSize()) {
			return false;
		}
		//����object����
		ZContainerBase<_ObjectType>::changeSize(-1);
		//���ͷ�ɾ��object����Դ
		ZContainerBase<_ObjectType>::deleteObject(_index);
		//��ɾ��object�����objectǰ��
		memcpy((Address)(&(*this)(_index)), (Address)(&(*this)(_index + 1)), (ZContainerBase<_ObjectType>::getSize() - _index) * sizeof(_ObjectType));
		//����Ԫ��λ�ò��䣬��ֹ����ʱ�����ͷ�
		ZContainerBase<_ObjectType>::newObject(ZContainerBase<_ObjectType>::getSize());
		return true;
	}

	/*
		�������
	*/
	template<typename _ObjectType>
	__forceinline const Void ZArray<_ObjectType>::clear() {
		ZContainerBase<_ObjectType>::clear();
	}


}


#endif // !ZArray_h
