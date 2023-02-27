#ifndef ZObject_h
#define ZObject_h


#include"ZCoreDependence.h"
#include"ZMemoryPool.h"

namespace ZEngine {


	/*
		Object��
		˵����
			����Ϊ���࣬����Ҫʹ���ڴ�ص��඼��Ҫ�̳��Ը���
			�����ڴ�ؿռ�ĺ����Ĺؼ�����create���ͷſռ�ĺ����Ĺؼ�����destroy
			���������л��Զ��ͷŶ���Ŀռ�

	*/
	class ZObject {

	private:

		//ָ�������ڴ���ָ��
		ZMemoryPiece* piecePtr;

	protected:

		/*
			���캯��
		*/
		__forceinline ZObject();

		/*
			��������
		*/
		__forceinline ~ZObject();




		/*
			���ڴ�������ڴ棨���ʹ���ڴ�صĻ��������ʧ����ֱ�������ϵͳ�����ڴ�
			ģ��������д��Ҫ�����ڴ��ָ�����ͣ�����A�����и�CChar*��Ա������Ҫ�����ڴ棬����дCChar
			������
				ObjectType** _objectPointerPointer ����ռ��ַָ��
				const Int32& _objectNum ����ĸ��������ͻ���Ķ��������
				const Boolean& _ifInitialElement �Ƿ�������ĵ�ַ�ϸ���Object����������new����
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		template<typename _ObjectType>
		const Boolean create(_ObjectType** _objectPointerPointer, const Int32& _objectNum, const Boolean& _ifInitialElement);




		/*
			���ڴ����չ�ڴ棨���ʹ���ڴ�صĻ��������ʧ����ֱ�������ϵͳ�����ڴ�
			ģ��������д��Ҫ�����ڴ��ָ�����ͣ�����A�����и�CChar*��Ա������Ҫ�����ڴ棬����дCChar
			������
				ObjectType** _objectPointerPointer ����ռ��ַָ��
				const Int32& _oldObjectNum ��չ���������ͻ���Ķ������սǰ��������
				const Int32& _newObjectNum ��չ���������ͻ���Ķ������ս���������
				const Boolean& _ifInitialElement �Ƿ�����չ�ĵ�ַ�ϸ���Object����������new����
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		template<typename _ObjectType>
		const Boolean extend(_ObjectType** _objectPointerPointer, const Int32& _oldObjectNum, const Int32& _newObjectNum, const Boolean& _ifInitialElement);




		/*
			�ͷ��ڴ棬�Զ��ж��ͷŸ��ڴ�ػ��߲���ϵͳ
			���أ�
				const ErrorIndex ������
		*/
		const Void destroy();


		/*
			��ȡobject�ĵ�ַ
			���أ�
				const Address object�ĵ�ַ
		*/
		__forceinline const Address& getObjectAddress();


	private:



		/*
			���ڴ�������ڴ棬���ʧ����ֱ�������ϵͳ�����ڴ�
			������
				Object* _objectPointer ����ռ��ַָ��
				const UInt64& _applyMemorySize ������ڴ��С
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		__forceinline const Boolean applyMemoryFromMemoryPool(ZObject* _objectPointer, const UInt64& _applyMemorySize);

		/*
			�ͷ��ڴ棬�Զ��ж��ͷŸ��ڴ�ػ��߲���ϵͳ
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		__forceinline const Boolean releaseMemoryToMemoryPool();


		/*
			�����ϵͳ�����ڴ�
			������
				Object* _objectPointer ����ռ��ַָ��
				const UInt64& _applyMemorySize ������ڴ��С
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		__forceinline const Boolean applyMemoryFromSystem(ZObject* _objectPointer, const UInt64& _applyMemorySize);

		/*
			�����ϵͳ�ͷ��ڴ�
			���أ�
				const Boolean �Ƿ�ɹ�
		*/
		__forceinline const Boolean releaseMemoryToSystem();

	};

	/*
		���캯��
	*/
	__forceinline ZObject::ZObject() :
		piecePtr(nullptr),
		objectAddress(nullptr),
		size(0ULL)
	{
	}

