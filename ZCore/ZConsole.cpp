#define DLL_API_FILE

#include"ZCore/ZCoreDependence/ZConsole.h"

using namespace ZEngine;
using namespace ZEngine::Console;
using namespace ZEngine::Console::Private;


extern UInt16 ZEngine::Console::Private::ConsoleFrontColour = CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE;
extern UInt16 ZEngine::Console::Private::ConsoleBackColour = CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK;
extern ZMutex ZEngine::Console::Private::ConsoleMutex = ZMutex();

/*
	��������ַ�������Ļ����ɫ
	������
		const UInt16&& _frontColour �����ǰ��ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
		const UInt16&& _backColour ����ı���ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
*/
DLL_API const Void ZEngine::Console::setPrintColour(const UInt16&& _frontColour, const UInt16&& _backColour) noexcept {
	ConsoleMutex.lock();
	ConsoleFrontColour = _frontColour;
	ConsoleBackColour = _backColour;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);//������ɫ��û�������ɫ����Ϊԭɫ	
	ConsoleMutex.unLock();
}

/*
	����ַ�������Ļ
	������
		const CChar* _string Ҫ������ַ���
*/

DLL_API const Void ZEngine::Console::print(const CChar* _string) noexcept {
	ConsoleMutex.lock();
	printf("%s", _string);
	ConsoleMutex.unLock();
}


/*
	����ַ�������Ļ���Զ�����
	������
		const CChar* _string Ҫ������ַ���
*/
DLL_API const Void ZEngine::Console::printInLine(const CChar* _string) noexcept {
	ConsoleMutex.lock();
	printf("%s\n", _string);
	ConsoleMutex.unLock();
}

/*
	����ַ�������Ļ
	������
		const TChar* _string Ҫ������ַ���
*/
DLL_API const Void ZEngine::Console::print(const TChar* _string) noexcept {
	ConsoleMutex.lock();
	printf("%ls", _string);
	ConsoleMutex.unLock();
}
/*
	����ַ�������Ļ���Զ�����
	������
		const TChar* _string Ҫ������ַ���
*/
DLL_API const Void ZEngine::Console::printInLine(const TChar* _string) noexcept {
	ConsoleMutex.lock();
	printf("%ls\n", _string);
	ConsoleMutex.unLock();
}

/*
	����ַ�������Ļ
	������
		const CChar* _string Ҫ������ַ���
		const UInt16&& _frontColour �����ǰ��ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
		const UInt16&& _backColour ����ı���ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
*/
DLL_API const Void ZEngine::Console::print(const CChar* _string, const UInt16&& _frontColour, const UInt16&& _backColour) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), std::forward<const Int32&&>(_frontColour | _backColour));//������ɫ��û�������ɫ����Ϊԭɫ
	printf("%s", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);	
	ConsoleMutex.unLock();
}

/*
	����ַ�������Ļ���Զ�����
	������
		const CChar* _string Ҫ������ַ���
		const UInt16&& _frontColour �����ǰ��ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
		const UInt16&& _backColour ����ı���ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
*/
DLL_API const Void ZEngine::Console::printInLine(const CChar* _string, const UInt16&& _frontColour, const UInt16&& _backColour) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), std::forward<const Int32&&>(_frontColour | _backColour));//������ɫ��û�������ɫ����Ϊԭɫ
	printf("%s\n", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);	
	ConsoleMutex.unLock();
}

/*
	����ַ�������Ļ
	������
		const CChar* _string Ҫ������ַ���
		const UInt16&& _frontColour �����ǰ��ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
		const UInt16&& _backColour ����ı���ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
*/
DLL_API const Void ZEngine::Console::print(const TChar* _string, const UInt16&& _frontColour, const UInt16&& _backColour) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), std::forward<const Int32&&>(_frontColour | _backColour));//������ɫ��û�������ɫ����Ϊԭɫ
	printf("%ls", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);	
	ConsoleMutex.unLock();
}

/*
	����ַ�������Ļ���Զ�����
	������
		const CChar* _string Ҫ������ַ���
		const UInt16&& _frontColour �����ǰ��ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
		const UInt16&& _backColour ����ı���ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
*/
DLL_API const Void ZEngine::Console::printInLine(const TChar* _string, const UInt16&& _frontColour, const UInt16&& _backColour) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), std::forward<const Int32&&>(_frontColour | _backColour));//������ɫ��û�������ɫ����Ϊԭɫ
	printf("%ls\n", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);
	ConsoleMutex.unLock();
}




/*
	����ַ�������Ļ
	������
		const CChar* _string Ҫ������ַ���
*/
DLL_API const Void ZEngine::Console::printSuccess(const CChar* _string) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_PRINT_FRONT_COLOUR_LIGHT_GREEN | CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK);//������ɫ��û�������ɫ����Ϊԭɫ
	printf("%s\n", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);
	ConsoleMutex.unLock();
}

/*
	����ַ�������Ļ
	������
		const TChar* _string Ҫ������ַ���
*/
DLL_API const Void ZEngine::Console::printSuccess(const TChar* _string) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_PRINT_FRONT_COLOUR_LIGHT_GREEN | CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK);//������ɫ��û�������ɫ����Ϊԭɫ
	printf("%ls\n", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);
	ConsoleMutex.unLock();
}

/*
	����ַ�������Ļ
	������
		const CChar* _string Ҫ������ַ���
*/
DLL_API const Void ZEngine::Console::printFail(const CChar* _string) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_PRINT_FRONT_COLOUR_LIGHT_RED | CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK);//������ɫ��û�������ɫ����Ϊԭɫ
	printf("%s\n", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);
	ConsoleMutex.unLock();
}

/*
	����ַ�������Ļ
	������
		const TChar* _string Ҫ������ַ���
*/
DLL_API const Void ZEngine::Console::printFail(const TChar* _string) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_PRINT_FRONT_COLOUR_LIGHT_RED | CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK);//������ɫ��û�������ɫ����Ϊԭɫ
	printf("%ls\n", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);
	ConsoleMutex.unLock();
}

/*
	���������Ϣ
	������
		const CChar* _string Ҫ����Ĵ�����Ϣ
*/
DLL_API const Void ZEngine::Console::printErrorMessage(const CChar* _string) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_PRINT_FRONT_COLOUR_DARK_RED | CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK);
	printf("������Ϣ��%s\n", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);
	ConsoleMutex.unLock();
}

/*
	���������Ϣ
	������
		const TChar* _string Ҫ����Ĵ�����Ϣ
*/
DLL_API const Void ZEngine::Console::printErrorMessage(const TChar* _string) noexcept {
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_PRINT_FRONT_COLOUR_DARK_RED | CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK);
	printf("������Ϣ��%ls\n", _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);
	ConsoleMutex.unLock();
}

