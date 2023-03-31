add_library(kalman
            kalman_filter.cpp)

target_include_directories(kalman PUBLIC include)
target_link_libraries(kalman CONAN_PKG::eigen)

install(DIRECTORY include/kalman DESTINATION include)
install(TARGETS kalman ${DEFAULT_DESTINATIONS})

add_test_subdirectory(test)
