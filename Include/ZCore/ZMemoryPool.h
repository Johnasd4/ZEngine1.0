#ifndef ZMemoryPool_h
#define ZMemoryPool_h

#include"ZCoreDependence.h"
#include"ZArray.h"


namespace ZEngine {

	namespace Private {

		/*
			�ڴ��
		*/
		struct ZMemoryPiece {

			//��һ���ڴ��ĵ�ַ
			Address memoryAddress;
			//��һ���ڴ��ĵ�ַ
			ZMemoryPool* nextPiecePointer;
			//�ڴ������
			UInt32 size;
			//�ڴ���С
			Int32 type;

		};




	}


	/*
		�ڴ��
		˵����
			ά��N���ڴ��ָ��������64B��ʼ��ÿ��ָ���������2��
		���棺
			��Ҫ�����ڴ��������ȫ�ֱ�������Ҫ�����ڴ���ж�ȫ��object����ʹ��create����destroy�������������ڴ���������ڽ���ʱ���ͷ������ڴ档
	*/
	class ZMemoryPool {

	public:

		/*
			��������
		*/
		static const Void CreateInstance();

		//����ָ��
		static ZMemoryPool* InstancePtr;


	private:

		//�ڴ����������
		static constexpr Int32 MEMORY_PIECE_TYPE_NUM = 16;
		//�ڴ����С��С
		static constexpr UInt64 MEMORY_PIECE_MIN_SIZE = 64;
		//�ڴ��ɳ�����
		static constexpr UInt64 MEMORY_PIECE_MUTIPLE_GROW_FACTOR = 2;
		//�ڴ���С����
		static constexpr ZConstArray<UInt64, MEMORY_PIECE_TYPE_NUM> MEMORY_PIECE_SIZE_ARRAY = ZConstArray<UInt64, MEMORY_PIECE_TYPE_NUM>(
			ZConstArray<UInt64, MEMORY_PIECE_TYPE_NUM>::Init_GeometricSequence<UInt64>, MEMORY_PIECE_MIN_SIZE, MEMORY_PIECE_MUTIPLE_GROW_FACTOR);

		//�ڴ�س�ʼÿ����С��������
		static constexpr Int32 MEMORY_POOL_SIZE_DEFAULT = 0;
		//�ڴ��Ĭ�ϴ�С
		static constexpr ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM> MEMORY_POOL_SIZE_DEFAULT_ARRAY = ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM>(
			ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM>::Init_FillSameElement, MEMORY_POOL_SIZE_DEFAULT);



	private:



		/*
			�ڴ������
		*/
		struct MemoryPieceList {
			Address headPointer;
			Int32 pieceNum;
		};

	private:
		
		/*
			���캯��
		*/
		ZMemoryPool();

		/*
			��������
		*/
		~ZMemoryPool();

		/*
			��ϵͳ�����ڴ�
			������
				const UInt64& _applySize �����ڴ�Ĵ�С
			���أ�
				const Boolean �Ƿ�����ɹ�
		*/
		const Address applyMemoryFromSystem(const UInt64& _applySize);

		/*
			����ڴ��
		*/
		const Void addMemoryPiece();

	private:

		//�ڴ��ָ����������
		ZFixedArray<MemoryPieceList, MEMORY_PIECE_TYPE_NUM> momoryPieceListArray;

		//ָ����ϵͳ�����ڴ������
		Address systemMemoryAddress;

	};



}

#endif // !ZMemoryPool_h
