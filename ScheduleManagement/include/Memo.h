#ifndef MEMO_H
#define MEMO_H

#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include "../lib/json.hpp"

namespace DailylifeAssistant {
    // Memo Class
    class Memo {
    public:
        // 构造函数
         Memo(std::string _content, bool _isTop = false);

        int getNumber() const; // 获取备忘录编号

        std::string getContent() const; // 获取备忘录内容

        bool getIsTop() const; // 判断备忘录是否置顶


        void setNumber(const int& newNumber);

        void setContent(const std::string &newContent);

        void setIsTop(bool _isTop); // 设置备忘录置顶状态

    private:
        static int count; // 备忘录编号计数器

        int number; // 备忘录编号
        std::string content; // 备忘录内容
        bool isTop; // 是否置顶
    };


    // Memo Manage
    class MemoManager {
    public:
        static std::string getMemoContent(); // Helper function to get user input for memo content

        void addMemo();

        void showMemos();

        void arrangeMemos();

        void topMemo();

        void modifyMemo();

        void deleteMemo();

        void saveMemosToFile(const std::string& filename);

        void loadMemosFromFile(const std::string& filename);

    private:
        std::vector<Memo> memos; // 定义vector存储内容
    };
}

#endif
