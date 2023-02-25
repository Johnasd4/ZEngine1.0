#include"ZCore/ZMemoryPool.h"

using namespace ZEngine;
using namespace ZEngine::Private;


//����ָ��
ZMemoryPool* ZMemoryPool::InstancePtr = nullptr;

/*
	��������
*/
const Void ZMemoryPool::CreateInstance() {
	static ZMemoryPool memoryPool;
	ZMemoryPool::InstancePtr = &memoryPool;
}

/*
	���캯��
*/
ZMemoryPool::ZMemoryPool() :
	systemMemoryAddress(nullptr)
{
	//��ʼ��ÿ���ڴ������
	for (Int32 index = 0; index < MEMORY_PIECE_TYPE_NUM; index++) {
		momoryPieceListArray(index).headPointer = nullptr;
		momoryPieceListArray(index).pieceNum = 0;
	}


}

/*
	��������
*/
ZMemoryPool::~ZMemoryPool() {

	/*�ͷ��ڴ�ص��ڴ�*/

	//��һ���ڴ�
	Address nextSystemMemoryAddress;
	while (systemMemoryAddress != nullptr) {
		//�ݴ���һ�ڴ���ַ	
		nextSystemMemoryAddress = *((Address*)systemMemoryAddress);
		//�ͷŵ�ǰ�ڴ��
		free(systemMemoryAddress);
		//������ͷָ����һ���ڴ��ַ
		systemMemoryAddress = nextSystemMemoryAddress;
	}

}


/*
	��ϵͳ�����ڴ�
	������
		const UInt64& _applySize �����ڴ�Ĵ�С
	���أ�
		const Boolean �Ƿ�����ɹ�
*/
const Address ZMemoryPool::applyMemoryFromSystem(const UInt64& _applySize) {
	Address tempAddress = malloc(_applySize + sizeof(Address));//������һ����ַ��С���ڴ���������洢
	*(Address*)tempAddress = systemMemoryAddress;	//���ڴ��Ϊ����ͷ
	systemMemoryAddress = tempAddress;
	return (Address)((UInt64)tempAddress + sizeof(Address));	//���������ڴ���λ�ĵ�ַ
}