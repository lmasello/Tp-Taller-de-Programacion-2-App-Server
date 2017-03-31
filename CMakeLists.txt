cmake_minimum_required(VERSION 3.5)
project(Tp_Taller_de_Programacion_2_App_Server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/lib/mongoose.h
        src/lib/mongoose.c
        src/server/Server.cpp
        src/server/Server.h
        src/server/Controller.cpp
        src/server/Controller.h
        src/SumController.cpp
        src/SumController.h
        src/TestController.cpp
        src/TestController.h
        src/MongoController.cpp
        src/MongoController.h)

#Adding mongo dependency
find_package(PkgConfig REQUIRED)
pkg_search_module(MONGOCXX REQUIRED libmongocxx)
include_directories(${MONGOCXX_INCLUDE_DIRS})
link_directories(${MONGOCXX_LIBRARY_DIRS})

add_executable(Tp_Taller_de_Programacion_2_App_Server ${SOURCE_FILES})

target_link_libraries(Tp_Taller_de_Programacion_2_App_Server ${MONGOCXX_LIBRARIES})
