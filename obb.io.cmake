
set(FRAME "obb")
set(WORK   "io")



project(${WORK} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET_DIR ${FRAME}/${WORK})
set(TARGETNAME ${WORK})

message(STATUS "TARGET_DIR: ${TARGET_DIR}")

set(HEADERS
    ${TARGET_DIR}/export.h
    ${TARGET_DIR}/lfd.h
    ${TARGET_DIR}/listener.h
    ${TARGET_DIR}/tcp_socket.h
    ${TARGET_DIR}/kbhit.h
    ${TARGET_DIR}/mouse.h
    ${TARGET_DIR}/console.h
    ${TARGET_DIR}/vchar.h
)

#set(OUT ${FRAME}_${WORK})
add_library(${TARGETNAME} STATIC

    ${HEADERS}
    ${TARGET_DIR}/lfd.cc
    ${TARGET_DIR}/listener.cc
    ${TARGET_DIR}/tcp_socket.cc
    ${TARGET_DIR}/kbhit.cc
    ${TARGET_DIR}/mouse.cc
    ${TARGET_DIR}/console.cc
    ${TARGET_DIR}/vchar.cc
)



target_include_directories(${TARGETNAME} PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                           $<INSTALL_INTERFACE:include/${TARGET_DIR}>
)


set_target_properties(${TARGETNAME} PROPERTIES OUTPUT_NAME "${FRAME}++.${WORK}")

target_compile_definitions(${TARGETNAME} PUBLIC "${TARGETNAME}_DEBUG=$<CONFIG:Debug>")
include(GenerateExportHeader)
generate_export_header(${TARGETNAME} EXPORT_FILE_NAME "${TARGETNAME}_export")

IF (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    )
ENDIF ()

# static .a should have been put into the current project archive file (libluss.io.a). So no need to link again with luss.a in the other project.
target_link_libraries(${TARGETNAME} ${CMAKE_DL_LIBS} "obb++")





install(TARGETS ${TARGETNAME}
        EXPORT  ${TARGETNAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        )

INSTALL(FILES ${HEADERS} DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${TARGET_DIR}")


add_custom_target("uninstall_${TARGETNAME}" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall_${TARGETNAME}"
    POST_BUILD
    COMMENT "Uninstall ${TARGETNAME} files under include and lib"
    COMMAND rm -vrf ${CMAKE_INSTALL_PREFIX}/include/${TARGET_DIR} ${CMAKE_INSTALL_PREFIX}/lib/lib${TARGETNAME}* || echo Nothing in install_manifest.txt to be uninstalled!
)


#add_subdirectory(test.app)
