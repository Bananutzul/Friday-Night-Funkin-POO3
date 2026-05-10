cmake_minimum_required(VERSION 3.10)
project(FNF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "/opt/homebrew/Cellar/sfml/3.0.2/lib/cmake/SFML")

find_package(SFML 3 COMPONENTS Graphics Audio REQUIRED)

add_executable(FNF main.cpp
        Arrow.h
        Arrow.cpp
        GameObject.h
        GameObject.cpp
        HoldArrow.h
        HoldArrow.cpp
        GameManager.h
        GameManager.cpp
        Chart.h)

target_include_directories(FNF PRIVATE
        "/opt/homebrew/Cellar/sfml/3.0.2/include"
)

target_link_libraries(FNF PRIVATE
        SFML::Graphics
        SFML::Audio
)