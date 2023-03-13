#ifndef ZConstArray_h
#define ZConstArray_h


#include"Private/ZBasicDrive.h"




namespace ZEngine {


	/*
		�������飬���ڱ����ڼ���
	*/
	template<typename _ElementType, Int32 _size>
	class ZConstArray 
	{

	public:


		/*
			��ʼ������
			��ʼ����ʽΪ�����ͬ��Ԫ��
			������
				const _ElementType& _element ����Ԫ��
		*/
		constexpr static const Void Init_FillSameElement(ZConstArray* _arrayPtr, const _ElementType& _element);



		/*
			��ʼ������
			��ʼ����ʽΪ�Ȳ�����
			������
				const _ElementType& _firstElement �����ֵ
				const _FactorType& _factor ϵ��
		*/
		template<typename _FactorType>
		constexpr static const Void Init_ArithmeticSequence(ZConstArray* _arrayPtr, const _ElementType& _firstElement, const _FactorType& _factor);

		/*
			��ʼ������
			��ʼ����ʽΪ�ȱ�����
			������
				const _ElementType& _firstElement �����ֵ
				const _FactorType& _factor ϵ��
		*/
		template<typename _FactorType>
		constexpr static const Void Init_GeometricSequence(ZConstArray* _arrayPtr, const _ElementType& _firstElement, const _FactorType& _factor);


		/*
			��ʼ������
			��ʼ����ʽΪ����ʽ�����д���ֵΪ������±꣬ϵ��˳��Ӹߴ���ʹ���
			������
				const _FirstFactor& _firstFactor ��ߴ���ϵ��
				const _OtherFactors&... _otherFactors ������ϵ��
		*/
		template<typename _FirstFactor, typename... _OtherFactors>
		constexpr static const Void Init_Polynomial(ZConstArray* _arrayPtr, const _FirstFactor& _firstFactor, const _OtherFactors&... _otherFactors);

		/*
			��ʼ������
			��ʼ����ʽΪ���ж�λ���
			������
				const _FirstSequence& _firstSequence ��һ������
				const _OtherSequences&... _otherSequences ��������
		*/
		template<typename _FirstSequence, typename... _OtherSequences>
		constexpr static const Void Init_AddSequence(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence, const _OtherSequences&... _otherSequences);


		/*
			��ʼ������
			��ʼ����ʽΪ���ж�λ�������һ�����г����������У�
			������
				const _FirstSequence& _firstSequence ��һ������
				const _OtherSequences&... _otherSequences ��������
		*/
		template<typename _FirstSequence, typename... _OtherSequences>
		constexpr static const Void Init_DevideSequence(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence, const _OtherSequences&... _otherSequences);


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
		consteval ZConstArray(_InitFunc&& _initFunc, _Args&&... _args);

		/*
			���ƺ���
			������
				const ZConstArray& _array �����Ƶ�����
		*/
		consteval ZConstArray(const ZConstArray& _array);


		/*
			�����ʼ��
			������
				_InitFunc&& _initFunc ZConstArray��ռ��µľ�̬������Init��ͷ
				_Args&&... _args ������Ӧ�Ĳ���������Ҫ�����һ����������һ������Ϊ������
		*/
		template<typename _InitFunc, typename... _Args>
		consteval const Void init(_InitFunc&& _initFunc, _Args&&... _args);


		/*
			����()
			������
				const Int32 _index Ԫ���±�
			���أ�
				ElementType& �±��Ӧ��Ԫ�ص�����
		*/
		constexpr _ElementType& operator()(const Int32 _index);

		/*
			����()
			������
				const Int32 _index Ԫ���±�
			���أ�
				ElementType& �±��Ӧ��Ԫ�ص�����
		*/
		constexpr const _ElementType& operator()(const Int32 _index) const;



		/*
			��ȡ����Ĵ�С
			���أ�
				const Int32 �����С
		*/
		consteval static const Int32 getSize();

		/*
			��������������Ԫ�ص�λ��
			���أ�
				const Int32 _index1 Ԫ��1���±�
				const Int32 _index2 Ԫ��2���±�
		*/
		constexpr const Void swap(const Int32 _index1, const Int32 _index2);


	private:

		/*
			��ʼ������
			��ʼ����ʽΪ����ʽ�����д���ֵΪ������±꣬ϵ��˳��Ӹߴ���ʹ���
			������
				const _FirstFactor& _firstFactor ��ߴ���ϵ��
				const _OtherFactors&... _otherFactors ������ϵ��
		*/
		template<typename _FirstFactor, typename... _OtherFactors>
		constexpr static const Void Init_PolynomialRecurse(ZConstArray* _arrayPtr, const _FirstFactor& _firstFactor, const _OtherFactors&... _otherFactors);




		/*
			��ʼ������
			��ʼ����ʽΪ����ʽ�����д���ֵΪ������±꣬ϵ��˳��Ӹߴ���ʹ���
			������
				const _FirstFactor& _firstFactor ��ߴ���ϵ��
		*/
		template<typename _FirstFactor>
		constexpr static const Void Init_PolynomialRecurse(ZConstArray* _arrayPtr, const _FirstFactor& _firstFactor);

