#ifndef ZBasicConstant_h
#define ZBasicConstant_h

#include"ZBasicType.h"

//Float32最大值
constexpr Float32 FLOAT32_MAX = 3.402823466e+38F;
//Float32最小值
constexpr Float32 FLOAT32_MIN = -3.402823466e+38F;



//文件大小
constexpr SizeT B_SIZE = 1;
constexpr SizeT KB_SIZE = 1024;
constexpr SizeT MB_SIZE = 1048576;
constexpr SizeT GB_SIZE = 1073741824;

//系统申请内存单元大小
constexpr SizeT SYSTEM_APPLY_MEMORY_UNIT_SIZE = 4 * KB_SIZE;



#endif // !ZBasicConstant_h
