#pragma once
#include <windows.h>
#include <list>
#include <utility>
#include <string>
#include <io.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <deque>
#include <fstream>
#include <map>
#include <algorithm>
#include <process.h>
#include <cstring>
#include <mutex>
#include <queue>
#include <sstream>
#include <cmath>
#include <cassert>
#include <climits>
#include <random>

#ifdef X86D
#pragma comment(lib, "GameLib32d.lib")
#endif

#ifdef X86
#pragma comment(lib, "GameLib32.lib")
#endif

#ifdef X64D
#pragma comment(lib, "GameLib64d.lib")
#endif

#ifdef X64
#pragma comment(lib, "GameLib64.lib")
#endif

#include "../GameLib/GameLib.h"