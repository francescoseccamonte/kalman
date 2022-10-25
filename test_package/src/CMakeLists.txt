add_executable(conan_test conan-test.cpp)

target_link_libraries(conan_test
	CONAN_PKG::cpp-travis-integration)
