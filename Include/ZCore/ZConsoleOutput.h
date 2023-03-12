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

			//控制台输出颜色
			extern UInt16 ConsoleFrontColour;
			extern UInt16 ConsoleBackColour;
			extern ZMutex ConsoleMutex;
		}



		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_DARK_BLACK = 0X00U;	//前景：深黑色 
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_DARK_BLUE = 0X01U;	//前景：深蓝色  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_DARK_GREEN = 0X02U;	//前景：深绿色  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_DARK_CYAN = 0X03U;	//前景：深青色  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_DARK_RED = 0X04U;	//前景：深红色  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_DARK_PURPLE = 0X05U;	//前景：深紫色  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_DARK_YELLOW = 0X06U;	//前景：深黄色  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE = 0X07U;	//前景：深白色 
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_LIGHT_BLACK = 0X08U;	//前景：浅黑色  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_LIGHT_BLUE = 0X09U;	//前景：浅蓝色  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_LIGHT_GREEN = 0X0AU;	//前景：浅绿色 
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_LIGHT_CYAN = 0X0BU;	//前景：浅青色  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_LIGHT_RED = 0X0CU;	//前景：浅红色  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_LIGHT_PURPLE = 0X0DU;	//前景：浅紫色  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_LIGHT_YELLOW = 0X0EU;	//前景：浅黄色  
		constexpr UInt16 CONSOLE_PRINT_FRONT_COLOUR_LIGHT_WHILE = 0X0FU;	//前景：浅白色  
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK = 0X00U;	//背景：深黑色 
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_DARK_BLUE = 0X10U;	//背景：深蓝色    
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_DARK_GREEN = 0X20U;	//背景：深绿色   
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_DARK_CYAN = 0X30U;//背景：深青色   
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_DARK_RED = 0X40U;	//背景：深红色  
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_DARK_PURPLE = 0X50U;	//背景：深紫色   
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_DARK_YELLOW = 0X60U;	//背景：深黄色  
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_DARK_WHITE = 0X70U;	//背景：深白色 
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_LIGHT_BLACK = 0X80U;	//背景：浅黑色   
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_LIGHT_BLUE = 0X90U;	//背景：浅蓝色   
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_LIGHT_GREEN = 0XA0U;	//背景：浅绿色  
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_LIGHT_CYAN = 0XB0U;	//背景：浅青色   
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_LIGHT_RED = 0XC0U;	//背景：浅红色   
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_LIGHT_PURPLE = 0XD0U;	//背景：浅紫色   
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_LIGHT_YELLOW = 0XE0U;	//背景：浅黄色   
		constexpr UInt16 CONSOLE_PRINT_BACK_COLOUR_LIGHT_WHILE = 0XF0U;	//背景：浅白色   






		/*
			设置输出字符串到屏幕的颜色
			参数：
				const UInt16 _frontColour 输出的前景色,颜色变量名称为：CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
				const UInt16 _backColour 输出的背景色,颜色变量名称为：CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
		*/
		DLL_API const Void setPrintColour(const UInt16 _frontColour, const UInt16 _backColour) noexcept;

		/*
			输出字符串到屏幕
			参数：
				const CChar* _string 要输出的字符串
		*/
		DLL_API const Void print(const CChar* _string) noexcept;

		/*
			输出字符串到屏幕，自动换行
			参数：
				const CChar* _string 要输出的字符串
		*/
		DLL_API const Void printInLine(const CChar* _string) noexcept;


		/*
			输出字符串到屏幕，自动换行
			参数：
				const CChar* _string 要输出的字符串
		*/
		DLL_API const Void printInLine(const CChar* _string) noexcept;

		/*
			输出字符串到屏幕
			参数：
				const TChar* _string 要输出的字符串
		*/
		DLL_API const Void print(const TChar* _string) noexcept;

		/*
			输出字符串到屏幕，自动换行
			参数：
				const TChar* _string 要输出的字符串
		*/
		DLL_API const Void printInLine(const TChar* _string) noexcept;

		/*
			输出字符串到屏幕
			参数：
				const CChar* _string 要输出的字符串
				const UInt16 _frontColour 输出的前景色,颜色变量名称为：CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
				const UInt16 _backColour 输出的背景色,颜色变量名称为：CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
		*/
		DLL_API const Void print(const CChar* _string, const UInt16 _frontColour, const UInt16 _backColour) noexcept;

		/*
			输出字符串到屏幕，自动换行
			参数：
				const CChar* _string 要输出的字符串
				const UInt16 _frontColour 输出的前景色,颜色变量名称为：CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
				const UInt16 _backColour 输出的背景色,颜色变量名称为：CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
		*/
		DLL_API const Void printInLine(const CChar* _string, const UInt16 _frontColour, const UInt16 _backColour) noexcept;

		/*
			输出字符串到屏幕
			参数：
				const CChar* _string 要输出的字符串
				const UInt16 _frontColour 输出的前景色,颜色变量名称为：CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
				const UInt16 _backColour 输出的背景色,颜色变量名称为：CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
		*/
		DLL_API const Void print(const TChar* _string, const UInt16 _frontColour, const UInt16 _backColour) noexcept;

		/*
			输出字符串到屏幕，自动换行
			参数：
				const CChar* _string 要输出的字符串
				const UInt16 _frontColour 输出的前景色,颜色变量名称为：CONSOLE_PRINT_FRONT_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_FRONT_COLOUR_DARK_WHITE
				const UInt16 _backColour 输出的背景色,颜色变量名称为：CONSOLE_PRINT_BACK_COLOUR_XXXX_XXXXX，原色为 CONSOLE_PRINT_BACK_COLOUR_DARK_BLACK
		*/
		DLL_API const Void printInLine(const TChar* _string, const UInt16 _frontColour, const UInt16 _backColour) noexcept;

		/*
			输出字符串到屏幕
			参数：
				const CChar* _string 要输出的字符串
		*/
		DLL_API const Void printSuccess(const CChar* _string) noexcept;

		/*
			输出字符串到屏幕
			参数：
				const TChar* _string 要输出的字符串
		*/
		DLL_API const Void printSuccess(const TChar* _string) noexcept;

		/*
			输出字符串到屏幕
			参数：
				const CChar* _string 要输出的字符串
		*/
		DLL_API const Void printFail(const CChar* _string) noexcept;

		/*
			输出字符串到屏幕
			参数：
				const TChar* _string 要输出的字符串
		*/
		DLL_API const Void printFail(const TChar* _string) noexcept;


		/*
			输出错误信息
			参数：
				const CChar* _string 要输出的错误信息
		*/
		DLL_API const Void printErrorMessage(const CChar* _string) noexcept;

		/*
			输出错误信息
			参数：
				const TChar* _string 要输出的错误信息
		*/
		DLL_API const Void printErrorMessage(const TChar* _string) noexcept;








	}
}

#endif // !ZConsoleOutput_h
