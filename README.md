# Parser
Text parser for a text adventure. This repo just holds the C++ code for the parser, writing using a test-first approach with Catch 2.

(devblog)[devblog.md] follows the steps I've taken.

## Compile
```
mkdir build //if it doesn't exist
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

## Run
Tests: `./build/test/Debug/test.exe`

Main: `./build/Debug/Parser.exe`