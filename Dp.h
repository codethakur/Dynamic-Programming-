#include <string>
#include <limits>
#include <algorithm>
#include <string_view>

int static t[1001][1001];

namespace DynamicProgramming
{

    namespace unbounded
    {
        int coinChangeMin(const int coin[], int n, int sum)
        {
            int t[n + 1][sum + 1];

            for (int i = 0; i <= n; ++i)
            {
                for (int j = 0; j <= sum; ++j)
                {
                    if (i == 0)
                        t[i][j] = INT_MAX - 1;
                    if (j == 0)
                        t[i][j] = 0;
                }
            }

            for (int j = 1; j <= sum; ++j)
            {
                t[1][j] = (j % coin[0] == 0) ? (j / coin[0]) : (INT_MAX - 1);
            }

            for (int i = 2; i <= n; ++i)
            {
                for (int j = 1; j <= sum; ++j)
                {
                    if (coin[i - 1] <= j)
                        t[i][j] = std::min(t[i][j - coin[i - 1]] + 1, t[i - 1][j]);
                    else
                        t[i][j] = t[i - 1][j];
                }
            }

            return (t[n][sum] == INT_MAX - 1) ? -1 : t[n][sum];
        }
    }

    namespace LCS
    {
        int Recursive(std::string_view s1, std::string_view s2, int n, int m)
        {
            if (n == 0 || m == 0)
                return 0;

            if (s1[n - 1] == s2[m - 1])
                return 1 + Recursive(s1, s2, n - 1, m - 1);
            else
                return std::max(Recursive(s1, s2, n, m - 1),
                                Recursive(s1, s2, n - 1, m));
        }

        int memoization(std::string_view s1, std::string_view s2, int n, int m)
        {
            if (n == 0 || m == 0)
                return 0;

            if (t[n][m] != -1)
                return t[n][m];

            if (s1[n - 1] == s2[m - 1])
                return t[n][m] = 1 + memoization(s1, s2, n - 1, m - 1);
            else
                return t[n][m] = std::max(memoization(s1, s2, n, m - 1),
                                          memoization(s1, s2, n - 1, m));
        }

        int Topdown(std::string_view s1, std::string_view s2, int n, int m)
        {
            for (int i = 0; i <= n; i++)
            {
                for (int j = 0; j <= m; j++)
                {
                    if (i == 0 || j == 0)
                    {
                        t[i][j] = 0;
                    }
                }
            }

            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    if (s1[i - 1] == s2[j - 1])
                        t[i][j] = 1 + t[i - 1][j - 1];
                    else
                        t[i][j] = std::max(t[i - 1][j], t[i][j - 1]);
                }
            }

            return t[n][m];
        }
        int LongestCommSubstringRecursive(std::string_view s1, std::string_view s2, int n, int m, int count)
        {
            if (n == 0 || m == 0)
                return count;

            if (s1[n - 1] == s2[m - 1])
            {
                count = LongestCommSubstringRecursive(s1, s2, n - 1, m - 1, count + 1);
            }

            int c1 = LongestCommSubstringRecursive(s1, s2, n - 1, m, 0);
            int c2 = LongestCommSubstringRecursive(s1, s2, n, m - 1, 0);

            return std::max({count, c1, c2});
        }


        int LongestCommSubstringMemo(std::string_view s1, std::string_view s2, int n, int m, int &maxLen)
        {
            if (n == 0 || m == 0)
                return 0;

            if (t[n][m] != -1)
                return t[n][m];

            LongestCommSubstringMemo(s1, s2, n - 1, m, maxLen);
            LongestCommSubstringMemo(s1, s2, n, m - 1, maxLen);

            if (s1[n - 1] == s2[m - 1])
            {
                t[n][m] = 1 + LongestCommSubstringMemo(s1, s2, n - 1, m - 1, maxLen);
                maxLen = std::max(maxLen, t[n][m]);
                return t[n][m];
            }
            else
            {
                t[n][m] = 0;
                return 0;
            }
        }


        int LongestCommSubstring(std::string s1, std::string s2, int n, int m)
        {
            int result = 0;
            for (int i = 0; i <= n; i++)
            {
                for (int j = 0; j <= m; j++)
                {
                    if (i == 0 || j == 0)
                    {
                        t[i][j] = 0;
                    }
                }
            }

            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    if (s1[i - 1] == s2[j - 1])
                    {
                        t[i][j] = 1 + t[i - 1][j - 1];
                        result = std::max(result, t[i][j]);
                    }
                    else
                        t[i][j] = 0;
                }
            }

            return result;
        }

        std::string printLongestCommSubsequence(std::string s1, std::string s2, int n, int m)
        {
            for (int i = 0; i <= n; i++)
            {
                for (int j = 0; j <= m; j++)
                {
                    if (i == 0 || j == 0)
                    {
                        t[i][j] = 0;
                    }
                }
            }
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    if (s1[i - 1] == s2[j - 1])
                        t[i][j] = 1 + t[i - 1][j - 1];
                    else
                        t[i][j] = std::max(t[i - 1][j], t[i][j - 1]);
                }
            }

            int i = n, j = m;
            std::string result = "";
            while (i > 0 && j > 0)
            {
                if (s1[i - 1] == s2[j - 1])
                {
                    result.push_back(s1[i - 1]);
                    i--;
                    j--;
                }
                else
                {
                    if (t[i][j - 1] > t[i - 1][j])
                    {
                        j--;
                    }
                    else
                    {
                        i--;
                    }
                }
            }
            std::reverse(result.begin(), result.end());
            return result;
        }
        int shortestCommSuperSequence(std::string s1, std::string s2, int n, int m)
        {
            return m+n - Topdown(s1,s2, n,m);
        }

        //Minimum Number of Insertion and Deletion to convert String a to String b
        #include <tuple>
        std::tuple<int, int> stringAtoB(const std::string& s1, const std::string& s2, int n, int m)
        {
            int lcs = Topdown(s1, s2, n, m);
            int Deletion = n - lcs;
            int Insertion = m - lcs;
        
            return {Insertion, Deletion};
        }
    }

}
