@echo off
chcp 65001 >nul
REM Tol'ko pokazat', chto novogo v Zagruzkah (nichego ne menyaet)
wsl.exe -e bash -lc "~/bin/take --list"
echo.
pause
