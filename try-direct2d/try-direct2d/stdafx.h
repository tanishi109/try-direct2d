// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
// Windows �w�b�_�[ �t�@�C��:
#include <windows.h>
#include <windowsx.h>

// C �����^�C�� �w�b�_�[ �t�@�C��
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[�������ŎQ�Ƃ��Ă�������
#include <wchar.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <stdio.h>
#include <string>
#include <vector>
// FIXME: M_PI����`����Ă��Ȃ��G���[���o��̂�stdafx.cpp��"#include stdafx.h"���O�Ɉړ�����
// #define _USE_MATH_DEFINES
// #include <cmath>  

// Player.h�Ŏg�p���Ă�
// #include <tuple> 

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#ifdef _DEBUG
    template<typename... Args>
    void log(char* text, Args... args) {
        char buf[256];
        sprintf_s(buf, text, args...);
        OutputDebugStringA(buf);
    }
#endif
