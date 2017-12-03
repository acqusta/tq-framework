cmake_minimum_required(VERSION 2.8)
    
project(tq_framework)

set(CMAKE_INSTALL_PREFIX "dist")

add_definitions ( -D_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS)

if (UNIX)
  add_definitions(-fPIC)
endif()

set(SOCI_STATIC OFF)
set(SOCI_TESTS  OFF)
set(SOCI_CXX_C11 ON)
set(SOCI_ODBC    OFF)
set(SOCI_EMPTY   OFF)
set(SOCI_SQLITE3 ON)
set(SOCI_MYSQL   ON)
set(SOCI_LIBDIR  "lib")

set(SQLITE3_INCLUDE_DIR sqlite3.11)
set(SQLITE3_LIBRARY   sqlite3)
include_directories( sqlite3.11 )



add_subdirectory(glog-master)
add_subdirectory(protobuf-2.6.1)
add_subdirectory(zeromq-4.2.1)
add_subdirectory(libsodium-1.0.12)
add_subdirectory(soci-master)
add_subdirectory(sqlite3.11)
add_subdirectory(zlib-1.2.11)

install(DIRECTORY tdb tdf ctp_v6.3.6 DESTINATION .)
