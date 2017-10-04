@echo off
IF not exist "Build/win64" ( mkdir "Build/win64")

cd Build/win64/
cmake -G "Visual Studio 14 2015 Win64" ../../Rigel

cd ../../

pause
