# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/coderish/src/repos/OHLCService/cmake/abseil/src/abseil"
  "/home/coderish/src/repos/OHLCService/cmake/abseil/src/abseil-build"
  "/home/coderish/src/repos/OHLCService/cmake/abseil"
  "/home/coderish/src/repos/OHLCService/cmake/abseil/tmp"
  "/home/coderish/src/repos/OHLCService/cmake/abseil/src/abseil-stamp"
  "/home/coderish/src/repos/OHLCService/cmake/abseil/src"
  "/home/coderish/src/repos/OHLCService/cmake/abseil/src/abseil-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/coderish/src/repos/OHLCService/cmake/abseil/src/abseil-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/coderish/src/repos/OHLCService/cmake/abseil/src/abseil-stamp${cfgdir}") # cfgdir has leading slash
endif()
