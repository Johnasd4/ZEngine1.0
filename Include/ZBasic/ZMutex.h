#ifndef ZMutex_h
#define ZMutex_h

#include"Private/ZBasicDrive.h"


namespace ZEngine 
{

	/*
		互斥锁
	*/
	class ZMutex 
	{

	public:

		/*
			构造函数
		*/
		__forceinline ZMutex();

		/*
			析构函数
		*/
		__forceinline ~ZMutex();

		/*
			互斥锁上锁
		*/
		__forceinline const Void lock();

		/*
			互斥锁解锁
		*/
		__forceinline const Void unLock();


	private:

		//互斥锁的句柄
		Handle handle;



	};


	/*
		构造函数
	*/
	__forceinline ZMutex::ZMutex() 
	{
		handle = CreateMutex(nullptr, FALSE, nullptr);
	}

	/*
		析构函数
	*/
	__forceinline ZMutex::~ZMutex() {}

	/*
		互斥锁上锁
	*/
	__forceinline const Void ZMutex::lock() 
	{
		WaitForSingleObject(handle, INFINITE);
	}

	/*
		互斥锁解锁
	*/
	__forceinline const Void ZMutex::unLock() 
	{
		ReleaseMutex(handle);
	}


}


#endif // !ZMutex_h
