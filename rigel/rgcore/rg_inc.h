#pragma once
#include <string>
#include <wchar.h>

#ifdef _DEBUG
#include <assert.h>
#define RG_ASSERT(x) //assert(x)
#else
#define RG_ASSERT(x)
#endif

typedef int RgInt;
typedef unsigned int RgUInt;
typedef unsigned char RgByte;
typedef char RgChar;
typedef unsigned short RgWord;
typedef short RgShort;

typedef std::string RgStr;


#define RG_RELEASE(x) if(x!= nullptr){delete x;x = 0;}
#define RG_RELEASE_A(x) if(x!= nullptr){delete []x;x = 0;}