# Basic shell
Basic shell emulator that can execute basic commands. Also supports a few command operators and history.
```bash
> echo "Hello, World!"
Hello, World!
```

```bash
> ls
src
README.md
CMakeLists.txt
include
.gitignore
build
shell
.history.txt
.git
.cache
```

```bash
> cat CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(shell)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
```

## Building
This project only depends on C++17 and can be built with CMake:
```bash
cmake -B build
cmake --build build
```
The executable will be located in `build/shell`. You can also build using your favorite compiler:
```bash
g++ -std=c++17 -Iinclude src/*.cpp -o shell
```

## Credits
This project was made by Daniel Vishnevsky and is licensed under MIT License. It was made in April of 2025 and was published in October 2026 in an effort to make all of my projects open-source.
