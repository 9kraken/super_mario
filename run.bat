@echo off
chcp 65001 > nul

REM Удаление старой сборки ( /s - включая подпапки, /q - без подтверждения)
if exist "build_ninja" rd /s /q "build_ninja"

REM Настройка размеров терминала
set cols=200
set lines=30

REM Проверка существования сборки (теперь она всегда будет отсутствовать при первом запуске)
if not exist "build_ninja\super_mario.exe" (
    echo [INFO] Сборка отсутствует или была удалена. Запуск build.bat...
    call build.bat
    if errorlevel 1 (
        echo [ERROR] Build failed!
        pause
        exit /b 1
    )
)

REM Запуск игры
start "Super Mario" cmd /c "mode con: cols=%cols% lines=%lines% && build_ninja\super_mario.exe"