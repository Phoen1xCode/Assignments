cmake_minimum_required(VERSION 3.26)
project(PasswordManagement)

set(CMAKE_CXX_STANDARD 17)

# 添加cryptopp-cmake子目录
add_subdirectory(lib/cryptopp-cmake)

# 设置Crypto++源码目录的位置
set(CRYPTOPP_SOURCES "${CMAKE_SOURCE_DIR}/lib/cryptopp")

add_executable(PasswordManagement PasswordManagement.cpp

        models/User.h
        applications/User.cpp

        models/PasswordManager.h
        applications/PasswordManager.cpp

        models/PasswordUtils.h
        applications/PasswordUtils.cpp

        lib/bcrypt/include/bcrypt.h
        lib/bcrypt/src/bcrypt.cpp
        lib/bcrypt/src/blowfish.cpp
        lib/bcrypt/src/node_blf.h
        lib/bcrypt/src/openbsd.h

        lib/json/json.hpp

        models/ConfigManager.h
        applications/ConfigManager.cpp

        models/Credential.h
        applications/Credential.cpp

        models/CredentialManager.h
        applications/CredentialManager.cpp

        models/KeyManager.h
        applications/KeyManager.cpp

)

# 链接到Crypto++
target_link_libraries(PasswordManagement cryptopp::cryptopp)
# 链接到User32.lib
target_link_libraries(PasswordManagement User32)