	/*
		��������
	*/
	__forceinline ZObject::~ZObject()
	{
		if (this->objectAddress != nullptr) {
			destroy();
		}
	}


	/*
		���ڴ�������ڴ棨���ʹ���ڴ�صĻ��������ʧ����ֱ�������ϵͳ�����ڴ�
		ģ��������д��Ҫ�����ڴ��ָ�����ͣ�����A�����и�CChar*��Ա������Ҫ�����ڴ棬����дCChar
		������
			ObjectType** _objectPointerPointer ����ռ��ַָ��
			const Int32& _objectNum ����ĸ��������ͻ���Ķ��������
			const Boolean& _ifInitialElement �Ƿ�������ĵ�ַ�ϸ���Object����������new����
		���أ�
			const Boolean �Ƿ�ɹ�
	*/
	template<typename _ObjectType>
	const Boolean ZObject::create(_ObjectType** _objectPointerPointer, const Int32& _objectNum, const Boolean& _ifInitialElement) {

		//��������ռ�Ĵ�С
		UInt64 objectSize = _objectNum * sizeof(_ObjectType);

		/*�����ڴ�*/

		//�����ǰ���ڴ泤�Ȳ�����֧�Ŵ����µ�object
		if (this->size < objectSize) {

			//��ʱobject������ȡ�ڴ棬��ֹ��ȡʧ�ܺ�ɾ��ԭ��object
			ZObject tempObject;

			//�ж��ڴ���Ƿ���ڣ�������ֱ�������ϵͳ�����ڴ�
			if (ZEngine::MemoryPool::CurrentMemoryPoolPointer == nullptr) {
				//����ʧ���򷵻ش�����
				IfFalseReturnFalse(applyMemoryFromSystem(&tempObject, objectSize), ErrorMessage::OBJECT_APPLY_MEMORY_FROM_SYETEM_FAILED_MESSAGE);
			}
			//���ڴ�������ڴ�
			else {
				//����ʧ���������ϵͳ�����ڴ�
				if (applyMemoryFromMemoryPool(&tempObject, objectSize) == false) {
					//ErrorMessageOutput(ErrorMessage::OBJECT_APPLY_MEMORY_FROM_MEMORY_POOL_FAILED_MESSAGE);
					IfFalseReturnFalse(applyMemoryFromSystem(&tempObject, objectSize), ErrorMessage::OBJECT_APPLY_MEMORY_FROM_SYETEM_FAILED_MESSAGE);
				}
			}

			//�ͷŵ�ǰ��objectռ�õ��ڴ�
			destroy();
			//����ʱobjectת��Ϊ��ǰobject
			memcpy(this, &tempObject, sizeof(ZObject));
			//��ֹ������ʱ����ʱ�ͷ��ڴ�
			tempObject.objectAddress = nullptr;
		}


		//����ɹ�����ָ����ַ��new�ö�������ݣ������Ҫ�Ļ���
		*_objectPointerPointer = _ifInitialElement ? new(this->objectAddress) _ObjectType[_objectNum] : (_ObjectType*)this->objectAddress;

		return true;
	}



