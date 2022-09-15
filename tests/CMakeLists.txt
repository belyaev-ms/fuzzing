################################################################################
# Набор unit-тестов
################################################################################
option(EXM_COVERAGE_ENABLED "включить проверку покрытия тестами" OFF)
if (EXM_COVERAGE_ENABLED)
    include(../cmake/coverage.cmake)
else (EXM_COVERAGE_ENABLED)
    set(CMAKE_CXX_FLAGS "-g3")
endif (EXM_COVERAGE_ENABLED)

set(EXM_TEST_DEFINITIONS
    "EXM_TEST_ENABLED"
)

set(EXM_SOURCES
    ../lib/example.cpp
)

add_library(exmtest STATIC
    ${EXM_SOURCES}
)

set_target_properties(exmtest PROPERTIES
    COMPILE_DEFINITIONS "${EXM_TEST_DEFINITIONS}"
)

set(EXM_TEST_LIBS
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

target_link_libraries(exmtest ${EXM_TEST_LIBS})

include_directories(../lib)
if (EXM_COVERAGE_ENABLED)
    exm_add_coverage(coverage ctest coverage)
endif (EXM_COVERAGE_ENABLED)

# макрос для добавления unit-теста
macro(exm_add_test test)
    add_executable(${test} ${test}.cpp)
    add_test(${test} ${test})
    set_target_properties(${test} PROPERTIES
        COMPILE_DEFINITIONS "${KPR_TEST_DEFINITIONS}"
    )
    target_link_libraries(${test} exmtest)
endmacro(exm_add_test)


# список unit-тестов
exm_add_test(example_test)

################################################################################
# Статический анализ
################################################################################
add_custom_target(
    cppcheck
    COMMAND cppcheck
    --inline-suppr
    --suppressions-list=${CMAKE_CURRENT_SOURCE_DIR}/suppressions.list
    --enable=all
    --template=gcc
    --project=${CMAKE_BINARY_DIR}/compile_commands.json #2> ${CMAKE_BINARY_DIR}/cppcheck.log
)

add_custom_target(
    clang-tidy
    COMMAND run-clang-tidy
)

################################################################################
# Динамический анализ
################################################################################
if (EXM_USE_CLANG)
    add_custom_target(fuzzer)
    set(EXM_FUZZER_DEFINITIONS
        ${EXM_TEST_DEFINITIONS}
        "EXM_FUZZER_ENABLED"
    )

    macro(exm_add_fuzzer source)
        add_executable(${source} ${source}.cpp ${EXM_SOURCES})
        set_target_properties(${source} PROPERTIES
            COMPILE_DEFINITIONS "${EXM_FUZZER_DEFINITIONS}"
        )
        target_compile_options(${source} PRIVATE "-fsanitize=address,undefined,fuzzer")
        target_link_libraries(${source} PRIVATE "-fsanitize=address,undefined,fuzzer")
        add_dependencies(fuzzer ${source})
    endmacro(exm_add_fuzzer)

    exm_add_fuzzer(example_fuzzer)
    exm_add_fuzzer(example_fuzzer_too)
endif (EXM_USE_CLANG)
