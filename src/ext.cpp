// based on tiny codes by iq/rgba

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <GL/gl.h>
#include "ext.h"

static char *strs[] = {
    "glUniform4f",
    "glCreateProgram",
    "glCreateShader",
    "glShaderSource",
    "glCompileShader",
    "glAttachShader",
    "glLinkProgram",
    "glUseProgram",
#ifdef _DEBUG
    "glGetProgramiv",
    "glGetProgramInfoLog",
#endif
};

void *myglfunc[NUMFUNCIONES];

int EXT_Init(void) {
  for (int i = 0; i < NUMFUNCIONES; i++) {
    myglfunc[i] = wglGetProcAddress(strs[i]);
    if (!myglfunc[i])
      return (0);
  }
  return (1);
}
