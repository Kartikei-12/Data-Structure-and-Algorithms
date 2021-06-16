
# Data Structure and Algorithms in C++14

## Running Project

### Prerequisites

1. C++ Compiler with C++14 Support(I am using MinGW GNU 8.1.0)
2. CMake (Available [here](https://cmake.org/))
3. Sense of whimsy.

### Building Project

```
git clone https://github.com/Kartikei-12/Data-Structure-and-Algorithms.git
cd .\Data-Structure-and-Algorithms\
cd cpp14 # For C++ Files
mkdir build # Destination of all our build files
cmake . -B build # Add -G "GENERATOR" for yuor system is default foes not work
cmake --build build
```

Above commands should suffice.

I have configired for all executables to end up in /bin folder(Find them there).

Build command automatically runs all GoogleTest in tests folder.
