# Project template

[![Github Actions](https://github.com/francescoseccamonte/kalman/actions/workflows/build.yml/badge.svg)](https://github.com/francescoseccamonte/kalman/actions/workflows/build.yml) [![codecov](https://codecov.io/gh/francescoseccamonte/kalman/branch/main/graph/badge.svg?token=ayRENb8Avd)](https://codecov.io/gh/francescoseccamonte/kalman) [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

Kalman filter written in C++ using Eigen.

Disclaimer: I wrote this project to simply brush up my C++ skills, and review the Kalman filter.
This means the code is not particularly optimized, and some design choices are suboptimal.

## Prerequisites

It is assumed that CMake and a python3 installation are available.

### Conan Package Manager

The [Conan](https://conan.io) package manager is used to manage project's external
dependencies, and is assumed to be installed.
For more details see the Conan [Getting Started](https://docs.conan.io/en/latest/getting_started.html) guide.

## Compiling

After cloning the repo, go somewhere preferably _outside_ of the source tree and create a folder for the build:

```
mkdir build && cd build
```

The first step is installing dependencies via conan:

```
conan install -o kalman:build_tests=True --build=missing <sources>
```
The `-o` specifies option to be passed to conan, and `--build-missing` is self-explanatory.

The second step is the configure step, and is performed via CMake.

```
cmake -S .. -B . -DCMAKE_BUILD_TYPE=<build-type>
```
The `-S` and `-B` specify source and build paths, respectively.
We can additionally specify a `<build-type>` (default: `Release`).

If you prefer to use [Ninja](https://ninja-build.org/) as your build system,
remember to pass `-G Ninja` to `cmake`.  The project may now be compiled by running
```
cd build
cmake --build . [-- -jN]
```


## Misc

### Running tests

After compiling, running tests is as simple as running `ctest [-jN]` in the build folder.

### Code Coverage

Code coverage is automatically computed in Github Actions via `gcovr`.

### Conan Package Creation

The project can be exported as a Conan package, and the repository contains
a recipe to do so.

To create the package, just run:

```
conan create <project_folder> <your_user>/<your_channel>
```

Typically, for your own development and testing you would use your user name
and `testing` or `dev` as a channel.

The version number is specified inside `conanfile.py`. Anytime the package is
generated using a newer version of the project sources, the version should
be increased.

### Consuming the project as a Conan pacakge

You can now consume the project as a conan package. You can use the kalman library by including
it in your `conanfile.txt/py` file and linking against the target `CONAN_PKG::kalman`.

### Documentation
Doxygen is used for documentation. To use it, you first need to install it via
```
sudo apt install doxygen graphviz
```

Then, pass the `ENABLE_DOXYGEN=ON` option to the cmake configure step. You can then build the target `doc` to generate documentation.
Documentation will be in the `doc` folder inside your build directory. Open `doc/index.html` in your browser to view the documentation.
