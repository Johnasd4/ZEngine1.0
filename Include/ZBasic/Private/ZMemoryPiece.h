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
			内存块
		*/
		template<UInt32 _size>
		struct ZMemoryPiece
		{
			//内存块类型
			UInt32 type;
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
