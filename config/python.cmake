function(PythonWheel PythonModule name version)
    set(PythonWheelTarget "target-${PythonModule}-${name}-${version}")
    set(PythonWheelFile "${name}-${version}-py3-none-any.whl")

    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${PythonModule}/dist/${PythonWheelFile}
        COMMAND python3 -m build --wheel 
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${PythonModule}
        COMMENT "Building wheel: ${name}-${version}"
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${PythonModule}/pyproject.toml
    )

    add_custom_target(${PythonWheelTarget} ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${PythonModule}/dist/${PythonWheelFile})

    install(
        FILES ${CMAKE_CURRENT_SOURCE_DIR}/${PythonModule}/dist/${PythonWheelFile}
        DESTINATION ${CMAKE_SOURCE_DIR}/release-debug/
        CONFIGURATIONS Debug
    )

    install(
        FILES ${CMAKE_CURRENT_SOURCE_DIR}/${PythonModule}/dist/${PythonWheelFile}
        DESTINATION ${CMAKE_SOURCE_DIR}/release/
        CONFIGURATIONS Release
    )
endfunction()
