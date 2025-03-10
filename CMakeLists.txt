cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

project(arkanoid)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)


set(SOURCES
        src/Arkanoid.cpp
        src/ArkanoidMain.cpp
        src/Component.cpp
        src/GameEngine.cpp
        src/Group.cpp
        src/Sprite.cpp
        src/SpriteFromSheet.cpp
        src/SpriteSheet.cpp
#        src/Utilities.cpp
        src/World.cpp
)

set(HEADER_FILES
        include/Arkanoid.h
        include/Component.h
        include/GameEngine.h
        include/Group.h
        include/Sprite.h
        include/SpriteFromSheet.h
        include/SpriteSheet.h
#        include/Utilities.h
        include/World.h
)

add_executable(arkanoid ${SOURCES} ${HEADER_FILES})

target_include_directories(arkanoid PRIVATE include)
target_link_libraries(arkanoid SDL2::SDL2 SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf)