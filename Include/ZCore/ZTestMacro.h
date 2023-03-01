#ifndef ZTestMacro_h
#define ZTestMacro_h




#include"ZBasicType.h"


#define TimeTest(_code)\
	{	\
		Int32 StartTime,EndTime;	\
		StartTime = clock();	\
		_code;	\
		EndTime = clock();	\
		std::cout << "���������ܹ����ģ�" << EndTime - StartTime << "ms" << std::endl;\
	}



#endif // !ZTestMacro_h
