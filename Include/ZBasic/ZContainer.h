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

		//��ʼ�����ͷ�ʱ�Ƿ���Ҫ���ù��캯������������
		static constexpr Boolean NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR = true;
		//������ʼ��Ĭ�Ͽռ��С
		static constexpr Int32 DEFAULT_CAPACITY = 10;
		//�����Զ���չ�ռ�ı���
		static constexpr Float32 AUTO_EXTEND_MUL_FACTOR = 1.2F;

	public:

		/*
			��ȡ������С
			���أ�
				const Int32 ������С
		*/
		__forceinline const Int32 getCapacity() const;

		/*
			��ȡ����object����
			���أ�
				const Int32 ����object����
		*/
		__forceinline const Int32 getSize() const;

	protected:

		/*
			���캯��
		*/
		__forceinline ZContainer();


		/*
			���캯��
			������
				const Int32 _capacity ������С
		*/
		__forceinline ZContainer(const Int32 _capacity);

		/*
			���캯��
			��ȸ���
			������
				const ZContainer& _container �����Ƶ����� 
		*/
		__forceinline ZContainer(const ZContainer& _container);

		/*
			���캯��
			�ƶ�����
			������
				ZContainer&& _container ���ƶ�������
		*/
		__forceinline ZContainer(ZContainer&& _container);

		/*
			��������
		*/
		__forceinline ~ZContainer();




		/*
			����=
			��ȸ���
			������
				const ZContainer& _container �����Ƶ�����
		*/
		__forceinline const Void operator=(const ZContainer& _container);

		/*
			����=
			�ƶ�����
			������
				ZContainer&& _container �����Ƶ�����
		*/
		__forceinline const Void operator=(ZContainer&& _container);

		/*
			���أ���
			��ȡ����object������
			������
				const Int32 _index object�±�
			���أ�
				_ObjectType& object������
		*/
		__forceinline _ObjectType& operator()(const Int32 _index);

		/*
			���أ���
			��ȡ����object������
			������
				const Int32 _index object�±�
			���أ�
				const _ObjectType& object������
		*/
		__forceinline const _ObjectType& operator()(const Int32 _index) const;



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
			����object����
			������
				const Int32 ����object����
		*/
		__forceinline const Void setSize(const Int32 _size);

		/*
			�ı�object����
			������
				const Int32 _offset ƫ��ֵ
		*/
		__forceinline const Void changeSize(const Int32 _offset);

		/*
			�������
		*/
		__forceinline const Void clear();

		/*
			���캯��
			�Զ��ж��Ƿ��ʼ��object
			˵����
				�ж����Ƿ����NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR��Ա
				����������ж��Ƿ���Ҫ��ʼ��object
			������
				const Address& _address ��ʼ���ĵ�ַ
		*/
		__forceinline const Void newObject(const Int32& _index);

		/*
			��������
			object�ͷ�
			˵����
				�ж����Ƿ����NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR��Ա
				����������ж��Ƿ���Ҫ��������
			������
				const Int32 _index ����object���±�
		*/
		__forceinline const Void deleteObject(const Int32 _index);

	private:

		/*
			������չ����
			������
				const Int32 _capacity ��չ��������С
		*/
		const Void extend(const Int32 _capacity) noexcept;

		/*
			�����Զ���չ����
		*/
		const Void autoExtend() noexcept;

		/*
			�滻�ڴ��
			������
				const Int32 _usedMemorySize ԭ��ʹ�õ��ڴ���С
				const Int32 _applyMemorySize �滻�ڴ����Ҫ�Ĵ�С
		*/
		const Void changeMemoryPiece(const Int32 _usedMemorySize, const Int32 _applyMemorySize);



		/*
			�ƶ�����ݻ�����
			�Ὣ��������������ն��������κβ���
			����黹�ڴ棬�������ƶ�����
		*/
		__forceinline const Void move_destroy();

		/*
			���캯��
			�Զ��ж��Ƿ��ʼ��object
			˵����
				�ж����Ƿ����NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR��Ա
				����������ж��Ƿ���Ҫ��ʼ��object
			������
				const Address _address ��ʼ���ĵ�ַ
				const Int32 _num ��ʼ��������
		*/
		__forceinline const Void newObjects(const Address _address, const Int32 _num);


		/*
			���ƹ��캯��
			�Զ��ж��Ƿ��ʼ��object
			˵����
				�ж����Ƿ����NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR��Ա
				����������ж��Ƿ���Ҫ��ʼ��object
			������
				const ZContainer& _container ��ʼ��ʱ���Ƶ�����
		*/
		__forceinline const Void newCopyObjects(const ZContainer& _container);

		/*
			���ƺ���
			����object����
			˵����
				�ж����Ƿ����NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR��Ա
				����������ж��Ƿ���Ҫ��ȸ���
			������
				const ZContainer& _container ���Ƶ�����
		*/
		__forceinline const Void copyObjects(const ZContainer& _container);

		/*
			��������
			����object�ͷ�
			˵����
				�ж����Ƿ����NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR��Ա
				����������ж��Ƿ���Ҫ��������
			������
				const ZContainer& _container ����������
		*/
		__forceinline const Void deleteObjects();



	private:
		//�ڴ��ָ��
		ZMemoryPiece* memoryPiecePtr;
		//ָ��������ָ��
		_ObjectType* objectPtr;
		//�����Ĵ�С
		Int32 capacity;
		//������object����
		Int32 size;
	};

	/*
		���캯��
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::ZContainer() :
		ZObject(),
		capacity(DEFAULT_CAPACITY),
		size(0) 
	{
		//��������ռ�Ĵ�С
		ZMemoryPiece::MemoryPieceSizeType memorySize = DEFAULT_CAPACITY * sizeof(_ObjectType);
		//�����ڴ�
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
		//��ʼ������ָ��
		objectPtr = (_ObjectType*)memoryPiecePtr->memoryAddress;
		//����ɹ�����ָ����ַ��new�ö�������ݣ������Ҫ�Ļ���,�����浽����ָ����		
		newObjects(memoryPiecePtr->memoryAddress, DEFAULT_CAPACITY);
	}


	/*
		���캯��
		��object������ʼ��
		������
			const Int32 _capacity ������С
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::ZContainer(const Int32 _capacity) :
		ZObject(),
		capacity(_capacity),
		size(0)
	{
		//��������ռ�Ĵ�С
		ZMemoryPiece::MemoryPieceSizeType memorySize = _capacity * sizeof(_ObjectType);
		//�����ڴ�
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
		//��ʼ������ָ��
		objectPtr = (_ObjectType*)memoryPiecePtr->memoryAddress;
		//����ɹ�����ָ����ַ��new�ö�������ݣ������Ҫ�Ļ���,�����浽����ָ����		
		newObjects(memoryPiecePtr->memoryAddress, _capacity);
	}

	/*
		���캯��
		��ȸ���
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
		//��ʼ������ָ��
		objectPtr = (_ObjectType*)memoryPiecePtr->memoryAddress;
		//����ɹ�����ָ����ַ��new�ö�������ݣ������Ҫ�Ļ���,�����浽����ָ����		
		newCopyObjects(_container);
	}

	/*
		���캯��
		�ƶ�����
		������
			ZContainer&& _container ���ƶ�������
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::ZContainer(ZContainer&& _container) :
		ZObject(std::forward<ZContainer>(_container)),
		memoryPiecePtr(_container.memoryPiecePtr),
		objectPtr(_container.objectPtr),
		capacity(_container.capacity),
		size(_container.size)
	{
		//��ֹ�ڴ�鱻�ͷ�����
		_container.move_destroy();
	}

	/*
		��������
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::~ZContainer() 
	{
		//�ͷ�object
		deleteObjects();
		//�ͷ��ڴ�
		ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
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
		//������Ҫ���ڴ��С
		ZMemoryPiece::MemoryPieceSizeType memorySize = _container.capacity * sizeof(_ObjectType);
		//�жϵ�ǰ�ڴ���Ƿ񲻹���
		if (memorySize > memoryPiecePtr->size) {
			changeMemoryPiece(capacity * sizeof(_ObjectType), memorySize);
		}
		//����object
		copyObjects(_container);
		capacity = _container.capacity;
		size = _container.size;

		
	}

	/*
		����=
		�ƶ�����
		������
			ZContainer&& _container ���ƶ�������
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::operator=(ZContainer&& _container) 
	{
		ZObject::operator=(std::forward<ZContainer>(_container));
		memoryPiecePtr = _container.memoryPiecePtr;
		objectPtr = _container.objectPtr;
		capacity = _container.capacity;
		size = _container.size;
		//��ֹ�ڴ�鱻�ͷ�����
		_container.move_destroy();
	}

	/*
		���أ���
		��ȡ����object������
		������
			const Int32 _index object�±�
		���أ�
			_ObjectType& object������
	*/
	template<typename _ObjectType>
	__forceinline _ObjectType& ZContainer<_ObjectType>::operator()(const Int32 _index)
	{
		return getObjectPtr()[_index];
	}

	/*
		���أ���
		��ȡ����object������
		������
			const Int32 _index object�±�
		���أ�
			const _ObjectType& object������
	*/
	template<typename _ObjectType>
	__forceinline const _ObjectType& ZContainer<_ObjectType>::operator()(const Int32 _index) const
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
		return objectPtr;
	}

	/*
		��ȡ�����洢ָ��
		���أ�
			const _ObjectType* �����洢ָ��
	*/
	template<typename _ObjectType>
	__forceinline const _ObjectType* ZContainer<_ObjectType>::getObjectPtr() const 
	{
		return objectPtr;
	}

	/*
		��ȡ������С
		���أ�
			const Int32 ������С
	*/
	template<typename _ObjectType>
	__forceinline const Int32 ZContainer<_ObjectType>::getCapacity() const 
	{
		return capacity;
	}

	/*
		��ȡ����object����
		���أ�
			const Int32 ����object����
	*/
	template<typename _ObjectType>
	__forceinline const Int32 ZContainer<_ObjectType>::getSize() const 
	{
		return size;
	}

	/*
		����object����
		���ж��Ƿ���Ҫ��չ�ռ�
		������
			const Int32 ����object����
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::setSize(const Int32 _size) 
	{
		size = _size;
		//���object���࣬���Զ���չ����
		if (size > capacity) {
			autoExtend();
		}
	}

	/*
		�ı�object����
		������
			const Int32 _offset ƫ��ֵ
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::changeSize(const Int32 _offset) {
		size += _offset;
		//���object���࣬���Զ���չ����
		if (size > capacity) {
			autoExtend();
		}
	}

	/*
		�������
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::clear() 
	{
		this->size = 0;	
	}

	/*
		���캯��
		�Զ��ж��Ƿ��ʼ��object
		˵����
			�ж����Ƿ����NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR��Ա
			����������ж��Ƿ���Ҫ��ʼ��object
		������
			const Address& _address ��ʼ���ĵ�ַ
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::newObject(const Int32& _index)
	{
		//�жϳ�Ա�Ƿ����
		if constexpr (requires{_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR; })
		{
			//�Ƿ����object�Ĺ��캯��
			if constexpr (_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR == true)
			{
				new((Address)(&((*this)(_index)))) _ObjectType();
			}
		}
	}

	/*
		��������
		object�ͷ�
		˵����
			�ж����Ƿ����NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR��Ա
			����������ж��Ƿ���Ҫ��������
		������
			const Int32 _index ����object���±�
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::deleteObject(const Int32 _index)
	{
		//�жϳ�Ա�Ƿ����
		if constexpr (requires{_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR; })
		{
			//�Ƿ����object����������
			if constexpr (_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR == true)
			{
				(*this)(_index).~_ObjectType();
			}
		}
	}


	/*
		������չ����
		������
			const Int32 _capacity ��չ��������С
	*/
	template<typename _ObjectType>
	const Void ZContainer<_ObjectType>::extend(const Int32 _capacity) noexcept
	{
		//��չǰ������Ҫ���ڴ��С
		ZMemoryPiece::MemoryPieceSizeType usedMemorySize = capacity * sizeof(_ObjectType);
		//��չ��������Ҫ���ڴ��С
		ZMemoryPiece::MemoryPieceSizeType applyMemorySize = _capacity * sizeof(_ObjectType);
		//�жϵ�ǰ�ڴ���Ƿ񲻹���
		if (applyMemorySize > memoryPiecePtr->size) {
			changeMemoryPiece(usedMemorySize, applyMemorySize);
		}
		//�����Ҫ����չ��λ���ϵ��ù��캯����ʼ���ڴ�
		newObjects((Address)(((UIntAddress)(memoryPiecePtr->memoryAddress)) + usedMemorySize), applyMemorySize - usedMemorySize);
		//�޸�������С
		capacity = _capacity;
	}

	/*
		�����Զ���չ����
	*/
	template<typename _ObjectType>
	const Void ZContainer<_ObjectType>::autoExtend() noexcept 
	{
		Float32 tempCapacity = (Float32)capacity;
		do {
			tempCapacity *= AUTO_EXTEND_MUL_FACTOR;
		} while (tempCapacity < this->size);
		extend((Int32)tempCapacity);
	}

	/*
		�滻�ڴ��
		������
			const Int32 _usedMemorySize ԭ��ʹ�õ��ڴ���С
			const Int32 _applyMemorySize �滻�ڴ����Ҫ�Ĵ�С
	*/
	template<typename _ObjectType>
	const Void ZContainer<_ObjectType>::changeMemoryPiece(const Int32 _usedMemorySize, const Int32 _applyMemorySize)
	{
		//���ڴ�������ڴ�
		ZMemoryPiece* tempMemoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(_applyMemorySize);
		//����ǰ�ڴ�鱣�������ת������ʱ�ڴ����
		memcpy(tempMemoryPiecePtr->memoryAddress, memoryPiecePtr->memoryAddress, _usedMemorySize);
		//�ͷŵ�ǰ�ڴ��
		ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
		//�޸ĵ�ǰ�������ڴ��
		memoryPiecePtr = tempMemoryPiecePtr;
		//�޸�����ָ��
		objectPtr = (_ObjectType*)memoryPiecePtr->memoryAddress;
	}


	/*
		�ƶ�����ݻ�����
		�Ὣ��������������ն��������κβ���
		����黹�ڴ棬�������ƶ�����
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::move_destroy() 
	{
		memoryPiecePtr = nullptr;
		objectPtr = nullptr;
		capacity = 0;
		size = 0;
	}

	/*
		���캯��
		�Զ��ж��Ƿ��ʼ��object
		˵����
			�ж����Ƿ����NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR��Ա
			����������ж��Ƿ���Ҫ��ʼ��object
		������
			const Address _address ��ʼ���ĵ�ַ
			const Int32 _num ��ʼ��������
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::newObjects(const Address _address, const Int32 _num)
	{
		//�жϳ�Ա�Ƿ����
		if constexpr (requires{_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR; })
		{
			//�Ƿ����object�Ĺ��캯��
			if constexpr (_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR == true)
			{
				new(_address) _ObjectType[_num];
			}
		}
	}


	/*
		���ƹ��캯��
		�Զ��ж��Ƿ��ʼ��object
		˵����
			�ж����Ƿ����NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR��Ա
			����������ж��Ƿ���Ҫ��ʼ��object
		������
			const ZContainer& _container ��ʼ��ʱ���Ƶ�����
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::newCopyObjects(const ZContainer& _container)
	{
		//�жϳ�Ա�Ƿ����
		if constexpr (requires{_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR; })
		{
			//�Ƿ����object�Ĺ��캯��
			if constexpr (_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR == true)
			{
				for (Int32 index = 0; index < _container.capacity; index++)
				{
					new((Address)(&((*this)(index)))) _ObjectType(_container(index));
				}
			}
			else
			{
				memcpy((Address)(this->getObjectPtr()), (Address)(_container.getObjectPtr()), (SizeT)_container.getCapacity() * sizeof(_ObjectType));
			}
		}
	}



	/*
		���ƺ���
		����object����
		˵����
			�ж����Ƿ����NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR��Ա
			����������ж��Ƿ���Ҫ��ȸ���
		������
			const ZContainer& _container ���Ƶ�����
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::copyObjects(const ZContainer& _container)
	{
		//�жϳ�Ա�Ƿ����
		if constexpr (requires{_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR; })
		{
			//�Ƿ����object�Ĺ��캯��
			if constexpr (_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR == true)
			{
				//�����ǰ��������
				if (capacity >= _container.capacity)
				{
					for (Int32 index = 0; index < _container.capacity; index++)
					{
						(*this)(index) = _container(index);
					}
				}
				//�����ǰ����������
				else {
					//��ǰ�Ѿ���ʼ������ֱ�ӵ��ø��ƺ���
					for (Int32 index = 0; index < capacity; index++)
					{
						(*this)(index) = _container(index);
					}
					//û�г�ʼ�����ĵ��ø��ƹ��캯��
					for (Int32 index = capacity; index < _container.capacity; index++)
					{
						new((Address)(&((*this)(index)))) _ObjectType(_container(index));
					}
				}
			}
			else {
				memcpy((Address)(this->getObjectPtr()), (Address)(_container.getObjectPtr()), (SizeT)_container.getCapacity() * sizeof(_ObjectType));
			}
		}
	}


	/*
		��������
		����object�ͷ�
		˵����
			�ж����Ƿ����NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR��Ա
			����������ж��Ƿ���Ҫ��������
		������
			const ZContainer& _container ����������
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::deleteObjects()
	{
		//�жϳ�Ա�Ƿ����
		if constexpr (requires{_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR; })
		{
			//�Ƿ����object����������
			if constexpr (_ObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR == true)
			{
				for (Int32 index = 0; index < this->capacity; index++)
				{
					(*this)(index).~_ObjectType();
				}
			}
		}
	}


}


#endif // !ZContainer_h
