// based on tiny codes by iq/rgba

#ifndef _DEBUG

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <mmsystem.h>
#include "intro.h"
#include "main.h"
#include "clinkster.h"

static const PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER, PFD_TYPE_RGBA,
    32, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 32, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0 };

static DEVMODE screenSettings = { {0},
    #if _MSC_VER < 1400
    0,0,148,0,0x001c0000,{0},0,0,0,0,0,0,0,0,0,{0},0,32,XRES,YRES,0,0,      // Visual C++ 6.0
    #else
    0,0,156,0,0x001c0000,{0},0,0,0,0,0,{0},0,32,XRES,YRES,{0}, 0,           // Visuatl Studio 2005
    #endif
    #if(WINVER >= 0x0400)
    0,0,0,0,0,0,
    #if (WINVER >= 0x0500) || (_WIN32_WINNT >= 0x0400)
    0,0
    #endif
    #endif
    };

#ifdef __cplusplus
extern "C" 
{
#endif
int  _fltused = 0;
#ifdef __cplusplus
}
#endif

void entrypoint(void) {
    // full screen
    if( ChangeDisplaySettings(&screenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL) return;
    ShowCursor( 0 );

    // create window
    HWND hWnd = CreateWindow( (LPCSTR)0xC018,0,WS_POPUP|WS_VISIBLE,0,0,XRES,YRES,0,0,0,0);
    if( !hWnd ) return;
    HDC hDC = GetDC(hWnd);

    // initalize opengl
    if( !SetPixelFormat(hDC,ChoosePixelFormat(hDC,&pfd),&pfd) ) return;
    wglMakeCurrent(hDC,wglCreateContext(hDC));

    Clinkster_GenerateMusic();
    if( !intro_init() ) return;
    Clinkster_StartMusic();

    do {
        float pos = Clinkster_GetPosition();
        if (pos > Clinkster_MusicLength) break;
        intro_do( pos / Clinkster_TicksPerSecond);
        wglSwapLayerBuffers( hDC, WGL_SWAP_MAIN_PLANE );
    } while (!GetAsyncKeyState(VK_ESCAPE));

    ExitProcess(0);
}

#endif