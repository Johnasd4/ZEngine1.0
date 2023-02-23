#ifndef ZMemoryPool_h
#define ZMemoryPool_h

#include"ZCoreDependence.h"
#include"ZArray.h"


namespace ZEngine {

	namespace Private {

		/*
			�ڴ��
		*/
		template<Int32 _sizeIndex, UInt64 _size>
		struct ZMemoryPiece {

			//��һ���ڴ��ĵ�ַ
			ZMemoryPiece* nextPiece;
			//ָ�������ڴ��
			ZMemoryPool* ownerMemoryPoolPointer;
			//�ڴ�ָ�룬ָ������ڴ��
			Byte memoryAddress[_size - sizeof(Address) * 2];

			/*
				��ȡ�ڴ��Ĵ�С���
				���أ�
					const Int32 ��ȡ�ڴ���С���
			*/
			constexpr static __forceinline const Int32 getSizeIndex() noexcept;

			/*
				��ȡ�ڴ��Ĵ�С
				���أ�
					const Int32 ��ȡ�ڴ���С
			*/
			constexpr static __forceinline const Int32 getSize() noexcept;

		};

		/*
			��ȡ�ڴ��Ĵ�С���
			���أ�
				const Int32 ��ȡ�ڴ���С���
		*/
		template<Int32 _sizeIndex, UInt64 _size>
		constexpr __forceinline const Int32 ZMemoryPiece<_sizeIndex, _size>::getSizeIndex() noexcept {
			return _sizeIndex;
		}

		/*
			��ȡ�ڴ��Ĵ�С
			���أ�
				const Int32 ��ȡ�ڴ���С
		*/
		template<Int32 _sizeIndex, UInt64 _size>
		constexpr __forceinline const Int32 ZMemoryPiece<_sizeIndex, _size>::getSize() noexcept {
			return _size;
		}



		/*
			ϵͳ�ڴ����������
			˵����
				���������ڴ����ϵͳ�����ڴ棬�ᱣ��ÿ�������ָ�뷽��ͳһ�ͷ�
				memoryPointerArrayָ���һ��������ڴ棬
				��Ƭ�ڴ��ǰһ�����ڴ棨MEMORY_POINTER_ARRAY_MEMORY_SIZE_DEFAULT�����������Ҫ���������ڴ�ĵ�ַ�������ڴ�ʱ���Զ�+ָ�������С����
				������Ϊ�����ڴ�ҳ���ڴ档
		*/
		class ZMemoryPoolBase {

			friend class MemoryPool;

		private:


			//����ָ�������
			Address* memoryPointerArray;
			//����ָ�������Ĵ�С
			Int32 memoryPointerArraySize;
			//ָ�������
			Int32 memoryPointerNum;

		private:

			/*
				���캯��
			*/
			ZMemoryPoolBase();

			/*
				�����������ͷ���������ռ䣬�����ͷ�ָ������
			*/
			~ZMemoryPoolBase();

		private:


			/*
				��ϵͳ�����ڴ�
				������
					Address* memporyPointer ��ȡ�ڴ�ָ�������
					const UInt64& memorySize ������ڴ�Ĵ�С
				���أ�
					const Boolean �Ƿ�ɹ�
			*/
			const Boolean applyMemory(Address* memporyPointer, const UInt64& memorySize);





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

	private:

		//�ڴ����������
		static constexpr Int32 MEMORY_PIECE_TYPE_NUM = 20;
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
			�ڴ���б�
		*/
		struct MemoryPieceList {
			Address headPointer;
			Int32 pieceNum;
		};

	private:



	private:

		//��ǰʹ�õ��ڴ��
		static ZMemoryPool* CurrentMemoryPoolPointer;

	};



}

#endif // !ZMemoryPool_h
