set(SRC_FILES
    src/main.c
    src/server.c
)

add_executable(${BINARY_SVR} ${SRC_FILES})

target_include_directories(${BINARY_SVR}
    PRIVATE
    ${COMMON_INC}/inc/
    inc/
)

install(
    TARGETS ${BINARY_SVR}
    CONFIGURATIONS Release
    DESTINATION ${CMAKE_SOURCE_DIR}/release/
)

install(
    TARGETS ${BINARY_SVR}
    CONFIGURATIONS Debug
    DESTINATION ${CMAKE_SOURCE_DIR}/release-debug/
)

# EOF
