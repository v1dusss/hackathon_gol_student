@echo off
cl /nologo ../life_main.c /O2 /Zi /Wall /WX /link life_renderer.obj life_simulate.obj /DEBUG:FULL

