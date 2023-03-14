#ifndef ZMemoryPiecePool_h
#define ZMemoryPiecePool_h

#include"ZBasicDrive.h"
#include"ZPoolBase.h"
#include"ZMemoryPiece.h"
#include"ZSystemMemoryController.h"
#include"..\ZMutex.h"
namespace ZEngine
{

	namespace Private
	{


		/*
			����������
			typename _ObjectType �ڵ�����
			Int32 _objectOffset �ڵ�����ʵ��ʹ�õĵ�ַƫ����
			Boolean _threadSafe �Ƿ��̰߳�ȫ
		*/
		template<Int32 Memory, Boolean _threadSafe>
		class ZSmallMemoryPiecePool :public ZPoolBase<ZMemoryPiece, sizeof(ZMemoryPiece), _threadSafe>
		{



		protected:

			/*
				���캯�����ճ���
			*/
			__forceinline ZSmallMemoryPiecePool();

			/*
				���캯��
				������
					const Int32 _capacity ���ӳ�ʼobject����
			*/
			__forceinline ZSmallMemoryPiecePool(const Int32 _capacity);

			/*
				��������
			*/
			__forceinline ~ZSmallMemoryPiecePool();


			/*
				��չ����
				��ʼ��һ������
				��Ҫ�޸ģ�
					Node<_ObjectType>* headNodePtr ����ʣ��object����ָ��
					Int32 capacity ����object����
				������
					const Int32 _num ���ӵ�����
			*/
			virtual const Void extend(const Int32 _num);

		private:

			

		};

		/*
			���캯�����ճ���
		*/
		template<Boolean _threadSafe>
		__forceinline ZSmallMemoryPiecePool<_threadSafe>::ZSmallMemoryPiecePool() :
			ZPoolBase<ZSmallMemoryPiece, sizeof(ZSmallMemoryPiece), _threadSafe>()
		{}

		/*
			���캯��
			������
				const Int32& _capacity ���ӳ�ʼobject����
		*/
		template<Boolean _threadSafe>
		__forceinline ZSmallMemoryPiecePool<_threadSafe>::ZSmallMemoryPiecePool(const Int32 _capacity) :
			ZPoolBase<ZSmallMemoryPiece, sizeof(ZSmallMemoryPiece), _threadSafe>(_capacity)
		{}

		/*
			��������
		*/
		template<Boolean _threadSafe>
		__forceinline ZSmallMemoryPiecePool<_threadSafe>::~ZSmallMemoryPiecePool()
		{}

		/*
			��չ����
			��ʼ��һ������
			��Ҫ�޸ģ�
				Node<_ObjectType>* headNodePtr ����ʣ��object����ָ��
				Int32 capacity ����object����
			������
				const Int32 _num ���ӵ�����
		*/
		template<Boolean _threadSafe>
		const Void ZSmallMemoryPiecePool<_threadSafe>::extend(const Int32 _num)
		{
			
		}

	}
}

#endif // !ZMemoryPiecePool_h