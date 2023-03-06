#ifndef ZTestMacro_h
#define ZTestMacro_h




#include"ZBasicType.h"

/*
	�������д����ʱ��
	������
		_code ���еĴ���
		_loopTime ���еĴ���

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
		std::cout << "���������ܹ����ģ�" << EndTime - StartTime << "ms" << std::endl;\
	}



#endif // !ZTestMacro_h
