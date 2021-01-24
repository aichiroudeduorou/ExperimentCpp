#pragma once

namespace FZJ {
    class Organization {
    public:
        CString name;
        int locationID;
        Organization(const CString &str) {
            name = str;
        }
        int longestSubstring(CString y) {
            CString x = name;
            std::vector<std::vector<int> > f(x.GetLength() + 1, std::vector<int>(y.GetLength() + 1, 0));
            int max = -1;
            for (int i = 1; i <= x.GetLength(); i++) {
                for (int j = 1; j <= y.GetLength(); j++) {
                    if (x[i - 1] != y[j - 1]) f[i][j] = 0;
                    else if (x[i - 1] == y[j - 1]) f[i][j] = f[i - 1][j - 1] + 1;
                    if (max < f[i][j]) {
                        max = f[i][j];
                    }
                }
            }
            return max;
        }
    };
}
