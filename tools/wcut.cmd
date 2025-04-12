@echo on
setlocal enabledelayedexpansion

if "%~1"=="" (
    echo Error: No se especifico archivo
    exit /b 1
)

if not exist "%~1" (
    echo Error: El archivo no existe
    exit /b 1
)

for %%A in ("%~1") do (
    set size=%%~zA
    echo !size!
)
exit /b 0