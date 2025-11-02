# Umbra Log

A lightweight C++ logging library for game development.

## Features

✅ Easy to use\
✅ Supports formatting\
✅ Modular and reusable

## Installation

### Using CMake:

```bash
git submodule add git@github.com:UmbraEngine/UmbraLog.git external/UmbraLog
git submodule update --init --recursive
```

Also add the following into your projects CMakeLists.txt file

```cmake
add_subdirectory(external/UmbraLog)
target_link_libraries(your-project PRIVATE UmbraLog)
```
