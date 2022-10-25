add_executable(myexec
               myexec.cpp)

target_link_libraries(myexec
	mylib)

install(TARGETS myexec ${DEFAULT_DESTINATIONS})
