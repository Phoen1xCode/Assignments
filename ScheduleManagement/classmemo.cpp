#include "memo.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int Memo::count = 0;

// ���뱸��¼
void MemoManager::addMemo()
{
    string input;
    string line;
    cout << "�����뱸��¼���ݣ�������н�������" << endl;
    cin.ignore(); // ���������
    // ���뱸��¼����
    while (true)
    {
        getline(cin, line);
        if (line.empty())
            break; // ��������
        input += line + "\n"; // ƴ�Ӷ�������
    }

    memos.push_back(Memo(input, false));
}

// ����¼����
void MemoManager::arrangeMemos()
{
    // ���±���¼�ı��
    for (size_t i = 0; i < memos.size(); ++i)
    {
        memos[i].setId(i + 1);
    }
    // ͨ����Ž�������
    sort(memos.begin(), memos.end(), [](const Memo& a, const Memo& b) {
        return a.getId() < b.getId();
        });
}

// �������¼
void MemoManager::showMemos()
{
    // ����������ö�����¼
    for (const auto& memo : memos)
    {
        if (memo.getIsTop())
        {
            cout << "[�ö�] ";
            cout << "[" << memo.getId() << "] " << memo.getContent() << endl;
        }
    }

    // ������������ö�����¼
    for (const auto& memo : memos)
    {
        if (!memo.getIsTop())
        {
            cout << "[" << memo.getId() << "] " << memo.getContent() << endl;
        }
    }
}

// ����¼�ö�
void MemoManager::topMemo()
{
    // �ų�����¼Ϊ��ʱ������
    if (memos.empty())
    {
        cout << "����¼Ϊ��" << endl;
        return;
    }

    // ѡ���ö��ı���¼
    int topid;
    cout << "����Ҫ�ö��ı���¼��ţ�" << endl;
    cin.ignore(); // ������з�
    cin >> topid;

    // �������ı���Ƿ���Ч
    while (cin.fail())
    {
        cout << "��Чѡ����������룡" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> topid;
    }

    // ���Ҷ�Ӧ����¼���ı����ö�״̬
    auto it = find_if(memos.begin(), memos.end(),
        [topid](const Memo& memo) { return memo.getId() == topid; });

    // ����Ƿ���ڶ�Ӧ�ı���¼
    if (it == memos.end())
    {
        cout << "���Ϊ" << topid << " �ı���¼������" << endl;
        return;
    }

    Memo memo = *it;
    memo.setIsTop(true);

    // ���ö��ı���¼�ƶ����б�Ŀ�ͷ
    memos.erase(it);
    memos.insert(memos.begin(), std::move(memo));

    // ���±���¼�ı�ź��ö�״̬
    for (std::vector<Memo>::iterator it = memos.begin(); it != memos.end(); ++it)
    {
        it->setId(std::distance(memos.begin(), it) + 1);
        it->setIsTop(it == memos.begin()); // ��һ������¼Ϊ�ö�����¼������Ϊ���ö�����¼
    }
}


// �޸ı���¼����
void MemoManager::modifyMemo()
{
    // �ų�����¼Ϊ��ʱ������
    if (memos.empty())
    {
        cout << "����¼Ϊ��" << endl;
        return;
    }

    // ���뱸��¼���
    int modifyId;
    cout << "����Ҫ�޸ĵı���¼��ţ�" << endl;
    cin.ignore(); // ������з�
    cin >> modifyId;

    // �������ı���Ƿ���Ч
    while (cin.fail())
    {
        cout << "��Чѡ����������룡" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> modifyId;
    }

    // ���Ҷ�Ӧ���
    auto it = find_if(memos.begin(), memos.end(),
        [modifyId](const Memo& memo) { return memo.getId() == modifyId; });

    if (it == memos.end())
    {
        cout << "���Ϊ" << modifyId << "�ı���¼������" << endl;
        return;
    }

    string newContent;
    cout << "�����µı���¼���ݣ�" << endl;
    cin.ignore(); // ������з�
    getline(cin, newContent);

    it->setContent(newContent);
    cout << "����¼�����޸ĳɹ�" << endl;
}


// ɾ������¼
void MemoManager::deleteMemo()
{
    // �ų�����¼Ϊ��ʱ������
    if (memos.empty())
    {
        cout << "����¼Ϊ��" << endl;
        return;
    }

    // �����Ӧ�ı��
    int deleteId;
    cout << "����Ҫɾ���ı���¼��ţ�" << endl;
    cin.ignore(); // ������з�
    cin >> deleteId;

    // �������ı���Ƿ���Ч
    while (cin.fail())
    {
        cout << "��Чѡ����������룡" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> deleteId;
    }

    // ���Ҷ�Ӧ�ı��
    auto it = find_if(memos.begin(), memos.end(),
        [deleteId](const Memo& memo) { return memo.getId() == deleteId; });

    if (it == memos.end())
    {
        cout << "���Ϊ" << deleteId << "�ı���¼������" << endl;
        return;
    }

    memos.erase(it);
    cout << "����¼ɾ���ɹ�" << endl;

}
