# rlFbo

A utility class for using multisampled framebuffers in [Raylib](https://github.com/raysan5/raylib).

Raylib's default framebuffer objects `RenderTexture2D` are not multisampled by
default. To use multisampled framebuffers in Raylib, you can use OpenGL APIs.
This class simplifies this step.

## Installation

### Manual Installation

You can directly copy `rlFbo/rlFbo.cpp` and `rlFbo/rlFbo.hpp` in to your project. Note that you will need `include/glad/glad.h` for raw OpenGL calls to work in Raylib, as the OpenGL context is initialized by `glad`. If you do not already have the header file, you can also copy it from this repo. 

### CMake
Clone the repo and install the library.

```sh
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=/desired/install/path
cmake --build build --target install
```

In your `CMakeLists.txt`:

```cmake
find_package(rlFbo)
target_link_libraries(YOUR_PROJECT PRIVATE rlFbo)
```

Alternatively you can clone this repo to your project root and in your `CMakeLists.txt`:

```cmake
add_subdirectory(rlFbo)
target_link_libraries(YOUR_PROJECT PRIVATE rlFbo)
```

## Example Usage

Below is an example of how you can use `rlFbo`. For more information, please
read the [header](rlFbo/rlFbo.hpp) file.

```cpp
#include <raylib.h>
#include <rlFbo/rlFbo.hpp>

void main(){
    InitWindow(1280,720,"rlFbo Demo");
    rlFbo myFbo(1280,720);
    while(!WindowShouldClose()){
        myFbo.begin();
            ClearBackground(WHITE);
            DrawCircle(640, 360, 300, RED);
        myFbo.end();

        myFbo.draw();

        BeginDrawing(); // needed for event polling
        EndDrawing();
    }
}
```

## TODO
- [ ] [Match OpenGL internalformat to Raylib's PixelFormat.](https://github.com/somecho/rlFbo/issues/1)
---

MIT License, Copyright © 2024 Somē Cho
