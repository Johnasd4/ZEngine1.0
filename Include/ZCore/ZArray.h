#ifndef ZArray_h
#define ZArray_h

#pragma warning(disable : 6387)
#pragma warning(disable : 26495)


#include"ZCoreDependence.h"


namespace ZEngine {



#pragma region ZConstArray

	/*
		�������飬���ڱ����ڼ���
	*/
	template<typename _ElementType, Int32 _size>
	class ZConstArray {



	public:

		/*
			���캯��
		*/
		constexpr __forceinline ZConstArray() noexcept;

		/*
			��������
		*/
		constexpr __forceinline ~ZConstArray() noexcept;

		/*
			����()
			������
				const Int32& _elementIndex Ԫ���±�
			���أ�
				ElementType& �±��Ӧ��Ԫ�ص�����
		*/
		constexpr __forceinline _ElementType& operator()(const Int32& _elementIndex) noexcept;

		/*
			����()
			������
				const Int32& _elementIndex Ԫ���±�
			���أ�
				ElementType& �±��Ӧ��Ԫ�ص�����
		*/
		constexpr __forceinline const _ElementType& operator()(const Int32& _elementIndex) const noexcept;

		/*
			����()
			������
				const Int32&& _elementIndex Ԫ���±�
			���أ�
				ElementType& �±��Ӧ��Ԫ�ص�����
		*/
		constexpr __forceinline _ElementType& operator()(const Int32&& _elementIndex) noexcept;

		/*
			����()
			������
				const Int32&& _elementIndex Ԫ���±�
			���أ�
				ElementType& �±��Ӧ��Ԫ�ص�����
		*/
		constexpr __forceinline const _ElementType& operator()(const Int32&& _elementIndex) const noexcept;


		/*
			��ȡ����Ĵ�С
			���أ�
				const Int32 �����С
		*/
		constexpr __forceinline const Int32 getSize() const noexcept;


	private:

		//����洢����ָ�� 
		_ElementType array[_size];

		//����Ĵ�С
		const Int32 size = _size;


	};

	/*
		���캯��
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline ZConstArray<_ElementType, _size>::ZConstArray() noexcept
	{
	}

	/*
		��������
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline ZConstArray<_ElementType, _size>::~ZConstArray() noexcept {}

	/*
		����()
		������
			const Int32& _elementIndex Ԫ���±�
		���أ�
			_ElementType& �±��Ӧ��Ԫ�ص�����
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32& _elementIndex) noexcept {
		return this->array[_elementIndex];
	}

	/*
		����()
		������
			const Int32& _elementIndex Ԫ���±�
		���أ�
			_ElementType& �±��Ӧ��Ԫ�ص�����
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline const _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32& _elementIndex) const noexcept {
		return this->array[_elementIndex];
	}

	/*
		����()
		������
			const Int32&& _elementIndex Ԫ���±�
		���أ�
			_ElementType& �±��Ӧ��Ԫ�ص�����
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32&& _elementIndex) noexcept {
		return this->array[_elementIndex];
	}

	/*
		����()
		������
			const Int32&& _elementIndex Ԫ���±�
		���أ�
			_ElementType& �±��Ӧ��Ԫ�ص�����
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline const _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32&& _elementIndex) const noexcept {
		return this->array[_elementIndex];
	}


	/*
		��ȡ����Ĵ�С
		���أ�
			const Int32 �����С
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline const Int32 ZConstArray<_ElementType, _size>::getSize() const noexcept {
		return this->size;
	}

#pragma endregion ZConstArray



}


#endif // !ZArray_h
