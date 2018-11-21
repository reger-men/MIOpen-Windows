# MIOpen

AMD's library for high peformance machine learning primitives. MIOpen supports two programming models - 
1. OpenCL 

## Windows Prerequisites
* MinGW development environment 
* OpenCL headers and OCL SDK
* [Half](http://half.sourceforge.net/) at least version 1.12.0
* [OpenSSL](https://www.openssl.org/) at least version 1.1.0i
* [Boost](http://www.boost.org/) at least version 1.5x.x
* You will need also the followng DLLs:
  * libstdc++-6, ssl, crypto (use 
  
## Installing the dependencies

The dependencies can be installed with the `install_deps.cmake`, script: `cmake -P install_deps.cmake`


This will install by default to `/usr/local` but it can be installed in another location with `--prefix` argument:
```
cmake -P install_deps.cmake --prefix /some/local/dir
```

Instructions to manually install all the dependencies on Ubuntu v16 are present in this [section](#installing-the-dependencies-manually).

## Building MIOpen from source

## Configuring with cmake

First create a build directory:

```
mkdir build; cd build;
```

Next configure cmake. The preferred backend for MIOpen can be set using the `-DMIOPEN_BACKEND` cmake variable. 

#### For OpenCL, run:

```
cmake -DMIOPEN_BACKEND=OpenCL ..
```

The above assumes that OpenCL is installed in one of the standard locations. If not, then manually set these two cmake variables: 

```
cmake -DMIOPEN_BACKEND=OpenCL -DOPENCL_LIBRARIES=<opencl-library-path> -DOPENCL_INCLUDE_DIRS=<opencl-headers-path> ..
```

## Building the library

The library can be built, from the `build` directory using the 'Release' configuration:

` cmake --build . --config Release ` **OR** ` make `

And can be installed by using the 'install' target:

` cmake --build . --config Release --target install ` **OR** ` make install `

This will install the library to the `CMAKE_INSTALL_PREFIX` path that was set. 
