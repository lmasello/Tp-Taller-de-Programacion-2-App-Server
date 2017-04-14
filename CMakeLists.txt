cmake_minimum_required(VERSION 3.5)
project(Tp_Taller_de_Programacion_2_App_Server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/lib/moongose/mongoose.h
        src/lib/moongose/mongoose.c
        src/logger/Logger.cpp
        src/logger/Logger.h
        src/logger/lockFile/LockFile.cpp
        src/logger/lockFile/LockFile.h
        src/logger/syscalls/SysCalls.h
        src/logger/syscalls/exceptions/SysCallException.h
        src/server/Server.cpp
        src/server/Server.h
        src/server/controller/Controller.cpp
        src/server/controller/Controller.h
        src/server/controller/PostSongs.cpp
        src/server/controller/PostSongs.h src/server/interceptor/Interceptor.cpp src/server/interceptor/Interceptor.h src/server/interceptor/JwtInterceptor.cpp src/server/interceptor/JwtInterceptor.h src/server/controller/GetSongs.cpp src/server/controller/GetSongs.h src/server/domain/song.h)

SET(CPACK_GENERATOR "DEB")
SET(CPACK_PACKAGE_CONTACT 'Macri gato')

#Adding mongo dependency
find_package(PkgConfig REQUIRED)
pkg_search_module(MONGOCXX REQUIRED libmongocxx)
include_directories(${MONGOCXX_INCLUDE_DIRS})
link_directories(${MONGOCXX_LIBRARY_DIRS})

add_executable(Tp_Taller_de_Programacion_2_App_Server ${SOURCE_FILES})

target_link_libraries(Tp_Taller_de_Programacion_2_App_Server ${MONGOCXX_LIBRARIES})

INCLUDE(CPack)