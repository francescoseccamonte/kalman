# lib contains all the libraries -> whathever logic and algorithm you develop
add_subdirectory(lib)

# exec contains all the executables -> using libraries without introducing any logic
add_subdirectory(exec)

# for the aforementioned reasons, the code that needs to be tested (and whose coverage
# is included in the coverage report) is only the one in lib. Code in exec is excluded

# examples contains example usage of the libraries
build_optional(BUILD_EXAMPLES examples)
