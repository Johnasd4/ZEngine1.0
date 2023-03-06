#define DLL_API_FILE

#include"ZMemoryPool.h"

#pragma warning(disable : 6011)


using namespace ZEngine;
using namespace ZEngine::Private;


//����ָ��
DLL_API ZMemoryPool* ZMemoryPool::InstancePtr = nullptr;

/*
	��������
*/
DLL_API const Void ZMemoryPool::CreateInstance() noexcept
{
	static ZMemoryPool memoryPool;
	ZMemoryPool::InstancePtr = &memoryPool;
}

/*
	�����ڴ�
	������
		const ZMemoryPiece::MemoryPieceSizeType& _size �����ڴ�Ĵ�С
	���أ�
		const ZMemoryPiece* �ڴ��ָ��
*/
DLL_API ZMemoryPiece* ZMemoryPool::applyMemory(const ZMemoryPiece::MemoryPieceSizeType& _size) noexcept
{

#ifdef MEMORY_POOL_THREAD_SAFE
	//�߳���
	mutex.lock();
#endif //MEMORY_POOL_THREAD_SAFE

	ZMemoryPiece* memoryPiecePtr = nullptr;

	/*���볣���ڴ��*/

	for (Int32 index = 0; index < MEMORY_PIECE_TYPE_NUM; index++) 
	{
		//�Ƿ񳬹���ǰ�ڴ�����洢��С
		if (_size > MEMORY_PIECE_SIZE_ARRAY(index)) 
		{
			continue;
		}
		//�����ڴ�
		if (momoryPieceListArray(index).headPointer == nullptr) 
		{
			//�������Զ������ڴ�
			this->autoAddMemoryPiece(index);
		}
		//��ȡ�����ڴ��ĵ�ַ
		memoryPiecePtr = momoryPieceListArray(index).headPointer;

		//����ǰָ��ָ����һ���ڴ��
		momoryPieceListArray(index).headPointer = momoryPieceListArray(index).headPointer->nextMemoryPiece;

#ifdef MEMORY_POOL_TEST_SIZE
		momoryPieceListUsedArray(index) += 1;
		momoryPieceListApplyedArray(index) += 1;
		if (momoryPieceListUsedMaxArray(index) < momoryPieceListUsedArray(index)) 
		{
			momoryPieceListUsedMaxArray(index) = momoryPieceListUsedArray(index);
		}
#endif // MEMORY_POOL_TEST_SIZE

		break;
	}

	/*������ڴ��*/


#ifdef MEMORY_POOL_THREAD_SAFE
	//�߳���
	mutex.unLock();
#endif //MEMORY_POOL_THREAD_SAFE

	return memoryPiecePtr;
}

/*
	�ͷ��ڴ�
	������
		ZMemoryPiece* _memoryPiecePtr �ڴ��ָ��
*/
DLL_API const Void ZMemoryPool::releaseMemory(ZMemoryPiece* _memoryPiecePtr) noexcept
{
	//�ж��ڴ���Ƭ�Ƿ����
	if(_memoryPiecePtr == nullptr){
		return;
	}

#ifdef MEMORY_POOL_THREAD_SAFE
	//�߳���
	mutex.lock();
#endif //MEMORY_POOL_THREAD_SAFE


	//���ͷŵ��ڴ��ָ��ͷָ��
	_memoryPiecePtr->nextMemoryPiece = momoryPieceListArray(_memoryPiecePtr->type).headPointer;
	//ͷָ��ָ��ǰ�ڴ��
	momoryPieceListArray(_memoryPiecePtr->type).headPointer = _memoryPiecePtr;

#ifdef MEMORY_POOL_TEST_SIZE
	momoryPieceListUsedArray(_memoryPiecePtr->type) -= 1;
#endif // MEMORY_POOL_TEST_SIZE

#ifdef MEMORY_POOL_THREAD_SAFE
	//�߳���
	mutex.unLock();
#endif //MEMORY_POOL_THREAD_SAFE

}



/*
	���캯��
*/
ZMemoryPool::ZMemoryPool() noexcept :
	systemMemoryAddress(nullptr)
{
	//��ʼ��ÿ���ڴ������
	for (Int32 index = 0; index < MEMORY_PIECE_TYPE_NUM; index++) 
	{
		momoryPieceListArray(index).headPointer = nullptr;
		momoryPieceListArray(index).num = 0;
		initMemoryPieceList(index);

#ifdef MEMORY_POOL_TEST_SIZE

		momoryPieceListUsedArray(index) = 0;
		momoryPieceListUsedMaxArray(index) = 0;
		momoryPieceListApplyedArray(index) = 0;

#endif // MEMORY_POOL_TEST_SIZE

	}


}

