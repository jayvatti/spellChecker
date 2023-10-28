//
// Created by Jay Vatti on 10/27/23.
//
#pragma once

//LCS of two strings
int longestCommonSubsequenceLength(const std::string& s1, const std::string& s2) {
    int m = s1.length();
    int n = s2.length();

    //2d vec to store the subproblems
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
        }
    }

    return dp[m][n];
}
