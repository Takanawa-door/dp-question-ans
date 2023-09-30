#include <chatgqt/chatgqt.hpp>
#include <chatgqt/bots.hpp>
#include <chatgqt/ansion.hpp>
#include <iostream>
#include <string>

ChatGQT::dtType data{
};

int main(int argc, char* argv[])
{
    enableANSI();
	std::cout << "ChatGQT Version 0.2\n  Made By LS\n";

    // 选择机器人
    if (argc <= 2)
    {
        std::cout << "应该如此调用：\n"
            << "chatgqt.exe [回答至少准确度] [语料库文件路径]\n"
            << "其中，[回答至少准确度] 的值在 0 至 10000 间。";
        return 0;
    }

    auto pBot = generateBotFromFile(std::string(argv[2]));

    if (pBot == nullptr)
    {
        std::cout << "生成 Bot 失败！\n";
        return 0;
    }

    int minConfidence;

    try
    {
        minConfidence = std::stoi(argv[1]);
    }
    catch (...)
    {
        std::cout << "无法获取回答至少准确度！\n";
        return 0;
    }

    // 问题输入
    std::string in;
    while (true)
    {
        std::cout << "\n\033[37;1m$ ";
        std::getline(std::cin, in);
        std::cout << "\033[0m";
        if (std::cin.bad() || in.empty()) break;
        try
        {
            auto ans = (*pBot).getAnswer(in);
            if (ans.que == "" || ans.confidence <= minConfidence)
            {
                std::cout << "找不到匹配答案。\n";
                continue;
            }

            std::cout
                << "\033[30;1m"
                << "答案可信度：" << ans.confidence / 100.0 << "%；"
                << "匹配的最佳问题：" << ans.que << "\n\n"
                << "\033[0m"
                << (*pBot).data[ans.que] << '\n';
        }
        catch (std::exception& exce)
        {
            std::cout << exce.what() << '\n'; break;
        }
        catch (...)
        {
            std::cout << "break.\n"; break;
        }
    }

	return 0;
}
