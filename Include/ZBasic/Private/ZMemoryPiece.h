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
			�ڴ��
		*/
		template<UInt32 _size>
		struct ZMemoryPiece
		{
			//�ڴ������
			UInt32 type;
		};

		/*
			����ָ������ڴ�飬��������ʽ�洢
		*/
		struct ZSmartPtrCounterMemoryPiece
		{

			//��һ���ڴ��ĵ�ַ
			ZSmartPtrCounterMemoryPiece* nextMemoryPiecePtr;

		};

	
	}
}

#endif // !ZPoolListBase_h
