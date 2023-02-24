#ifndef ZMemoryPool_h
#define ZMemoryPool_h

#include"ZCoreDependence.h"
#include"ZArray.h"


namespace ZEngine {

	namespace Private {

		/*
			内存块
		*/
		struct ZMemoryPiece {

			//下一块内存块的地址
			Address memoryAddress;
			//下一块内存块的地址
			ZMemoryPool* nextPiecePointer;
			//内存块类型
			UInt32 size;
			//内存块大小
			Int32 type;

		};




	}


	/*
		内存池
		说明：
			维护N个内存块指针链表，从64B开始，每个指针链表相差2倍
		警告：
			不要再子内存池中申请全局变量（不要再子内存池中对全局object对象使用create或者destroy函数），在子内存池声明中期结束时会释放所有内存。
	*/
	class ZMemoryPool {

	public:

		/*
			创建单例
		*/
		static const Void CreateInstance();

		//单例指针
		static ZMemoryPool* InstancePtr;


	private:

		//内存块类型数量
		static constexpr Int32 MEMORY_PIECE_TYPE_NUM = 16;
		//内存块最小大小
		static constexpr UInt64 MEMORY_PIECE_MIN_SIZE = 64;
		//内存块成长倍数
		static constexpr UInt64 MEMORY_PIECE_MUTIPLE_GROW_FACTOR = 2;
		//内存块大小数组
		static constexpr ZConstArray<UInt64, MEMORY_PIECE_TYPE_NUM> MEMORY_PIECE_SIZE_ARRAY = ZConstArray<UInt64, MEMORY_PIECE_TYPE_NUM>(
			ZConstArray<UInt64, MEMORY_PIECE_TYPE_NUM>::Init_GeometricSequence<UInt64>, MEMORY_PIECE_MIN_SIZE, MEMORY_PIECE_MUTIPLE_GROW_FACTOR);

		//内存池初始每个大小申请数量
		static constexpr Int32 MEMORY_POOL_SIZE_DEFAULT = 0;
		//内存池默认大小
		static constexpr ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM> MEMORY_POOL_SIZE_DEFAULT_ARRAY = ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM>(
			ZConstArray<Int32, MEMORY_PIECE_TYPE_NUM>::Init_FillSameElement, MEMORY_POOL_SIZE_DEFAULT);



	private:



		/*
			内存块链表
		*/
		struct MemoryPieceList {
			Address headPointer;
			Int32 pieceNum;
		};

	private:
		
		/*
			构造函数
		*/
		ZMemoryPool();

		/*
			析构函数
		*/
		~ZMemoryPool();

		/*
			向系统申请内存
			参数：
				const UInt64& _applySize 申请内存的大小
			返回：
				const Boolean 是否申请成功
		*/
		const Address applyMemoryFromSystem(const UInt64& _applySize);

		/*
			添加内存块
		*/
		const Void addMemoryPiece();

	private:

		//内存块指针链表数组
		ZFixedArray<MemoryPieceList, MEMORY_PIECE_TYPE_NUM> momoryPieceListArray;

		//指向向系统申请内存的链表
		Address systemMemoryAddress;

	};



}

#endif // !ZMemoryPool_h
