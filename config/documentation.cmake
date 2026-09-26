function(documentation)
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/docs/userguide.pdf
        COMMAND pandoc userguide.md -o userguide.pdf
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/docs
        DEPENDS ${CMAKE_SOURCE_DIR}/docs/userguide.md
    )

    add_custom_target(pdf_documents ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/docs/userguide.pdf)

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/docs/html ${CMAKE_CURRENT_SOURCE_DIR}/docs/latex
        COMMAND doxygen Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS Doxyfile
    )

    add_custom_target(doxygen_documents ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/docs/html ${CMAKE_CURRENT_SOURCE_DIR}/docs/latex)

    install(
        FILES ${CMAKE_CURRENT_SOURCE_DIR}/docs/userguide.pdf
        DESTINATION ${CMAKE_SOURCE_DIR}/release-debug/docs
        CONFIGURATIONS Debug
    )
    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs/html ${CMAKE_CURRENT_SOURCE_DIR}/docs/latex
        DESTINATION ${CMAKE_SOURCE_DIR}/release-debug/docs
        CONFIGURATIONS Debug
    )

    install(
        FILES ${CMAKE_CURRENT_SOURCE_DIR}/docs/userguide.pdf
        DESTINATION ${CMAKE_SOURCE_DIR}/release/docs
        CONFIGURATIONS Release
    )

    install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs/html ${CMAKE_CURRENT_SOURCE_DIR}/docs/latex
        DESTINATION ${CMAKE_SOURCE_DIR}/release/docs
        CONFIGURATIONS Release
    )
endfunction()
