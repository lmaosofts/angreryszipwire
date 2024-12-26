@echo off
del angreryszipwire.exe >nul 2>&1
windres src.rc -O coff -o src.res
gcc src.res angreryszipwire.c -o angreryszipwire.exe -lgdi32 -lcomdlg32 -lhtmlhelp -lwinmm -mwindows
del src.res >nul 2>&1