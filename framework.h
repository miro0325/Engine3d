// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN      

#include "Types.h"
// 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>

// C++ 메모리 릭 체크
#define _CRTDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#pragma comment(lib, "msimg32.lib")
// C++ 헤더
#include <iostream>
#include <vector>
#include <string>
#include <locale>


using namespace std;

#include <format>
#include <filesystem>
namespace fs = std::filesystem;


#include "Vector.h"
#include "Types.h"
#include "Mesh.h"
#include "Utils.h"
#include "Defines.h"
#include "Enums.h"
#include "Scene.h"

#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"

#include "olcEngine3D.h"
#include "olcEngine3d_2.h"

