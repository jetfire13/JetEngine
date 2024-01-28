@echo off

where cmake
IF %ERRORLEVEL% NEQ 0 (
	echo "Could Not find CMake"
	PAUSE
	EXIT 1
)

where ninja
IF %ERRORLEVEL% NEQ 0 (
	echo "Could Not find ninja"
	PAUSE
	EXIT 1
)

where clang
IF %ERRORLEVEL% NEQ 0 (
	echo "Could Not find clang compiler"
	PAUSE
	EXIT 1
)

where clang++
IF %ERRORLEVEL% NEQ 0 (
	echo "Could Not find clang++ compiler"
	PAUSE
	EXIT 1
)

pushd ..\ 
call cmake . -GNinja -DCMAKE_CXX_COMPILER="clang++" -DCMAKE_C_COMPILER="clang" -DCMAKE_EXPORT_COMPILE_COMMANDS=1
popd
PAUSE
