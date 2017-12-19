@echo off
g++ -std=c++11 ../Helpers/Helpers.h ../Helpers/Helpers.cpp main.cpp
echo. 
echo Program output:
echo.
cmd.exe /c "a.exe < input.txt"
echo.