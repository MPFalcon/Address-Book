cmake_minimum_required(VERSION 3.10.0)
project(AddressBook "C")

set(BINARY_SVR "address_book_server")
set(BINARY_CLI "address_book_client")
set(COMMON_INC "${CMAKE_SOURCE_DIR}/common")

if(CMAKE_BUILD_TYPE EQUAL Debug)
    message("Building debug...")
endif()

add_subdirectory(common)
add_subdirectory(back-end)
add_subdirectory(front-end)

if (DOCUMENTATION)
    include(config/documentation.cmake)
    documentation()
endif()

# EOF
