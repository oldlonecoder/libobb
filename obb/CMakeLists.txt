cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(obb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADERS
    ${PROJECT_NAME}/export.h
    ${PROJECT_NAME}/cadres.h
    ${PROJECT_NAME}/cmdargs.h
    ${PROJECT_NAME}/colors.h
    ${PROJECT_NAME}/notify.h
    ${PROJECT_NAME}/expect.h
    ${PROJECT_NAME}/geometry.h
    ${PROJECT_NAME}/glyphes.h
    ${PROJECT_NAME}/journal.h
    ${PROJECT_NAME}/object.h
    ${PROJECT_NAME}/rem.h
    ${PROJECT_NAME}/string.h
)


add_library( ${PROJECT_NAME} STATIC

    ${HEADERS}
    ${PROJECT_NAME}/colors.cc
    ${PROJECT_NAME}/geometry.cc
    ${PROJECT_NAME}/journal.cc
    ${PROJECT_NAME}/cadres.cc
    ${PROJECT_NAME}/glyphes.cc
    ${PROJECT_NAME}/object.cc
    ${PROJECT_NAME}/rem.cc
    ${PROJECT_NAME}/cmdargs.cc
    ${PROJECT_NAME}/string.cc

)

target_include_directories(${PROJECT_NAME} PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                           $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

target_compile_definitions("${PROJECT_NAME}" PUBLIC "${PROJECT_NAME}_DEBUG=$<CONFIG:Debug>")
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME "${PROJECT_NAME}_export")

IF (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    )
ENDIF ()


target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS} ) # and other system dependencies...





install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        )

INSTALL(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME})


add_custom_target("uninstall_${PROJECT_NAME}" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall_${PROJECT_NAME}"
    POST_BUILD
    COMMENT "Uninstall ${PROJECT_NAME} files under include and lib"
    COMMAND rm -vrf ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME} ${CMAKE_INSTALL_PREFIX}/lib/lib${PROJECT_NAME}* || echo Nothing in install_manifest.txt to be uninstalled!
)


#add_subdirectory(test.app)
