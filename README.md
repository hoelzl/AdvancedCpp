# Material for the Advanced C++ Course

This folder contains the materials for the advanced C++ course.

## Installation

Clone the repository and its submodules with git:

```
git clone --recursive https://github.com/hoelzl/AdvancedCpp.git
```

You need a relatively current development environment to run the examples.
The projects are configured with CMake; the minimum requirement is version 3.21;
most sub-projects require C++20, some use some proposed features from the C++23
standard.

### Preparing your system

On Windows, install Visual Studio 2022 with the "Desktop development with C++"
workload and you're good to go.

On Linux, install the packages for CMake and clang/gcc. For example on Debian
stable (bullseye):

- Enable [bullseye-backports](https://packages.debian.org/bullseye-backports/)
- Install gcc-10 and cmake, and potentially the gtk+ development headers

```
sudo apt install gcc-10 g++-10 cmake -t bullseye-backports
```


### Building using CMake

If you want to build the projects from the command line, perform the following
steps from inside the cloned directory:

```
mkdir build
cd build
cmake ..
cmake --build .
```
Run one of the example programs to check whether the build succeeded. On Windows:
```
.\examples\tic_tac_toe\Debug\tic_tac_toe.exe
```
and on Linux:
```
./examples/tic_tac_toe/tic_tac_toe
```

### Building using Visual Studio 2022

Click `File->Open Folder...` from the menu and choose the root folder of the project.
Visual Studio should automatically configure CMake and offer all the subprojects
as startup projects.
