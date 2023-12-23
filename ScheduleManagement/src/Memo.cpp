#include "../include/Memo.h"
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>


namespace DailylifeAssistant {
    using json = nlohmann::json;
    // ����¼�����
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
        std::cout << "�����뱸��¼���ݣ�������н�������" << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ���������

        while (std::getline(std::cin, line)) {
            if (line.empty()) {
                break; // ��������
            }
            input += line + "\n"; // ƴ�Ӷ�������
        }

        return input;
    }

    // ���뱸��¼
    void MemoManager::addMemo() {
        try {
            // ��ȡ����¼����
            std::string content = getMemoContent();

            // ѯ���û��Ƿ��ö�����¼
            char isTopChar;
            bool isTop = false;
            std::cout << "�Ƿ��ö��˱���¼��(y/n): ";
            std::cin >> isTopChar;
            if (isTopChar == 'y' || isTopChar == 'Y') {
                isTop = true;
            }

            // ���ʣ������
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // ��ӱ���¼���б�
            memos.push_back(Memo(content, isTop));

        } catch (const std::exception& e) {
            std::cerr << "��������: " << e.what() << std::endl;
        }
    }

    // ����¼����
    void MemoManager::arrangeMemos() {
        // ���±���¼�ı��
        for (size_t i = 0; i < memos.size(); ++i) {
            memos[i].setNumber(i + 1);
        }

        // ͨ����Ž�������
        std::sort(memos.begin(), memos.end(), [](const Memo &a, const Memo &b) {
            return a.getNumber() < b.getNumber();
        });
    }

    // �������¼
    void MemoManager::showMemos() {
        // ����������ö�����¼
        for (const auto &memo: memos) {
            if (memo.getIsTop()) {
                std::cout << "[�ö�] ";
                std::cout << "[" << memo.getNumber() << "] " << memo.getContent() << std::endl;
            }
        }

        // ������������ö�����¼
        for (const auto &memo: memos) {
            if (!memo.getIsTop()) {
                std::cout << "[" << memo.getNumber() << "] " << memo.getContent() << std::endl;
            }
        }
    }

    // ����¼�ö�
    void MemoManager::topMemo() {
        // �ų�����¼Ϊ��ʱ������
        if (memos.empty()) {
            std::cout << "����¼Ϊ��" << std::endl;
            return;
        }

        // ѡ���ö��ı���¼
        int topNumber;
        std::cout << "����Ҫ�ö��ı���¼��ţ�" << std::endl;
        std::cin.ignore(); // ������з�
        std::cin >> topNumber;

        // �������ı���Ƿ���Ч
        while (std::cin.fail()) {
            std::cout << "��Чѡ����������룡" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> topNumber;
        }

        // ���Ҷ�Ӧ����¼���ı����ö�״̬
        auto it = std::find_if(memos.begin(), memos.end(),
                               [topNumber](const Memo &memo) { return memo.getNumber() == topNumber; });

        // ����Ƿ���ڶ�Ӧ�ı���¼
        if (it == memos.end()) {
            std::cout << "���Ϊ" << topNumber << " �ı���¼������" << std::endl;
            return;
        }

        Memo memo = *it;
        memo.setIsTop(true);

        // ���ö��ı���¼�ƶ����б�Ŀ�ͷ
        memos.erase(it);
        memos.insert(memos.begin(), std::move(memo));

        // ���±���¼�ı�ź��ö�״̬
        for (std::vector<Memo>::iterator it = memos.begin(); it != memos.end(); ++it) {
            it->setNumber(std::distance(memos.begin(), it) + 1);
            it->setIsTop(it == memos.begin()); // ��һ������¼Ϊ�ö�����¼������Ϊ���ö�����¼
        }
    }

    // �޸ı���¼����
    void MemoManager::modifyMemo() {
        // �ų�����¼Ϊ��ʱ������
        if (memos.empty()) {
            std::cout << "����¼Ϊ��" << std::endl;
            return;
        }

        // ���뱸��¼���
        int modifyId;
        std::cout << "����Ҫ�޸ĵı���¼��ţ�" << std::endl;
        std::cin.ignore(); // ������з�
        std::cin >> modifyId;

        // �������ı���Ƿ���Ч
        while (std::cin.fail()) {
            std::cout << "��Чѡ����������룡" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> modifyId;
        }

        // ���Ҷ�Ӧ���
        auto it = std::find_if(memos.begin(), memos.end(),
                               [modifyId](const Memo &memo) { return memo.getNumber() == modifyId; });

        if (it == memos.end()) {
            std::cout << "���Ϊ" << modifyId << "�ı���¼������" << std::endl;
            return;
        }

        std::string newContent;
        std::cout << "�����µı���¼���ݣ�" << std::endl;
        std::cin.ignore(); // ������з�
        std::getline(std::cin, newContent);

        it->setContent(newContent);
        std::cout << "����¼�����޸ĳɹ�" << std::endl;
    }

    // ɾ������¼
    void MemoManager::deleteMemo() {
        // �ų�����¼Ϊ��ʱ������
        if (memos.empty()) {
            std::cout << "����¼Ϊ��" << std::endl;
            return;
        }

        // �����Ӧ�ı��
        int deleteId;
        std::cout << "����Ҫɾ���ı���¼��ţ�" << std::endl;
        std::cin.ignore(); // ������з�
        std::cin >> deleteId;

        // �������ı���Ƿ���Ч
        while (std::cin.fail()) {
            std::cout << "��Чѡ����������룡" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> deleteId;
        }

        // ���Ҷ�Ӧ�ı��
        auto it = std::find_if(memos.begin(), memos.end(),
                               [deleteId](const Memo &memo) { return memo.getNumber() == deleteId; });

        // ������ʱ����
        if (it == memos.end()) {
            std::cout << "���Ϊ" << deleteId << "�ı���¼������" << std::endl;
            return;
        }

        // ����ɾ������
        memos.erase(it);
        std::cout << "����¼ɾ���ɹ�" << std::endl;
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
            std::cerr << "�޷����ļ�: " << filename << std::endl;
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
            std::cerr << "�޷����ļ�: " << filename << std::endl;
        }
    }
}


