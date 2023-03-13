#ifndef ZErrorMessageMacro_h
#define ZErrorMessageMacro_h

//ʹ�ÿ���̨�������
#define USE_ERROR_MESSAGE_CONSOLE_PRINT


#include"ZBasicType.h"

/*
	����������ʱ����ָ��ֵ�����������Ϣ
	������
		_condition ����
		_returnValue ����ֵ
		_errorMessage ������Ϣ
*/
#define Return(_condition, _returnValue, _errorMessage) \
	if(_condition)	\
	{	\
		ErrorMessageOutput(_errorMessage);	\
		return _returnValue;	\
	}


namespace ZEngine 
{
	namespace Private 
	{
		/*
			���������Ϣ
			������
				const CChar* _file �ļ���
				const CChar* _func ������
				const Int32 _line ����
				const CChar* _string Ҫ����Ĵ�����Ϣ
		*/
		DLL_API const Void errorMessageConsolePrint(const CChar* _file, const CChar* _func, const Int32 _line, const CChar* _string) noexcept;

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


#endif // !ZErrorMessageMacro_h
