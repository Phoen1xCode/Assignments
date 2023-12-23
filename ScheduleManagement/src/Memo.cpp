#include "../include/Memo.h"
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>


namespace DailylifeAssistant {
    using json = nlohmann::json;
    // 备忘录编号器
    int Memo::count = 0;

    Memo::Memo(std::string _content, bool _isTop) {
        number = ++count;
        content = std::move(_content);
        isTop = _isTop;
    }

    int Memo::getNumber() const {
        return this->number;
    }

    std::string Memo::getContent() const {
        return this->content;
    }

    bool Memo::getIsTop() const {
        return this->isTop;
    }

    void Memo::setNumber(const int &newNumber) {
        this->number = newNumber;
    }

    void Memo::setContent(const std::string &newContent) {
        this->content = newContent;
    }

    void Memo::setIsTop(bool _isTop) {
        this->isTop = _isTop;
    }

    std::string MemoManager::getMemoContent() {
        std::string input;
        std::string line;
        std::cout << "请输入备忘录内容（输入空行结束）：" << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清除缓冲区

        while (std::getline(std::cin, line)) {
            if (line.empty()) {
                break; // 结束输入
            }
            input += line + "\n"; // 拼接多行内容
        }

        return input;
    }

    // 输入备忘录
    void MemoManager::addMemo() {
        try {
            // 获取备忘录内容
            std::string content = getMemoContent();

            // 询问用户是否置顶备忘录
            char isTopChar;
            bool isTop = false;
            std::cout << "是否置顶此备忘录？(y/n): ";
            std::cin >> isTopChar;
            if (isTopChar == 'y' || isTopChar == 'Y') {
                isTop = true;
            }

            // 清除剩余输入
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // 添加备忘录到列表
            memos.push_back(Memo(content, isTop));

        } catch (const std::exception& e) {
            std::cerr << "发生错误: " << e.what() << std::endl;
        }
    }

    // 备忘录排序
    void MemoManager::arrangeMemos() {
        // 更新备忘录的编号
        for (size_t i = 0; i < memos.size(); ++i) {
            memos[i].setNumber(i + 1);
        }

        // 通过编号进行排序
        std::sort(memos.begin(), memos.end(), [](const Memo &a, const Memo &b) {
            return a.getNumber() < b.getNumber();
        });
    }

    // 输出备忘录
    void MemoManager::showMemos() {
        // 遍历并输出置顶备忘录
        for (const auto &memo: memos) {
            if (memo.getIsTop()) {
                std::cout << "[置顶] ";
                std::cout << "[" << memo.getNumber() << "] " << memo.getContent() << std::endl;
            }
        }

        // 遍历并输出非置顶备忘录
        for (const auto &memo: memos) {
            if (!memo.getIsTop()) {
                std::cout << "[" << memo.getNumber() << "] " << memo.getContent() << std::endl;
            }
        }
    }

    // 备忘录置顶
    void MemoManager::topMemo() {
        // 排除备忘录为空时的问题
        if (memos.empty()) {
            std::cout << "备忘录为空" << std::endl;
            return;
        }

        // 选择置顶的备忘录
        int topNumber;
        std::cout << "输入要置顶的备忘录编号：" << std::endl;
        std::cin.ignore(); // 清除换行符
        std::cin >> topNumber;

        // 检查输入的编号是否有效
        while (std::cin.fail()) {
            std::cout << "无效选项，请重新输入！" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> topNumber;
        }

        // 查找对应备忘录，改变其置顶状态
        auto it = std::find_if(memos.begin(), memos.end(),
                               [topNumber](const Memo &memo) { return memo.getNumber() == topNumber; });

        // 检查是否存在对应的备忘录
        if (it == memos.end()) {
            std::cout << "编号为" << topNumber << " 的备忘录不存在" << std::endl;
            return;
        }

        Memo memo = *it;
        memo.setIsTop(true);

        // 将置顶的备忘录移动到列表的开头
        memos.erase(it);
        memos.insert(memos.begin(), std::move(memo));

        // 更新备忘录的编号和置顶状态
        for (std::vector<Memo>::iterator it = memos.begin(); it != memos.end(); ++it) {
            it->setNumber(std::distance(memos.begin(), it) + 1);
            it->setIsTop(it == memos.begin()); // 第一个备忘录为置顶备忘录，其余为非置顶备忘录
        }
    }

    // 修改备忘录内容
    void MemoManager::modifyMemo() {
        // 排除备忘录为空时的问题
        if (memos.empty()) {
            std::cout << "备忘录为空" << std::endl;
            return;
        }

        // 输入备忘录编号
        int modifyId;
        std::cout << "输入要修改的备忘录编号：" << std::endl;
        std::cin.ignore(); // 清除换行符
        std::cin >> modifyId;

        // 检查输入的编号是否有效
        while (std::cin.fail()) {
            std::cout << "无效选项，请重新输入！" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> modifyId;
        }

        // 查找对应编号
        auto it = std::find_if(memos.begin(), memos.end(),
                               [modifyId](const Memo &memo) { return memo.getNumber() == modifyId; });

        if (it == memos.end()) {
            std::cout << "编号为" << modifyId << "的备忘录不存在" << std::endl;
            return;
        }

        std::string newContent;
        std::cout << "输入新的备忘录内容：" << std::endl;
        std::cin.ignore(); // 清除换行符
        std::getline(std::cin, newContent);

        it->setContent(newContent);
        std::cout << "备忘录内容修改成功" << std::endl;
    }

    // 删除备忘录
    void MemoManager::deleteMemo() {
        // 排除备忘录为空时的问题
        if (memos.empty()) {
            std::cout << "备忘录为空" << std::endl;
            return;
        }

        // 输入对应的编号
        int deleteId;
        std::cout << "输入要删除的备忘录编号：" << std::endl;
        std::cin.ignore(); // 清除换行符
        std::cin >> deleteId;

        // 检查输入的编号是否有效
        while (std::cin.fail()) {
            std::cout << "无效选项，请重新输入！" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> deleteId;
        }

        // 查找对应的编号
        auto it = std::find_if(memos.begin(), memos.end(),
                               [deleteId](const Memo &memo) { return memo.getNumber() == deleteId; });

        // 不存在时反馈
        if (it == memos.end()) {
            std::cout << "编号为" << deleteId << "的备忘录不存在" << std::endl;
            return;
        }

        // 进行删除操作
        memos.erase(it);
        std::cout << "备忘录删除成功" << std::endl;
    }

    void MemoManager::saveMemosToFile(const std::string &filename) {
        json j;
        for (const auto& memo : memos) {
            json memo_json;
            memo_json["number"] = memo.getNumber();
            memo_json["content"] = memo.getContent();
            memo_json["isTop"] = memo.getIsTop();
            j.push_back(memo_json);
        }
        std::ofstream file(filename);
        if (file.is_open()) {
            file << std::setw(4) << j << std::endl;
            file.close();
        } else {
            std::cerr << "无法打开文件: " << filename << std::endl;
        }
    }

    void MemoManager::loadMemosFromFile(const std::string &filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            json j;
            file >> j;
            memos.clear();
            for (const auto& memo_json : j) {
                Memo memo(memo_json["content"], memo_json["isTop"]);
                memo.setNumber(memo_json["number"]);
                memos.push_back(memo);
            }
            file.close();
        } else {
            std::cerr << "无法打开文件: " << filename << std::endl;
        }
    }
}


