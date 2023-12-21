# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -fexceptions -frtti)

# Declares and names the project.

project("breakout")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

add_library(game_loop SHARED
        GameLoop.cpp
        BreakoutGame.cpp
        Ball.cpp
        Paddle.cpp
        MathHelper.cpp
        BrickGrid.cpp
        Brick.cpp

        )

target_link_libraries(game_loop ${log-lib})



#target_link_libraries(BreakoutGame PRIVATE stdc++ stdc++fs)
#target_link_libraries(BreakoutGame PRIVATE stdc++)

