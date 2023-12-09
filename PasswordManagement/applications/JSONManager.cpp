//
// Created by Jake Jia on 2023/12/8.
//

#include <fstream>
#include "../models/JSONManager.h"

namespace PasswordManagement {
    // 为了方便，使用json命名空间
    using json = nlohmann::json;
    void saveJSONFile(const Credential& Credential) {
        json j;
        j["项目名称"] = Credential.getItemName();
        j["用户名"] = Credential.getUsername();
        j["密码"] = Credential.getPassword();

        std::string filePath = "file/" + Credential.getItemName() + ".json";
        std::ofstream outFile(filePath);
        if(outFile.is_open()) {
            outFile << j.dump(4);
            outFile.close();
        } else {
            std::cerr << "ERROR." << std::endl;
        }

    }





} // PasswordManagement