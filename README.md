# Note: This is not an official release!

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
  * libstdc++-6, ssl, crypto (use MinGW Installation Manager)
  
## Installing the dependencies

* [MinGW with Boost](requirements/mingw-16.0.exe)
* [OCL SDK](requirements/OCL_SDK_Light_AMD.exe)
* [OpenSSL](requirements/win32openssl-1_1_0f.exe)
* [MinGW Installation Manager](requirements/mingw-get-setup.exe)

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
