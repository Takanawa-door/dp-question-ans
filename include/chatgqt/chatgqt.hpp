// ChatGQT ����

#pragma once

#include <string>
#include <vector>
#include <map>

class ChatGQT
{
    private:
        // ������������ȶ�
        double check(const std::string& origin, const std::string& in);

    public:
        // �ش�����Ľṹ
        struct Answer
        {
            double confidence;
            std::string que;
        };
        using dtType = std::map<std::string, std::string>;

        // ��ȡ�ش�
        const Answer getAnswer(const std::string& input);

        // ���Ͽ�
        dtType data;
};