/*
	��������
*/
ZMemoryPool::~ZMemoryPool() noexcept
{

	/*�ͷ��ڴ�ص��ڴ�*/

	//��һ���ڴ�
	Address nextSystemMemoryAddress;
	while (systemMemoryAddress != nullptr) 
	{
		//�ݴ���һ�ڴ���ַ	
		nextSystemMemoryAddress = *((Address*)systemMemoryAddress);
		//�ͷŵ�ǰ�ڴ��
		free(systemMemoryAddress);
		//������ͷָ����һ���ڴ��ַ
		systemMemoryAddress = nextSystemMemoryAddress;
	}

#ifdef MEMORY_POOL_TEST_SIZE

	printf("\n/*********�ڴ��ʹ�����*********/\n");
	for (Int32 index = 0; index < MEMORY_PIECE_TYPE_NUM; index++) 
	{
		printf("��� %d:��СΪ %u ���ڴ��ͬʱʹ���������Ϊ %d ��,������ %d ��,�ͷ��ڴ��ʱ %d ��δ�ͷ�\n",
			index,
			MEMORY_PIECE_SIZE_ARRAY(index),
			momoryPieceListUsedMaxArray(index),
			momoryPieceListApplyedArray(index),
			momoryPieceListUsedArray(index)
		);
	}

#endif // MEMORY_POOL_TEST_SIZE

}





/*
	����ڴ��
	������
		const Int32 _type �ڴ������
*/
const Void ZMemoryPool::initMemoryPieceList(const Int32 _type) noexcept
{
	//��Ҫ�����ڴ������
	Int32 addPieceNum = MEMORY_POOL_SIZE_DEFAULT_ARRAY(_type);
	//��������С�������ֵ��1��G��1��G����
	while (addPieceNum > ADD_PIECE_MAX_NUM_ARRAY(_type)) 
	{
		//�����ڴ��
		addMemoryPiece(_type, ADD_PIECE_MAX_NUM_ARRAY(_type));
		//��Ҫ�����ڴ���ܴ�С��ȥ��ǰ����Ĵ�С
		addPieceNum -= ADD_PIECE_MAX_NUM_ARRAY(_type);
	}
	//�Ƿ�����Ҫ�����
	if (addPieceNum == 0) 
	{
		return;
	}

	//���С����������Сֵ�򲹳�
	if (addPieceNum < ADD_PIECE_MIN_NUM_ARRAY(_type)) 
	{
		addPieceNum = ADD_PIECE_MIN_NUM_ARRAY(_type);
	}
	//�����ڴ��
	addMemoryPiece(_type, addPieceNum);
}

/*
	����ڴ��
	������
		const Int32 _type �ڴ������
*/
const Void ZMemoryPool::autoAddMemoryPiece(const Int32 _type) noexcept
{
	Int32 addPieceNum = (Int32)(momoryPieceListArray(_type).num * MEMORY_PIECE_AUTO_EXTEND_MUL_FACTOR);
	//�ж������Ƿ���ٻ��߹���
	if (addPieceNum < ADD_PIECE_MIN_NUM_ARRAY(_type)) 
	{
		addPieceNum = ADD_PIECE_MIN_NUM_ARRAY(_type);
	}
	else if (addPieceNum > ADD_PIECE_MAX_NUM_ARRAY(_type)) 
	{
		addPieceNum = ADD_PIECE_MAX_NUM_ARRAY(_type);
	}
	//�����ڴ��
	addMemoryPiece(_type, addPieceNum);
}

/*
	Ϊ�ڴ������ڴ��
	������
		const Int32 _type �ڴ������
		const Int32 _num �ڴ������
*/
const Void ZMemoryPool::addMemoryPiece(const Int32 _type, const Int32 _num) noexcept
{
	//�����ڴ�
	Address memoryApplyAddress = malloc(_num * MEMORY_PIECE_WITH_CLASS_SIZE_ARRAY(_type) + sizeof(Address));//������һ����ַ��С���ڴ���������洢
	*((Address*)memoryApplyAddress) = systemMemoryAddress;	//���ڴ��Ϊ����ͷ
	systemMemoryAddress = memoryApplyAddress;
	//����ַָ��ȥ��ͷ����Ϣ���ڴ��ĵ�ַ
	memoryApplyAddress = (Address)((UIntAddress)memoryApplyAddress + sizeof(Address));
	//�����ڴ��
	UIntAddress pieceAddress = (UIntAddress)memoryApplyAddress;
	UIntAddress memoryAddress = pieceAddress + sizeof(ZMemoryPiece) * _num;
	//��ʼ���ڴ��
	for (Int32 pieceCount = 0; pieceCount < _num; pieceCount++) 
	{
		((ZMemoryPiece*)pieceAddress)->nextMemoryPiece = (ZMemoryPiece*)(pieceAddress + sizeof(ZMemoryPiece));
		((ZMemoryPiece*)pieceAddress)->memoryAddress = (Address)memoryAddress;
		((ZMemoryPiece*)pieceAddress)->type = _type;
		((ZMemoryPiece*)pieceAddress)->size = MEMORY_PIECE_SIZE_ARRAY(_type);
		pieceAddress = pieceAddress + sizeof(ZMemoryPiece);
		memoryAddress = memoryAddress + MEMORY_PIECE_SIZE_ARRAY(_type);
	}
	//��ʼ��ͷβ
	//β
	((ZMemoryPiece*)(pieceAddress - sizeof(ZMemoryPiece)))->nextMemoryPiece = momoryPieceListArray(_type).headPointer;
	//ͷ
	momoryPieceListArray(_type).headPointer = (ZMemoryPiece*)(memoryApplyAddress);
	//�����б�����
	momoryPieceListArray(_type).num += _num;



}
