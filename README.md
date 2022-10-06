# Wavey

Playing around with audio.

## Building on Windows

```bash
mkdir build && cd build
(maybe)conan install .. --build=missing
conan install ..
cmake .. -G "Visual Studio 17"
cmake --build . --config Release
```

Run

```bash
.\bin\wavey.exe
```
