@echo off
cl /nologo life_simulate.c /O2 /Zi /Wall /WX /DEBUG:FULL life_main.obj life_renderer.obj 
