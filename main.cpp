#include <iostream>
#include <string>
#include "LCS/LCS.h"
#include <cstring>

int main()
{
    std::string s1 = "AXY";
    std::string s2 = "ADXCPY";

    int n = s1.length();
    int m = s2.length();
#if 0
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

    std::cout << "Shortes Super Sequence: "
              << DynamicProgramming::LCS::shortestCommSuperSequence(s1, s2, n, m)
              << std::endl;


    auto [insertion, deletion] = DynamicProgramming::LCS::stringAtoB(s1, s2, s1.length(), s2.length());
    std::cout << "Minimum Number of Insertion = " << insertion<<"\n"
              << " and Deletion = " << deletion
              << " to convert String a to String b." 
              << std::endl;

    std::cout<<"longest palindromic subsequence's length:"
             <<DynamicProgramming::LCS::longestPalindromeSubseq(s1)
             <<std::endl;
        
    
        std::cout<<"Minimum no of Deletion to make plaindrom: "
            <<DynamicProgramming::LCS::minDeletions(s1)
            <<std::endl;
#endif
    std::cout << "SCS: " << DynamicProgramming::LCS::printShortestCommSubsequence(s1, s2, n, m)
              << std::endl;
    std::cout << "LongestReaptingSubsequence: " << DynamicProgramming::LCS::LongestReaptingSubsequence(s1)
              << std::endl;
    std::cout << "Sequence Pattern Matching: "
              << DynamicProgramming::LCS::SequencePatternMatching(s1, s2)
              << std::endl;

    system("pause>0");
    return 0;
}
