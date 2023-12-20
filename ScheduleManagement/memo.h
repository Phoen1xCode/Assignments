#include <vector>
#include <string>

using namespace std;

// 管理各个变量
class Memo
{
private:
    static int count;  // 备忘录编号计数器
    int id;            // 备忘录编号
    string content;    // 备忘录内容
    bool isTop;        // 是否置顶

public:
    // 构造函数
    Memo(string _content, bool _isTop = false)
    {
        id = ++count;
        content = _content;
        isTop = _isTop;
    }

    // 获取备忘录编号
    int getId() const
    {
        return id;
    }
    void setId(int id)
    {
        this->id = id;
    }

    // 获取备忘录内容
    const string& getContent() const
    {
        return content;
    }
    void setContent(const string& newContent)
    {
        content = newContent;
    }

    // 判断备忘录是否置顶
    bool getIsTop() const
    {
        return isTop;
    }

    // 设置备忘录置顶状态
    void setIsTop(bool _isTop)
    {
        isTop = _isTop;
    }

    // 修改备忘录内容
    void modifyContent(string newContent)
    {
        content = newContent;
    }
};

//管理各个功能
class MemoManager 
{
private:
    // 定义vector存储内容
    vector<Memo> memos;

public:
    // 各功能函数
    void addMemo();
    void showMemos();
    void arrangeMemos();
    void topMemo();
    void modifyMemo();
    void deleteMemo();
};
