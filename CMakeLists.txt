cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
set (BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR})

project(libobb
    VERSION 0.1.0
    DESCRIPTION "A non-standard c++ framework suite of my personal projects"
    LANGUAGES CXX)

OPTION(OBB          "Build the core sublib..........................[libobb++.a]"     ON)
OPTION(IO           "Build the IO sublib............................[libobb++.io.a]"  ON)
OPTION(LEXER        "Build the lexer sublib.........................[libobb++.lexer.a]" OFF)
OPTION(EST          "Build the est (Expression Syntax Tree) sublib..[libobb++.est.a]" OFF)
OPTION(TUI          "Build the console ANSI UI  sublib..............[libobb++.tui.a]" OFF)
OPTION(TESTS        "Build the tests................................[framework_tests_app/tests.app]" ON)


if(OBB)
    message(STATUS "Building libobb.a")
    include(obb.cmake)
endif()

if(IO)
    message(STATUS "Building libobb.io.a")
    include(obb.io.cmake)

target_sources(io
  PRIVATE
    obb/io/terminal.h obb/io/terminal.cc
)
endif()

if(LEXER)
    message(STATUS "Building libobb.lexer.a")
    add_subdirectory(obb/lexer)
endif()

if(EST)
    message(STATUS "Building libobb.est.a")
    add_subdirectory(obb/est)
endif()

if(TUI)
    message(STATUS "Building libobb.tui.a")
    add_subdirectory(obb/tui)
endif()

if(TESTS)
    message(STATUS "framework tests:")
    include(obb.tests.cmake)
endif()

