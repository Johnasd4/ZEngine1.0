#ifndef ZErrorMessageMacro_h
#define ZErrorMessageMacro_h

//使用控制台错误输出
#define USE_ERROR_MESSAGE_CONSOLE_PRINT


#include"ZBasicType.h"

/*
	当条件成立时返回指定值并输出错误信息
	参数：
		_condition 条件
		_returnValue 返回值
		_errorMessage 报错信息
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
			输出错误信息
			参数：
				const CChar* _file 文件名
				const CChar* _func 函数名
				const Int32 _line 行数
				const CChar* _string 要输出的错误信息
		*/
		DLL_API const Void errorMessageConsolePrint(const CChar* _file, const CChar* _func, const Int32 _line, const CChar* _string) noexcept;

	}
}


/*
	输出错误信息
	参数：
		const CChar* _errorMessage 错误信息
*/
#define ErrorMessageOutput(_errorMessage)	\
		ErrorMessageConsolePrint(_errorMessage);	


/*
	控制台打印错误信息
*/
#ifdef USE_ERROR_MESSAGE_CONSOLE_PRINT
#define ErrorMessageConsolePrint(_errorMessage)	\
		::ZEngine::Private::errorMessageConsolePrint(__FILE__, __func__, __LINE__, _errorMessage);	
#else
#define ErrorMessageConsolePrint(_errorMessage) ;
#endif // USE_ERROR_CONSOLE_PRINT


#endif // !ZErrorMessageMacro_h
