# CMake generated Testfile for 
# Source directory: X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit
# Build directory: X:/CLionProjects/PasswordManagement/cmake-build-debug/lib/cryptopp-cmake/test/unit
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[cryptopp-disable-asm-configure]=] "C:/Program Files/JetBrains/CLion 2023.2/bin/cmake/win/x64/bin/cmake.exe" "-GNinja" "-D" "TEST_CMAKE_FILES_DIR=X:/CLionProjects/PasswordManagement/cmake" "-D" "TEST_EXAMPLE_SOURCES_DIR=X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/example-src" "-D" "USE_CCACHE=TRUE" "-D" "CMAKE_USER_MAKE_RULES_OVERRIDE=X:/CLionProjects/PasswordManagement/cmake/ResetInitialCompilerOptions.cmake" "-S" "X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/disable-asm" "-B" "X:/CLionProjects/PasswordManagement/cmake-build-debug/test-dirs/disable-asm" "-D" "CPM_cryptopp-cmake_SOURCE=X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake" "-D" "CMAKE_VERBOSE_MAKEFILE=ON" "-D" "CMAKE_BUILD_TYPE=Debug")
set_tests_properties([=[cryptopp-disable-asm-configure]=] PROPERTIES  FIXTURES_SETUP "disable-asm-config" LABELS "cryptopp;cryptopp-unit-tests;cryptopp-disable-asm" _BACKTRACE_TRIPLES "X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/CMakeLists.txt;14;add_test;X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/CMakeLists.txt;0;")
add_test([=[cryptopp-disable-asm-build]=] "C:/Program Files/JetBrains/CLion 2023.2/bin/cmake/win/x64/bin/cmake.exe" "--build" "X:/CLionProjects/PasswordManagement/cmake-build-debug/test-dirs/disable-asm" "--config" "Debug")
set_tests_properties([=[cryptopp-disable-asm-build]=] PROPERTIES  FIXTURES_REQUIRED "disable-asm-config" LABELS "cryptopp;cryptopp-unit-tests;cryptopp-disable-asm" _BACKTRACE_TRIPLES "X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/CMakeLists.txt;41;add_test;X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/CMakeLists.txt;0;")
add_test([=[cryptopp-include-prefix-configure]=] "C:/Program Files/JetBrains/CLion 2023.2/bin/cmake/win/x64/bin/cmake.exe" "-GNinja" "-D" "TEST_CMAKE_FILES_DIR=X:/CLionProjects/PasswordManagement/cmake" "-D" "TEST_EXAMPLE_SOURCES_DIR=X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/example-src" "-D" "USE_CCACHE=TRUE" "-D" "CMAKE_USER_MAKE_RULES_OVERRIDE=X:/CLionProjects/PasswordManagement/cmake/ResetInitialCompilerOptions.cmake" "-S" "X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/include-prefix" "-B" "X:/CLionProjects/PasswordManagement/cmake-build-debug/test-dirs/include-prefix" "-D" "CPM_cryptopp-cmake_SOURCE=X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake" "-D" "CMAKE_VERBOSE_MAKEFILE=ON" "-D" "CMAKE_BUILD_TYPE=Debug")
set_tests_properties([=[cryptopp-include-prefix-configure]=] PROPERTIES  FIXTURES_SETUP "include-prefix-config" LABELS "cryptopp;cryptopp-unit-tests;cryptopp-include-prefix" _BACKTRACE_TRIPLES "X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/CMakeLists.txt;14;add_test;X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/CMakeLists.txt;0;")
add_test([=[cryptopp-include-prefix-build]=] "C:/Program Files/JetBrains/CLion 2023.2/bin/cmake/win/x64/bin/cmake.exe" "--build" "X:/CLionProjects/PasswordManagement/cmake-build-debug/test-dirs/include-prefix" "--config" "Debug")
set_tests_properties([=[cryptopp-include-prefix-build]=] PROPERTIES  FIXTURES_REQUIRED "include-prefix-config" LABELS "cryptopp;cryptopp-unit-tests;cryptopp-include-prefix" _BACKTRACE_TRIPLES "X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/CMakeLists.txt;41;add_test;X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/CMakeLists.txt;0;")
add_test([=[cryptopp-no-install-configure]=] "C:/Program Files/JetBrains/CLion 2023.2/bin/cmake/win/x64/bin/cmake.exe" "-GNinja" "-D" "TEST_CMAKE_FILES_DIR=X:/CLionProjects/PasswordManagement/cmake" "-D" "TEST_EXAMPLE_SOURCES_DIR=X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/example-src" "-D" "USE_CCACHE=TRUE" "-D" "CMAKE_USER_MAKE_RULES_OVERRIDE=X:/CLionProjects/PasswordManagement/cmake/ResetInitialCompilerOptions.cmake" "-S" "X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/no-install" "-B" "X:/CLionProjects/PasswordManagement/cmake-build-debug/test-dirs/no-install" "-D" "CPM_cryptopp-cmake_SOURCE=X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake" "-D" "CMAKE_VERBOSE_MAKEFILE=ON" "-D" "CMAKE_BUILD_TYPE=Debug")
set_tests_properties([=[cryptopp-no-install-configure]=] PROPERTIES  FIXTURES_SETUP "no-install-config" LABELS "cryptopp;cryptopp-unit-tests;cryptopp-no-install" _BACKTRACE_TRIPLES "X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/CMakeLists.txt;14;add_test;X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/CMakeLists.txt;0;")
add_test([=[cryptopp-no-install-build]=] "C:/Program Files/JetBrains/CLion 2023.2/bin/cmake/win/x64/bin/cmake.exe" "--build" "X:/CLionProjects/PasswordManagement/cmake-build-debug/test-dirs/no-install" "--config" "Debug")
set_tests_properties([=[cryptopp-no-install-build]=] PROPERTIES  FIXTURES_REQUIRED "no-install-config" LABELS "cryptopp;cryptopp-unit-tests;cryptopp-no-install" _BACKTRACE_TRIPLES "X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/CMakeLists.txt;41;add_test;X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/CMakeLists.txt;0;")
add_test([=[cryptopp-standard-cpm-configure]=] "C:/Program Files/JetBrains/CLion 2023.2/bin/cmake/win/x64/bin/cmake.exe" "-GNinja" "-D" "TEST_CMAKE_FILES_DIR=X:/CLionProjects/PasswordManagement/cmake" "-D" "TEST_EXAMPLE_SOURCES_DIR=X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/example-src" "-D" "USE_CCACHE=TRUE" "-D" "CMAKE_USER_MAKE_RULES_OVERRIDE=X:/CLionProjects/PasswordManagement/cmake/ResetInitialCompilerOptions.cmake" "-S" "X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/standard-cpm" "-B" "X:/CLionProjects/PasswordManagement/cmake-build-debug/test-dirs/standard-cpm" "-D" "CPM_cryptopp-cmake_SOURCE=X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake" "-D" "CMAKE_VERBOSE_MAKEFILE=ON" "-D" "CMAKE_BUILD_TYPE=Debug")
set_tests_properties([=[cryptopp-standard-cpm-configure]=] PROPERTIES  FIXTURES_SETUP "standard-cpm-config" LABELS "cryptopp;cryptopp-unit-tests;cryptopp-standard-cpm" _BACKTRACE_TRIPLES "X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/CMakeLists.txt;14;add_test;X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/CMakeLists.txt;0;")
add_test([=[cryptopp-standard-cpm-build]=] "C:/Program Files/JetBrains/CLion 2023.2/bin/cmake/win/x64/bin/cmake.exe" "--build" "X:/CLionProjects/PasswordManagement/cmake-build-debug/test-dirs/standard-cpm" "--config" "Debug")
set_tests_properties([=[cryptopp-standard-cpm-build]=] PROPERTIES  FIXTURES_REQUIRED "standard-cpm-config" LABELS "cryptopp;cryptopp-unit-tests;cryptopp-standard-cpm" _BACKTRACE_TRIPLES "X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/CMakeLists.txt;41;add_test;X:/CLionProjects/PasswordManagement/lib/cryptopp-cmake/test/unit/CMakeLists.txt;0;")
