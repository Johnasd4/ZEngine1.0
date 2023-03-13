#ifndef ZMemoryPiece_h
#define ZMemoryPiece_h

#include"ZBasicDrive.h"

namespace ZEngine 
{

	namespace Private
	{

		struct ZSystemMemoryPiece {

		};


		/*
			小内存块，用链表形式存储
		*/
		struct ZSmallMemoryPiece
		{
			//下一块内存块的地址
			ZSmallMemoryPiece* nextMemoryPiecePtr;
			//内存块类型
			UInt32 type;
			//内存块大小
			UInt32 size;

		};

		/*
			智能指针计数内存块，用链表形式存储
		*/
		struct ZSmartPtrCounterMemoryPiece
		{

			//下一块内存块的地址
			ZSmartPtrCounterMemoryPiece* nextMemoryPiecePtr;

		};

	
	}
}

#endif // !ZPoolListBase_h
