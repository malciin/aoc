@echo off
g++ -std=c++11 -O3 ../Helpers/Helpers.h ../Helpers/Helpers.cpp main3.cpp
echo. 
echo Program output:
echo.
cmd.exe /c "a.exe < input.txt"
echo.