add_test_executable(mylib-tests mylib-tests.cpp)
target_link_libraries(mylib-tests CONAN_PKG::gtest mylib)
