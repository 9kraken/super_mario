@echo off

set BUILD_TYPE=Ninja
set BUILD_SUFFIX=ninja
set QT_OPTION=%1

chcp 65001

set BUILD_FOLDER=build_%BUILD_SUFFIX%
set SOURCE_FOLDER=src

if not exist %BUILD_FOLDER% mkdir %BUILD_FOLDER%
cd %BUILD_FOLDER%

if %QT_OPTION%=="" set QT_OPTION=OFF
cmake -G %BUILD_TYPE% -DUSE_QT=%QT_OPTION% ..\%SOURCE_FOLDER%
cmake --build .

cd ..
