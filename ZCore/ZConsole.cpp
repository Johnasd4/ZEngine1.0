#define DLL_API_FILE

#include"ZCore/ZCoreDependence/ZConsole.h"

using namespace ZEngine;
using namespace ZEngine::Console;
using namespace ZEngine::Console::Private;


extern UInt16 ZEngine::Console::Private::ConsoleFrontColour = CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE;
extern UInt16 ZEngine::Console::Private::ConsoleBackColour = CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK;
extern ZMutex ZEngine::Console::Private::ConsoleMutex = ZMutex();

/*
	设置输出字符串到屏幕的颜色
	参数：
		const UInt16&& _frontColour 输出的前景色,颜色变量名称为：CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
		const UInt16&& _backColour 输出的背景色,颜色变量名称为：CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
*/
DLL_API const Void ZEngine::Console::setPrintColour(const UInt16&& _frontColour, const UInt16&& _backColour) noexcept {
	ConsoleMutex.lock();
	ConsoleFrontColour = _frontColour;
	ConsoleBackColour = _backColour;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);//设置颜色，没有添加颜色，故为原色	
	ConsoleMutex.unLock();
}

/*
	输出字符串到屏幕
	参数：
		const CChar* _string 要输出的字符串
*/

DLL_API const Void ZEngine::Console::print(const CChar* _string) noexcept {
	ConsoleMutex.lock();
	printf("%s", _string);
	ConsoleMutex.unLock();
}


/*
	输出字符串到屏幕，自动换行
	参数：
		const CChar* _string 要输出的字符串
*/
DLL_API const Void ZEngine::Console::printInLine(const CChar* _string) noexcept {
	ConsoleMutex.lock();
	printf("%s\n", _string);
	ConsoleMutex.unLock();
}

/*
	输出字符串到屏幕
	参数：
		const TChar* _string 要输出的字符串
*/
DLL_API const Void ZEngine::Console::print(const TChar* _string) noexcept {
	ConsoleMutex.lock();
	printf("%ls", _string);
	ConsoleMutex.unLock();
}
/*
	输出字符串到屏幕，自动换行
	参数：
		const TChar* _string 要输出的字符串
*/
DLL_API const Void ZEngine::Console::printInLine(const TChar* _string) noexcept {
	ConsoleMutex.lock();
	printf("%ls\n", _string);
	ConsoleMutex.unLock();
}

/*
	输出字符串到屏幕
	参数：
		const CChar* _string 要输出的字符串
		const UInt16&& _frontColour 输出的前景色,颜色变量名称为：CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
		const UInt16&& _backColour 输出的背景色,颜色变量名称为：CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
*/
DLL_API const Void ZEngine::Console::print(const CChar* _string, const UInt16&& _frontColour, const UInt16&& _backColour) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), std::forward<const Int32&&>(_frontColour | _backColour));//设置颜色，没有添加颜色，故为原色
	printf("%s", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);	
	ConsoleMutex.unLock();
}

/*
	输出字符串到屏幕，自动换行
	参数：
		const CChar* _string 要输出的字符串
		const UInt16&& _frontColour 输出的前景色,颜色变量名称为：CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
		const UInt16&& _backColour 输出的背景色,颜色变量名称为：CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
*/
DLL_API const Void ZEngine::Console::printInLine(const CChar* _string, const UInt16&& _frontColour, const UInt16&& _backColour) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), std::forward<const Int32&&>(_frontColour | _backColour));//设置颜色，没有添加颜色，故为原色
	printf("%s\n", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);	
	ConsoleMutex.unLock();
}

/*
	输出字符串到屏幕
	参数：
		const CChar* _string 要输出的字符串
		const UInt16&& _frontColour 输出的前景色,颜色变量名称为：CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
		const UInt16&& _backColour 输出的背景色,颜色变量名称为：CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
*/
DLL_API const Void ZEngine::Console::print(const TChar* _string, const UInt16&& _frontColour, const UInt16&& _backColour) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), std::forward<const Int32&&>(_frontColour | _backColour));//设置颜色，没有添加颜色，故为原色
	printf("%ls", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);	
	ConsoleMutex.unLock();
}

/*
	输出字符串到屏幕，自动换行
	参数：
		const CChar* _string 要输出的字符串
		const UInt16&& _frontColour 输出的前景色,颜色变量名称为：CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
		const UInt16&& _backColour 输出的背景色,颜色变量名称为：CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
*/
DLL_API const Void ZEngine::Console::printInLine(const TChar* _string, const UInt16&& _frontColour, const UInt16&& _backColour) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), std::forward<const Int32&&>(_frontColour | _backColour));//设置颜色，没有添加颜色，故为原色
	printf("%ls\n", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);
	ConsoleMutex.unLock();
}




/*
	输出字符串到屏幕
	参数：
		const CChar* _string 要输出的字符串
*/
DLL_API const Void ZEngine::Console::printSuccess(const CChar* _string) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_PRINT_FRONT_COLOUR_LIGHT_GREEN | CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK);//设置颜色，没有添加颜色，故为原色
	printf("%s\n", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);
	ConsoleMutex.unLock();
}

/*
	输出字符串到屏幕
	参数：
		const TChar* _string 要输出的字符串
*/
DLL_API const Void ZEngine::Console::printSuccess(const TChar* _string) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_PRINT_FRONT_COLOUR_LIGHT_GREEN | CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK);//设置颜色，没有添加颜色，故为原色
	printf("%ls\n", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);
	ConsoleMutex.unLock();
}

/*
	输出字符串到屏幕
	参数：
		const CChar* _string 要输出的字符串
*/
DLL_API const Void ZEngine::Console::printFail(const CChar* _string) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_PRINT_FRONT_COLOUR_LIGHT_RED | CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK);//设置颜色，没有添加颜色，故为原色
	printf("%s\n", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);
	ConsoleMutex.unLock();
}

/*
	输出字符串到屏幕
	参数：
		const TChar* _string 要输出的字符串
*/
DLL_API const Void ZEngine::Console::printFail(const TChar* _string) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_PRINT_FRONT_COLOUR_LIGHT_RED | CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK);//设置颜色，没有添加颜色，故为原色
	printf("%ls\n", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);
	ConsoleMutex.unLock();
}

/*
	输出错误信息
	参数：
		const CChar* _string 要输出的错误信息
*/
DLL_API const Void ZEngine::Console::printErrorMessage(const CChar* _string) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_PRINT_FRONT_COLOUR_DARK_RED | CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK);
	printf("报错信息：%s\n", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);
	ConsoleMutex.unLock();
}

/*
	输出错误信息
	参数：
		const TChar* _string 要输出的错误信息
*/
DLL_API const Void ZEngine::Console::printErrorMessage(const TChar* _string) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_PRINT_FRONT_COLOUR_DARK_RED | CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK);
	printf("报错信息：%ls\n", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);
	ConsoleMutex.unLock();
}

