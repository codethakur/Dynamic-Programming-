#include <iostream>
#include <string>
#include "LCS/LCS.h"
#include <cstring>

int main()
{
    std::string s1 = "AGGTAB";
    std::string s2 = "GXTXAYB";
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

    std::cout<<"Shortes Super Sequence: "
            << DynamicProgramming::LCS::shortestCommSuperSequence(s1,s2,n, m)
            <<std::endl;

    auto [insertion, deletion] = DynamicProgramming::LCS::stringAtoB(s1, s2, s1.length(), s2.length());
    std::cout << "Minimum Number of Insertion = " << insertion<<"\n"
              << " and Deletion = " << deletion
              << " to convert String a to String b." << std::endl;

    system("pause>0");
    return 0;
}
