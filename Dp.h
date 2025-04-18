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
            return m + n - Topdown(s1, s2, n, m);
        }

// Minimum Number of Insertion and Deletion to convert String a to String b
#include <tuple>
        std::tuple<int, int> stringAtoB(const std::string &s1, const std::string &s2, int n, int m)
        {
            int lcs = Topdown(s1, s2, n, m);
            int Deletion = n - lcs;
            int Insertion = m - lcs;

            return {Insertion, Deletion};
        }

        int longestPalindromeSubseq(std::string_view s)
        {
            int n = s.length();
            std::string rev(s.rbegin(), s.rend());
            return Topdown(s, std::string_view(rev), n, n);
        }

        // Minimum no of Deletion to Make a String Palindrome

        int minDeletions(std::string_view s)
        {
            int n = s.length();
            int LPSlenth = longestPalindromeSubseq(s);

            return (n - LPSlenth);
        }

        std::string printShortestCommSubsequence(std::string s1, std::string s2, int n, int m)
        {
            // Build LCS table
            for (int i = 0; i <= n; i++)
            {
                for (int j = 0; j <= m; j++)
                {
                    if (i == 0 || j == 0)
                        t[i][j] = 0;
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

            // Backtracking
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
                else if (t[i][j - 1] > t[i - 1][j])
                {
                    result.push_back(s2[j - 1]);
                    j--;
                }
                else
                {
                    result.push_back(s1[i - 1]);
                    i--;
                }
            }

            // Add remaining characters
            while (i > 0)
            {
                result.push_back(s1[i - 1]);
                i--;
            }
            while (j > 0)
            {
                result.push_back(s2[j - 1]);
                j--;
            }

            std::reverse(result.begin(), result.end());
            return result;
        }

        int LongestReaptingSubsequence(const std::string str)
        {
            std::string c_str = str;
            int n = str.length();
            int m = c_str.length();
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
                    if (str[i - 1] == c_str[j - 1] && i != j)
                        t[i][j] = 1 + t[i - 1][j - 1];
                    else
                        t[i][j] = std::max(t[i - 1][j], t[i][j - 1]);
                }
            }

            return t[n][m];
        }
        bool SequencePatternMatching(const std::string_view s1, const std::string_view s2)
        {
            int n = s1.length();
            int m = s2.length();

            int LCS_length = Topdown(s1, s2, n, m);
            if (LCS_length == s1.length())
                return true;
            return false;
        }

    }
    namespace MatrixChainMultiplication
    {
        int Recursive(int arr[], int i, int j)
        {
            if (i >= j)
            {
                return 0;
            }
            int mn = INT_MAX;
            for (int k = i; k <= j - 1; k++)
            {
                long long tempAns = Recursive(arr, i, k) +
                                    Recursive(arr, k + 1, j) +
                                    arr[i - 1] * arr[k] * arr[j];

                if (tempAns < mn)
                {
                    mn = tempAns;
                }
            }
            return mn;
        }
        int Memoized(int arr[], int i, int j)
        {
            if (t[i][j] != -1)
            {
                return t[i][j];
            }
            int mn = INT_MAX;
            for (int k = i; k <= j - 1; k++)
            {
                long long tempAns = Memoized(arr, i, k) +
                                    Memoized(arr, k + 1, j) +
                                    arr[i - 1] * arr[k] * arr[j];

                if (tempAns < mn)
                {
                    mn = tempAns; //  mn = std::min(mn, tempAns);
                }
            }
            return t[i][j] = mn;
        }
        
        int evaluateExpr(const std::string &str, int i, int j, bool isTrue)
        {
            if (i > j)
                return 0;

            if (i == j)
            {
                if (isTrue)
                    return str[i] == 'T' ? 1 : 0;
                else
                    return str[i] == 'F' ? 1 : 0;
            }

            int ans = 0;

            for (int k = i + 1; k <= j - 1; k += 2)
            {
                char op = str[k];

                int leftT = evaluateExpr(str, i, k - 1, true);
                int leftF = evaluateExpr(str, i, k - 1, false);
                int rightT = evaluateExpr(str, k + 1, j, true);
                int rightF = evaluateExpr(str, k + 1, j, false);

                if (op == '&')
                {
                    if (isTrue)
                        ans += leftT * rightT;
                    else
                        ans += leftF * rightT + leftT * rightF + leftF * rightF;
                }
                else if (op == '|')
                {
                    if (isTrue)
                        ans += leftT * rightT + leftT * rightF + leftF * rightT;
                    else
                        ans += leftF * rightF;
                }
                else if (op == '^')
                {
                    if (isTrue)
                        ans += leftT * rightF + leftF * rightT;
                    else
                        ans += leftT * rightT + leftF * rightF;
                }
            }

            return ans;
        }

    }
    namespace PalindromePartitioning
    {
        bool isPlindrom(const std::string &str, int i, int j)
        {
            while (i < j)
            {
                if (str[i] != str[j])
                    return false;
                ++i;
                --j;
            }
            return true;
        }

        int recursive(const std::string &str, int i, int j)
        {
            if (i >= j)
                return 0;

            if (isPlindrom(str, i, j))
                return 0;

            int min = INT_MAX;
            for (int k = i; k < j; k++)
            {
                int tempAns = recursive(str, i, k) + 1 +
                              recursive(str, k + 1, j);
                if (tempAns < min)
                    min = tempAns;
            }
            return min;
        }
        int memoized(const std::string &str, int i, int j)
        {
            if (i >= j)
                return 0;

            if (isPlindrom(str, i, j))
                return 0;

            int min = INT_MAX;
            for (int k = i; k < j; k++)
            {
                // int tempAns = recursive(str, i, k) + 1 + recursive(str, k + 1, j);
                long left = 0, right = 0;

                if (t[i][k] != -1)
                {
                    left = t[i][k];
                }
                else
                {
                    left = memoized(str, i, k);
                    t[i][k] = left;
                }

                if (t[k + 1][j] != -1)
                {
                    right = t[k + 1][j];
                }
                else
                {
                    right = memoized(str, k + 1, j);
                    t[k + 1][j] = right;
                }

                long long tempAns = left + 1 + right;

                if (tempAns < min)
                    min = tempAns;
            }
            return min;
        }

    }

}
