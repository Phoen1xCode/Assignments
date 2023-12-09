//
// Created by Jake Jia on 2023/12/8.
//

#ifndef PASSWORDMANAGEMENT_JSONMANAGER_H
#define PASSWORDMANAGEMENT_JSONMANAGER_H
#include "Credential.h"
#include "../lib/json/json.hpp"


namespace PasswordManagement {

    // 保存JSON文件
    // 对不同类使用函数重载
    void saveJSONFile(const Identity& Identity);
    void saveJSONFile(const Credential& Credential);
    void saveJSONFile(const WebsiteCredential& WebsiteCredential);
    void saveJSONFile(const BankCardCredential& BankCardCredential);
    void saveJSONFile(const SoftwareCredential& SoftwareCredential);
    void saveJSONFile(const WifiCredential& WifiCredential);




} // PasswordManagement

#endif //PASSWORDMANAGEMENT_JSONMANAGER_H
