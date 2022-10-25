from conans import ConanFile, CMake, tools
import os, subprocess, stat

class CppTravisIntegrationConan(ConanFile):
    name = "cpp-travis-integration"
    version = "0.1"
    url = "https://github.com/francescoseccamonte/cpp-travis-integration"
    description = "C++ Travis integration"
    license = "Apache 2.0"
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "CMakeLists.txt", "cmake/*", "src/*"
    no_copy_source = True
    generators = "cmake", "virtualenv"
    options = {
        "shared": [True, False],
        "build_tests": [True, False],
        "build_examples": [True, False],
        }
    default_options = {
        "shared": True,
        "build_tests": False,
        "build_examples": False,
        }

    def build_requirements(self):
        if self.options.build_tests:
            self.build_requires("gtest/cci.20210126")

    def build(self):
        cmake = CMake(self)
        cmake.definitions["BUILD_SHARED_LIBS"] = self.options.shared
        cmake.definitions["BUILD_TESTING"] = self.options.build_tests
        cmake.definitions["BUILD_EXAMPLES"] = self.options.build_examples
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
        self.env_info.LD_LIBRARY_PATH.append(os.path.join(self.package_folder, "lib"))
        self.env_info.PATH.append(os.path.join(self.package_folder, "bin"))

        # Allow binaries to find all libraries from its dependencies
        for libpath in self.deps_cpp_info.lib_paths:
            self.env_info.LD_LIBRARY_PATH.append(libpath)
