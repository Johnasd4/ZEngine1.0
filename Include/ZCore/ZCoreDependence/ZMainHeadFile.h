#ifndef ZMainHeadFile_h
#define ZMainHeadFile_h


//

//���Ӱ�ȫ��������
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

//�ų���Winsock.h��Winsock2.h��ͻ����
#define WIN32_LEAN_AND_MEAN

#include<iostream>
#include<windows.h>
#include<process.h>


#ifdef DLL_API_FILE
#define DLL_API __declspec(dllexport)//����
#else
#define DLL_API __declspec(dllimport)//����
#endif



#endif // !ZMainHeadFile_h