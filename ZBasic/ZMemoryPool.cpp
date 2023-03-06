#define DLL_API_FILE

#include"ZMemoryPool.h"

#pragma warning(disable : 6011)


using namespace ZEngine;
using namespace ZEngine::Private;


//单例指针
DLL_API ZMemoryPool* ZMemoryPool::InstancePtr = nullptr;

/*
	创建单例
*/
DLL_API const Void ZMemoryPool::CreateInstance() noexcept
{
	static ZMemoryPool memoryPool;
	ZMemoryPool::InstancePtr = &memoryPool;
}

/*
	申请内存
	参数：
		const ZMemoryPiece::MemoryPieceSizeType& _size 申请内存的大小
	返回：
		const ZMemoryPiece* 内存块指针
*/
DLL_API ZMemoryPiece* ZMemoryPool::applyMemory(const ZMemoryPiece::MemoryPieceSizeType& _size) noexcept
{

#ifdef MEMORY_POOL_THREAD_SAFE
	//线程锁
	mutex.lock();
#endif //MEMORY_POOL_THREAD_SAFE

	ZMemoryPiece* memoryPiecePtr = nullptr;

	/*申请常规内存块*/

	for (Int32 index = 0; index < MEMORY_PIECE_TYPE_NUM; index++) 
	{
		//是否超过当前内存链表存储大小
		if (_size > MEMORY_PIECE_SIZE_ARRAY(index)) 
		{
			continue;
		}
		//分配内存
		if (momoryPieceListArray(index).headPointer == nullptr) 
		{
			//不足则自动申请内存
			this->autoAddMemoryPiece(index);
		}
		//获取返回内存块的地址
		memoryPiecePtr = momoryPieceListArray(index).headPointer;

		//将当前指针指向下一个内存块
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

	/*申请大内存块*/


#ifdef MEMORY_POOL_THREAD_SAFE
	//线程锁
	mutex.unLock();
#endif //MEMORY_POOL_THREAD_SAFE

	return memoryPiecePtr;
}

/*
	释放内存
	参数：
		ZMemoryPiece* _memoryPiecePtr 内存块指针
*/
DLL_API const Void ZMemoryPool::releaseMemory(ZMemoryPiece* _memoryPiecePtr) noexcept
{
	//判断内存碎片是否存在
	if(_memoryPiecePtr == nullptr){
		return;
	}

#ifdef MEMORY_POOL_THREAD_SAFE
	//线程锁
	mutex.lock();
#endif //MEMORY_POOL_THREAD_SAFE


	//将释放的内存块指向头指针
	_memoryPiecePtr->nextMemoryPiece = momoryPieceListArray(_memoryPiecePtr->type).headPointer;
	//头指针指向当前内存块
	momoryPieceListArray(_memoryPiecePtr->type).headPointer = _memoryPiecePtr;

#ifdef MEMORY_POOL_TEST_SIZE
	momoryPieceListUsedArray(_memoryPiecePtr->type) -= 1;
#endif // MEMORY_POOL_TEST_SIZE

#ifdef MEMORY_POOL_THREAD_SAFE
	//线程锁
	mutex.unLock();
#endif //MEMORY_POOL_THREAD_SAFE

}



/*
	构造函数
*/
ZMemoryPool::ZMemoryPool() noexcept :
	systemMemoryAddress(nullptr)
{
	//初始化每种内存块链表
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
	析构函数
*/
ZMemoryPool::~ZMemoryPool() noexcept
{

	/*释放内存池的内存*/

	//下一块内存
	Address nextSystemMemoryAddress;
	while (systemMemoryAddress != nullptr) 
	{
		//暂存下一内存块地址	
		nextSystemMemoryAddress = *((Address*)systemMemoryAddress);
		//释放当前内存块
		free(systemMemoryAddress);
		//将链表头指向下一块内存地址
		systemMemoryAddress = nextSystemMemoryAddress;
	}

#ifdef MEMORY_POOL_TEST_SIZE

	printf("\n/*********内存池使用情况*********/\n");
	for (Int32 index = 0; index < MEMORY_PIECE_TYPE_NUM; index++) 
	{
		printf("编号 %d:大小为 %u 的内存块同时使用数量最多为 %d 块,共申请 %d 次,释放内存池时 %d 块未释放\n",
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
	添加内存块
	参数：
		const Int32 _type 内存块类型
*/
const Void ZMemoryPool::initMemoryPieceList(const Int32 _type) noexcept
{
	//需要申请内存块数量
	Int32 addPieceNum = MEMORY_POOL_SIZE_DEFAULT_ARRAY(_type);
	//如果申请大小大于最大值则1个G，1个G申请
	while (addPieceNum > ADD_PIECE_MAX_NUM_ARRAY(_type)) 
	{
		//申请内存块
		addMemoryPiece(_type, ADD_PIECE_MAX_NUM_ARRAY(_type));
		//需要申请内存的总大小减去当前申请的大小
		addPieceNum -= ADD_PIECE_MAX_NUM_ARRAY(_type);
	}
	//是否还有需要申请的
	if (addPieceNum == 0) 
	{
		return;
	}

	//如果小于最申请最小值则补充
	if (addPieceNum < ADD_PIECE_MIN_NUM_ARRAY(_type)) 
	{
		addPieceNum = ADD_PIECE_MIN_NUM_ARRAY(_type);
	}
	//申请内存块
	addMemoryPiece(_type, addPieceNum);
}

/*
	添加内存块
	参数：
		const Int32 _type 内存块类型
*/
const Void ZMemoryPool::autoAddMemoryPiece(const Int32 _type) noexcept
{
	Int32 addPieceNum = (Int32)(momoryPieceListArray(_type).num * MEMORY_PIECE_AUTO_EXTEND_MUL_FACTOR);
	//判断数量是否过少或者过多
	if (addPieceNum < ADD_PIECE_MIN_NUM_ARRAY(_type)) 
	{
		addPieceNum = ADD_PIECE_MIN_NUM_ARRAY(_type);
	}
	else if (addPieceNum > ADD_PIECE_MAX_NUM_ARRAY(_type)) 
	{
		addPieceNum = ADD_PIECE_MAX_NUM_ARRAY(_type);
	}
	//申请内存块
	addMemoryPiece(_type, addPieceNum);
}

/*
	为内存池添加内存块
	参数：
		const Int32 _type 内存块类型
		const Int32 _num 内存块数量
*/
const Void ZMemoryPool::addMemoryPiece(const Int32 _type, const Int32 _num) noexcept
{
	//申请内存
	Address memoryApplyAddress = malloc(_num * MEMORY_PIECE_WITH_CLASS_SIZE_ARRAY(_type) + sizeof(Address));//多申请一个地址大小的内存用于链表存储
	*((Address*)memoryApplyAddress) = systemMemoryAddress;	//新内存块为链表头
	systemMemoryAddress = memoryApplyAddress;
	//将地址指向去除头部信息的内存块的地址
	memoryApplyAddress = (Address)((UIntAddress)memoryApplyAddress + sizeof(Address));
	//分配内存块
	UIntAddress pieceAddress = (UIntAddress)memoryApplyAddress;
	UIntAddress memoryAddress = pieceAddress + sizeof(ZMemoryPiece) * _num;
	//初始化内存块
	for (Int32 pieceCount = 0; pieceCount < _num; pieceCount++) 
	{
		((ZMemoryPiece*)pieceAddress)->nextMemoryPiece = (ZMemoryPiece*)(pieceAddress + sizeof(ZMemoryPiece));
		((ZMemoryPiece*)pieceAddress)->memoryAddress = (Address)memoryAddress;
		((ZMemoryPiece*)pieceAddress)->type = _type;
		((ZMemoryPiece*)pieceAddress)->size = MEMORY_PIECE_SIZE_ARRAY(_type);
		pieceAddress = pieceAddress + sizeof(ZMemoryPiece);
		memoryAddress = memoryAddress + MEMORY_PIECE_SIZE_ARRAY(_type);
	}
	//初始化头尾
	//尾
	((ZMemoryPiece*)(pieceAddress - sizeof(ZMemoryPiece)))->nextMemoryPiece = momoryPieceListArray(_type).headPointer;
	//头
	momoryPieceListArray(_type).headPointer = (ZMemoryPiece*)(memoryApplyAddress);
	//修正列表数量
	momoryPieceListArray(_type).num += _num;



}
