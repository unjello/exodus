// based on tiny codes by iq/rgba
#pragma once

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <GL/gl.h>
#include "glext.h"

#ifdef _DEBUG
#define NUMFUNCIONES 10
#else
#define NUMFUNCIONES 8
#endif

extern void *myglfunc[NUMFUNCIONES];

#define oglUniform4f ((PFNGLUNIFORM4FPROC)myglfunc[0])
#define oglCreateProgram ((PFNGLCREATEPROGRAMPROC)myglfunc[1])
#define oglCreateShader ((PFNGLCREATESHADERPROC)myglfunc[2])
#define oglShaderSource ((PFNGLSHADERSOURCEPROC)myglfunc[3])
#define oglCompileShader ((PFNGLCOMPILESHADERPROC)myglfunc[4])
#define oglAttachShader ((PFNGLATTACHSHADERPROC)myglfunc[5])
#define oglLinkProgram ((PFNGLLINKPROGRAMPROC)myglfunc[6])
#define oglUseProgram ((PFNGLUSEPROGRAMPROC)myglfunc[7])

#ifdef _DEBUG
#define oglGetProgramiv ((PFNGLGETPROGRAMIVPROC)myglfunc[8])
#define oglGetProgramInfoLog ((PFNGLGETPROGRAMINFOLOGPROC)myglfunc[9])
#endif

int EXT_Init(void);
