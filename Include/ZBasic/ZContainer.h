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
		//�����Զ���չ�ռ�ı���
		static constexpr Float32 AUTO_GROW_MUL_FACTOR = 0.2F;

	protected:

		/*
			���캯��
			��Ԫ��������ʼ�������ù��캯��
			������
				_ObjectType** _objectPtrPtr ������ַָ��
				Args&&... args ���캯���Ĳ���
		*
		template<typename _ObjectType,typename... Args>
		__forceinline ZContainer(_ObjectType** _objectPtrPtr, Args&&... args);


		/*
			���캯��
			��Ԫ��������ʼ��
			������
				const Int32& _capacity ������С
				const Boolean&& _containerElementIfCallConstructor = false Ĭ�ϲ����ù��캯��
		*/
		
		__forceinline ZContainer(const Int32& _capacity, const Boolean&& _containerElementIfCallConstructor = false);

		/*
			��������
		*/
		__forceinline ~ZContainer() noexcept;


		/*
			������չ����
			������
				const Int32& _capacity ��չ��������С
				const Boolean&& _containerElementIfCallConstructor = false Ĭ�ϲ����ù��캯��
		*/
		const Void extend(const Int32& _capacity, const Boolean&& _containerElementIfCallConstructor = false);

		/*
			��ȡ�����洢ָ��
			���أ�
				_ObjectType* �����洢ָ��
		*/
		__forceinline _ObjectType* getObjectPtr() noexcept;

		/*
			��ȡ�����洢ָ��
			���أ�
				const _ObjectType* �����洢ָ��
		*/
		__forceinline const _ObjectType* getObjectPtr() const noexcept;

		/*
			��ȡ������С
			���أ�
				const Int32& ������С
		*/
		__forceinline const Int32& getCapacity() const noexcept;
		
		/*
			��ȡ����Ԫ������
			���أ�
				const Int32& ����Ԫ������
		*/
		__forceinline const Int32& getSize() const noexcept;

		/*
			����Ԫ������
			������
				const Int32& ����Ԫ������
		*/
		__forceinline const Void setSize(const Int32& _size) noexcept;

		/*
			�������
		*/
		__forceinline const Void clear();

	private:

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
		��Ԫ��������ʼ�������ù��캯��
		������
			_ObjectType** _objectPtrPtr ������ַָ��
			Args&&... args ���캯���Ĳ���
	*
	template<typename _ObjectType, typename... Args>
	__forceinline ZContainer::ZContainer(_ObjectType** _objectPtrPtr, Args&&... args) {
		//�����ڴ�
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(capacityof(_ObjectType));
		//����ɹ�����ָ����ַ��new�ö�������ݣ������Ҫ�Ļ���,�����浽����ָ����
		*_objectPtrPtr = new(memoryPiecePtr->memoryAddress) _ObjectType(std::forward<Args>(args)...);
	}



	/*
		���캯��
		������ʼ��
		������
			const Int32& _capacity ������С
			const Boolean&& _containerElementIfCallConstructor = false Ĭ�ϲ����ù��캯��
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::ZContainer(const Int32& _capacity, const Boolean&& _containerElementIfCallConstructor) :
		capacity(_capacity)
	{
		//��������ռ�Ĵ�С
		ZMemoryPiece::MemoryPieceSizeType memorySize = _capacity * sizeof(_ObjectType);
		//�����ڴ�
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
		//����ɹ�����ָ����ַ��new�ö�������ݣ������Ҫ�Ļ���,�����浽����ָ����
		if (_containerElementIfCallConstructor) 
		{
			new(memoryPiecePtr->memoryAddress) _ObjectType[_capacity];
		}
	}

	/*
		��������
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::~ZContainer() noexcept 
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
	const Void ZContainer<_ObjectType>::extend(const Int32& _capacity, const Boolean&& _containerElementIfCallConstructor) 
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
		//�����Ҫ��ʼ����չ�ڴ�
		if (_containerElementIfCallConstructor) {
			//����չ��λ���ϵ��ù��캯����ʼ���ڴ�
			new((Address)(((UIntAddress)(memoryPiecePtr->memoryAddress)) + originMemorySize)) _ObjectType[currentMemorySize - originMemorySize];
		}
		//�޸�������С
		capacity = _capacity;
	}

	/*
		��ȡ�����洢ָ��
		���أ�
			_ObjectType* �����洢ָ��
	*/
	template<typename _ObjectType>
	__forceinline _ObjectType* ZContainer<_ObjectType>::getObjectPtr() noexcept 
	{
		return (_ObjectType*)memoryPiecePtr->memoryAddress;
	}

	/*
		��ȡ�����洢ָ��
		���أ�
			const _ObjectType* �����洢ָ��
	*/
	template<typename _ObjectType>
	__forceinline const _ObjectType* ZContainer<_ObjectType>::getObjectPtr() const noexcept 
	{
		return (_ObjectType*)memoryPiecePtr->memoryAddress;
	}

	/*
		��ȡ������С
		���أ�
			const Int32& ������С
	*/
	template<typename _ObjectType>
	__forceinline const Int32& ZContainer<_ObjectType>::getCapacity() const noexcept 
	{
		return capacity;
	}

	/*
		��ȡ����Ԫ������
		���أ�
			const Int32& ����Ԫ������
	*/
	template<typename _ObjectType>
	__forceinline const Int32& ZContainer<_ObjectType>::getSize() const noexcept 
	{
		return size;
	}

	/*
		����Ԫ������
		������
			const Int32& ����Ԫ������
	*/
	template<typename _ObjectType>
	__forceinline const Void ZContainer<_ObjectType>::setSize(const Int32& _size) noexcept 
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
