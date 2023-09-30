#include <chatgqt/chatgqt.hpp>

// ��ȡ��
const ChatGQT::Answer ChatGQT::getAnswer(const std::string& str)
{
    Answer answer;
    answer.confidence = 0;
    answer.que = "";

    // �����Ͽ���Ѱ�������Ƶ�
    for (const auto& libEle : this->data)
    {
        const std::string& ques = libEle.first,
        ans = libEle.second;

        double t = check(ques, str);

        if (t > answer.confidence)
        {
            answer.confidence = t;
            answer.que        = ques;
        }

    }

    return answer;
}

// �ж����Ͽ�����������
double ChatGQT::check(const std::string& origin, const std::string& in)
{
    double conf = 0;

    // ��ȡ�ַ�������
    const int m = origin.length(), n = in.length();

    // int dp[m + 1][n + 1];
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    for (int i = 0; i <= m; ++i) dp[i][0] = i;
    for (int i = 0; i <= n; ++i) dp[0][i] = i;

    // ��ȡ���ٸĶ�����
    for (int i = 1; i <= m; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (origin[i - 1] == in[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
                continue;
            }
            dp[i][j] = std::min(dp[i - 1][j - 1], std::min(
                dp[i - 1][j], dp[i][j - 1]
            )) + 1;
        }
    }

    // �������ƶ�
    conf = (1.0 - static_cast<double>(dp[m][n]) / std::max(m, n)) * 10000.0;

    return conf;
}
