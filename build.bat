@echo off
cl /c /nologo life_simulate.c /Od /Zi /Wall /WX /DEBUG:FULL

link life_main.obj life_renderer.obj life_simulate.obj
