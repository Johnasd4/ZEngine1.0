#ifndef ZBasicType_h
#define ZBasicType_h

#include"ZMainHeadFile.h"

//Ӣ���ַ���ÿ��1B
typedef char CChar;
//ȫ�����ַ���ÿ��2B
typedef wchar_t TChar;


//8λ���ͣ���Χ��-128~127��3λ����
typedef char Int8;
//16λ���ͣ���Χ��-3,2768~3,2767��5λ����
typedef short Int16;
//32λ���ͣ���Χ��-21,4748,3648~21,4748,3647��10λ����
typedef int Int32;
//64λ���ͣ���Χ��-922,3372,0368,5477,5808~922,3372,0368,5477,5807��19λ����
typedef long long Int64;

//8λ���ͣ���Χ��0~255��3λ����
typedef unsigned char UInt8;
//16λ���ͣ���Χ��0~6,5535��5λ����
typedef unsigned short UInt16;
//32λ���ͣ���Χ��0~42,9496,7295��10λ����
typedef unsigned int UInt32;
//64λ���ͣ���Χ��0~1844,6744,0737,0955,1616��20λ����
typedef unsigned long long UInt64;

//32λ�����ͣ���Χ��-3.40E+38 ~ +3.40E+38
typedef float Float32;

//64λ�����ͣ���Χ��-1.79E+308 ~ +1.79E+308
typedef double Float64;

//������
typedef bool Boolean;

//�ֽ�
typedef unsigned char Byte;

//������
typedef void Void;

//��ַ
typedef void* Address;

//���
typedef void* Handle;


#endif // !ZBasicType_h
