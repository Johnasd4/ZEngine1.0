#include"ZCore/ZMemoryPool.h"

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
		momoryPieceListArray(index).pieceNum = 0;
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


/*
	向系统申请内存
	参数：
		const UInt64& _applySize 申请内存的大小
	返回：
		const Boolean 是否申请成功
*/
const Address ZMemoryPool::applyMemoryFromSystem(const UInt64& _applySize) {
	Address tempAddress = malloc(_applySize + sizeof(Address));//多申请一个地址大小的内存用于链表存储
	*(Address*)tempAddress = systemMemoryAddress;	//新内存块为链表头
	systemMemoryAddress = tempAddress;
	return (Address)((UInt64)tempAddress + sizeof(Address));	//返回申请内存后八位的地址
}