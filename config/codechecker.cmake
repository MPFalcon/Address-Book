function(codechecker target)
    set (CODECHECKER_OUTPUT_DIRS "${CMAKE_SOURCE_DIR}/output/CodeCheckerReport" "${CMAKE_SOURCE_DIR}/output/CodeCheckerHTML")
    add_custom_command(
        TARGET ${target} POST_BUILD
        COMMAND CodeChecker analyze ${CMAKE_BINARY_DIR}/compile_commands.json -o ${CMAKE_SOURCE_DIR}/output/CodeCheckerReport --config ${CMAKE_SOURCE_DIR}/.clang-analyzer/config.yaml --cppcheckargs ${CMAKE_SOURCE_DIR}/.cppcheck.args -i ${CMAKE_SOURCE_DIR}/.SkipFile -c || echo ""
        COMMAND CodeChecker parse ${CMAKE_SOURCE_DIR}/output/CodeCheckerReport -e html -o ${CMAKE_SOURCE_DIR}/output/CodeCheckerHTML || echo ""
        DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json 
    )
    #add_custom_target(codechecker_${target} ALL DEPENDS ${CODECHECKER_OUTPUT_DIRS})
endfunction()
