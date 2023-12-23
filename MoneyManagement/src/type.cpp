#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "../include/type.h"

namespace finance {
    // 构造函数
    Type::Type() : predefined_type({ "医疗", "食品", "住房", "交通", "娱乐", "工资", "投资", "社交", "储蓄", "其他" }) {}

    // 析构函数
    Type::~Type() {}

    // 用户添加自定义消费类别的函数（一次只能添加一个）
    void Type::add_userdefined_type(const std::string& s) {
        userdefined_type.insert(s);
    }

    // 展现已有元素（包括初始设定和用户自定义）
    void Type::show_alltype() {
        int n = sizeof(predefined_type) / sizeof(std::string);
        int a = 1;
        for (const auto& type : predefined_type) {
            std::cout << a << "." << type << " ";
            a++;  // 利用两个范围for语句来实现对已定义类别的遍历
        }
        int b = 11;
        for (const auto& type : userdefined_type) {
            std::cout << b << "." << type << " ";
            b++;
        }
        std::cout << std::endl;
    }

    // 获取用户选择的消费类型，主要用于为账目提供支持
    std::string Type::select_type() {
        std::cout << "请选择您的消费类型：" << std::endl;
        int n;
        int startindex = userdefined_type.size();
        std::cin >> n;
        std::cin.get();
        if (n <= 10) {
            return predefined_type[n - 1];
        }
        else {
            auto it = userdefined_type.begin();
            std::advance(it, n - startindex - 1);
            return *it;
        }
    }

    bool Type::operator==(const Type& t) const {
        return type == t.type;
    }
}