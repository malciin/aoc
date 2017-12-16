@echo off
g++ -std=c++11 -O3 main.cpp
echo. 
echo Program output:
echo.
cmd.exe /c "a.exe < input.txt"
echo.