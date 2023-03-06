#ifndef ZMemoryPool_h
#define ZMemoryPool_h

#include"ZBasicDrive.h"

#include"ZConstArray.h"
#include"ZFixedArray.h"
#include"ZMutex.h"

//�ڴ�ز��Կ���̨���
#define MEMORY_POOL_TEST_SIZE
//�ڴ���̰߳�ȫ
#define MEMORY_POOL_THREAD_SAFE

namespace ZEngine {


	/*
		�ڴ��
	*/
	struct ZMemoryPiece 
	{

		//�ڴ���С�洢����
		typedef UInt32 MemoryPieceSizeType;

		//��һ���ڴ��ĵ�ַ
		Address memoryAddress;
		//�ڴ������
		MemoryPieceSizeType size;
		//�ڴ���С
		Int32 type;
		//��һ���ڴ��ĵ�ַ
		ZMemoryPiece* nextMemoryPiece;

	};




	/*
		�ڴ��
		˵����
			ά��N���ڴ��ָ��������64B��ʼ��ÿ��ָ���������2��

	*/
	class ZMemoryPool 
	{




	public:

		/*
			��������
		*/
		DLL_API static const Void CreateInstance() noexcept;

		//����ָ��
		DLL_API static ZMemoryPool* InstancePtr;

		/*
			�����ڴ�
			������
				const ZMemoryPiece::MemoryPieceSizeType& _size �����ڴ�Ĵ�С
			���أ�
				const ZMemoryPiece* �ڴ��ָ��
		*/
		DLL_API ZMemoryPiece* applyMemory(const ZMemoryPiece::MemoryPieceSizeType& _size) noexcept;

		/*
			�ͷ��ڴ�
			������
				ZMemoryPiece* _memoryPiecePtr �ڴ��ָ��
		*/
		DLL_API const Void releaseMemory(ZMemoryPiece* _memoryPiecePtr) noexcept;

	private:


		//�ڴ����������
		static constexpr Int32 MEMORY_PIECE_TYPE_NUM = 16;
		//�ڴ����С��С
		static constexpr ZMemoryPiece::MemoryPieceSizeType MEMORY_PIECE_MIN_SIZE = 64;
		//�ڴ��ɳ�����
		static constexpr ZMemoryPiece::MemoryPieceSizeType MEMORY_PIECE_MUTIPLE_GROW_FACTOR = 2;
		//�ڴ���С����
		static constexpr ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM> MEMORY_PIECE_SIZE_ARRAY = ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>(
			ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>::Init_GeometricSequence<ZMemoryPiece::MemoryPieceSizeType>, MEMORY_PIECE_MIN_SIZE, MEMORY_PIECE_MUTIPLE_GROW_FACTOR);

		//����ڴ�����С������
		static constexpr ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM> MEMORY_PIECE_CLASS_SIZE_ARRAY = ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>(ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>::Init_FillSameElement, (ZMemoryPiece::MemoryPieceSizeType)sizeof(ZMemoryPiece));
		//�ڴ��������С����
		static constexpr ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM> MEMORY_PIECE_WITH_CLASS_SIZE_ARRAY = ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>(
			ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>::Init_AddSequence<ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>, ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>>,
			MEMORY_PIECE_SIZE_ARRAY,
			MEMORY_PIECE_CLASS_SIZE_ARRAY);

		//�ڴ�س�ʼÿ����С��������
		static constexpr Int32 MEMORY_POOL_SIZE_DEFAULT = 0;
		//�ڴ��Ĭ�ϴ�С
		static constexpr ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM> MEMORY_POOL_SIZE_DEFAULT_ARRAY = ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM>(
			ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM>::Init_FillSameElement, MEMORY_POOL_SIZE_DEFAULT);

		//�ڴ��������ʱ���ڵ�ǰ�ڴ�����������ϵ���������ڴ�� = ��ǰ�ڴ�� * ϵ����
		static constexpr Float32 MEMORY_PIECE_AUTO_EXTEND_MUL_FACTOR = 0.2F;
		//ÿ�������ڴ�ʱ�����ֵ
		static constexpr ZMemoryPiece::MemoryPieceSizeType APPLY_MEMORY_MAX_SIZE = 1 * GB_SIZE;
		static constexpr ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM> APPLY_MEMORY_MAX_SIZE_ARRAY = ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>(
			ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>::Init_FillSameElement, APPLY_MEMORY_MAX_SIZE);
		//ÿ�������ڴ�ʱ����Сֵ
		static constexpr ZMemoryPiece::MemoryPieceSizeType APPLY_MEMORY_MIN_SIZE = 4 * KB_SIZE;
		static constexpr ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM> APPLY_MEMORY_MIN_SIZE_ARRAY = ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>(
			ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>::Init_FillSameElement, APPLY_MEMORY_MIN_SIZE);
		//�ڴ�������������
		static constexpr ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM> ADD_PIECE_MAX_NUM_ARRAY = ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM>(
			ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM>::Init_DevideSequence<ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>, ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>>,
			APPLY_MEMORY_MAX_SIZE_ARRAY,
			MEMORY_PIECE_WITH_CLASS_SIZE_ARRAY);

		//�ڴ��������С����
		static constexpr ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM> ADD_PIECE_MIN_NUM_ARRAY = ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM>(
			ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM>::Init_DevideSequence<ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>, ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>>,
			APPLY_MEMORY_MIN_SIZE_ARRAY,
			MEMORY_PIECE_WITH_CLASS_SIZE_ARRAY);




	private:



		/*
			�ڴ������
		*/
		struct MemoryPieceList {
			ZMemoryPiece* headPointer;
			Int32 num;
		};

	private:
		
		/*
			���캯��
		*/
		ZMemoryPool() noexcept;

		/*
			��������
		*/
		~ZMemoryPool() noexcept;



		/*
			����ڴ��
			������
				const Int32 _type �ڴ������
		*/
		const Void initMemoryPieceList(const Int32 _type) noexcept;

		/*
			����ڴ��
			������
				const Int32 _type �ڴ������
		*/
		const Void autoAddMemoryPiece(const Int32 _type) noexcept;


		/*
			Ϊ�ڴ������ڴ��
			������
				const Int32 _type �ڴ������
				const Int32 _num �ڴ������
		*/
		const Void addMemoryPiece(const Int32 _type, const Int32 _num) noexcept;

		/*
			��Ӵ��ڴ��
		*/
		const Void addBigMemoryPiece() noexcept;

	private:


#ifdef MEMORY_POOL_TEST_SIZE

		//�ڴ��ʹ�ü���
		ZFixedArray<Int32, MEMORY_PIECE_TYPE_NUM> momoryPieceListUsedArray;
		//�ڴ��ʹ�����ֵ
		ZFixedArray<Int32, MEMORY_PIECE_TYPE_NUM> momoryPieceListUsedMaxArray;
		//�ڴ�����������ֵ
		ZFixedArray<Int32, MEMORY_PIECE_TYPE_NUM> momoryPieceListApplyedArray;

#endif // MEMORY_POOL_TEST_CONSOLE_OUTPUT


#ifdef MEMORY_POOL_THREAD_SAFE
		//�߳���
		ZMutex mutex;
#endif // MEMORY_POOL_THREAD_SAFE

	private:

		//�ڴ��ָ����������
		ZFixedArray<MemoryPieceList, MEMORY_PIECE_TYPE_NUM> momoryPieceListArray;

		//ָ����ϵͳ�����ڴ������
		Address systemMemoryAddress;

	};



}

#endif // !ZMemoryPool_h
