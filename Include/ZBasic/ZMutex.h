#ifndef ZMutex_h
#define ZMutex_h

#include"Private/ZBasicDrive.h"


namespace ZEngine 
{

	/*
		������
	*/
	class ZMutex 
	{

	public:

		/*
			���캯��
		*/
		__forceinline ZMutex();

		/*
			��������
		*/
		__forceinline ~ZMutex();

		/*
			����������
		*/
		__forceinline const Void lock();

		/*
			����������
		*/
		__forceinline const Void unLock();


	private:

		//�������ľ��
		Handle handle;



	};


	/*
		���캯��
	*/
	__forceinline ZMutex::ZMutex() 
	{
		handle = CreateMutex(nullptr, FALSE, nullptr);
	}

	/*
		��������
	*/
	__forceinline ZMutex::~ZMutex() {}

	/*
		����������
	*/
	__forceinline const Void ZMutex::lock() 
	{
		WaitForSingleObject(handle, INFINITE);
	}

	/*
		����������
	*/
	__forceinline const Void ZMutex::unLock() 
	{
		ReleaseMutex(handle);
	}


}


#endif // !ZMutex_h
