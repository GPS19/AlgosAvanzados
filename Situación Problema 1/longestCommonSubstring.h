#include <vector>
#include <iostream>
using namespace std;

#pragma once
class LCS
{

public:
    vector<int> longestCommonSubstring(string &text1, string &text2)
    {
        vector<int> ans;
        int length = 0;   // length of lcs
        int position = 0; // position of lcs

        int m = text1.length() + 1;
        int n = text2.length() + 1;

        // initialization
        vector<vector<int>> dp(m, vector<int>(n, 0));

        // dynamic programming
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (text1[i - 1] != text2[j - 1])
                {

                    dp[i][j] = 0;
                }
                else
                {

                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    if (dp[i][j] > length)
                    {
                        length = dp[i][j];
                        position = i;
                    }
                }
            }
        }

        position = abs(position - length); // Index where it starts
        ans.push_back(length);
        ans.push_back(position);
        return ans;
    }
};