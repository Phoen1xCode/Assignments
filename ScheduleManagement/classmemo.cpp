#include "memo.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int Memo::count = 0;

// 输入备忘录
void MemoManager::addMemo()
{
    string input;
    string line;
    cout << "请输入备忘录内容（输入空行结束）：" << endl;
    cin.ignore(); // 清除缓冲区
    // 输入备忘录内容
    while (true)
    {
        getline(cin, line);
        if (line.empty())
            break; // 结束输入
        input += line + "\n"; // 拼接多行内容
    }

    memos.push_back(Memo(input, false));
}

// 备忘录排序
void MemoManager::arrangeMemos()
{
    // 更新备忘录的编号
    for (size_t i = 0; i < memos.size(); ++i)
    {
        memos[i].setId(i + 1);
    }
    // 通过编号进行排序
    sort(memos.begin(), memos.end(), [](const Memo& a, const Memo& b) {
        return a.getId() < b.getId();
        });
}

// 输出备忘录
void MemoManager::showMemos()
{
    // 遍历并输出置顶备忘录
    for (const auto& memo : memos)
    {
        if (memo.getIsTop())
        {
            cout << "[置顶] ";
            cout << "[" << memo.getId() << "] " << memo.getContent() << endl;
        }
    }

    // 遍历并输出非置顶备忘录
    for (const auto& memo : memos)
    {
        if (!memo.getIsTop())
        {
            cout << "[" << memo.getId() << "] " << memo.getContent() << endl;
        }
    }
}

// 备忘录置顶
void MemoManager::topMemo()
{
    // 排除备忘录为空时的问题
    if (memos.empty())
    {
        cout << "备忘录为空" << endl;
        return;
    }

    // 选择置顶的备忘录
    int topid;
    cout << "输入要置顶的备忘录编号：" << endl;
    cin.ignore(); // 清除换行符
    cin >> topid;

    // 检查输入的编号是否有效
    while (cin.fail())
    {
        cout << "无效选项，请重新输入！" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> topid;
    }

    // 查找对应备忘录，改变其置顶状态
    auto it = find_if(memos.begin(), memos.end(),
        [topid](const Memo& memo) { return memo.getId() == topid; });

    // 检查是否存在对应的备忘录
    if (it == memos.end())
    {
        cout << "编号为" << topid << " 的备忘录不存在" << endl;
        return;
    }

    Memo memo = *it;
    memo.setIsTop(true);

    // 将置顶的备忘录移动到列表的开头
    memos.erase(it);
    memos.insert(memos.begin(), std::move(memo));

    // 更新备忘录的编号和置顶状态
    for (std::vector<Memo>::iterator it = memos.begin(); it != memos.end(); ++it)
    {
        it->setId(std::distance(memos.begin(), it) + 1);
        it->setIsTop(it == memos.begin()); // 第一个备忘录为置顶备忘录，其余为非置顶备忘录
    }
}


// 修改备忘录内容
void MemoManager::modifyMemo()
{
    // 排除备忘录为空时的问题
    if (memos.empty())
    {
        cout << "备忘录为空" << endl;
        return;
    }

    // 输入备忘录编号
    int modifyId;
    cout << "输入要修改的备忘录编号：" << endl;
    cin.ignore(); // 清除换行符
    cin >> modifyId;

    // 检查输入的编号是否有效
    while (cin.fail())
    {
        cout << "无效选项，请重新输入！" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> modifyId;
    }

    // 查找对应编号
    auto it = find_if(memos.begin(), memos.end(),
        [modifyId](const Memo& memo) { return memo.getId() == modifyId; });

    if (it == memos.end())
    {
        cout << "编号为" << modifyId << "的备忘录不存在" << endl;
        return;
    }

    string newContent;
    cout << "输入新的备忘录内容：" << endl;
    cin.ignore(); // 清除换行符
    getline(cin, newContent);

    it->setContent(newContent);
    cout << "备忘录内容修改成功" << endl;
}


// 删除备忘录
void MemoManager::deleteMemo()
{
    // 排除备忘录为空时的问题
    if (memos.empty())
    {
        cout << "备忘录为空" << endl;
        return;
    }

    // 输入对应的编号
    int deleteId;
    cout << "输入要删除的备忘录编号：" << endl;
    cin.ignore(); // 清除换行符
    cin >> deleteId;

    // 检查输入的编号是否有效
    while (cin.fail())
    {
        cout << "无效选项，请重新输入！" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> deleteId;
    }

    // 查找对应的编号
    auto it = find_if(memos.begin(), memos.end(),
        [deleteId](const Memo& memo) { return memo.getId() == deleteId; });

    if (it == memos.end())
    {
        cout << "编号为" << deleteId << "的备忘录不存在" << endl;
        return;
    }

    memos.erase(it);
    cout << "备忘录删除成功" << endl;

}
