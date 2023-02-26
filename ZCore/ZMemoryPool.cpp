#include"ZCore/ZMemoryPool.h"

#pragma warning(disable : 6011)


using namespace ZEngine;
using namespace ZEngine::Private;


//单例指针
ZMemoryPool* ZMemoryPool::InstancePtr = nullptr;

/*
	创建单例
*/
const Void ZMemoryPool::CreateInstance() {
	static ZMemoryPool memoryPool;
	ZMemoryPool::InstancePtr = &memoryPool;
}

/*
	构造函数
*/
ZMemoryPool::ZMemoryPool() :
	systemMemoryAddress(nullptr)
{
	//初始化每种内存块链表
	for (Int32 index = 0; index < MEMORY_PIECE_TYPE_NUM; index++) {
		momoryPieceListArray(index).headPointer = nullptr;
		momoryPieceListArray(index).num = 0;
	}


}

/*
	析构函数
*/
ZMemoryPool::~ZMemoryPool() {

	/*释放内存池的内存*/

	//下一块内存
	Address nextSystemMemoryAddress;
	while (systemMemoryAddress != nullptr) {
		//暂存下一内存块地址	
		nextSystemMemoryAddress = *((Address*)systemMemoryAddress);
		//释放当前内存块
		free(systemMemoryAddress);
		//将链表头指向下一块内存地址
		systemMemoryAddress = nextSystemMemoryAddress;
	}

}



const Boolean ZMemoryPool::addMemoryPiece(const Int32& _type, const Int32& _num) {

}




/*
	添加内存块
*/
const Boolean ZMemoryPool::initMemoryPieceList(const Int32& _type, const Int32& _num) {
	//临时地址保存容器
	Address memoryApplyAddress;
	//申请内存块数量
	Int32 memoryApplyPieceNum;
	//内存块地址的UInt64类型保存
	UInt64 pieceAddress;
	//内存块对应内存地址的UInt64类型保存
	UInt64 memoryAddress;

	//实际每个内存块的大小
	UInt64 pieceRealSize = MEMORY_PIECE_SIZE_ARRAY(_type) + sizeof(ZMemoryPiece);
	//默认大小不为0则计算申请多少个
	Int32 addPieceFixedNum = (Int32)(((((_num * pieceRealSize - 1) / APPLY_MEMORY_MIN_SIZE) + 1) * APPLY_MEMORY_MIN_SIZE) / pieceRealSize);

	//计算申请内存大小
	UInt64 memoryApplySize = pieceRealSize * addPieceFixedNum;
	//如果申请大小大于最大值则1个G，1个G申请
	while (memoryApplySize > 0ULL) {
		//申请内存块数量
		if (memoryApplySize > APPLY_MEMORY_MAX_SIZE) {
			memoryApplyPieceNum = (Int32)(APPLY_MEMORY_MAX_SIZE / pieceRealSize);
		}
		else {
			memoryApplyPieceNum = (Int32)(memoryApplySize / pieceRealSize);
		}
		//申请内存
		memoryApplyAddress = applyMemoryFromSystem(memoryApplyPieceNum * pieceRealSize);
		//分配内存块
		pieceAddress = (UInt64)memoryApplyAddress;
		memoryAddress = pieceAddress + sizeof(ZMemoryPiece) * memoryApplyPieceNum;
		//初始化内存块
		for (Int32 pieceCount = 0; pieceCount < memoryApplyPieceNum; pieceCount++) {
			((ZMemoryPiece*)pieceAddress)->nextPiece = (ZMemoryPiece*)(pieceAddress + sizeof(ZMemoryPiece));
			((ZMemoryPiece*)pieceAddress)->memoryAddress = (Address)memoryAddress;
			((ZMemoryPiece*)pieceAddress)->type = _type;
			((ZMemoryPiece*)pieceAddress)->size = MEMORY_PIECE_SIZE_ARRAY(_type);
			pieceAddress = pieceAddress + sizeof(ZMemoryPiece);
			memoryAddress = memoryAddress + MEMORY_PIECE_SIZE_ARRAY(_type);
		}
		//初始化头尾
		//尾
		((ZMemoryPiece*)(pieceAddress - sizeof(ZMemoryPiece)))->nextPiece = momoryPieceListArray(_type).headPointer;
		//头
		momoryPieceListArray(_type).headPointer = (ZMemoryPiece*)memoryApplyAddress;
		//需要申请内存的总大小减去当前申请的大小
		memoryApplySize -= memoryApplyPieceNum * pieceRealSize;
	}

	//修改内存块数量
	momoryPieceListArray(_type).num += addPieceFixedNum;
	return true;
}


/*
	向系统申请内存
	参数：
		const UInt64& _applySize 申请内存的大小
	返回：
		const Boolean 是否申请成功
*/
const Address ZMemoryPool::applyMemoryFromSystem(const UInt64& _applySize) {
	Address tempAddress = malloc(_applySize + sizeof(Address));//多申请一个地址大小的内存用于链表存储
	*((Address*)tempAddress) = systemMemoryAddress;	//新内存块为链表头
	systemMemoryAddress = tempAddress;
	return (Address)((UInt64)tempAddress + sizeof(Address));	//返回申请内存后八位的地址
}

