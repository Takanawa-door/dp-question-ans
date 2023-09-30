// 对话核心

#pragma once

#include <string>
#include <vector>
#include <map>

// 实现一个简易的基于 DP 的 Bot
class ChatGQT
{
    private:
        // 将问题与输入比对
        double check(const std::string& origin, const std::string& in);

    public:
        // 回答问题的结构
        struct Answer
        {
            double confidence;
            std::string que;
        };
        using dtType = std::map<std::string, std::string>;

        // 获取回答
        const Answer getAnswer(const std::string& input);

        // 语料库
        dtType data;
};
