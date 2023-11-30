cmake_minimum_required(VERSION 3.27)
project(penduv2 C)

set(CMAKE_C_STANDARD 11)

add_executable(penduv2
        main.c
        Pendu.c
        Pendu.h
)
