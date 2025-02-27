set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("Dir: " ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(obb++.tests.app
    obb/olbitsnbytes-tests.app/main.cc
)


target_include_directories(obb++.tests.app PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
)

message("Build dir : build/")

target_link_directories(obb++.tests.app PUBLIC build)

target_link_libraries(obb++.tests.app
    obb++
    obb++.io
    #obb++lexer
    #obb++est
    #obb++tui
)

