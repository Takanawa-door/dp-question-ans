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

    // ѡ�������
    if (argc <= 2)
    {
        std::cout << "Ӧ����˵��ã�\n"
            << "chatgqt.exe [�ش�����׼ȷ��] [���Ͽ��ļ�·��]\n"
            << "���У�[�ش�����׼ȷ��] ��ֵ�� 0 �� 10000 �䡣";
        return 0;
    }

    auto pBot = generateBotFromFile(std::string(argv[2]));

    if (pBot == nullptr)
    {
        std::cout << "���� Bot ʧ�ܣ�\n";
        return 0;
    }

    int minConfidence;

    try
    {
        minConfidence = std::stoi(argv[1]);
    }
    catch (...)
    {
        std::cout << "�޷���ȡ�ش�����׼ȷ�ȣ�\n";
        return 0;
    }

    // ��������
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
                std::cout << "�Ҳ���ƥ��𰸡�\n";
                continue;
            }

            std::cout
                << "\033[30;1m"
                << "�𰸿��Ŷȣ�" << ans.confidence / 100.0 << "%��"
                << "ƥ���������⣺" << ans.que << "\n\n"
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
