#include <chatgqt/bots.hpp>

// 从文件构建 Bot
std::unique_ptr<ChatGQT> generateBotFromFile(const std::string& path)
{
    std::ifstream file(path, std::ios::in);

    if (!file.is_open())
    {
        return nullptr;
    }

    auto pBot = std::unique_ptr<ChatGQT>(new ChatGQT);
    
    std::string ques, ans, line;
    bool isAnswer = false; // 读取的行是否为答案行
    bool isFirstLine = true; // 特殊标记
    int x = 0;
    while (std::getline(file, line))
    {
        if (line.empty()) continue;
        // 切换模式
        if (line == "\"Question\"" || line == "\"End\"") // 新的问题
        {
            if (isFirstLine)
            {
                isFirstLine = false;
                continue;
            }
            // 去除回答末尾空行
            while (!ans.empty() && ans.back() == '\n')
            {
                ans.pop_back();
            }

            pBot->data[ques] = ans;
            isAnswer = false;
            ques = "";
            ++x;
            continue;
        }
        else if (line == "\"Answer\"") // 新的回答
        {
            isAnswer = true;
            ans = "";
            continue;
        }

        // 追加文本
        if (isAnswer)
        {
            ans += line + "\n\n";
        }
        else
        {
            ques += line;
        }
    }

    file.close();

    return pBot;
}
