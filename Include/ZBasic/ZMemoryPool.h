#ifndef ZMemoryPool_h
#define ZMemoryPool_h

#include"ZBasicDrive.h"

#include"ZConstArray.h"
#include"ZFixedArray.h"
#include"ZMutex.h"

//内存池测试控制台输出
#define MEMORY_POOL_TEST_SIZE
//内存池线程安全
#define MEMORY_POOL_THREAD_SAFE

namespace ZEngine {


	/*
		内存块
	*/
	struct ZMemoryPiece 
	{

		//内存块大小存储类型
		typedef UInt32 MemoryPieceSizeType;

		//下一块内存块的地址
		Address memoryAddress;
		//内存块类型
		MemoryPieceSizeType size;
		//内存块大小
		Int32 type;
		//下一块内存块的地址
		ZMemoryPiece* nextMemoryPiece;

	};




	/*
		内存池
		说明：
			维护N个内存块指针链表，从64B开始，每个指针链表相差2倍

	*/
	class ZMemoryPool 
	{




	public:

		/*
			创建单例
		*/
		DLL_API static const Void CreateInstance() noexcept;

		//单例指针
		DLL_API static ZMemoryPool* InstancePtr;

		/*
			申请内存
			参数：
				const ZMemoryPiece::MemoryPieceSizeType& _size 申请内存的大小
			返回：
				const ZMemoryPiece* 内存块指针
		*/
		DLL_API ZMemoryPiece* applyMemory(const ZMemoryPiece::MemoryPieceSizeType& _size) noexcept;

		/*
			释放内存
			参数：
				ZMemoryPiece* _memoryPiecePtr 内存块指针
		*/
		DLL_API const Void releaseMemory(ZMemoryPiece* _memoryPiecePtr) noexcept;

	private:


		//内存块类型数量
		static constexpr Int32 MEMORY_PIECE_TYPE_NUM = 16;
		//内存块最小大小
		static constexpr ZMemoryPiece::MemoryPieceSizeType MEMORY_PIECE_MIN_SIZE = 64;
		//内存块成长倍数
		static constexpr ZMemoryPiece::MemoryPieceSizeType MEMORY_PIECE_MUTIPLE_GROW_FACTOR = 2;
		//内存块大小数组
		static constexpr ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM> MEMORY_PIECE_SIZE_ARRAY = ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>(
			ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>::Init_GeometricSequence<ZMemoryPiece::MemoryPieceSizeType>, MEMORY_PIECE_MIN_SIZE, MEMORY_PIECE_MUTIPLE_GROW_FACTOR);

		//填充内存块类大小的数组
		static constexpr ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM> MEMORY_PIECE_CLASS_SIZE_ARRAY = ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>(ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>::Init_FillSameElement, (ZMemoryPiece::MemoryPieceSizeType)sizeof(ZMemoryPiece));
		//内存块包含类大小数组
		static constexpr ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM> MEMORY_PIECE_WITH_CLASS_SIZE_ARRAY = ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>(
			ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>::Init_AddSequence<ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>, ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>>,
			MEMORY_PIECE_SIZE_ARRAY,
			MEMORY_PIECE_CLASS_SIZE_ARRAY);

		//内存池初始每个大小申请数量
		static constexpr Int32 MEMORY_POOL_SIZE_DEFAULT = 0;
		//内存池默认大小
		static constexpr ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM> MEMORY_POOL_SIZE_DEFAULT_ARRAY = ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM>(
			ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM>::Init_FillSameElement, MEMORY_POOL_SIZE_DEFAULT);

		//内存块自增长时基于当前内存块申请的数量系数（申请内存块 = 当前内存块 * 系数）
		static constexpr Float32 MEMORY_PIECE_AUTO_EXTEND_MUL_FACTOR = 0.2F;
		//每次申请内存时的最大值
		static constexpr ZMemoryPiece::MemoryPieceSizeType APPLY_MEMORY_MAX_SIZE = 1 * GB_SIZE;
		static constexpr ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM> APPLY_MEMORY_MAX_SIZE_ARRAY = ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>(
			ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>::Init_FillSameElement, APPLY_MEMORY_MAX_SIZE);
		//每次申请内存时的最小值
		static constexpr ZMemoryPiece::MemoryPieceSizeType APPLY_MEMORY_MIN_SIZE = 4 * KB_SIZE;
		static constexpr ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM> APPLY_MEMORY_MIN_SIZE_ARRAY = ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>(
			ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>::Init_FillSameElement, APPLY_MEMORY_MIN_SIZE);
		//内存块申请最大数量
		static constexpr ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM> ADD_PIECE_MAX_NUM_ARRAY = ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM>(
			ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM>::Init_DevideSequence<ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>, ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>>,
			APPLY_MEMORY_MAX_SIZE_ARRAY,
			MEMORY_PIECE_WITH_CLASS_SIZE_ARRAY);

		//内存块申请最小数量
		static constexpr ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM> ADD_PIECE_MIN_NUM_ARRAY = ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM>(
			ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM>::Init_DevideSequence<ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>, ZConstArray<ZMemoryPiece::MemoryPieceSizeType, MEMORY_PIECE_TYPE_NUM>>,
			APPLY_MEMORY_MIN_SIZE_ARRAY,
			MEMORY_PIECE_WITH_CLASS_SIZE_ARRAY);




	private:



		/*
			内存块链表
		*/
		struct MemoryPieceList {
			ZMemoryPiece* headPointer;
			Int32 num;
		};

	private:
		
		/*
			构造函数
		*/
		ZMemoryPool() noexcept;

		/*
			析构函数
		*/
		~ZMemoryPool() noexcept;



		/*
			添加内存块
			参数：
				const Int32 _type 内存块类型
		*/
		const Void initMemoryPieceList(const Int32 _type) noexcept;

		/*
			添加内存块
			参数：
				const Int32 _type 内存块类型
		*/
		const Void autoAddMemoryPiece(const Int32 _type) noexcept;


		/*
			为内存池添加内存块
			参数：
				const Int32 _type 内存块类型
				const Int32 _num 内存块数量
		*/
		const Void addMemoryPiece(const Int32 _type, const Int32 _num) noexcept;

		/*
			添加大内存块
		*/
		const Void addBigMemoryPiece() noexcept;

	private:


#ifdef MEMORY_POOL_TEST_SIZE

		//内存块使用计数
		ZFixedArray<Int32, MEMORY_PIECE_TYPE_NUM> momoryPieceListUsedArray;
		//内存块使用最大值
		ZFixedArray<Int32, MEMORY_PIECE_TYPE_NUM> momoryPieceListUsedMaxArray;
		//内存块总申请最大值
		ZFixedArray<Int32, MEMORY_PIECE_TYPE_NUM> momoryPieceListApplyedArray;

#endif // MEMORY_POOL_TEST_CONSOLE_OUTPUT


#ifdef MEMORY_POOL_THREAD_SAFE
		//线程锁
		ZMutex mutex;
#endif // MEMORY_POOL_THREAD_SAFE

	private:

		//内存块指针链表数组
		ZFixedArray<MemoryPieceList, MEMORY_PIECE_TYPE_NUM> momoryPieceListArray;

		//指向向系统申请内存的链表
		Address systemMemoryAddress;

	};



}

#endif // !ZMemoryPool_h
