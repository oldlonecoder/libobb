set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("Dir: " ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(obb++.tests.app
    obb/oldbitsnbytes-tests.app/main.cc
)


target_include_directories(obb++.tests.app PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
)

message("Build dir : build/")

target_link_directories(obb++.tests.app PUBLIC bin)



# TABARNAK! j'joubli toujours de linker les librairies dans le bon ordre!!!!!
target_link_libraries(obb++.tests.app
    #obb++tui    
    #obb++est
    #obb++lexer    
    obb++.io    
    obb++
)

