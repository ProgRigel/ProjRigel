#pragma once
#include "rg_inc.h"
#include "rg_log.h"
#include "rg_math.h"
#include "rg_utility.h"
#include "rg_signal.hpp"
#include "rg_window.h"
#include "rg_window_manager.h"

#ifdef _MSC_VER
#include "rg_window_windows.h"
#else __GNUC__

#endif

#include <Windows.h>
#include <string>

#include <iostream>
#include <stdio.h>
#include <vector>

#include <memory>
#include <algorithm>
#include <comdef.h>
#include <wchar.h>
