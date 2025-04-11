#include <iostream>
#include <string>
#include <cstring>
#include "LCS/LCS.h"

int main()
{
    std::string s1 = "acbcf";
    std::string s2 = "abcdaf";
    int n = s1.length();
    int m = s2.length();

    std::cout << "LCS-Recursive of S1 and S2: "
              << DynamicProgramming::LCS::Recursive(s1, s2, n, m)
              << std::endl;

    std::memset(t, -1, sizeof(t));
    std::cout << "LCS-memoization of S1 and S2: "
              << DynamicProgramming::LCS::memoization(s1, s2, n, m)
              << std::endl;

    std::cout << "LCS-Top Down of S1 and S2: "
              << DynamicProgramming::LCS::Topdown(s1, s2, n, m)
              << std::endl;

    std::cout << "LongestCommSubstring: "
              << DynamicProgramming::LCS::LongestCommSubstring(s1, s2, n, m)
              << std::endl;

    std::cout << "Printing Longest common subsequence: "
              << DynamicProgramming::LCS::printLongestCommSubsequence(s1, s2, n, m)
              << std::endl;
    system("pause>0");
    return 0;
}
