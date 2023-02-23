#ifndef ZMemoryPool_h
#define ZMemoryPool_h

#include"ZCoreDependence.h"
#include"ZArray.h"


namespace ZEngine {

	namespace Private {

		/*
			内存块
		*/
		template<Int32 _sizeIndex, UInt64 _size>
		struct ZMemoryPiece {

			//下一块内存块的地址
			ZMemoryPiece* nextPiece;
			//指向所在内存池
			ZMemoryPool* ownerMemoryPoolPointer;
			//内存指针，指向可用内存块
			Byte memoryAddress[_size - sizeof(Address) * 2];

			/*
				获取内存块的大小编号
				返回：
					const Int32 获取内存块大小编号
			*/
			constexpr static __forceinline const Int32 getSizeIndex() noexcept;

			/*
				获取内存块的大小
				返回：
					const Int32 获取内存块大小
			*/
			constexpr static __forceinline const Int32 getSize() noexcept;

		};

		/*
			获取内存块的大小编号
			返回：
				const Int32 获取内存块大小编号
		*/
		template<Int32 _sizeIndex, UInt64 _size>
		constexpr __forceinline const Int32 ZMemoryPiece<_sizeIndex, _size>::getSizeIndex() noexcept {
			return _sizeIndex;
		}

		/*
			获取内存块的大小
			返回：
				const Int32 获取内存块大小
		*/
		template<Int32 _sizeIndex, UInt64 _size>
		constexpr __forceinline const Int32 ZMemoryPiece<_sizeIndex, _size>::getSize() noexcept {
			return _size;
		}



		/*
			系统内存申请控制器
			说明：
				控制整个内存池向系统申请内存，会保存每次申请的指针方便统一释放
				memoryPointerArray指向第一次申请的内存，
				该片内存的前一部分内存（MEMORY_POINTER_ARRAY_MEMORY_SIZE_DEFAULT）保存后续需要补充申请内存的地址（申请内存时会自动+指针数组大小），
				后续的为用于内存页的内存。
		*/
		class ZMemoryPoolBase {

			friend class MemoryPool;

		private:


			//保存指针的数组
			Address* memoryPointerArray;
			//保存指针的数组的大小
			Int32 memoryPointerArraySize;
			//指针的数量
			Int32 memoryPointerNum;

		private:

			/*
				构造函数
			*/
			ZMemoryPoolBase();

			/*
				析构函数，释放所有申请空间，并且释放指针数组
			*/
			~ZMemoryPoolBase();

		private:


			/*
				向系统申请内存
				参数：
					Address* memporyPointer 获取内存指针的容器
					const UInt64& memorySize 申请的内存的大小
				返回：
					const Boolean 是否成功
			*/
			const Boolean applyMemory(Address* memporyPointer, const UInt64& memorySize);





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

	private:

		//内存块类型数量
		static constexpr Int32 MEMORY_PIECE_TYPE_NUM = 20;
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
			内存块列表
		*/
		struct MemoryPieceList {
			Address headPointer;
			Int32 pieceNum;
		};

	private:



	private:

		//当前使用的内存池
		static ZMemoryPool* CurrentMemoryPoolPointer;

	};



}

#endif // !ZMemoryPool_h