	/*
		���ڴ����չ�ڴ棨���ʹ���ڴ�صĻ��������ʧ����ֱ�������ϵͳ�����ڴ�
		ģ��������д��Ҫ�����ڴ��ָ�����ͣ�����A�����и�CChar*��Ա������Ҫ�����ڴ棬����дCChar
		������
			ObjectType** _objectPointerPointer ����ռ��ַָ��
			const Int32& _oldObjectNum ��չ���������ͻ���Ķ������սǰ��������
			const Int32& _newObjectNum ��չ���������ͻ���Ķ������ս���������
			const Boolean& _ifInitialElement �Ƿ�����չ�ĵ�ַ�ϸ���Object����������new����
		���أ�
			const Boolean �Ƿ�ɹ�
	*/
	template<typename _ObjectType>
	const Boolean ZObject::extend(_ObjectType** _objectPointerPointer, const Int32& _oldObjectNum, const Int32& _newObjectNum, const Boolean& _ifInitialElement) {


		//�ж���չ��С�Ƿ�Ϊ������
		if (_newObjectNum <= _oldObjectNum) {
			return true;
		}



		//�жϵ�ǰobject�Ƿ����,����������д���
		if (this->objectAddress == nullptr) {
			return this->create(_objectPointerPointer, _newObjectNum, _ifInitialElement);
		}

		//����ǰ�Ĵ�С
		UInt64 oldObjectSize = _oldObjectNum * sizeof(_ObjectType);
		//������Ĵ�С
		UInt64 newObjectSize = _newObjectNum * sizeof(_ObjectType);
		//��Ҫ�����Ĵ�С
		UInt64 addObjectSize = newObjectSize - oldObjectSize;

		//�����ǰ���ڴ泤�Ȳ�����֧����չobject
		if (this->size < newObjectSize) {

			//��ʱobject������ȡ�ڴ棬��ֹ��ȡʧ�ܺ�ɾ��ԭ��object
			ZObject tempObject;

			//�ж��ڴ���Ƿ���ڣ�������ֱ�������ϵͳ�����ڴ�
			if (ZEngine::MemoryPool::CurrentMemoryPoolPointer == nullptr) {
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
			memcpy(this, &tempObject, sizeof(ZObject));
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

	/*
		��ȡobject�ĵ�ַ
		���أ�
			const Address object�ĵ�ַ
	*/
	__forceinline const Address& ZObject::getObjectAddress() {
		return this->objectAddress;
	}


	/*
		���ڴ�������ڴ棬���ʧ����ֱ�������ϵͳ�����ڴ�
		������
			Object* _objectPointer ����ռ��ַָ��
			const UInt64& _applyMemorySize ������ڴ��С
		���أ�
			const Boolean �Ƿ�ɹ�
	*/
	__forceinline const Boolean ZObject::applyMemoryFromMemoryPool(ZObject* _objectPointer, const UInt64& _applyMemorySize) {
		//�ж��Ƿ��Ѿ����ڴ�������������������ʹ��ԭ���ڴ��
		if (this->piecePtr == nullptr) {
			IfFalseReturnFalse(ZEngine::MemoryPool::CurrentMemoryPoolPointer->applyMemory(_objectPointer, _applyMemorySize), ErrorMessage::OBJECT_APPLY_MEMORY_FROM_MEMORY_POOL_FAILED_MESSAGE);
		}
		else {
			IfFalseReturnFalse(this->piecePtr->ownerMemoryPoolPointer->applyMemory(_objectPointer, _applyMemorySize), ErrorMessage::OBJECT_APPLY_MEMORY_FROM_MEMORY_POOL_FAILED_MESSAGE);
		}
		return true;
	}

	/*
		�ͷ��ڴ棬�Զ��ж��ͷŸ��ڴ�ػ��߲���ϵͳ
		���أ�
			const Boolean �Ƿ�ɹ�
	*/
	__forceinline const Boolean ZObject::releaseMemoryToMemoryPool() {
		return ZEngine::MemoryPool::CurrentMemoryPoolPointer->releaseMemory(this);
	}

	/*
		�����ϵͳ�����ڴ�
		������
			Object* _objectPointer ����ռ��ַָ��
			const UInt64& _applyMemorySize ������ڴ��С
		���أ�
			const Boolean �Ƿ�ɹ�
	*/
	__forceinline const Boolean ZObject::applyMemoryFromSystem(ZObject* _objectPointer, const UInt64& _applyMemorySize) {
		_objectPointer->objectAddress = malloc(_applyMemorySize);
		IfNullptrReturnFalse(_objectPointer->objectAddress, ErrorMessage::OBJECT_OUT_OF_MEMORY_MESSAGE);
		this->size = _applyMemorySize;
		return true;
	}

	/*
		�����ϵͳ�ͷ��ڴ�
		���أ�
			const Boolean ������
	*/
	__forceinline const Boolean ZObject::releaseMemoryToSystem() {
		free(this->objectAddress);
		return true;
	}



}


#endif // !ZObject_h
