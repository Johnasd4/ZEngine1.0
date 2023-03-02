#ifndef ZContainer_h
#define ZContainer_h

#include"ZBasicDrive.h"


#include"ZObject.h"
#include"ZMemoryPool.h"

namespace ZEngine 
{


	/*
		ZContainer��
		˵����
			����Ϊ�������࣬���������̳��Ը���
			��Ҫ��չ��������ʱʹ��extend������
			���������л��Զ��ͷ��ڴ档
	*/
	template<typename _ObjectType>
	class ZContainer: ZObject
	{

	public:

		//��Ϊ��������ʱ�Ƿ���ù��캯��
		constexpr static Boolean ContainerElementIfCallConstructor = true;
		//������ʼ��Ĭ�Ͽռ��С
		static constexpr Int32 DEFAULT_CAPACITY = 10;
		//�����Զ���չ�ռ�ı���
		static constexpr Float32 AUTO_GROW_MUL_FACTOR = 0.2F;


	public:

		/*
			���캯��
			��Ԫ��������ʼ��
			������
				const Int32& _capacity ������С
				const Boolean&& _containerElementIfCallConstructor = false Ĭ�ϲ����ù��캯��
		*/
		__forceinline ZContainer(const Int32& _capacity = DEFAULT_CAPACITY);

		/*
			���캯��
			��ȫ����
			������
				const ZContainer& _container �����Ƶ����� 
		*/
		__forceinline ZContainer(const ZContainer& _container);

		/*
			���캯��
			�ƶ�����
			������
				const ZContainer&& _container ���ƶ�������
		*/
		__forceinline ZContainer(const ZContainer&& _container);

		/*
			��������
		*/
		__forceinline ~ZContainer();


		/*
			������չ����
			������
				const Int32& _capacity ��չ��������С
				const Boolean&& _containerElementIfCallConstructor = false Ĭ�ϲ����ù��캯��
		*/
		const Void extend(const Int32& _capacity) noexcept;

		/*
			����=
			��ȸ���
			������
				const ZContainer& _container �����Ƶ�����
		*/
		__forceinline const Void operator=(const ZContainer& _container);

		/*
			����=
			ǳ�ȸ���
			������
				const ZContainer&& _container �����Ƶ�����
		*/
		__forceinline const Void operator=(const ZContainer&& _container);

		/*
			���أ���
			��ȡ����Ԫ�ص�����
			������
				const Int32& _index Ԫ���±�
			���أ�
				_ObjectType& Ԫ�ص�����
		*/
		__forceinline _ObjectType& operator()(const Int32& _index);

		/*
			���أ���
			��ȡ����Ԫ�ص�����
			������
				const Int32& _index Ԫ���±�
			���أ�
				const _ObjectType& Ԫ�ص�����
		*/
		__forceinline const _ObjectType& operator()(const Int32& _index) const;



		/*
			��ȡ�����洢ָ��
			���أ�
				_ObjectType* �����洢ָ��
		*/
		__forceinline _ObjectType* getObjectPtr();

		/*
			��ȡ�����洢ָ��
			���أ�
				const _ObjectType* �����洢ָ��
		*/
		__forceinline const _ObjectType* getObjectPtr() const;

		/*
			��ȡ������С
			���أ�
				const Int32& ������С
		*/
		__forceinline const Int32& getCapacity() const;
		
		/*
			��ȡ����Ԫ������
			���أ�
				const Int32& ����Ԫ������
		*/
		__forceinline const Int32& getSize() const;

		/*
			����Ԫ������
			������
				const Int32& ����Ԫ������
		*/
		__forceinline const Void setSize(const Int32& _size);

		/*
			�������
		*/
		__forceinline const Void clear();

	private:


		/*
			���캯��
			�Զ��ж��Ƿ��ʼ��Object
			˵����
				�ж����Ƿ����ContainerElementIfCallConstructor��Ա
				����������ж��Ƿ���Ҫ��ʼ��Object
			������
				const Address& _address ��ʼ���ĵ�ַ
				const Int32& _num ��ʼ��������
		*/
		template<typename __ObjectType, decltype(__ObjectType::ContainerElementIfCallConstructor) _memberExist = true>
		__forceinline const Void initObject(const Address& _address, const Int32& _num)
		{
			//constexpr decltype(__ObjectType::ContainerElementIfCallConstructor) a = true;
			initCallConstructor<__ObjectType::ContainerElementIfCallConstructor>(_address, _num);
		}
		template<typename __ObjectType>
		__forceinline const Void initObject(...) {}
		//�����ù��캯��
		template<Boolean _ifCallConstructor>
		__forceinline const Void initCallConstructor(const Address& _address, const Int32& _num) {}
		//���ù��캯��
		template<>
		__forceinline const Void initCallConstructor<true>(const Address& _address, const Int32& _num)
		{
			new(_address) _ObjectType[_num];
		}

