#ifndef ZMainHeadFile_h
#define ZMainHeadFile_h


//

//忽视安全函数警告
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

//排除与Winsock.h与Winsock2.h冲突部分
#define WIN32_LEAN_AND_MEAN

#include<iostream>
#include<windows.h>
#include<process.h>


#ifdef DLL_API_FILE
#define DLL_API __declspec(dllexport)//导出
#else
#define DLL_API __declspec(dllimport)//导入
#endif



#endif // !ZMainHeadFile_h