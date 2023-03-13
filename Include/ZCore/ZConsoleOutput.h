#ifndef ZConsoleOutput_h
#define ZConsoleOutput_h

#include"ZBasicType.h"
#include"..\ZBasic\ZMutex.h"

namespace ZEngine 
{

	namespace Console 
	{

		namespace Private
		{

			//����̨�����ɫ
			extern UInt16 ConsoleFrontColour;
			extern UInt16 ConsoleBackColour;
			extern ZMutex ConsoleMutex;
		}



		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_DARK_BLACK = 0X00U;	//ǰ�������ɫ 
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_DARK_BLUE = 0X01U;	//ǰ��������ɫ  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_DARK_GREEN = 0X02U;	//ǰ��������ɫ  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_DARK_CYAN = 0X03U;	//ǰ��������ɫ  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_DARK_RED = 0X04U;	//ǰ�������ɫ  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_DARK_PURPLE = 0X05U;	//ǰ��������ɫ  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_DARK_YELLOW = 0X06U;	//ǰ�������ɫ  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE = 0X07U;	//ǰ�������ɫ 
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_LIGHT_BLACK = 0X08U;	//ǰ����ǳ��ɫ  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_LIGHT_BLUE = 0X09U;	//ǰ����ǳ��ɫ  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_LIGHT_GREEN = 0X0AU;	//ǰ����ǳ��ɫ 
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_LIGHT_CYAN = 0X0BU;	//ǰ����ǳ��ɫ  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_LIGHT_RED = 0X0CU;	//ǰ����ǳ��ɫ  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_LIGHT_PURPLE = 0X0DU;	//ǰ����ǳ��ɫ  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_LIGHT_YELLOW = 0X0EU;	//ǰ����ǳ��ɫ  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_LIGHT_WHILE = 0X0FU;	//ǰ����ǳ��ɫ  
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK = 0X00U;	//���������ɫ 
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_DARK_BLUE = 0X10U;	//����������ɫ    
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_DARK_GREEN = 0X20U;	//����������ɫ   
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_DARK_CYAN = 0X30U;//����������ɫ   
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_DARK_RED = 0X40U;	//���������ɫ  
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_DARK_PURPLE = 0X50U;	//����������ɫ   
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_DARK_YELLOW = 0X60U;	//���������ɫ  
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_DARK_WHITE = 0X70U;	//���������ɫ 
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_LIGHT_BLACK = 0X80U;	//������ǳ��ɫ   
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_LIGHT_BLUE = 0X90U;	//������ǳ��ɫ   
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_LIGHT_GREEN = 0XA0U;	//������ǳ��ɫ  
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_LIGHT_CYAN = 0XB0U;	//������ǳ��ɫ   
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_LIGHT_RED = 0XC0U;	//������ǳ��ɫ   
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_LIGHT_PURPLE = 0XD0U;	//������ǳ��ɫ   
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_LIGHT_YELLOW = 0XE0U;	//������ǳ��ɫ   
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_LIGHT_WHILE = 0XF0U;	//������ǳ��ɫ   






		/*
			��������ַ�������Ļ����ɫ
			������
				const UInt16 _frontColour �����ǰ��ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
				const UInt16 _backColour ����ı���ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
		*/
		DLL_API const Void setPrintColour(const UInt16 _frontColour, const UInt16 _backColour) noexcept;

		/*
			����ַ�������Ļ
			������
				const CChar* _string Ҫ������ַ���
		*/
		DLL_API const Void print(const CChar* _string) noexcept;

		/*
			����ַ�������Ļ���Զ�����
			������
				const CChar* _string Ҫ������ַ���
		*/
		DLL_API const Void printInLine(const CChar* _string) noexcept;


		/*
			����ַ�������Ļ���Զ�����
			������
				const CChar* _string Ҫ������ַ���
		*/
		DLL_API const Void printInLine(const CChar* _string) noexcept;

		/*
			����ַ�������Ļ
			������
				const TChar* _string Ҫ������ַ���
		*/
		DLL_API const Void print(const TChar* _string) noexcept;

		/*
			����ַ�������Ļ���Զ�����
			������
				const TChar* _string Ҫ������ַ���
		*/
		DLL_API const Void printInLine(const TChar* _string) noexcept;

		/*
			����ַ�������Ļ
			������
				const CChar* _string Ҫ������ַ���
				const UInt16 _frontColour �����ǰ��ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
				const UInt16 _backColour ����ı���ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
		*/
		DLL_API const Void print(const CChar* _string, const UInt16 _frontColour, const UInt16 _backColour) noexcept;

		/*
			����ַ�������Ļ���Զ�����
			������
				const CChar* _string Ҫ������ַ���
				const UInt16 _frontColour �����ǰ��ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
				const UInt16 _backColour ����ı���ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
		*/
		DLL_API const Void printInLine(const CChar* _string, const UInt16 _frontColour, const UInt16 _backColour) noexcept;

		/*
			����ַ�������Ļ
			������
				const CChar* _string Ҫ������ַ���
				const UInt16 _frontColour �����ǰ��ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
				const UInt16 _backColour ����ı���ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
		*/
		DLL_API const Void print(const TChar* _string, const UInt16 _frontColour, const UInt16 _backColour) noexcept;

		/*
			����ַ�������Ļ���Զ�����
			������
				const CChar* _string Ҫ������ַ���
				const UInt16 _frontColour �����ǰ��ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
				const UInt16 _backColour ����ı���ɫ,��ɫ��������Ϊ��CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX��ԭɫΪ CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
		*/
		DLL_API const Void printInLine(const TChar* _string, const UInt16 _frontColour, const UInt16 _backColour) noexcept;

		/*
			����ַ�������Ļ
			������
				const CChar* _string Ҫ������ַ���
		*/
		DLL_API const Void printSuccess(const CChar* _string) noexcept;

		/*
			����ַ�������Ļ
			������
				const TChar* _string Ҫ������ַ���
		*/
		DLL_API const Void printSuccess(const TChar* _string) noexcept;

		/*
			����ַ�������Ļ
			������
				const CChar* _string Ҫ������ַ���
		*/
		DLL_API const Void printFail(const CChar* _string) noexcept;

		/*
			����ַ�������Ļ
			������
				const TChar* _string Ҫ������ַ���
		*/
		DLL_API const Void printFail(const TChar* _string) noexcept;


		/*
			���������Ϣ
			������
				const CChar* _string Ҫ����Ĵ�����Ϣ
		*/
		DLL_API const Void printErrorMessage(const CChar* _string) noexcept;

		/*
			���������Ϣ
			������
				const TChar* _string Ҫ����Ĵ�����Ϣ
		*/
		DLL_API const Void printErrorMessage(const TChar* _string) noexcept;








	}
}

#endif // !ZConsoleOutput_h
