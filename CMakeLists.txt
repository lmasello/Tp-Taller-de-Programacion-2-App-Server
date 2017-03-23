cmake_minimum_required(VERSION 3.6)
project(Tp_Taller_de_Programacion_2_App_Server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/lib/mongoose.h src/lib/mongoose.c src/server/Server.cpp src/server/Server.h)
add_executable(Tp_Taller_de_Programacion_2_App_Server ${SOURCE_FILES})