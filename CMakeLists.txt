cmake_minimum_required(VERSION 3.20)
project(rtsim)

set(CMAKE_CXX_STANDARD 17)

add_executable(rtsim main.cpp Vector.h Object.h RGB.h Render.h Camera.h Ray.h Scene.h Source.h)