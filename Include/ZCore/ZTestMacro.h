#ifndef ZTestMacro_h
#define ZTestMacro_h




#include"ZBasicType.h"

/*
	测试运行代码的时间
	参数：
		_code 运行的代码
		_loopTime 运行的次数

*/
#define TimeTest(_code, _loopTime)\
	{	\
	    system("pause");	\
		Int32 StartTime,EndTime;	\
		StartTime = clock();	\
		for (UInt64 count = 0; count < _loopTime; count++)	\
		{	\
			_code;	\
		}	\
		EndTime = clock();	\
		std::cout << "代码运行总共消耗：" << EndTime - StartTime << "ms" << std::endl;\
	}



#endif // !ZTestMacro_h
