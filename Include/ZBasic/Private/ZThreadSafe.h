#ifndef ZThreadSafe_h
#define ZThreadSafe_h

#include"ZBasicDrive.h"
#include"..\ZMutex.h"

namespace ZEngine
{

	namespace Private
	{

		/*
			����������Ƿ��̰߳�ȫ
		*/
		template<Boolean _threadSafe>
		class ZThreadSafe
		{

		protected:

			/*
				����
			*/
			__forceinline const Void lock();

			/*
				����
			*/
			__forceinline const Void unLock();

		private:
			
			//�߳���
			ZMutex mutex;
		};
		template<>
		class ZThreadSafe<false>
		{};


		/*
			����
		*/
		template<Boolean _threadSafe>
		__forceinline const Void ZThreadSafe<_threadSafe>::lock() 
		{
			if constexpr (_threadSafe)
			{
				mutex.lock();
			}
		}

		/*
			����
		*/
		template<Boolean _threadSafe>
		__forceinline const Void ZThreadSafe<_threadSafe>::unLock()
		{
			if constexpr (_threadSafe)
			{
				mutex.unLock();
			}
		}


	}
}

#endif // !ZThreadSafe_h
