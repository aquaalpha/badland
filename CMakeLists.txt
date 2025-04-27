cmake_minimum_required(VERSION 3.29)
project(porjet_badland C)

set(CMAKE_C_STANDARD 11)

add_executable(porjet_badland main.c
        menu.c
        menu.h
        jeu.c
        jeu.h)
target_link_libraries(porjet_badland -lmingw32 -lalleg44)
