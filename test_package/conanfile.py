from conans import ConanFile, CMake
import os

class ProjectTest(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        os.chdir("bin")
        # put all your tests here explicitely
        self.run(".%sconan_test" % os.sep)
