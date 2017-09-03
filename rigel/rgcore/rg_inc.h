#pragma once

#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <assert.h>
#include <memory>
#include <algorithm>

typedef int RgInt;
typedef unsigned int RgUInt;
typedef unsigned char RgByte;
typedef char RgChar;
typedef unsigned short RgWord;
typedef short RgShort;


#define RG_RELEASE(x) if(x!= nullptr){delete x;x = 0;}
#define RG_RELEASE_A(x) if(x!= nullptr){delete []x;x = 0;}