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


	protected:

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
			�Զ��ж��Ƿ��ʼ��Object
			˵����
				�ж����Ƿ����ContainerElementIfCallConstructor��Ա
				����������ж��Ƿ���Ҫ��ʼ��Object
			������
				const Address& address ��ʼ���ĵ�ַ
				const Int32& objectNum ��ʼ��������
		*/
		template<typename __ObjectType>
		__forceinline const Void initObject(Address&& address, Int32&& objectNum)
		{
			callConstructor<__ObjectType::ContainerElementIfCallConstructor>(std::forward<Address&&>(address), std::forward<Int32&&>(objectNum));
		}
		template<typename __ObjectType>
		__forceinline const Void initObject(...) {}
		template<Boolean _ifCallConstructor>
		__forceinline const Void callConstructor(const Address& address, const Int32& objectNum) {}
		template<>
		__forceinline const Void callConstructor<true>(const Address& address, const Int32& objectNum) 
		{
			new(address) _ObjectType[objectNum];
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

	}

	/*
		���캯��
		�ƶ�����
		������
			const ZContainer&& _container ���ƶ�������
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::ZContainer(const ZContainer&& _container) :
		ZObject(_container),
		memoryPiecePtr(_container.memoryPiecePtr),
		capacity(_container.capacity),
		size(_container.size)
	{
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
