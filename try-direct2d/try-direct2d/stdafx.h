// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>
#include <windowsx.h>

// C ランタイム ヘッダー ファイル
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: プログラムに必要な追加ヘッダーをここで参照してください
#include <wchar.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <direct.h>
#include <ctime>
#include <filesystem>
#include <tuple> 
#include <functional> 
#include <map>

// M_PIが定義されていないエラーが出るのでstdafx.cppの"#include stdafx.h"より前に移動した
// #define _USE_MATH_DEFINES
// #include <cmath>  


#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")

#ifdef _DEBUG
    #include "Debug.h" 
#endif
