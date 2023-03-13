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
			С�ڴ�飬��������ʽ�洢
		*/
		struct ZSmallMemoryPiece
		{
			//��һ���ڴ��ĵ�ַ
			ZSmallMemoryPiece* nextMemoryPiecePtr;
			//�ڴ������
			UInt32 type;
			//�ڴ���С
			UInt32 size;

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
