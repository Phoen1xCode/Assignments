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
        // ���캯��
         Memo(std::string _content, bool _isTop = false);

        int getNumber() const; // ��ȡ����¼���

        std::string getContent() const; // ��ȡ����¼����

        bool getIsTop() const; // �жϱ���¼�Ƿ��ö�


        void setNumber(const int& newNumber);

        void setContent(const std::string &newContent);

        void setIsTop(bool _isTop); // ���ñ���¼�ö�״̬

    private:
        static int count; // ����¼��ż�����

        int number; // ����¼���
        std::string content; // ����¼����
        bool isTop; // �Ƿ��ö�
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
        std::vector<Memo> memos; // ����vector�洢����
    };
}

#endif
