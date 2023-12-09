cmake_minimum_required(VERSION 3.26)
project(PasswordManagement)

set(CMAKE_CXX_STANDARD 17)


# 添加cryptopp-cmake子目录
add_subdirectory(lib/cryptopp-cmake)

# 设置Crypto++源码目录的位置
#set(CRYPTOPP_SOURCES lib/cryptopp)
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

        lib/json/json.hpp

        models/ConfigManager.h
        applications/ConfigManager.cpp

        models/JSONManager.h
        applications/JSONManager.cpp

        models/Credential.h
        applications/Credential.cpp
)

target_link_libraries(PasswordManagement cryptopp::cryptopp)