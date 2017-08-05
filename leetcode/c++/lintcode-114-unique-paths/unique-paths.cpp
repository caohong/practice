/*
 * http://www.lintcode.com/en/problem/unique-paths/
 */

class Solution {
public:
    /**
     * @param n, m: positive integer (1 <= n ,m <= 100)
     * @return an integer
     */
    int uniquePaths(int m, int n) {
        if ((m < 1) || (n < 1)) {
            return 0;
        }
        if ((m == 1) || (n == 1)) {
            return 1;
        }
        return uniquePaths(m - 1, n) + uniquePaths(m, n - 1);
    }
};
