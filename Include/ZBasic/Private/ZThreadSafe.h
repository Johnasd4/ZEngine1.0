#ifndef ZThreadSafe_h
#define ZThreadSafe_h

#include"ZBasicDrive.h"
#include"..\ZMutex.h"

namespace ZEngine
{

	namespace Private
	{

		/*
			池类链表基是否线程安全
		*/
		template<Boolean _threadSafe>
		class ZThreadSafe
		{

		protected:

			/*
				上锁
			*/
			__forceinline const Void lock();

			/*
				解锁
			*/
			__forceinline const Void unLock();

		private:
			
			//线程锁
			ZMutex mutex;
		};
		template<>
		class ZThreadSafe<false>
		{};


		/*
			上锁
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
			解锁
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
