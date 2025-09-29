@echo off
REM cl /c /nologo life_simulate.c /O2 /Zi /Wall /WX /link life_renderer.obj life_simulate.obj /DEBUG:FULL
cl /c /nologo life_simulate.c /O2 /Zi /Wall /WX /DEBUG:FULL

link life_main.obj life_renderer.obj life_simulate.obj
