# Deepnote C++

Realtime THX deepnote rendering in C++.
Differs from the original by omitting initial random phase.

## Build and run on Linux

```bash
# Use the build script
sh build.sh
```

## Build and run on Windows

```bash
mkdir build && cd build
(maybe)conan install .. --build=missing
conan install ..
cmake .. -G "Visual Studio 17"
cmake --build . --config Release
.\bin\deepnote.exe
```
