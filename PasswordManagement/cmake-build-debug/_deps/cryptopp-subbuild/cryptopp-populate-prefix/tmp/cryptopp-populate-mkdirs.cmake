# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "X:/CLionProjects/PasswordManagement/cmake-build-debug/lib/cryptopp-cmake/cryptopp"
  "X:/CLionProjects/PasswordManagement/cmake-build-debug/_deps/cryptopp-build"
  "X:/CLionProjects/PasswordManagement/cmake-build-debug/_deps/cryptopp-subbuild/cryptopp-populate-prefix"
  "X:/CLionProjects/PasswordManagement/cmake-build-debug/_deps/cryptopp-subbuild/cryptopp-populate-prefix/tmp"
  "X:/CLionProjects/PasswordManagement/cmake-build-debug/_deps/cryptopp-subbuild/cryptopp-populate-prefix/src/cryptopp-populate-stamp"
  "X:/CLionProjects/PasswordManagement/cmake-build-debug/_deps/cryptopp-subbuild/cryptopp-populate-prefix/src"
  "X:/CLionProjects/PasswordManagement/cmake-build-debug/_deps/cryptopp-subbuild/cryptopp-populate-prefix/src/cryptopp-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "X:/CLionProjects/PasswordManagement/cmake-build-debug/_deps/cryptopp-subbuild/cryptopp-populate-prefix/src/cryptopp-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "X:/CLionProjects/PasswordManagement/cmake-build-debug/_deps/cryptopp-subbuild/cryptopp-populate-prefix/src/cryptopp-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
