add_test_executable(kalman_filter-tests kalman_filter-tests.cpp)
target_link_libraries(kalman_filter-tests CONAN_PKG::gtest kalman)

add_test_executable(extended_kalman_filter-tests extended_kalman_filter-tests.cpp)
target_link_libraries(extended_kalman_filter-tests CONAN_PKG::gtest kalman)