		/*
			���ƹ��캯��
			�Զ��ж��Ƿ��ʼ��Object
			˵����
				�ж����Ƿ����ContainerElementIfCallConstructor��Ա
				����������ж��Ƿ���Ҫ��ʼ��Object
			������
				const ZContainer& _container ��ʼ��ʱ���Ƶ�����
		*/
		template<typename __ObjectType, decltype(__ObjectType::ContainerElementIfCallConstructor) _memberExist = true>
		__forceinline const Void initCopyObject(const ZContainer& _container)
		{
			initCopyCallConstructor<__ObjectType::ContainerElementIfCallConstructor>(_container);
		}
		template<typename __ObjectType>
		__forceinline const Void initCopyObject(...) {}
		//�����ù��캯��
		template<Boolean _ifCallConstructor>
		__forceinline const Void initCopyCallConstructor(const ZContainer& _container) {
			memcpy((Address)(this->getObjectPtr()), (Address)(_container.getObjectPtr()), (UInt64)_container.getCapacity() * sizeof(_ObjectType));
		}
		//���ù��캯��
		template<>
		__forceinline const Void initCopyCallConstructor<true>(const ZContainer& _container)
		{
			for (Int32 index = 0; index < _container.capacity; index++) {
				new((Address)&(*this)(index)) _ObjectType(_container(index));
			}
		}




		/*
			���ƺ���
			����Ԫ�ظ���
			˵����
				�ж����Ƿ����ContainerElementIfCallConstructor��Ա
				����������ж��Ƿ���Ҫ��ȸ���
			������
				const ZContainer& _container ���Ƶ�����
		*/
		template<typename __ObjectType, decltype(__ObjectType::ContainerElementIfCallConstructor) _memberExist = true>
		__forceinline const Void copyObject(const ZContainer& _container)
		{
			copyCallConstructor<__ObjectType::ContainerElementIfCallConstructor>(_container);
		}
		template<typename __ObjectType>
		__forceinline const Void copyObject(...) {}
		//�����ù��캯��
		template<Boolean _ifCallConstructor>
		__forceinline const Void copyCallConstructor(const ZContainer& _container)
		{
			memcpy((Address)(this->getObjectPtr()), (Address)(_container.getObjectPtr()), (UInt64)_container.getCapacity() * sizeof(_ObjectType));
		}
		//���ù��캯��
		template<>
		const Void copyCallConstructor<true>(const ZContainer& _container)
		{
			for (Int32 index = 0; index < _container.capacity; index++) {
				(*this)(index) = _container(index);
			}
		}



		/*
			��Ԫ��������չ����
			������
				const Int32& _capacity ��չ��������С
				const Boolean&& _containerElementIfCallConstructor = false Ĭ�ϲ����ù��캯��
		*/
		const Void autoExtend(const Boolean&& _containerElementIfCallConstructor = false);


	private:
		//�ڴ��ָ��
		ZMemoryPiece* memoryPiecePtr;
		//�����Ĵ�С
		Int32 capacity;
		//������Ԫ������
		Int32 size;
	};


	/*
		���캯��
		��Ԫ��������ʼ��
		������
			const Int32& _capacity ������С
			const Boolean&& _containerElementIfCallConstructor = false Ĭ�ϲ����ù��캯��
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::ZContainer(const Int32& _capacity) :
		ZObject(),
		capacity(_capacity),
		size(0)
	{
		//��������ռ�Ĵ�С
		ZMemoryPiece::MemoryPieceSizeType memorySize = _capacity * sizeof(_ObjectType);
		//�����ڴ�
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
		//����ɹ�����ָ����ַ��new�ö�������ݣ������Ҫ�Ļ���,�����浽����ָ����		
		initObject<_ObjectType>(memoryPiecePtr->memoryAddress, _capacity);
	}

	/*
		���캯��
		��ȫ����
		������
			const ZContainer& _container �����Ƶ�����
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::ZContainer(const ZContainer& _container) :
		ZObject(_container),
		capacity(_container.capacity),
		size(_container.size)
	{
		//��������ռ�Ĵ�С
		ZMemoryPiece::MemoryPieceSizeType memorySize = capacity * sizeof(_ObjectType);
		//�����ڴ�
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
		//����ɹ�����ָ����ַ��new�ö�������ݣ������Ҫ�Ļ���,�����浽����ָ����		
		initCopyObject<_ObjectType>(_container);
	}

	/*
		���캯��
		�ƶ�����
		������
			const ZContainer&& _container ���ƶ�������
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::ZContainer(const ZContainer&& _container) :
		ZObject(std::forward<ZContainer>(_container)),
		memoryPiecePtr(_container.memoryPiecePtr),
		capacity(_container.capacity),
		size(_container.size)
	{
		//��ֹ�ڴ�鱻�ͷ�����
		_container.memoryPiecePtr = nullptr;
	}

	/*
		��������
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::~ZContainer() 
	{
		
		//�ͷ��ڴ�
		ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
	}

	/*
		������չ����
		������
			const Int32& _capacity ��չ��������С
			const Boolean&& _containerElementIfCallConstructor = false Ĭ�ϲ����ù��캯��
	*/
	template<typename _ObjectType>
	const Void ZContainer<_ObjectType>::extend(const Int32& _capacity) noexcept
	{
		//��չǰ������Ҫ���ڴ��С
		ZMemoryPiece::MemoryPieceSizeType originMemorySize = capacity * sizeof(_ObjectType);
		//��չ��������Ҫ���ڴ��С
		ZMemoryPiece::MemoryPieceSizeType currentMemorySize = _capacity * sizeof(_ObjectType);
		//�жϵ�ǰ�ڴ���Ƿ񲻹���
		if (currentMemorySize > memoryPiecePtr->size) {
			//���ڴ�������ڴ�
			ZMemoryPiece* tempMemoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(currentMemorySize);
			//����ǰ�ڴ�鱣�������ת������ʱ�ڴ����
			memcpy(tempMemoryPiecePtr->memoryAddress, memoryPiecePtr->memoryAddress, originMemorySize);
			//�ͷŵ�ǰ�ڴ��
			ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
			//�޸ĵ�ǰ�������ڴ��
			memoryPiecePtr = tempMemoryPiecePtr;
		}
		//�����Ҫ����չ��λ���ϵ��ù��캯����ʼ���ڴ�
		initObject<_ObjectType>((Address)(((UIntAddress)(memoryPiecePtr->memoryAddress)) + originMemorySize), currentMemorySize - originMemorySize);
		//�޸�������С
		capacity = _capacity;
	}

