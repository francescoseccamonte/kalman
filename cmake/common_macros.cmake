# Conveniece function to add an executable _and_ declare it as a test.
# - Call it with the same arguments you would call `add_executable()`.
# - The name of the test will be the same as the target.
# - This function does _not_ set up link libraries, so you need to do that yourself.
#
# Example:
#   add_test_executable(mylib-test mytest.cpp)
#   target_link_libraries(mylib-test mylib CONAN_PKG::gtest)
#
function(add_test_executable)
    cmake_parse_arguments(ADD_TEST_EXECUTABLE "" "TEST_ARGS" "" ${ARGN})
    add_executable(${ADD_TEST_EXECUTABLE_UNPARSED_ARGUMENTS})
    add_test(${ARGV0} ${CMAKE_BINARY_DIR}/bin/${ARGV0} ${ADD_TEST_EXECUTABLE_TEST_ARGS})

    if (${CODE_COVERAGE})
        add_dependencies(${COVERAGE_TARGET} ${ARGV0})
    endif()
endfunction()

macro(build_optional var  subdir)
    message(STATUS "${var}: ${${var}}")
    if (${${var}})
        add_subdirectory(${subdir})
    endif()
endmacro()

function(add_test_subdirectory directory)
    if(BUILD_TESTING)
        add_subdirectory(${directory})
    endif()
endfunction()
