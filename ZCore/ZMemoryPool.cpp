#include"ZCore/ZMemoryPool.h"

#pragma warning(disable : 6011)


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
		momoryPieceListArray(index).num = 0;
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



const Boolean ZMemoryPool::addMemoryPiece(const Int32& _type, const Int32& _num) {

}




/*
	����ڴ��
*/
const Boolean ZMemoryPool::initMemoryPieceList(const Int32& _type, const Int32& _num) {
	//��ʱ��ַ��������
	Address memoryApplyAddress;
	//�����ڴ������
	Int32 memoryApplyPieceNum;
	//�ڴ���ַ��UInt64���ͱ���
	UInt64 pieceAddress;
	//�ڴ���Ӧ�ڴ��ַ��UInt64���ͱ���
	UInt64 memoryAddress;

	//ʵ��ÿ���ڴ��Ĵ�С
	UInt64 pieceRealSize = MEMORY_PIECE_SIZE_ARRAY(_type) + sizeof(ZMemoryPiece);
	//Ĭ�ϴ�С��Ϊ0�����������ٸ�
	Int32 addPieceFixedNum = (Int32)(((((_num * pieceRealSize - 1) / APPLY_MEMORY_MIN_SIZE) + 1) * APPLY_MEMORY_MIN_SIZE) / pieceRealSize);

	//���������ڴ��С
	UInt64 memoryApplySize = pieceRealSize * addPieceFixedNum;
	//��������С�������ֵ��1��G��1��G����
	while (memoryApplySize > 0ULL) {
		//�����ڴ������
		if (memoryApplySize > APPLY_MEMORY_MAX_SIZE) {
			memoryApplyPieceNum = (Int32)(APPLY_MEMORY_MAX_SIZE / pieceRealSize);
		}
		else {
			memoryApplyPieceNum = (Int32)(memoryApplySize / pieceRealSize);
		}
		//�����ڴ�
		memoryApplyAddress = applyMemoryFromSystem(memoryApplyPieceNum * pieceRealSize);
		//�����ڴ��
		pieceAddress = (UInt64)memoryApplyAddress;
		memoryAddress = pieceAddress + sizeof(ZMemoryPiece) * memoryApplyPieceNum;
		//��ʼ���ڴ��
		for (Int32 pieceCount = 0; pieceCount < memoryApplyPieceNum; pieceCount++) {
			((ZMemoryPiece*)pieceAddress)->nextPiece = (ZMemoryPiece*)(pieceAddress + sizeof(ZMemoryPiece));
			((ZMemoryPiece*)pieceAddress)->memoryAddress = (Address)memoryAddress;
			((ZMemoryPiece*)pieceAddress)->type = _type;
			((ZMemoryPiece*)pieceAddress)->size = MEMORY_PIECE_SIZE_ARRAY(_type);
			pieceAddress = pieceAddress + sizeof(ZMemoryPiece);
			memoryAddress = memoryAddress + MEMORY_PIECE_SIZE_ARRAY(_type);
		}
		//��ʼ��ͷβ
		//β
		((ZMemoryPiece*)(pieceAddress - sizeof(ZMemoryPiece)))->nextPiece = momoryPieceListArray(_type).headPointer;
		//ͷ
		momoryPieceListArray(_type).headPointer = (ZMemoryPiece*)memoryApplyAddress;
		//��Ҫ�����ڴ���ܴ�С��ȥ��ǰ����Ĵ�С
		memoryApplySize -= memoryApplyPieceNum * pieceRealSize;
	}

	//�޸��ڴ������
	momoryPieceListArray(_type).num += addPieceFixedNum;
	return true;
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
	*((Address*)tempAddress) = systemMemoryAddress;	//���ڴ��Ϊ����ͷ
	systemMemoryAddress = tempAddress;
	return (Address)((UInt64)tempAddress + sizeof(Address));	//���������ڴ���λ�ĵ�ַ
}

