#ifndef ZContainer_h
#define ZContainer_h


#include"ZCoreDependence.h"
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
	class ZContainer: ZObject{

	protected:

		/*
			���캯��
			��Ԫ��������ʼ��
			������
				_ObjectType** _objectPtrPtr ����ָ���ָ��
				const Int32& _size ������С
				const Boolean&& _containerElementIfCallConstructor = false Ĭ�ϲ����ù��캯��
		*/
		template<typename _ObjectType>
		__forceinline ZContainer(_ObjectType** _objectPtrPtr, const Int32& _size, const Boolean&& _containerElementIfCallConstructor = false);

		/*
			��������
		*/
		__forceinline ~ZContainer();


		/*
			��Ԫ��������չ����
			������
				const Int32& _originSize ԭ��������С
				const Int32& _currentSize ��չ��������С
				const Boolean&& _containerElementIfCallConstructor = false Ĭ�ϲ����ù��캯��
		*
		template<typename _ObjectType>
		_ObjectType* extend(const Int32& _originSize, const Int32& _currentSize, const Boolean&& _containerElementIfCallConstructor = false) {

			//����ǰ�Ĵ�С
			UInt64 oldObjectSize = _oldObjectNum * sizeof(_ObjectType);
			//������Ĵ�С
			UInt64 newObjectSize = _newObjectNum * sizeof(_ObjectType);
			//��Ҫ�����Ĵ�С
			UInt64 addObjectSize = newObjectSize - oldObjectSize;

			//�����ǰ���ڴ泤�Ȳ�����֧����չobject
			if (this->size < newObjectSize) {

				//��ʱobject������ȡ�ڴ棬��ֹ��ȡʧ�ܺ�ɾ��ԭ��object
				Object tempObject;

				//�ж��ڴ���Ƿ���ڣ�������ֱ�������ϵͳ�����ڴ�
				if (Core::MemoryPool::CurrentMemoryPoolPointer == nullptr) {
					//����ʧ���򷵻�
					IfFalseReturnFalse(applyMemoryFromSystem(&tempObject, newObjectSize), ErrorMessage::OBJECT_APPLY_MEMORY_FROM_SYETEM_FAILED_MESSAGE);
				}
				//���ڴ�������ڴ�
				else {
					//����ʧ���������ϵͳ�����ڴ�
					if (applyMemoryFromMemoryPool(&tempObject, newObjectSize) == false) {
						//ErrorMessageOutput(ErrorMessage::OBJECT_APPLY_MEMORY_FROM_MEMORY_POOL_FAILED_MESSAGE);
						IfFalseReturnFalse(applyMemoryFromSystem(&tempObject, newObjectSize), ErrorMessage::OBJECT_APPLY_MEMORY_FROM_SYETEM_FAILED_MESSAGE);

					}
				}

				//������ĵ�ַָ��ָ���µĵ�ַ
				*_objectPointerPointer = (_ObjectType*)tempObject.objectAddress;
				//����ǰobject���������ת������ʱobject��
				memcpy(tempObject.objectAddress, this->objectAddress, oldObjectSize);
				//�ͷŵ�ǰ��objectռ�õ��ڴ�
				destroy();
				//����ʱobjectת��Ϊ��ǰobject
				memcpy(this, &tempObject, sizeof(Object));
				//��ֹ������ʱ����ʱ�ͷ��ڴ�
				tempObject.objectAddress = nullptr;
			}

			//�����Ҫ��ʼ����չ�ڴ�
			if (_ifInitialElement == true) {
				//����չ�ռ�λ���ϵ��ù��캯����ʼ���ڴ�
				//for (Int32 objectCount = 0; objectCount < newObjectNum - oldObjectNum; objectCount++) {
				new((Address)(((UInt64)*_objectPointerPointer) + oldObjectSize)) _ObjectType[_newObjectNum - _oldObjectNum];
				//}
			}

			return true;
		}
		*/

	private:

		//�ڴ��ָ��
		ZMemoryPiece* memoryPiecePtr;

	};

	/*
		���캯��
		��Ԫ��������ʼ��
		������
			_ObjectType** _objectPtrPtr ����ָ���ָ��
			const Int32& _size ������С
			const Boolean&& _containerElementIfCallConstructor = false Ĭ�ϲ����ù��캯��
	*/
	template<typename _ObjectType>
	__forceinline ZContainer::ZContainer(_ObjectType** _objectPtrPtr, const Int32& _size, const Boolean&& _containerElementIfCallConstructor) {
		//��������ռ�Ĵ�С
		ZMemoryPool::MemoryPieceSizeType applyMemorySize = _size * sizeof(_ObjectType);
		//�����ڴ�
		memoryPiecePtr = ZMemoryPool::InstancePtr->applyMemory(applyMemorySize);
		//����ɹ�����ָ����ַ��new�ö�������ݣ������Ҫ�Ļ���,�����浽����ָ����
		*_objectPtrPtr = _containerElementIfCallConstructor ? new(memoryPiecePtr->memoryAddress) _ObjectType[_size] : (_ObjectType*)memoryPiecePtr->memoryAddress;
	}

	/*
		��������
	*/
	__forceinline ZContainer::~ZContainer() {
		//�ͷ��ڴ�
		if (memoryPiecePtr != nullptr) {
			ZMemoryPool::InstancePtr->releaseMemory(memoryPiecePtr);
		}
	}



}


#endif // !ZContainer_h
