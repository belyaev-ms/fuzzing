# Пример использования:
#   exm_add_coverage(
#       sample_coverage     # имя для coverage target
#       sample_test         # имя теста
#       coverage            # имя директории для результатов
#   )
#
#   make
#   make sample_coverage

find_program(GCOV_PATH gcov)
find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)
find_program(GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/tests)

if (NOT GCOV_PATH)
    MESSAGE(FATAL_ERROR "gcov not found!")
endif (NOT GCOV_PATH)

set(CMAKE_C_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-coverage -fprofile-arcs -ftest-coverage")

function(exm_add_coverage coverage test outputname)
    if (NOT LCOV_PATH)
        MESSAGE(FATAL_ERROR "lcov not found!")
    endif (NOT LCOV_PATH)

    if (NOT GENHTML_PATH)
        MESSAGE(FATAL_ERROR "genhtml not found!")
    endif (NOT GENHTML_PATH)

    add_custom_target(${coverage}
        # cleanup lcov
        ${LCOV_PATH} --directory . --zerocounters
        # run tests
        COMMAND ${test} ${ARGV3}
        # capturing lcov counters and generating report
        COMMAND ${LCOV_PATH} --directory . --capture --output-file ${outputname}.info
        COMMAND ${LCOV_PATH} --remove ${outputname}.info 'tests/*' 'storage/*' '/usr/*' --output-file ${outputname}.info.cleaned
        COMMAND ${GENHTML_PATH} -o ${outputname} ${outputname}.info.cleaned
        COMMAND ${CMAKE_COMMAND} -E remove ${outputname}.info ${outputname}.info.cleaned

        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Resetting code coverage counters to zero.\nProcessing code coverage counters and generating report."
    )

    # Show info where to find the report
    add_custom_command(TARGET ${coverage} POST_BUILD
        COMMAND ;
        COMMENT "Open ./${outputname}/index.html in your browser to view the coverage report."
    )
endfunction(exm_add_coverage)
