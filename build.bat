SET ASM=nasm -f win32 
SET CXX=cl /c /nologo /W1 /WX- /diagnostics:classic /std:c++latest /O2 /Ob1 /Oi /Os /Oy /QIfist /D WINDOWS /D _CRT_SECURE_NO_WARNINGS /D _VC80_UPGRADE=0x0600 /D _USING_V110_SDK71_ /GF /Gm- /MT /Zp1 /GS- /Gy /arch:IA32 /fp:fast /fp:except- /Zc:wchar_t /Zc:forScope /Zc:inline /FAs /Gz /TP /analyze- 
SET LNK=crinkler.exe /SUBSYSTEM:WINDOWS /CRINKLER /SATURATE /HASHSIZE:500 /HASHTRIES:500 /COMPMODE:VERYSLOW /ORDERTRIES:10000 /UNALIGNCODE /REPORT:.\build\out.html /ENTRY:"entrypoint" "opengl32.lib" "winmm.lib" "kernel32.lib" "user32.lib" "gdi32.lib"
.\shader_minifier.exe -v -o .\src\shader.inl --preserve-externals --no-renaming-list main .\glsl\main.frag .\glsl\screen.vert
.\RenoiseConvert.exe music\music.xrns src\music.asm
rd /s /q build
mkdir build
%CXX% /FC src\ext.cpp /Fobuild\ext.obj
%CXX% /FC src\intro.cpp /Fobuild\intro.obj
%CXX% /FC src\main_win_rel.cpp /Fobuild\main_win_rel.obj
%ASM% src\clinkster_multithreaded.asm -o build\clinkster_multithreaded.obj
%LNK% build\clinkster_multithreaded.obj build\ext.obj build\intro.obj build\main_win_rel.obj /OUT:build\exs.exe
