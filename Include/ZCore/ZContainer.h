#ifndef ZContainer_h
#define ZContainer_h

#include"ZObject.h"
#include"ZMemoryPool.h"

namespace ZEngine {


	/*
		ZContainer��
		˵����
			����Ϊ�������࣬���������̳��Ը���
			��Ҫ��չ��������ʱʹ��extend������
			���������л��Զ��ͷ��ڴ档
	*/
	template<typename _ObjectType>
	class ZContainer: ZObject{

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
				_ObjectType** _objectPtrPtr ������ַָ��
				const Int32& _size ������С
				const Boolean&& _containerElementIfCallConstructor = false Ĭ�ϲ����ù��캯��
		*/
		
		__forceinline ZContainer(_ObjectType** _objectPtrPtr, const Int32& _size, const Boolean&& _containerElementIfCallConstructor = false);

		/*
			��������
		*/
		__forceinline ~ZContainer();


		/*
			��Ԫ��������չ����
			������
				_ObjectType** _objectPtrPtr ������ַָ��
				const Int32& _originSize ԭ��������С
				const Int32& _currentSize ��չ��������С
				const Boolean&& _containerElementIfCallConstructor = false Ĭ�ϲ����ù��캯��
		*/
		const Void extend(_ObjectType** _objectPtrPtr, const Int32& _originSize, const Int32& _currentSize, const Boolean&& _containerElementIfCallConstructor = false);

		_ObjectType* getObjectPtr() const;
		const Int32& getSize();

	private:
		//�ڴ��ָ��
		ZMemoryPiece* memoryPiecePtr;

		//�����Ĵ�С
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
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(sizeof(_ObjectType));
		//����ɹ�����ָ����ַ��new�ö�������ݣ������Ҫ�Ļ���,�����浽����ָ����
		*_objectPtrPtr = new(memoryPiecePtr->memoryAddress) _ObjectType(std::forward<Args>(args)...);
	}



	/*
		���캯��
		��Ԫ��������ʼ��
		������
			_ObjectType** _objectPtrPtr ������ַָ��
			const Int32& _size ������С
			const Boolean&& _containerElementIfCallConstructor = false Ĭ�ϲ����ù��캯��
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::ZContainer(_ObjectType** _objectPtrPtr, const Int32& _size, const Boolean&& _containerElementIfCallConstructor) {
		//��������ռ�Ĵ�С
		ZMemoryPiece::MemoryPieceSizeType memorySize = _size * sizeof(_ObjectType);
		//�����ڴ�
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(memorySize);
		//����ɹ�����ָ����ַ��new�ö�������ݣ������Ҫ�Ļ���,�����浽����ָ����
		*_objectPtrPtr = _containerElementIfCallConstructor ? new(memoryPiecePtr->memoryAddress) _ObjectType[_size] : (_ObjectType*)memoryPiecePtr->memoryAddress;
	}

	/*
		��������
	*/
	template<typename _ObjectType>
	__forceinline ZContainer<_ObjectType>::~ZContainer() {
		//�ͷ��ڴ�
		ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
	}

	/*
		��Ԫ��������չ����
		������
			_ObjectType** _objectPtrPtr ������ַָ��
			const Int32& _originSize ԭ��������С
			const Int32& _currentSize ��չ��������С
			const Boolean&& _containerElementIfCallConstructor = false Ĭ�ϲ����ù��캯��
	*/
	template<typename _ObjectType>
	const Void ZContainer<_ObjectType>::extend(_ObjectType** _objectPtrPtr, const Int32& _originSize, const Int32& _currentSize, const Boolean&& _containerElementIfCallConstructor) {

		//��չǰ������Ҫ���ڴ��С
		ZMemoryPiece::MemoryPieceSizeType originMemorySize = _originSize * sizeof(_ObjectType);
		//��չ��������Ҫ���ڴ��С
		ZMemoryPiece::MemoryPieceSizeType currentMemorySize = _currentSize * sizeof(_ObjectType);
		//�жϵ�ǰ�ڴ���Ƿ񲻹���
		if (_currentSize * sizeof(_ObjectType) > memoryPiecePtr->size) {
			//���ڴ�������ڴ�
			ZMemoryPiece* tempMemoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(currentMemorySize);
			//����ǰ�ڴ�鱣�������ת������ʱ�ڴ����
			memcpy(tempMemoryPiecePtr->memoryAddress, (Address)_objectPtrPtr, originMemorySize);
			//�ͷŵ�ǰ�ڴ��
			ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
			//���µ�������ַ����������ַָ��
			*_objectPtrPtr = (_ObjectType*)tempMemoryPiecePtr->memoryAddress;
			//�޸ĵ�ǰ�������ڴ��
			memoryPiecePtr = tempMemoryPiecePtr;
		}
		//�����Ҫ��ʼ����չ�ڴ�
		if (_containerElementIfCallConstructor) {
			//����չ��λ���ϵ��ù��캯����ʼ���ڴ�
			new((Address)(((UIntAddress)(*_objectPtrPtr)) + originMemorySize)) _ObjectType[currentMemorySize - originMemorySize];
		}
	}

}


#endif // !ZContainer_h
