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
		template<typename _CheckMemberObjectType, decltype(_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void newObject(const Int32& _index)
		{
			newObjectCallConstructor<_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_index);
		}
		template<typename _CheckMemberObjectType>
		__forceinline const Void newObject(...) {}
		//�����ù��캯��
		template<Boolean _ifCallConstructor>
		__forceinline const Void newObjectCallConstructor(const Int32& _index) {}
		//���ù��캯��
		template<>
		__forceinline const Void newObjectCallConstructor<true>(const Int32& _index)
		{
			new((Address)(&((*this)(_index)))) _ObjectType();
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
		template<typename _CheckMemberObjectType, decltype(_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void freeObject(const Int32 _index)
		{
			freeObjectCallDestructor<_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_index);
		}
		template<typename _CheckMemberObjectType>
		__forceinline const Void freeObject(...) {}
		//��������������
		template<Boolean _ifCallDestructor>
		__forceinline const Void freeObjectCallDestructor(const Int32 _index) {}
		//������������
		template<>
		__forceinline const Void freeObjectCallDestructor<true>(const Int32 _index)
		{
			(*this)(_index).~_ObjectType();
		}

		/**/

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
		template<typename _CheckMemberObjectType, decltype(_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void newContainer(const Address _address, const Int32 _num)
		{
			newContainerCallConstructor<_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_address, _num);
		}
		template<typename _CheckMemberObjectType>
		__forceinline const Void newContainer(...) {}
		//�����ù��캯��
		template<Boolean _ifCallConstructor>
		__forceinline const Void newContainerCallConstructor(const Address _address, const Int32 _num) {}
		//���ù��캯��
		template<>
		__forceinline const Void newContainerCallConstructor<true>(const Address _address, const Int32 _num)
		{
			new(_address) _ObjectType[_num];
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
		template<typename _CheckMemberObjectType, decltype(_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void newCopyContainer(const ZContainer& _container)
		{
			newCopyContainerCallConstructor<_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_container);
		}
		template<typename _CheckMemberObjectType>
		__forceinline const Void newCopyContainer(...) {}
		//�����ù��캯��
		template<Boolean _ifCallConstructor>
		__forceinline const Void newCopyContainerCallConstructor(const ZContainer& _container) {
			memcpy((Address)(this->getObjectPtr()), (Address)(_container.getObjectPtr()), (UInt64)_container.getCapacity() * sizeof(_ObjectType));
		}
		//���ù��캯��
		template<>
		__forceinline const Void newCopyContainerCallConstructor<true>(const ZContainer& _container)
		{
			for (Int32 index = 0; index < _container.capacity; index++) {
				new((Address)(&((*this)(index)))) _ObjectType(_container(index));
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
		template<typename _CheckMemberObjectType, decltype(_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void copyContainer(const ZContainer& _container)
		{
			copyContainerCallConstructor<_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_container);
		}
		template<typename _CheckMemberObjectType>
		__forceinline const Void copyContainer(...) {}
		//�����ø��ƺ���
		template<Boolean _ifCallConstructor>
		__forceinline const Void copyContainerCallConstructor(const ZContainer& _container)
		{
			memcpy((Address)(this->getObjectPtr()), (Address)(_container.getObjectPtr()), (UInt64)_container.getCapacity() * sizeof(_ObjectType));
		}
		//���ø��ƺ���
		template<>
		const Void copyContainerCallConstructor<true>(const ZContainer& _container)
		{
			//�����ǰ��������
			if (capacity >= _container.capacity) {
				for (Int32 index = 0; index < _container.capacity; index++) {
					(*this)(index) = _container(index);
				}
			}
			//�����ǰ����������
			else {
				//��ǰ�Ѿ���ʼ������ֱ�ӵ��ø��ƺ���
				for (Int32 index = 0; index < capacity; index++) {
					(*this)(index) = _container(index);
				}
				//û�г�ʼ�����ĵ��ø��ƹ��캯��
				for (Int32 index = capacity; index < _container.capacity; index++) {
					new((Address) & (*this)(index)) _ObjectType(_container(index));
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
		template<typename _CheckMemberObjectType, decltype(_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void freeContainer()
		{
			freeContainerCallDestructor<_CheckMemberObjectType::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>();
		}
		template<typename _CheckMemberObjectType>
		__forceinline const Void freeContainer(...) {}
		//��������������
		template<Boolean _ifCallDestructor>
		__forceinline const Void freeContainerCallDestructor(){}
		//������������
		template<>
		const Void freeContainerCallDestructor<true>()
		{
			for (Int32 index = 0; index < this->capacity; index++) {
				(*this)(index).~_ObjectType();
			}
		}


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
		newContainer<_ObjectType>(memoryPiecePtr->memoryAddress, DEFAULT_CAPACITY);
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
		newContainer<_ObjectType>(memoryPiecePtr->memoryAddress, _capacity);
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
		newCopyContainer<_ObjectType>(_container);
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
		freeContainer<_ObjectType>();
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
		copyContainer<_ObjectType>(_container);
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
		newContainer<_ObjectType>((Address)(((UIntAddress)(memoryPiecePtr->memoryAddress)) + usedMemorySize), applyMemorySize - usedMemorySize);
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


}


#endif // !ZContainer_h
