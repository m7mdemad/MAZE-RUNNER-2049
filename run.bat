@echo off

set arg1=%1
IF EXIST %arg1%.obj del %arg1%.obj
IF EXIST %arg1%.exe del %arg1%.exe
masm %arg1%.asm;
IF EXIST %arg1%.obj link %arg1%.obj; 
IF EXIST %arg1%.obj %arg1%.exe 


