#define DLL_API_FILE

#include"ZErrorMessageMacro.h"
#include"ZConsole.h"

using namespace ZEngine::Console;
using namespace ZEngine::Console::Private;

/*
	输出错误信息
	参数：
		const CChar* _file 文件名
		const CChar* _func 函数名
		const Int32 _line 行数
		const CChar* _string 要输出的错误信息
*/
DLL_API const Void ZEngine::Private::errorMessageConsolePrint(const CChar* _file, const CChar* _func, const Int32 _line, const CChar* _string) noexcept 
{
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_PRINT_FRONT_COLOUR_DARK_RED | CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK);
	printf("报错文件路径：%s\n报错函数：%s\n报错行：%d\n报错信息：%s\n", _file, _func, std::forward<const Int32>(_line), _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);
	ConsoleMutex.unLock();
}
