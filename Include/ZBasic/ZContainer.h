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
	template<typename _Object>
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
				const Int32& ������С
		*/
		__forceinline const Int32& getCapacity() const;

		/*
			��ȡ����object����
			���أ�
				const Int32& ����object����
		*/
		__forceinline const Int32& getSize() const;

	protected:

		/*
			���캯��
		*/
		__forceinline ZContainer();


		/*
			���캯��
			������
				const Int32& _capacity ������С
		*/
		__forceinline ZContainer(const Int32& _capacity);

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
				const ZContainer&& _container ���ƶ�������
		*/
		__forceinline ZContainer(const ZContainer&& _container);

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
				const ZContainer&& _container �����Ƶ�����
		*/
		__forceinline const Void operator=(const ZContainer&& _container);

		/*
			���أ���
			��ȡ����object������
			������
				const Int32& _index object�±�
			���أ�
				_Object& object������
		*/
		__forceinline _Object& operator()(const Int32& _index);

		/*
			���أ���
			��ȡ����object������
			������
				const Int32& _index object�±�
			���أ�
				const _Object& object������
		*/
		__forceinline const _Object& operator()(const Int32& _index) const;



		/*
			��ȡ�����洢ָ��
			���أ�
				_Object* �����洢ָ��
		*/
		__forceinline _Object* getObjectPtr();

		/*
			��ȡ�����洢ָ��
			���أ�
				const _Object* �����洢ָ��
		*/
		__forceinline const _Object* getObjectPtr() const;

		/*
			����object����
			������
				const Int32& ����object����
		*/
		__forceinline const Void setSize(const Int32& _size);

		/*
			�ı�object����
			������
				const Int32& _offset ƫ��ֵ
		*/
		__forceinline const Void changeSize(const Int32& _offset);

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
		template<typename _CheckMemberObject, decltype(_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void newObject(const Int32& _index)
		{
			newObjectCallConstructor<_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_index);
		}
		template<typename _CheckMemberObject>
		__forceinline const Void newObject(...) {}
		//�����ù��캯��
		template<Boolean _ifCallConstructor>
		__forceinline const Void newObjectCallConstructor(const Int32& _index) {}
		//���ù��캯��
		template<>
		__forceinline const Void newObjectCallConstructor<true>(const Int32& _index)
		{
			new((Address)(&((*this)(_index)))) _Object();
		}


		/*
			��������
			object�ͷ�
			˵����
				�ж����Ƿ����NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR��Ա
				����������ж��Ƿ���Ҫ��������
			������
				const Int32& _index ����object���±�
		*/
		template<typename _CheckMemberObject, decltype(_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void freeObject(const Int32& _index)
		{
			freeObjectCallDestructor<_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_index);
		}
		template<typename _CheckMemberObject>
		__forceinline const Void freeObject(...) {}
		//��������������
		template<Boolean _ifCallDestructor>
		__forceinline const Void freeObjectCallDestructor(const Int32& _index) {}
		//������������
		template<>
		__forceinline const Void freeObjectCallDestructor<true>(const Int32& _index)
		{
			(*this)(_index).~_Object();
		}

		/**/

	private:

		/*
			������չ����
			������
				const Int32& _capacity ��չ��������С
		*/
		const Void extend(const Int32& _capacity) noexcept;

		/*
			�����Զ���չ����
		*/
		const Void autoExtend() noexcept;

		/*
			���캯��
			�Զ��ж��Ƿ��ʼ��object
			˵����
				�ж����Ƿ����NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR��Ա
				����������ж��Ƿ���Ҫ��ʼ��object
			������
				const Address& _address ��ʼ���ĵ�ַ
				const Int32& _num ��ʼ��������
		*/
		template<typename _CheckMemberObject, decltype(_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void newContainer(const Address& _address, const Int32& _num)
		{
			newContainerCallConstructor<_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_address, _num);
		}
		template<typename _CheckMemberObject>
		__forceinline const Void newContainer(...) {}
		//�����ù��캯��
		template<Boolean _ifCallConstructor>
		__forceinline const Void newContainerCallConstructor(const Address& _address, const Int32& _num) {}
		//���ù��캯��
		template<>
		__forceinline const Void newContainerCallConstructor<true>(const Address& _address, const Int32& _num)
		{
			new(_address) _Object[_num];
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
		template<typename _CheckMemberObject, decltype(_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void newCopyContainer(const ZContainer& _container)
		{
			newCopyContainerCallConstructor<_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_container);
		}
		template<typename _CheckMemberObject>
		__forceinline const Void newCopyContainer(...) {}
		//�����ù��캯��
		template<Boolean _ifCallConstructor>
		__forceinline const Void newCopyContainerCallConstructor(const ZContainer& _container) {
			memcpy((Address)(this->getObjectPtr()), (Address)(_container.getObjectPtr()), (UInt64)_container.getCapacity() * sizeof(_Object));
		}
		//���ù��캯��
		template<>
		__forceinline const Void newCopyContainerCallConstructor<true>(const ZContainer& _container)
		{
			for (Int32 index = 0; index < _container.capacity; index++) {
				new((Address)(&((*this)(index)))) _Object(_container(index));
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
		template<typename _CheckMemberObject, decltype(_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void copyContainer(const ZContainer& _container)
		{
			copyContainerCallConstructor<_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>(_container);
		}
		template<typename _CheckMemberObject>
		__forceinline const Void copyContainer(...) {}
		//�����ø��ƺ���
		template<Boolean _ifCallConstructor>
		__forceinline const Void copyContainerCallConstructor(const ZContainer& _container)
		{
			memcpy((Address)(this->getObjectPtr()), (Address)(_container.getObjectPtr()), (UInt64)_container.getCapacity() * sizeof(_Object));
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
					new((Address) & (*this)(index)) _Object(_container(index));
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
		template<typename _CheckMemberObject, decltype(_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR) _memberExist = true>
		__forceinline const Void freeContainer()
		{
			freeContainerCallDestructor<_CheckMemberObject::NEW_CALL_CONSTRUCTOR_FREE_CALL_DESTRUCTOR>();
		}
		template<typename _CheckMemberObject>
		__forceinline const Void freeContainer(...) {}
		//��������������
		template<Boolean _ifCallDestructor>
		__forceinline const Void freeContainerCallDestructor(){}
		//������������
		template<>
		const Void freeContainerCallDestructor<true>()
		{
			for (Int32 index = 0; index < this->capacity; index++) {
				(*this)(index).~_Object();
			}
		}


	private:
		//�ڴ��ָ��
		ZMemoryPiece* memoryPiecePtr;
		//�����Ĵ�С
		Int32 capacity;
		//������object����
		Int32 size;
	};

	/*
		���캯��
	*/
	template<typename _Object>
	__forceinline ZContainer<_Object>::ZContainer() :
		ZObject(),
		capacity(DEFAULT_CAPACITY),
		size(0) 
	{
		//��������ռ�Ĵ�С
		ZMemoryPiece::MemoryPieceSizeType memorySize = DEFAULT_CAPACITY * sizeof(_Object);
		//�����ڴ�
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
		//����ɹ�����ָ����ַ��new�ö�������ݣ������Ҫ�Ļ���,�����浽����ָ����		
		newContainer<_Object>(memoryPiecePtr->memoryAddress, DEFAULT_CAPACITY);
	}


	/*
		���캯��
		��object������ʼ��
		������
			const Int32& _capacity ������С
	*/
	template<typename _Object>
	__forceinline ZContainer<_Object>::ZContainer(const Int32& _capacity) :
		ZObject(),
		capacity(_capacity),
		size(0)
	{
		//��������ռ�Ĵ�С
		ZMemoryPiece::MemoryPieceSizeType memorySize = _capacity * sizeof(_Object);
		//�����ڴ�
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
		//����ɹ�����ָ����ַ��new�ö�������ݣ������Ҫ�Ļ���,�����浽����ָ����		
		newContainer<_Object>(memoryPiecePtr->memoryAddress, _capacity);
	}

	/*
		���캯��
		��ȸ���
		������
			const ZContainer& _container �����Ƶ�����
	*/
	template<typename _Object>
	__forceinline ZContainer<_Object>::ZContainer(const ZContainer& _container) :
		ZObject(_container),
		capacity(_container.capacity),
		size(_container.size)
	{
		//��������ռ�Ĵ�С
		ZMemoryPiece::MemoryPieceSizeType memorySize = capacity * sizeof(_Object);
		//�����ڴ�
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
		//����ɹ�����ָ����ַ��new�ö�������ݣ������Ҫ�Ļ���,�����浽����ָ����		
		newCopyContainer<_Object>(_container);
	}

	/*
		���캯��
		�ƶ�����
		������
			const ZContainer&& _container ���ƶ�������
	*/
	template<typename _Object>
	__forceinline ZContainer<_Object>::ZContainer(const ZContainer&& _container) :
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
	template<typename _Object>
	__forceinline ZContainer<_Object>::~ZContainer() 
	{
		//�ͷ�object
		freeContainer<_Object>();
		//�ͷ��ڴ�
		ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
	}



	/*
		����=
		��ȸ���
		������
			const ZContainer& _container �����Ƶ�����
	*/
	template<typename _Object>
	__forceinline const Void ZContainer<_Object>::operator=(const ZContainer& _container) 
	{
		ZObject::operator=(_container);

		//������Ҫ���ڴ��С
		ZMemoryPiece::MemoryPieceSizeType memorySize = _container.capacity * sizeof(_Object);

		//�жϵ�ǰ�ڴ���Ƿ񲻹���
		if (memorySize > memoryPiecePtr->size) {
			//���ڴ�������ڴ�
			ZMemoryPiece* tempMemoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
			//����ǰ�ڴ�鱣�������ת������ʱ�ڴ����
			memcpy(tempMemoryPiecePtr->memoryAddress, memoryPiecePtr->memoryAddress, capacity * sizeof(_Object));
			//�ͷŵ�ǰ�ڴ��
			ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
			//�޸ĵ�ǰ�������ڴ��
			memoryPiecePtr = tempMemoryPiecePtr;
		}
		//����object
		copyContainer<_Object>(_container);
		capacity = _container.capacity;
		size = _container.size;

		
	}

	/*
		����=
		�ƶ�����
		������
			const ZContainer&& _container ���ƶ�������
	*/
	template<typename _Object>
	__forceinline const Void ZContainer<_Object>::operator=(const ZContainer&& _container) 
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
		��ȡ����object������
		������
			const Int32& _index object�±�
		���أ�
			_Object& object������
	*/
	template<typename _Object>
	__forceinline _Object& ZContainer<_Object>::operator()(const Int32& _index)
	{
		return getObjectPtr()[_index];
	}

	/*
		���أ���
		��ȡ����object������
		������
			const Int32& _index object�±�
		���أ�
			const _Object& object������
	*/
	template<typename _Object>
	__forceinline const _Object& ZContainer<_Object>::operator()(const Int32& _index) const
	{
		return getObjectPtr()[_index];
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
			_Object* �����洢ָ��
	*/
	template<typename _Object>
	__forceinline _Object* ZContainer<_Object>::getObjectPtr() 
	{
		return (_Object*)memoryPiecePtr->memoryAddress;
	}

	/*
		��ȡ�����洢ָ��
		���أ�
			const _Object* �����洢ָ��
	*/
	template<typename _Object>
	__forceinline const _Object* ZContainer<_Object>::getObjectPtr() const 
	{
		return (_Object*)memoryPiecePtr->memoryAddress;
	}

	/*
		��ȡ������С
		���أ�
			const Int32& ������С
	*/
	template<typename _Object>
	__forceinline const Int32& ZContainer<_Object>::getCapacity() const 
	{
		return capacity;
	}

	/*
		��ȡ����object����
		���أ�
			const Int32& ����object����
	*/
	template<typename _Object>
	__forceinline const Int32& ZContainer<_Object>::getSize() const 
	{
		return size;
	}

	/*
		����object����
		���ж��Ƿ���Ҫ��չ�ռ�
		������
			const Int32& ����object����
	*/
	template<typename _Object>
	__forceinline const Void ZContainer<_Object>::setSize(const Int32& _size) 
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
			const Int32& _offset ƫ��ֵ
	*/
	template<typename _Object>
	__forceinline const Void ZContainer<_Object>::changeSize(const Int32& _offset) {
		size += _offset;
		//���object���࣬���Զ���չ����
		if (size > capacity) {
			autoExtend();
		}
	}

	/*
		�������
	*/
	template<typename _Object>
	__forceinline const Void ZContainer<_Object>::clear() 
	{
		this->size = 0;
	}

	/*
		������չ����
		������
			const Int32& _capacity ��չ��������С
	*/
	template<typename _Object>
	const Void ZContainer<_Object>::extend(const Int32& _capacity) noexcept
	{
		//��չǰ������Ҫ���ڴ��С
		ZMemoryPiece::MemoryPieceSizeType originMemorySize = capacity * sizeof(_Object);
		//��չ��������Ҫ���ڴ��С
		ZMemoryPiece::MemoryPieceSizeType currentMemorySize = _capacity * sizeof(_Object);
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
		newContainer<_Object>((Address)(((UIntAddress)(memoryPiecePtr->memoryAddress)) + originMemorySize), currentMemorySize - originMemorySize);
		//�޸�������С
		capacity = _capacity;
	}

	/*
		�����Զ���չ����
	*/
	template<typename _Object>
	const Void ZContainer<_Object>::autoExtend() noexcept {
		Float32 tempCapacity = (Float32)capacity;
		do {
			tempCapacity *= AUTO_EXTEND_MUL_FACTOR;
		} while (tempCapacity < this->size);
		extend((Int32)tempCapacity);
	}

}


#endif // !ZContainer_h
