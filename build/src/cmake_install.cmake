# Install script for directory: C:/Users/Adil/Desktop/MLOpen-1-1.5.x/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/opt/rocm/x86_64-w64-mingw32")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/miopen/miopen/db" TYPE FILE FILES
    "C:/Users/Adil/Desktop/MLOpen-1-1.5.x/src/kernels/gfx803_36.cd.pdb.txt"
    "C:/Users/Adil/Desktop/MLOpen-1-1.5.x/src/kernels/gfx803_64.cd.pdb.txt"
    "C:/Users/Adil/Desktop/MLOpen-1-1.5.x/src/kernels/gfx900_64.cd.pdb.txt"
    "C:/Users/Adil/Desktop/MLOpen-1-1.5.x/src/kernels/gfx900_56.cd.pdb.txt"
    "C:/Users/Adil/Desktop/MLOpen-1-1.5.x/src/kernels/gfx906_64.cd.pdb.txt"
    "C:/Users/Adil/Desktop/MLOpen-1-1.5.x/src/kernels/gfx906_56.cd.pdb.txt"
    )
endif()

