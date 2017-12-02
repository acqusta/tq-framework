project(sqlite3)

cmake_minimum_required(VERSION 2.8)

if (UNIX)
  add_definitions(-fPIC)
endif()

add_library(sqlite3 STATIC sqlite3.c sqlite3.h sqlite3ext.h)

install(TARGETS sqlite3 DESTINATION lib)
install(FILES sqlite3.h sqlite3ext.h DESTINATION include)
