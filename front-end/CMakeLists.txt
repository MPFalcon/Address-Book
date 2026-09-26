set(BUILDER_XML_PATH "\"${CMAKE_SOURCE_DIR}/assets/builder.ui\"")
set(SRC_FILES
    src/main.c
    src/model.c
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)
add_executable(${BINARY_CLI} ${SRC_FILES})

add_compile_definitions(
    BUILDER_UI_PATH=${BUILDER_XML_PATH}
)

target_link_libraries(${BINARY_CLI} PRIVATE PkgConfig::GTK4)

target_include_directories(${BINARY_CLI}
    PRIVATE
    ${COMMON_INC}/inc/
    inc/
)

install(
    TARGETS ${BINARY_CLI}
    CONFIGURATIONS Release
    DESTINATION ${CMAKE_SOURCE_DIR}/release/
)

install(
    TARGETS ${BINARY_CLI}
    CONFIGURATIONS Debug
    DESTINATION ${CMAKE_SOURCE_DIR}/release-debug/
)

# EOF