		/*
			��ʼ������
			��ʼ����ʽΪ���ж�λ���
			������
				const _FirstSequence& _firstSequence ��һ������
				const _OtherSequences&... _otherSequences ��������
		*/
		template<typename _FirstSequence, typename... _OtherSequences>
		constexpr static const Void Init_AddSequenceRecurse(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence, const _OtherSequences&... _otherSequences);

		/*
			��ʼ������
			��ʼ����ʽΪ���ж�λ���
			������
				const _FirstSequence& _firstSequence ��һ������
		*/
		template<typename _FirstSequence>
		constexpr static const Void Init_AddSequenceRecurse(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence);

		/*
			��ʼ������
			��ʼ����ʽΪ���ж�λ�������һ�����г����������У�
			������
				const _FirstSequence& _firstSequence ��һ������
				const _OtherSequences&... _otherSequences ��������
		*/
		template<typename _FirstSequence, typename... _OtherSequences>
		constexpr static const Void Init_DevideSequenceRecurse(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence, const _OtherSequences&... _otherSequences);

		/*
			��ʼ������
			��ʼ����ʽΪ���ж�λ�������һ�����г����������У�
			������
				const _FirstSequence& _firstSequence ��һ������
				const _OtherSequences&... _otherSequences ��������
		*/
		template<typename _FirstSequence>
		constexpr static const Void Init_DevideSequenceRecurse(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence);




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
	constexpr const Void ZConstArray<_ElementType, _size>::Init_FillSameElement(ZConstArray* _arrayPtr, const _ElementType& _element)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) = _element;
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
	constexpr const Void ZConstArray<_ElementType, _size>::Init_ArithmeticSequence(ZConstArray* _arrayPtr, const _ElementType& _firstElement, const _FactorType& _factor)
	{
		(*_arrayPtr)(0) = _firstElement;
		for (Int32 index = 1; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) = (*_arrayPtr)(index - 1) + _factor;
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
	constexpr const Void ZConstArray<_ElementType, _size>::Init_GeometricSequence(ZConstArray* _arrayPtr, const _ElementType& _firstElement, const _FactorType& _factor)
	{
		(*_arrayPtr)(0) = _firstElement;
		for (Int32 index = 1; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) = (*_arrayPtr)(index - 1) * _factor;
		}
	}

