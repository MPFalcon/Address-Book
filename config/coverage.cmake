function(coverage_clean)
    add_custom_target(
        coverage-clean
        COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_SOURCE_DIR}/output/CoverageProfiles/*
        COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_SOURCE_DIR}/output/CoverageReports/*
        COMMAND ${CMAKE_COMMAND} -E rm -f ${CMAKE_SOURCE_DIR}/output/CoverageHTML/*
    )
endfunction()

#function(add_test_coverage target test_name)
#    add_test(NAME ${test_name}
#             COMMAND ${target} && llvm-profdata merge -sparse ${target}.profraw -o ${target}.profdata && llvm-cov show -show-branches="percent" -show-mcdc -show-line-counts -show-regions -output-dir=${CMAKE_SOURCE_DIR}/output/CoverageHTML -instr-profile ${CMAKE_SOURCE_DIR}/output/CoverageProfiles/${target}.profdata ${target} && llvm-cov report -show-mcdc-summary -instr-profile ${CMAKE_SOURCE_DIR}/output/CoverageProfiles/${target}.profdata ${target} > ${CMAKE_SOURCE_DIR}/output/CoverageReports/${target}.txt
#    )
#    set_tests_properties(test_name PROPERTIES ENVIRONMENT "LLVM_PROFILIE_FILE=${CMAKE_SOURCE_DIR}/output/CoverageProfiles/")
#endfunction()

function(add_test_coverage target test_name)
    file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/output/CoverageReports")
    set(PROFILE_PATH ${CMAKE_SOURCE_DIR}/output/CoverageProfiles/${target}.profraw)
#    if (COVERAGE)
#        add_test(
#            NAME ${test_name}
#            COMMAND bash -c "${CMAKE_CURRENT_BINARY_DIR}/${target} && llvm-profdata merge -sparse ${CMAKE_SOURCE_DIR}/output/CoverageProfiles/${target}.profraw -o ${CMAKE_SOURCE_DIR}/output/CoverageProfiles/${target}.profdata "
##"&& llvm-cov show -show-branches='percent' -show-mcdc -show-line-counts -show-regions -format='html' -output-dir=${CMAKE_SOURCE_DIR}/output/CoverageHTML/${target} -instr-profile ${CMAKE_SOURCE_DIR}/output/CoverageProfiles/${target}.profdata ${target} && llvm-cov report -show-mcdc-summary -instr-profile ${CMAKE_SOURCE_DIR}/output/CoverageProfiles/${target}.profdata ${target} > ${CMAKE_SOURCE_DIR}/output/CoverageReports/${target}.txt && llvm-cov export -format='lcov' -instr-profile ${CMAKE_SOURCE_DIR}/output/CoverageProfiles/${target}.profdata ${CMAKE_CURRENT_BINARY_DIR}/${target} > ${CMAKE_SOURCE_DIR}/output/CoverageReports/${target}.lcov"
#        )
#        set_tests_properties(
#            ${test_name}
#            PROPERTIES ENVIRONMENT "LLVM_PROFILE_FILE=${CMAKE_SOURCE_DIR}/output/CoverageProfiles/${target}.profraw"
#        )
#    else()
        add_test(NAME ${test_name}
                 COMMAND ${target} 
        )
#    endif()
endfunction()
