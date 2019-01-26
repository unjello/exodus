// based on tiny codes by iq/rgba

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <GL/gl.h>
#include <math.h>
#include "main.h"
#include "ext.h"
#include "shader.inl"
#include "fp.h"
#include "clinkster.h"


int intro_init(void)
{
  if (!EXT_Init())
    return 0;

  int pid = oglCreateProgram();
  int vsid = oglCreateShader(GL_VERTEX_SHADER);
  oglShaderSource(vsid, 1, &screen_vert, 0);
  oglCompileShader(vsid);
  oglAttachShader(pid, vsid);
  int fsid = oglCreateShader(GL_FRAGMENT_SHADER);
  oglShaderSource(fsid, 1, &main_frag, 0);
  oglCompileShader(fsid);
  oglAttachShader(pid, fsid);
  oglLinkProgram(pid);
  oglUseProgram(pid);

#ifdef DEBUG
  int result;
  char info[1536];
  oglGetProgramiv(vsid, GL_LINK_STATUS, &result);
  oglGetProgramInfoLog(vsid, 1024, NULL, (char *)info);
  if (!result)
    DebugBreak();
  oglGetProgramiv(fsid, GL_LINK_STATUS, &result);
  oglGetProgramInfoLog(fsid, 1024, NULL, (char *)info);
  if (!result)
    DebugBreak();
  oglGetProgramiv(pid, GL_LINK_STATUS, &result);
  oglGetProgramInfoLog(pid, 1024, NULL, (char *)info);
  if (!result)
    DebugBreak();
#endif

  return 1;
}

void intro_do(float time) {
  oglUniform4f(0, (float)XRES, (float)YRES, time, 0.0f);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}