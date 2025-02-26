cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(FRAME "lus")
set(WORK  "lexer")



project(${WORK} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET_DIR ${FRAME}/${WORK})
message (STATUS "TARGET_DIR: ${TARGET_DIR}")

set(HEADERS
    ${TARGET_DIR}/export.h
    ${TARGET_DIR}/lexer_types.h
    ${TARGET_DIR}/token_data.h
    ${TARGET_DIR}/tokens_table.h
    ${TARGET_DIR}/sscan.h
    ${TARGET_DIR}/lexer.h
)

set(OUT ${FRAME}_${WORK})
add_library(${OUT} STATIC

    ${HEADERS}

    ${TARGET_DIR}/lexer_types.cc
    ${TARGET_DIR}/token_data.cc
    ${TARGET_DIR}/tokens_table.cc
    ${TARGET_DIR}/sscan.cc
    ${TARGET_DIR}/lexer.cc
)

target_include_directories(${OUT} PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                           "$<INSTALL_INTERFACE:include/${TARGET_DIR}>"
)

target_compile_definitions(${OUT} PUBLIC "${OUT}_DEBUG=$<CONFIG:Debug>")
include(GenerateExportHeader)
generate_export_header(${OUT} EXPORT_FILE_NAME "${OUT}_export")

IF (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    )
ENDIF ()

# static libluss.a should have been put into the current project archive file (libluss.io.a). So no need to link again with luss.a in the other project.
target_link_libraries(${OUT} ${CMAKE_DL_LIBS} lus lus_io)





install(TARGETS ${OUT}
        EXPORT  ${OUT}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        )

INSTALL(FILES ${HEADERS} DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${TARGET_DIR}")


add_custom_target("uninstall_${OUT}" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall_${OUT}"
    POST_BUILD
    COMMENT "Uninstall ${OUT} files under include and lib"
    COMMAND rm -vrf ${CMAKE_INSTALL_PREFIX}/include/${TARGET_DIR} ${CMAKE_INSTALL_PREFIX}/lib/lib${OUT}* || echo Nothing in install_manifest.txt to be uninstalled!
)


#add_subdirectory(test.app)
