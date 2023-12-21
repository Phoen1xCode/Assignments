#include <iostream>
#include "PasswordManagement/models/PasswordManager.h"

int main() {
    PasswordManagement::PasswordManager passwordManager;
    if(!passwordManager.loginPasswordManagement())
        return 0;
    else // 运行程序
    passwordManager.managePasswords();


    return 0;
}






