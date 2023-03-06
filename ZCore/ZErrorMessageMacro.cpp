#define DLL_API_FILE

#include"ZErrorMessageMacro.h"
#include"ZConsole.h"

using namespace ZEngine::Console;
using namespace ZEngine::Console::Private;

/*
	���������Ϣ
	������
		const CChar* _file �ļ���
		const CChar* _func ������
		const Int32 _line ����
		const CChar* _string Ҫ����Ĵ�����Ϣ
*/
DLL_API const Void ZEngine::Private::errorMessageConsolePrint(const CChar* _file, const CChar* _func, const Int32 _line, const CChar* _string) noexcept 
{
	ConsoleMutex.lock();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_PRINT_FRONT_COLOUR_DARK_RED | CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK);
	printf("�����ļ�·����%s\n��������%s\n�����У�%d\n������Ϣ��%s\n", _file, _func, std::forward<const Int32>(_line), _string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleFrontColour | ConsoleBackColour);
	ConsoleMutex.unLock();
}
