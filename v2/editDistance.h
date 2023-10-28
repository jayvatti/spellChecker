//
// Created by Jay Vatti on 10/27/23.
//
#pragma once


// function to find the edit distance between two strings
int editDistance(const std::string& s1, const std::string& s2) {
    int m = s1.length();
    int n = s2.length();

    // 2D vector (table) to store results of subproblems
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else if (s1[i-1] == s2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + std::min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    }

    return dp[m][n];
}