	/*
		��ʼ������
		��ʼ����ʽΪ����ʽ�����д���ֵΪ������±꣬ϵ��˳��Ӹߴ���ʹ���
		������
			const _FirstFactor& _firstFactor ��ߴ���ϵ��
			const _OtherFactors&... _otherFactors ������ϵ��
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FirstFactor, typename... _OtherFactors>
	constexpr const Void ZConstArray<_ElementType, _size>::Init_Polynomial(ZConstArray* _arrayPtr, const _FirstFactor& _firstFactor, const _OtherFactors&... _otherFactors)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) = _firstFactor;
		}
		Init_PolynomialRecurse<_OtherFactors...>(_arrayPtr, _otherFactors...);
	}

	/*
		��ʼ������
		��ʼ����ʽΪ����ʽ�����д���ֵΪ������±꣬ϵ��˳��Ӹߴ���ʹ���
		������
			const _FirstFactor& _firstFactor ��ߴ���ϵ��
			const _OtherFactors&... _otherFactors ������ϵ��
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FirstFactor, typename... _OtherFactors>
	constexpr const Void ZConstArray<_ElementType, _size>::Init_PolynomialRecurse(ZConstArray* _arrayPtr, const _FirstFactor& _firstFactor, const _OtherFactors&... _otherFactors)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) *= index;
			(*_arrayPtr)(index) += _firstFactor;
		}
		Init_PolynomialRecurse<_OtherFactors...>(_arrayPtr, _otherFactors...);

	}




	/*
		��ʼ������
		��ʼ����ʽΪ����ʽ�����д���ֵΪ������±꣬ϵ��˳��Ӹߴ���ʹ���
		������
			const _FirstFactor& _firstFactor ��ߴ���ϵ��
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FirstFactor>
	constexpr const Void ZConstArray<_ElementType, _size>::Init_PolynomialRecurse(ZConstArray* _arrayPtr, const _FirstFactor& _firstFactor)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) *= index;
			(*_arrayPtr)(index) += _firstFactor;
		}
	}

	/*
		��ʼ������
		��ʼ����ʽΪ���ж�λ���
		������
			const _FirstSequence& _firstSequence ��һ������
			const _OtherSequences&... _otherSequences ��������
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FirstSequence, typename... _OtherSequences>
	constexpr const Void ZConstArray<_ElementType, _size>::Init_AddSequence(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence, const _OtherSequences&... _otherSequences)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) = _firstSequence(index);
		}
		Init_AddSequenceRecurse<_OtherSequences...>(_arrayPtr, _otherSequences...);
	}

	/*
		��ʼ������
		��ʼ����ʽΪ���ж�λ���
		������
			const _FirstSequence& _firstSequence ��һ������
			const _OtherSequences&... _otherSequences ��������
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FirstSequence, typename... _OtherSequences>
	constexpr const Void ZConstArray<_ElementType, _size>::Init_AddSequenceRecurse(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence, const _OtherSequences&... _otherSequences)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) += _firstSequence(index);
		}
		Init_AddSequenceRecurse<_OtherSequences...>(_arrayPtr, _otherSequences...);
	}

	/*
		��ʼ������
		��ʼ����ʽΪ���ж�λ���
		������
			const _FirstSequence& _firstSequence ��һ������
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FirstSequence>
	constexpr const Void ZConstArray<_ElementType, _size>::Init_AddSequenceRecurse(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) += _firstSequence(index);
		}
	}

	/*
		��ʼ������
		��ʼ����ʽΪ���ж�λ�������һ�����г����������У�
		������
			const _FirstSequence& _firstSequence ��һ������
			const _OtherSequences&... _otherSequences ��������
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FirstSequence, typename... _OtherSequences>
	constexpr const Void ZConstArray<_ElementType, _size>::Init_DevideSequence(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence, const _OtherSequences&... _otherSequences)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) = _firstSequence(index);
		}
		Init_DevideSequenceRecurse<_OtherSequences...>(_arrayPtr, _otherSequences...);
	}

	/*
		��ʼ������
		��ʼ����ʽΪ���ж�λ�������һ�����г����������У�
		������
			const _FirstSequence& _firstSequence ��һ������
			const _OtherSequences&... _otherSequences ��������
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FirstSequence, typename... _OtherSequences>
	constexpr const Void ZConstArray<_ElementType, _size>::Init_DevideSequenceRecurse(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence, const _OtherSequences&... _otherSequences)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) /= _firstSequence(index);
		}
		Init_DevideSequenceRecurse<_OtherSequences...>(_arrayPtr, _otherSequences...);
	}

	/*
		��ʼ������
		��ʼ����ʽΪ���ж�λ�������һ�����г����������У�
		������
			const _FirstSequence& _firstSequence ��һ������
			const _OtherSequences&... _otherSequences ��������
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _FirstSequence>
	constexpr const Void ZConstArray<_ElementType, _size>::Init_DevideSequenceRecurse(ZConstArray* _arrayPtr, const _FirstSequence& _firstSequence)
	{
		for (Int32 index = 0; index < _arrayPtr->getSize(); index++) 
		{
			(*_arrayPtr)(index) /= _firstSequence(index);
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
	consteval ZConstArray<_ElementType, _size>::ZConstArray(_InitFunc&& _initFunc, _Args&&... _args)
	{
		this->init(std::forward<_InitFunc>(_initFunc), std::forward<_Args>(_args)...);
	}

	/*
		���ƺ���
		������
			const ZConstArray& _array �����Ƶ�����
	*/
	template<typename _ElementType, Int32 _size>
	consteval ZConstArray<_ElementType, _size>::ZConstArray(const ZConstArray& _array)
	{
		for (Int32 index = 0; index < _size; index++) 
		{
			(*this)(index) = _array(index);
		}
	}


	/*
		�����ʼ��
		������
			_InitFunc&& _initFunc ZConstArray��ռ��µľ�̬������Init��ͷ
			_Args&&... _args ������Ӧ�Ĳ���������Ҫ�����һ����������һ������Ϊ������
	*/
	template<typename _ElementType, Int32 _size>
	template<typename _InitFunc, typename... _Args>
	consteval const Void ZConstArray<_ElementType, _size>::init(_InitFunc&& _initFunc, _Args&&... _args)
	{
		_initFunc(this, std::forward<_Args>(_args)...);
	}


	/*
		����()
		������
			const Int32 _index Ԫ���±�
		���أ�
			_ElementType& �±��Ӧ��Ԫ�ص�����
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32 _index) 
	{
		return this->array[_index];
	}

	/*
		����()
		������
			const Int32 _index Ԫ���±�
		���أ�
			_ElementType& �±��Ӧ��Ԫ�ص�����
	*/
	template<typename _ElementType, Int32 _size>
	constexpr __forceinline const _ElementType& ZConstArray<_ElementType, _size>::operator()(const Int32 _index) const 
	{
		return this->array[_index];
	}


	/*
		��ȡ����Ĵ�С
		���أ�
			const Int32 �����С
	*/
	template<typename _ElementType, Int32 _size>
	consteval const Int32 ZConstArray<_ElementType, _size>::getSize()
	{
		return _size;
	}


	/*
		��������������Ԫ�ص�λ��
		���أ�
			const Int32 _index1 Ԫ��1���±�
			const Int32 _index2 Ԫ��2���±�
	*/
	template<typename _ElementType, Int32 _size>
	constexpr const Void ZConstArray<_ElementType, _size>::swap(const Int32 _index1, const Int32 _index2)
	{
		_ElementType tempElement = (*this)(_index1);
		(*this)(_index1) = (*this)(_index2);
		(*this)(_index2) = tempElement;
	}




}


#endif // !ZConstArray_h
