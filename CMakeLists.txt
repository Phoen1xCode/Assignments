cmake_minimum_required(VERSION 3.26)
project(Assignments)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(MoneyManagement/lib/fmt)

# 查找MySQL头文件和库文件的路径
find_path(MYSQL_INCLUDE_DIR NAMES mysql.h PATHS "C:/MySQL/mysql-8.2.0-winx64/include" NO_DEFAULT_PATH)
find_library(MYSQL_LIBRARY NAMES mysql libmysql PATHS "C:/MySQL/mysql-8.2.0-winx64/lib" NO_DEFAULT_PATH)
# 引入头文件
include_directories(${MYSQL_INCLUDE_DIR})

# 添加cryptopp-cmake子目录
add_subdirectory(PasswordManagement/lib/cryptopp-cmake)
# 设置Crypto++源码目录的位置
set(CRYPTOPP_SOURCES "${CMAKE_SOURCE_DIR}PasswordManagement/lib/cryptopp")





add_executable(Assignments main.cpp
########################################################################################################################
        MoneyManagement/include/account.h
        MoneyManagement/src/account.cpp

        MoneyManagement/include/analyse.h
        MoneyManagement/src/analyse.cpp

        MoneyManagement/include/data_in_out.h
        MoneyManagement/src/data_in_out.cpp

        MoneyManagement/include/date.h
        MoneyManagement/src/date.cpp

        MoneyManagement/include/ledger.h
        MoneyManagement/src/ledger.cpp

        MoneyManagement/include/plan.h
        MoneyManagement/src/plan.cpp

        MoneyManagement/include/search.h
        MoneyManagement/src/search.cpp

        MoneyManagement/include/summary.h
        MoneyManagement/src/summary.cpp

        MoneyManagement/include/type.h
        MoneyManagement/src/type.cpp

        MoneyManagement/include/submain.h
        MoneyManagement/src/submain.cpp
########################################################################################################################

        PasswordManagement/include/User.h
        PasswordManagement/src/User.cpp

        PasswordManagement/include/PasswordManager.h
        PasswordManagement/src/PasswordManager.cpp

        PasswordManagement/include/PasswordUtils.h
        PasswordManagement/src/PasswordUtils.cpp

        PasswordManagement/lib/bcrypt/include/bcrypt.h
        PasswordManagement/lib/bcrypt/src/bcrypt.cpp
        PasswordManagement/lib/bcrypt/src/blowfish.cpp
        PasswordManagement/lib/bcrypt/src/node_blf.h
        PasswordManagement/lib/bcrypt/src/openbsd.h

        PasswordManagement/lib/json/json.hpp

        PasswordManagement/include/ConfigManager.h
        PasswordManagement/src/ConfigManager.cpp

        PasswordManagement/include/Credential.h
        PasswordManagement/src/Credential.cpp

        PasswordManagement/include/CredentialManager.h
        PasswordManagement/src/CredentialManager.cpp

        PasswordManagement/include/KeyManager.h
        PasswordManagement/src/KeyManager.cpp

########################################################################################################################
        ScheduleManagement/include/Course.h
        ScheduleManagement/include/DailyAssistant.h
        ScheduleManagement/include/Homework.h
        ScheduleManagement/include/Memo.h
        ScheduleManagement/include/Schedule.h

        ScheduleManagement/lib/json.hpp

        ScheduleManagement/src/Course.cpp
        ScheduleManagement/src/DailyAssistant.cpp
        ScheduleManagement/src/Homework.cpp
        ScheduleManagement/src/Memo.cpp
        ScheduleManagement/src/Schedule.cpp



)

# 链接MySQL库
target_link_libraries(Assignments ${MYSQL_LIBRARY})

# 链接 fmt 库
target_link_libraries(Assignments fmt::fmt)

# 链接到Crypto++
target_link_libraries(Assignments cryptopp::cryptopp)
# 链接到User32.lib
target_link_libraries(Assignments User32)