#include <vector>
#include <string>

using namespace std;

// �����������
class Memo
{
private:
    static int count;  // ����¼��ż�����
    int id;            // ����¼���
    string content;    // ����¼����
    bool isTop;        // �Ƿ��ö�

public:
    // ���캯��
    Memo(string _content, bool _isTop = false)
    {
        id = ++count;
        content = _content;
        isTop = _isTop;
    }

    // ��ȡ����¼���
    int getId() const
    {
        return id;
    }
    void setId(int id)
    {
        this->id = id;
    }

    // ��ȡ����¼����
    const string& getContent() const
    {
        return content;
    }
    void setContent(const string& newContent)
    {
        content = newContent;
    }

    // �жϱ���¼�Ƿ��ö�
    bool getIsTop() const
    {
        return isTop;
    }

    // ���ñ���¼�ö�״̬
    void setIsTop(bool _isTop)
    {
        isTop = _isTop;
    }

    // �޸ı���¼����
    void modifyContent(string newContent)
    {
        content = newContent;
    }
};

//�����������
class MemoManager 
{
private:
    // ����vector�洢����
    vector<Memo> memos;

public:
    // �����ܺ���
    void addMemo();
    void showMemos();
    void arrangeMemos();
    void topMemo();
    void modifyMemo();
    void deleteMemo();
};
