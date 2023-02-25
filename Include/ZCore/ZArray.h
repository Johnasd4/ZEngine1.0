#ifndef ZArray_h
#define ZArray_h



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
			��ʼ������
			��ʼ����ʽΪ�����ͬ��Ԫ��
			������
				const _ElementType& _element ����Ԫ��
		*/
		constexpr static const Void Init_FillSameElement(ZConstArray* _array, const _ElementType& _element) noexcept;



		/*
			��ʼ������
			��ʼ����ʽΪ�Ȳ�����
			������
				const _ElementType& _firstElement �����ֵ
				const _FactorType& _factor ϵ��
		*/
		template<typename _FactorType>
		constexpr static const Void Init_ArithmeticSequence(ZConstArray* _array, const _ElementType& _firstElement, const _FactorType& _factor) noexcept;

		/*
			��ʼ������
			��ʼ����ʽΪ�ȱ�����
			������
				const _ElementType& _firstElement �����ֵ
				const _FactorType& _factor ϵ��
		*/
		template<typename _FactorType>
		constexpr static const Void Init_GeometricSequence(ZConstArray* _array, const _ElementType& _firstElement, const _FactorType& _factor) noexcept;


	public:

		/*
			���캯��
			������
				_InitFunc&& _initFunc ZConstArray��ռ��µľ�̬������Init��ͷ
				_Args&&... _args ������Ӧ�Ĳ���������Ҫ�����һ����������һ������Ϊ������
			ע��
				�����Ҫ�Զ����ʼ�������������ĵ�һ�����������ǡ�ZConstArray*��������Ϊ��ʽ�������
		*/
		template<typename _InitFunc, typename... _Args>
		constexpr __forceinline ZConstArray(_InitFunc&& _initFunc, _Args&&... _args) noexcept;


		/*
			��������
		*/
		constexpr __forceinline ~ZConstArray() noexcept;

		/*
			�����ʼ��
			������
				_InitFunc&& _initFunc ZConstArray��ռ��µľ�̬������Init��ͷ
				_Args&&... _args ������Ӧ�Ĳ���������Ҫ�����һ����������һ������Ϊ������
		*/
		template<typename _InitFunc, typename... _Args>
		constexpr __forceinline const Void init(_InitFunc&& _initFunc, _Args&&... _args) noexcept;


		/*
			����()
			������
				const Int32& _index Ԫ���±�
			���أ�
				ElementType& �±��Ӧ��Ԫ�ص�����
		*/
		constexpr __forceinline _ElementType& operator()(const Int32& _index) noexcept;

		/*
			����()
			������
				const Int32& _index Ԫ���±�
			���أ�
				ElementType& �±��Ӧ��Ԫ�ص�����
		*/
		constexpr __forceinline const _ElementType& operator()(const Int32& _index) const noexcept;

		/*
			����()
			������
				const Int32&& _index Ԫ���±�
			���أ�
				ElementType& �±��Ӧ��Ԫ�ص�����
		*/
		constexpr __forceinline _ElementType& operator()(const Int32&& _index) noexcept;

		/*
			����()
			������
				const Int32&& _index Ԫ���±�
			���أ�
				ElementType& �±��Ӧ��Ԫ�ص�����
		*/
		constexpr __forceinline const _ElementType& operator()(const Int32&& _index) const noexcept;


		/*
			��ȡ����Ĵ�С
			���أ�
				const Int32 �����С
		*/
		constexpr static __forceinline const Int32 getSize() noexcept;

		/*
			��������������Ԫ�ص�λ��
			���أ�
				const Int32& _index1 Ԫ��1���±�
				const Int32& _index2 Ԫ��2���±�
		*/
		constexpr __forceinline const Void swap(const Int32& _index1, const Int32& _index2) noexcept;




	private:

		//����洢����ָ�� 
		_ElementType array[_size];


	};


	/*
		��ʼ������
		��ʼ����ʽΪ�����ͬ��Ԫ��
		������
			const _ElementType& _element ����Ԫ��
	*/
	template<typename _ElementType, Int32 _size>
	constexpr static const Void ZConstArray<_ElementType, _size>::Init_FillSameElement(ZConstArray* _array, const _ElementType& _element) noexcept {
		for (Int32 index = 0; index < _array->getSize(); index++) {
			(*_array)(index) = _element;
		}
	}


	/*
		��ʼ������
		��ʼ����ʽΪ�Ȳ�����
		������
			const _ElementType& _firstElement �����ֵ
			const _FactorType& _factor ϵ��
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FactorType>
	constexpr static const Void ZConstArray<_ElementType, _size>::Init_ArithmeticSequence(ZConstArray* _array, const _ElementType& _firstElement, const _FactorType& _factor) noexcept {
		(*_array)(0) = _firstElement;
		for (Int32 index = 1; index < _array->getSize(); index++) {
			(*_array)(index) = (*_array)(index - 1) + _factor;
		}
	}

	/*
		��ʼ������
		��ʼ����ʽΪ�ȱ�����
		������
			const _ElementType& _firstElement �����ֵ
			const _FactorType& _factor ϵ��
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FactorType>
	constexpr static const Void ZConstArray<_ElementType, _size>::Init_GeometricSequence(ZConstArray* _array, const _ElementType& _firstElement, const _FactorType& _factor) noexcept {
		(*_array)(0) = _firstElement;
		for (Int32 index = 1; index < _array->getSize(); index++) {
			(*_array)(index) = (*_array)(index - 1) * _factor;
		}
	}


	/*
		��ʼ������
		��ʼ����ʽΪ�����ͬ��Ԫ��
		������
			const _ElementType& _element ����Ԫ��
	*/
	template<typename _ElementType, Int32 _size>
	constexpr static const Void ZConstArray<_ElementType, _size>::Init_FillSameElement(ZConstArray* _array, const _ElementType& _element) noexcept {
		for (Int32 index = 0; index < _array->getSize(); index++) {
			(*_array)(index) = _element;
		}
	}


	/*
		��ʼ������
		��ʼ����ʽΪ�Ȳ�����
		������
			const _ElementType& _firstElement �����ֵ
			const _FactorType& _factor ��ֵ
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FactorType>
	constexpr static const Void ZConstArray<_ElementType, _size>::Init_ArithmeticSequence(ZConstArray* _array, const _ElementType& _firstElement, const _FactorType& _factor) noexcept {
		(*_array)(0) = _firstElement;
		for (Int32 index = 1; index < _array->getSize(); index++) {
			(*_array)(index) = (*_array)(index - 1) + _factor;
		}
	}
	
	/*
		��ʼ������
		��ʼ����ʽΪ�ȱ�����
		������
			const _ElementType& _firstElement �����ֵ
			const _FactorType& _factor ��ֵ
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FactorType>
	constexpr static const Void ZConstArray<_ElementType, _size>::Init_GeometricSequence(ZConstArray* _array, const _ElementType& _firstElement, const _FactorType& _factor) noexcept {
		(*_array)(0) = _firstElement;
		for (Int32 index = 1; index < _array->getSize(); index++) {
			(*_array)(index) = (*_array)(index - 1) * _factor;
		}
	}


	/*
		���캯��
		������
			_InitFunc&& _initFunc ZConstArray��ռ��µľ�̬������Init��ͷ
			_Args&&... _args ������Ӧ�Ĳ���������Ҫ�����һ����������һ������Ϊ������
			ע��
				�����Ҫ�Զ����ʼ�������������ĵ�һ�����������ǡ�ZConstArray*��������Ϊ��ʽ�������
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _InitFunc, typename... _Args>
	constexpr __forceinline ZConstArray<_ElementType, _size>::ZConstArray(_InitFunc&& _initFunc, _Args&&... _args) noexcept {
		this->init(std::forward<_InitFunc>(_initFunc), std::forward<_Args>(_args)...);
	}

	/*
		��������
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline ZConstArray<_ElementType, _size>::~ZConstArray() noexcept {}

	/*
		�����ʼ��
		������
			_InitFunc&& _initFunc ZConstArray��ռ��µľ�̬������Init��ͷ
			_Args&&... _args ������Ӧ�Ĳ���������Ҫ�����һ����������һ������Ϊ������
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _InitFunc, typename... _Args>
	constexpr __forceinline const Void ZConstArray<_ElementType, _size>::init(_InitFunc&& _initFunc, _Args&&... _args) noexcept {
		_initFunc(this, std::forward<_Args>(_args)...);
	}


	/*
		����()
		������
			const Int32& _index Ԫ���±�
		���أ�
			_ElementType& �±��Ӧ��Ԫ�ص�����
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32& _index) noexcept {
		return this->array[_index];
	}

	/*
		����()
		������
			const Int32& _index Ԫ���±�
		���أ�
			_ElementType& �±��Ӧ��Ԫ�ص�����
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline const _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32& _index) const noexcept {
		return this->array[_index];
	}

	/*
		����()
		������
			const Int32&& _index Ԫ���±�
		���أ�
			_ElementType& �±��Ӧ��Ԫ�ص�����
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32&& _index) noexcept {
		return this->array[_index];
	}

	/*
		����()
		������
			const Int32&& _index Ԫ���±�
		���أ�
			_ElementType& �±��Ӧ��Ԫ�ص�����
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline const _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32&& _index) const noexcept {
		return this->array[_index];
	}



	/*
		��ȡ����Ĵ�С
		���أ�
			const Int32 �����С
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline const Int32 ZConstArray<_ElementType, _size>::getSize() noexcept {
		return _size;
	}


	/*
		��������������Ԫ�ص�λ��
		���أ�
			const Int32& _index1 Ԫ��1���±�
			const Int32& _index2 Ԫ��2���±�
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline const Void ZConstArray<_ElementType, _size>::swap(const Int32& _index1, const Int32& _index2) noexcept {
		_ElementType tempElement = (*this)(_index1);
		(*this)(_index1) = (*this)(_index2);
		(*this)(_index2) = tempElement;
	}



#pragma endregion ZConstArray

#pragma region ZFixedArray


	/*
		��̬���飬˳��洢���洢��ջ��
		ע�⣬����������ʹ��ZArray������洢�ڶ���
		���ʺ����ڴ洢��Ҫ�����ڴ������
	*/
	template<typename _ElementType, Int32 _size>
	class ZFixedArray {

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
				const Int32& _index Ԫ���±�
			���أ�
				ElementType& �±��Ӧ��Ԫ�ص�����
		*/
		__forceinline _ElementType& operator()(const Int32& _index);

		/*
			����()
			������
				const Int32& _index Ԫ���±�
			���أ�
				const _ElementType& �±��Ӧ��Ԫ�ص�����
		*/
		__forceinline const _ElementType& operator()(const Int32& _index) const;

		/*
			��ȡ����Ĵ�С
			���أ�
				const Int32 �����С
		*/
		constexpr static __forceinline const Int32 getSize() noexcept;



	private:

		//����洢����ָ�� 
		_ElementType array[_size];

	};

	/*
		���캯��
	*/
	template<typename _ElementType, Int32 _size>
	__forceinline ZFixedArray<_ElementType, _size>::ZFixedArray(){}


	/*
		��������
	*/
	template<typename _ElementType, Int32 _size>
	__forceinline ZFixedArray<_ElementType, _size>::~ZFixedArray() {}


	/*
		����()
		������
			const Int32& _index Ԫ���±�
		���أ�
			_ElementType& �±��Ӧ��Ԫ�ص�����
	*/
	template<typename _ElementType, Int32 _size>
	__forceinline _ElementType& ZFixedArray<_ElementType, _size>::operator()(const Int32& _index) {
		return this->array[_index];
	}

	/*
		����()
		������
			const Int32& _index Ԫ���±�
		���أ�
			const _ElementType& �±��Ӧ��Ԫ�ص�����
	*/
	template<typename _ElementType, Int32 _size>
	__forceinline const _ElementType& ZFixedArray<_ElementType, _size>::operator()(const Int32& _index) const {
		return this->array[_index];
	}

	/*
		��ȡ����Ĵ�С
		���أ�
			const Int32 �����С
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline const Int32 ZFixedArray<_ElementType, _size>::getSize() noexcept {
		return _size;
	}


#pragma endregion ZFixedArray


}


#endif // !ZArray_h
