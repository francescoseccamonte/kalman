add_library(kalman INTERFACE)

target_include_directories(kalman INTERFACE include)
target_link_libraries(kalman INTERFACE CONAN_PKG::eigen)

install(DIRECTORY include/kalman DESTINATION include)
install(TARGETS kalman ${DEFAULT_DESTINATIONS})

add_test_subdirectory(test)
