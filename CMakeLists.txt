cmake_minimum_required(VERSION 3.29)
project(renderer)

set(CMAKE_CXX_STANDARD 20)

add_executable(renderer main.cpp
        dependencies/Vector.cpp
        dependencies/Vector.h
        dependencies/Matrix.cpp
        dependencies/Matrix.h
        dependencies/Common.cpp
        dependencies/Common.h
        dependencies/Color.cpp
        dependencies/Color.h
        dependencies/Transform.cpp
        dependencies/Transform.h
        dependencies/Camera.cpp
        dependencies/Camera.h
        dependencies/Screen.cpp
        dependencies/Screen.h
        dependencies/Triangle.cpp
        dependencies/Triangle.h
        dependencies/Vertex.cpp
        dependencies/Vertex.h)
