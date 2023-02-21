#ifndef ZMacro_h
#define ZMacro_h


#pragma warning(disable : 4005)
#pragma warning(disable : 4002)


#include"ZBasicType.h"

#pragma region ���ر����



/*
	����������ʱ����ָ��ֵ�����������Ϣ
	������
		_condition ����
		_returnValue ����ֵ
		_errorMessage ������Ϣ
*/
#define Return(_condition, _returnValue, _errorMessage) \
	if(_condition){	\
		ErrorMessageOutput(_errorMessage);	\
		return _returnValue;	\
	}


namespace ZEngine {
	namespace Private {
		/*
			���������Ϣ
			������
				const CChar* _file �ļ���
				const CChar* _func ������
				const Int32&& _line ����
				const CChar* _string Ҫ����Ĵ�����Ϣ
		*/
		DLL_API const Void errorMessageConsolePrint(const CChar* _file, const CChar* _func, const Int32&& _line, const CChar* _string) noexcept;

		/*
			���������Ϣ
			������
				const CChar* _file �ļ���
				const CChar* _func ������
				const Int32&& _line ����
				const TChar* _string Ҫ����Ĵ�����Ϣ
		*/
		DLL_API const Void errorMessageConsolePrint(const CChar* _file, const CChar* _func, const Int32&& _line, const TChar* _string) noexcept;
	}
}


/*
	���������Ϣ
	������
		const CChar* _errorMessage ������Ϣ
*/
#define ErrorMessageOutput(_errorMessage)	\
		ErrorMessageConsolePrint(_errorMessage);	


/*
	����̨��ӡ������Ϣ
*/
#ifdef USE_ERROR_MESSAGE_CONSOLE_PRINT
#define ErrorMessageConsolePrint(_errorMessage)	\
		::ZEngine::Private::errorMessageConsolePrint(__FILE__, __func__, __LINE__, _errorMessage);	
#else
#define ErrorMessageConsolePrint(_errorMessage) ;
#endif // USE_ERROR_CONSOLE_PRINT


#pragma endregion ���ر����

#pragma region ���Ժ�


#define TimeTest(_code)\
	{	\
		Int32 StartTime,EndTime;	\
		StartTime = clock();	\
		_code;	\
		EndTime = clock();	\
		std::cout << "���������ܹ����ģ�" << EndTime - StartTime << "ms" << std::endl;\
	}



#pragma endregion ���Ժ�

#endif // !ZMacro_h
