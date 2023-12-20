
#pragma once
#include<vector>
#include<string>
#include<set>
class Type {
    
    std::set<std::string> userdefined_type;
    std::string type;
public:
    friend std::vector<std::vector<double>> sum_all_yearly();
    Type();
    std::vector<std::string> predefined_type;
    void add_userdefined_type(const std::string& s);
    void show_alltype();
    ~Type();
    std::string select_type();
    bool operator == (const Type& t)const;
};
