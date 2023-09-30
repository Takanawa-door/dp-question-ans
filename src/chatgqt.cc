#include <chatgqt/chatgqt.hpp>

// 获取答案
const ChatGQT::Answer ChatGQT::getAnswer(const std::string& str)
{
    Answer answer;
    answer.confidence = 0;
    answer.que = "";

    // 在语料库中寻找最相似的
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

// 判断语料库问题与输入
double ChatGQT::check(const std::string& origin, const std::string& in)
{
    double conf = 0;

    // 获取字符串长度
    const int m = origin.length(), n = in.length();

    // int dp[m + 1][n + 1];
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    for (int i = 0; i <= m; ++i) dp[i][0] = i;
    for (int i = 0; i <= n; ++i) dp[0][i] = i;

    // 获取最少改动次数
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

    // 计算相似度
    conf = (1.0 - static_cast<double>(dp[m][n]) / std::max(m, n)) * 10000.0;

    return conf;
}
