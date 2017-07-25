/*
 * http://www.lintcode.com/en/problem/compare-strings/
 */


class Solution {
public:
    /**
     * @param A: A string includes Upper Case letters
     * @param B: A string includes Upper Case letter
     * @return:  if string A contains all of the characters in B return true 
     *           else return false
     */
    bool compareStrings(string A, string B) {
        int hash[32] = {0};
        if (A.size() == 0 && B.size() > 0) {
            return false;
        }
        for (int i = 0; i < A.size(); i++) {
            hash[A[i] - 'A']++;
        }

        for (int i = 0; i < B.size(); i++) {
            if (--hash[B[i] - 'A'] < 0) {
                return false;
            }
        }
        return true;
    }
};
