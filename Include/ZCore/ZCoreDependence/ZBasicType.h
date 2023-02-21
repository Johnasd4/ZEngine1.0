#ifndef ZBasicType_h
#define ZBasicType_h

#include"ZMainHeadFile.h"

//英文字符，每个1B
typedef char CChar;
//全语言字符，每个2B
typedef wchar_t TChar;


//8位整型，范围：-128~127（3位数）
typedef char Int8;
//16位整型，范围：-3,2768~3,2767（5位数）
typedef short Int16;
//32位整型，范围：-21,4748,3648~21,4748,3647（10位数）
typedef int Int32;
//64位整型，范围：-922,3372,0368,5477,5808~922,3372,0368,5477,5807（19位数）
typedef long long Int64;

//8位整型，范围：0~255（3位数）
typedef unsigned char UInt8;
//16位整型，范围：0~6,5535（5位数）
typedef unsigned short UInt16;
//32位整型，范围：0~42,9496,7295（10位数）
typedef unsigned int UInt32;
//64位整型，范围：0~1844,6744,0737,0955,1616（20位数）
typedef unsigned long long UInt64;

//32位浮点型，范围：-3.40E+38 ~ +3.40E+38
typedef float Float32;

//64位浮点型，范围：-1.79E+308 ~ +1.79E+308
typedef double Float64;

//布尔型
typedef bool Boolean;

//字节
typedef unsigned char Byte;

//无类型
typedef void Void;

//地址
typedef void* Address;

//句柄
typedef void* Handle;


#endif // !ZBasicType_h