	/*
		����=
		��ȸ���
		������
			const ZContainer& _container �����Ƶ�����
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::operator=(const ZContainer& _container) 
	{
		ZObject::operator=(_container);
		//��չǰ������Ҫ���ڴ��С
		ZMemoryPiece::MemoryPieceSizeType memorySize = _container.capacity * sizeof(_ObjectType);
		//�жϵ�ǰ�ڴ���Ƿ񲻹���
		if (memorySize > memoryPiecePtr->size) {
			//���ڴ�������ڴ�
			ZMemoryPiece* tempMemoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
			//�ͷŵ�ǰ�ڴ��
			ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
			//�޸ĵ�ǰ�������ڴ��
			memoryPiecePtr = tempMemoryPiecePtr;
		}
		//����Ԫ��
		capacity = _container.capacity;
		size = _container.size;
		copyObject<_ObjectType>(_container);
		
	}

	/*
		����=
		ǳ�ȸ���
		������
			const ZContainer&& _container �����Ƶ�����
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::operator=(const ZContainer&& _container) 
	{
		ZObject::operator=(std::forward<ZContainer>(_container));
		memoryPiecePtr = _container.memoryPiecePtr;
		capacity = _container.capacity;
		size = _container.size;
		//��ֹ�ڴ�鱻�ͷ�����
		_container.memoryPiecePtr = nullptr;
	}

	/*
		���أ���
		��ȡ����Ԫ�ص�����
		������
			const Int32& _index Ԫ���±�
		���أ�
			_ObjectType& Ԫ�ص�����
	*/
	template<typename _ObjectType>
	__forceinline _ObjectType& ZContainer<_ObjectType>::operator()(const Int32& _index)
	{
		return getObjectPtr()[_index];
	}

	/*
		���أ���
		��ȡ����Ԫ�ص�����
		������
			const Int32& _index Ԫ���±�
		���أ�
			const _ObjectType& Ԫ�ص�����
	*/
	template<typename _ObjectType>
	__forceinline const _ObjectType& ZContainer<_ObjectType>::operator()(const Int32& _index) const
	{
		return getObjectPtr()[_index];
	}


	/*
		��ȡ�����洢ָ��
		���أ�
			_ObjectType* �����洢ָ��
	*/
	template<typename _ObjectType>
	__forceinline _ObjectType* ZContainer<_ObjectType>::getObjectPtr() 
	{
		return (_ObjectType*)memoryPiecePtr->memoryAddress;
	}

	/*
		��ȡ�����洢ָ��
		���أ�
			const _ObjectType* �����洢ָ��
	*/
	template<typename _ObjectType>
	__forceinline const _ObjectType* ZContainer<_ObjectType>::getObjectPtr() const 
	{
		return (_ObjectType*)memoryPiecePtr->memoryAddress;
	}

	/*
		��ȡ������С
		���أ�
			const Int32& ������С
	*/
	template<typename _ObjectType>
	__forceinline const Int32& ZContainer<_ObjectType>::getCapacity() const 
	{
		return capacity;
	}

	/*
		��ȡ����Ԫ������
		���أ�
			const Int32& ����Ԫ������
	*/
	template<typename _ObjectType>
	__forceinline const Int32& ZContainer<_ObjectType>::getSize() const 
	{
		return size;
	}

	/*
		����Ԫ������
		������
			const Int32& ����Ԫ������
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::setSize(const Int32& _size) 
	{
		size = _size;
	}

	/*
		�������
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::clear() 
	{
		this->size = 0;
	}




}


#endif // !ZContainer_h
