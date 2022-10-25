add_library(kalman
            kalman_filter.cpp
            extended_kalman_filter.cpp)

target_include_directories(kalman PUBLIC include)

install(DIRECTORY include/kalman DESTINATION include)
install(TARGETS kalman ${DEFAULT_DESTINATIONS})

add_test_subdirectory(test)
