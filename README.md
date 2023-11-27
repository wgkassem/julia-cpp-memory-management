# Introduction

A project to help elucidate memory management in C++/Julia.

- `mymemory` is a shared header-only library for implementing the proxy design pattern implemented in [std::shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr/shared_ptr).
- `MyJuliaLib` is a Julia library used for testing. It exports one function and two structs for doing trapezoidal intergration.
- `mixedlib` is a shared library that tries to calculate trapezoidal integration using `MyJuliaLib`.

# How to build

Currently, there is no script for building the whole thing.

1. Install `mymemory`
```
cmake -Bbuild_mymemory -Smymemory -DBUILD_TESTING=True -DCMAKE_INSTALL_PREFIX=~/local
cmake --build build_mymemory --target install
```

2. "Install" `MyJuliaLib`
```
julia 
using Pkg
Pkg.develop('./MyJuliaLib')
exit
```

3. Build `mixedlib`
```
CMAKE_PREFIX_PATH=~/local cmake -Bbuild -Smixedlib -DBUILD_TESTING=True
cmake --build build 
cd build 
```

4. Run tests
```
cd build 
ctest -R common
ctest -R TrapzStressTest
```

