cmake_minimum_required(VERSION 3.5)
project(Tp_Taller_de_Programacion_2_App_Server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main/main.cpp
        src/main/lib/moongose/mongoose.h
        src/main/lib/moongose/mongoose.c
        src/main/logger/Logger.cpp
        src/main/logger/Logger.h
        src/main/logger/lockFile/LockFile.cpp
        src/main/logger/lockFile/LockFile.h
        src/main/logger/syscalls/SysCalls.h
        src/main/logger/syscalls/exceptions/SysCallException.h
        src/main/server/Server.cpp
        src/main/server/Server.h
        src/main/server/controller/Controller.cpp
        src/main/server/controller/Controller.h
        src/main/server/controller/PostSongs.cpp
        src/main/server/controller/PostSongs.h
        src/main/server/interceptor/Interceptor.cpp
        src/main/server/interceptor/Interceptor.h
        src/main/server/interceptor/JwtInterceptor.cpp
        src/main/server/interceptor/JwtInterceptor.h
        src/main/server/controller/GetSongs.cpp
        src/main/server/controller/GetSongs.h
        src/main/server/domain/song.h
        src/main/mongo/MongoClient.cpp
        src/main/mongo/MongoClient.h
        src/main/lib/base64/base64.cpp
        src/main/lib/base64/base64.h)

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_CONTACT 'Macri gato')

#Adding mongo dependency
find_package(PkgConfig REQUIRED)
pkg_search_module(MONGOCXX REQUIRED libmongocxx)
include_directories(${MONGOCXX_INCLUDE_DIRS})
link_directories(${MONGOCXX_LIBRARY_DIRS})

add_executable(Tp_Taller_de_Programacion_2_App_Server ${SOURCE_FILES})

target_link_libraries(Tp_Taller_de_Programacion_2_App_Server ${MONGOCXX_LIBRARIES})

include(CPack)


###########################################3
# TESTS
# Gtest
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/googletest)
enable_testing()
include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR})

set (TEST_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/test")

include_directories(${TEST_SOURCE_FILES})

add_executable(Tests
        ${TEST_SOURCE_FILES}/mainTests.cpp
        )

target_link_libraries(Tests gtest gtest_main)
#target_link_libraries (Tests Tp_Taller_de_Programacion_2_App_Server)

add_test(
        NAME Tests
        COMMAND Tests
)
