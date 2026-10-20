@echo off
chcp 65001 >nul
REM Zaberat' vse novoe iz Zagruzok Windows v repozitorij WSL i zapushit'
wsl.exe -e bash -lc "~/bin/take --ship"
echo.
pause
