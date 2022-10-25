# Project template

[![Github Actions](https://github.com/francescoseccamonte/cpp-travis-integration/actions/workflows/build.yml/badge.svg)](https://github.com/francescoseccamonte/cpp-travis-integration/actions/workflows/build.yml) [![Travis CI](https://travis-ci.org/francescoseccamonte/cpp-travis-integration.svg?branch=master)](https://travis-ci.org/francescoseccamonte/cpp-travis-integration) [![codecov](https://codecov.io/gh/francescoseccamonte/cpp-travis-integration/branch/main/graph/badge.svg?token=ayRENb8Avd)](https://codecov.io/gh/francescoseccamonte/cpp-travis-integration) [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

C++ project template, using CMake and [Conan](https://conan.io).

## Prerequisites

It is assumed that CMake and a python3 installation are available.

### Conan Setup

The [Conan](https://conan.io) package manager is used to manage project's external
dependencies.
This section describes the process of setting it up.
Installation is as simple as running

```
pip3 install --user conan
```

#### Creating Profiles
We need to setup a Conan profile — a list of properties that characterize the
environment.
The following commands will create a new profile called `default`, and populate it with the info collected in your system (compiler version, architecture, etc.).
```
# create new profile called 'default'
conan profile new default --detect
conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan
conan config set general.revisions_enabled=1
```

Note that you can have multiple profiles and also modify existing ones when needed.
For more details see the Conan [Getting Started](https://docs.conan.io/en/latest/getting_started.html) guide.

## Compiling

After cloning the repo, go somewhere preferably _outside_ of the source tree and create a folder for the build:

```
mkdir build && cd build
```

The first step is installing dependencies via conan:

```
conan install -o cpp-travis-integration:build_tests=True --build=missing <sources>
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
As always, you may use your build system command directly (e.g., `make` or `ninja`) instead
of calling the more cumbersome `cmake --build .`.

## Misc

### Running tests

After compiling, running tests is as simple as running `ctest [-jN]` in the build folder.

### Code Coverage

Code coverage is automatically computed in Github Actions via `gcovr`.

### Conan Package Creation

The project can be exported as a Conan package, and the repository contains
a recipe to do so.  The `conanfile.py` file contains not only the information
about the required build dependencies, but also instructions to create a Conan
package from the project, so its libraries can be consumed by other projects.

To create the package, just run:

```
conan create <project_folder> <your_user>/<your_channel>
```

Typically, for your own development and testing you would use your user name
and `testing` or `dev` as a channel.

The version number is specified inside `conanfile.py`. Anytime the package is
generated using a newer version of the project sources, the version should
be increased. It is left to the discretion of the code owners to decide
when the changes made qualify for a major or minor version number increase.

### Consuming the project as a Conan pacakge

You can now consume the project as a conan package. If it simply contains libraries, you can include
it in your `conanfile.txt/py` and use it by linking against the target `CONAN_PKG::project_template`.

If it contains executables also and you intend to run them, you can obtain and install the package via
```
conan install project_template/<version>@<user>/<channel> -g virtualenv
```

This command will create two scripts, `activate.sh` and `deactivate.sh`. You will then run

```
source ./activate.sh
```

to activate the virtual environment which will set all the relevant paths to find your project files and correctly link against the libraries needed.

Once finished, you can deactivate the virtualenv by running `source ./deactivate.sh`.

### Documentation
Doxygen is used for documentation. To use it, you first need to install it via
```
sudo apt install doxygen graphviz
```

Then, pass the `ENABLE_DOXYGEN=ON` option to the cmake configure step. You can then build the target `doc` to generate documentation.
Documentation will be in the `doc` folder inside your build directory. Open `doc/index.html` in your browser to view the documentation.

### Add files to be ignored

Files to be ignored for everybody can be added to the `.gitignore` file. Files related to the IDE you use can be specified in the `.git/info/exclude` file (locally).
